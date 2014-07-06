#include "FileImpl.h"
#include <algorithm>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <utime.h>
#include <cstring>


namespace System {

namespace priv {

FileImpl::FileImpl()
{
}


FileImpl::FileImpl(const std::string& path): _path(path)
{
	std::string::size_type n = _path.size();
	if (n > 1 && _path[n - 1] == '/')
		_path.resize(n - 1);
}


FileImpl::~FileImpl()
{
}


void FileImpl::swapImpl(FileImpl& file)
{
	std::swap(_path, file._path);
}


void FileImpl::setPathImpl(const std::string& path)
{
	_path = path;
	std::string::size_type n = _path.size();
	if (n > 1 && _path[n - 1] == '/')
		_path.resize(n - 1);
}


bool FileImpl::existsImpl() const
{
	struct stat st;
	return stat(_path.c_str(), &st) == 0;
}


bool FileImpl::canReadImpl() const
{
	struct stat st;
	if (stat(_path.c_str(), &st) == 0)
	{
		if (geteuid() == 0)
			return true;
		else if (st.st_uid == geteuid())
			return (st.st_mode & S_IRUSR) != 0;
		else if (st.st_gid == getegid())
			return (st.st_mode & S_IRGRP) != 0;
		else
			return (st.st_mode & S_IROTH) != 0;
	}
	else handleLastErrorImpl(_path);
	return false;
}


bool FileImpl::canWriteImpl() const
{
	struct stat st;
	if (stat(_path.c_str(), &st) == 0)
	{
		if (geteuid() == 0)
			return true;
		else if (st.st_uid == geteuid())
			return (st.st_mode & S_IWUSR) != 0;
		else if (st.st_gid == getegid())
			return (st.st_mode & S_IWGRP) != 0;
		else
			return (st.st_mode & S_IWOTH) != 0;
	}
	else handleLastErrorImpl(_path);
	return false;
}


bool FileImpl::canExecuteImpl() const
{
	struct stat st;
	if (stat(_path.c_str(), &st) == 0)
	{
		if (st.st_uid == geteuid() || geteuid() == 0)
			return (st.st_mode & S_IXUSR) != 0;
		else if (st.st_gid == getegid())
			return (st.st_mode & S_IXGRP) != 0;
		else
			return (st.st_mode & S_IXOTH) != 0;
	}
	else handleLastErrorImpl(_path);
	return false;
}


bool FileImpl::isFileImpl() const
{
	struct stat st;
	if (stat(_path.c_str(), &st) == 0)
		return S_ISREG(st.st_mode);
	else
		handleLastErrorImpl(_path);
	return false;
}


bool FileImpl::isDirectoryImpl() const
{
	struct stat st;
	if (stat(_path.c_str(), &st) == 0)
		return S_ISDIR(st.st_mode);
	else
		handleLastErrorImpl(_path);
	return false;
}


bool FileImpl::isLinkImpl() const
{
	struct stat st;
	if (lstat(_path.c_str(), &st) == 0)
		return S_ISLNK(st.st_mode);
	else
		handleLastErrorImpl(_path);
	return false;
}


bool FileImpl::isDeviceImpl() const
{
	struct stat st;
	if (stat(_path.c_str(), &st) == 0)
		return S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode);
	else
		handleLastErrorImpl(_path);
	return false;
}


bool FileImpl::isHiddenImpl() const
{
	Path p(_path);
	p.makeFile();

	return p.getFileName()[0] == '.';
}


UInt64 FileImpl::createdImpl() const
{
#if defined(__APPLE__) && defined(st_birthtime) // st_birthtime is available only on 10.5
	struct stat64 st;
	if (stat64(_path.c_str(), &st) == 0)
		return st.st_birthtime;
#elif defined(__FreeBSD__)
	struct stat st;
	if (stat(_path.c_str(), &st) == 0)
		return st.st_birthtime;
#else
	struct stat st;
	if (stat(_path.c_str(), &st) == 0)
		return st.st_ctime;
#endif 
	else
		handleLastErrorImpl(_path);
	return 0;
}


UInt64 FileImpl::getLastModifiedImpl() const
{
	struct stat st;
	if (stat(_path.c_str(), &st) == 0)
		return st.st_mtime;
	else
		handleLastErrorImpl(_path);
	return 0;
}


void FileImpl::setLastModifiedImpl(UInt64 ts)
{
	struct utimbuf tb;
	tb.actime  = ts;
	tb.modtime = ts;
	if (utime(_path.c_str(), &tb) != 0)
		handleLastErrorImpl(_path);
}


UInt64 FileImpl::getSizeImpl() const
{
	struct stat st;
	if (stat(_path.c_str(), &st) == 0)
		return st.st_size;
	else
		handleLastErrorImpl(_path);
	return 0;
}


void FileImpl::setSizeImpl(UInt64 size)
{
	if (truncate(_path.c_str(), size) != 0)
		handleLastErrorImpl(_path);
}


void FileImpl::setWriteableImpl(bool flag)
{
	struct stat st;
	if (stat(_path.c_str(), &st) != 0) 
		handleLastErrorImpl(_path);
	mode_t mode;
	if (flag)
	{
		mode = st.st_mode | S_IWUSR;
	}
	else
	{
		mode_t wmask = S_IWUSR | S_IWGRP | S_IWOTH;
		mode = st.st_mode & ~wmask;
	}
	if (chmod(_path.c_str(), mode) != 0) 
		handleLastErrorImpl(_path);
}


void FileImpl::setExecutableImpl(bool flag)
{
	struct stat st;
	if (stat(_path.c_str(), &st) != 0) 
		handleLastErrorImpl(_path);
	mode_t mode;
	if (flag)
	{
		mode = st.st_mode | S_IXUSR;
	}
	else
	{
		mode_t wmask = S_IXUSR | S_IXGRP | S_IXOTH;
		mode = st.st_mode & ~wmask;
	}
	if (chmod(_path.c_str(), mode) != 0) 
		handleLastErrorImpl(_path);
}


void FileImpl::copyToImpl(const std::string& path) const
{
	int sd = open(_path.c_str(), O_RDONLY);
	if (sd == -1) handleLastErrorImpl(_path);

	struct stat st;
	if (fstat(sd, &st) != 0) 
	{
		close(sd);
		handleLastErrorImpl(_path);
	}
	const long blockSize = st.st_blksize;

	int dd = open(path.c_str(), O_CREAT | O_TRUNC | O_WRONLY, st.st_mode & S_IRWXU);
	if (dd == -1)
	{
		close(sd);
		handleLastErrorImpl(path);
	}
	try
	{
		char * buffer = new char[blockSize];
		int n;
		while ((n = read(sd, buffer, blockSize)) > 0)
		{
			if (write(dd, buffer, n) != n) 
				handleLastErrorImpl(path);
		}
		if (n < 0)
			handleLastErrorImpl(_path);
		delete[] buffer;
	}
	catch (...)
	{
		close(sd);
		close(dd);
		throw;
	}
	close(sd);
	if (fsync(dd) != 0) 
	{
		close(dd);
		handleLastErrorImpl(path);
	}
	if (close(dd) != 0)
		handleLastErrorImpl(path);
}

void FileImpl::renameToImpl(const std::string& path)
{
	if (rename(_path.c_str(), path.c_str()) != 0)
		handleLastErrorImpl(_path);
}


void FileImpl::removeImpl()
{
	int rc;
	if (!isLinkImpl() && isDirectoryImpl())
		rc = rmdir(_path.c_str());
	else
		rc = unlink(_path.c_str());
	if (rc) handleLastErrorImpl(_path);
}


bool FileImpl::createFileImpl()
{
	int n = open(_path.c_str(), O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (n != -1)
	{
		close(n);
		return true;
	}
	if (n == -1 && errno == EEXIST)
		return false;
	else
		handleLastErrorImpl(_path);
	return false;
}


bool FileImpl::createDirectoryImpl()
{
	if (existsImpl() && isDirectoryImpl())
		return false;
	if (mkdir(_path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) != 0) 
		handleLastErrorImpl(_path);
	return true;
}


void FileImpl::handleLastErrorImpl(const std::string& path)
{
	/*
	switch (errno)
	{
	case EIO:
		throw IOException(path);
	case EPERM:
		throw FileAccessDeniedException("insufficient permissions", path);
	case EACCES:
		throw FileAccessDeniedException(path);
	case ENOENT:
		throw FileNotFoundException(path);
	case ENOTDIR:
		throw OpenFileException("not a directory", path);
	case EISDIR:
		throw OpenFileException("not a file", path);
	case EROFS:
		throw FileReadOnlyException(path);
	case EEXIST:
		throw FileExistsException(path);
	case ENOSPC:
		throw FileException("no space left on device", path);
	case EDQUOT:
		throw FileException("disk quota exceeded", path);
	case ENAMETOOLONG:
		throw PathSyntaxException(path);
	case ENFILE:
	case EMFILE:
		throw FileException("too many open files", path);
	default:
		throw FileException(std::strerror(errno), path);
	}
	*/
	throw std::exception();
}

}

} // namespace System
