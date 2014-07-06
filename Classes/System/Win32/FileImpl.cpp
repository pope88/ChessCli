#include "FileImpl.h"

namespace System {

namespace priv {

class FileHandle
{
public:
	FileHandle(const std::string& path, DWORD access, DWORD share, DWORD disp)
	{
		_h = CreateFileA(path.c_str(), access, share, 0, disp, 0, 0);
		if (_h == INVALID_HANDLE_VALUE)
		{
			throw std::exception();
		}
	}
	
	~FileHandle()
	{
		if (_h != INVALID_HANDLE_VALUE) CloseHandle(_h);
	}
	
	HANDLE get() const
	{
		return _h;
	}
	
private:
	HANDLE _h;
};


FileImpl::FileImpl()
{
}


FileImpl::FileImpl(const std::string& path): _path(path)
{
	std::string::size_type n = _path.size();
	if (n > 1 && (_path[n - 1] == '\\' || _path[n - 1] == '/') && !((n == 3 && _path[1]==':')))
	{
		_path.resize(n - 1);
	}
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
	if (n > 1 && (_path[n - 1] == '\\' || _path[n - 1] == '/') && !((n == 3 && _path[1]==':')))
	{
		_path.resize(n - 1);
	}
}


bool FileImpl::existsImpl() const
{
	DWORD attr = GetFileAttributes(_path.c_str());
	if (attr == 0xFFFFFFFF)
	{
		switch (GetLastError())
		{
		case ERROR_FILE_NOT_FOUND:
		case ERROR_PATH_NOT_FOUND:
		case ERROR_NOT_READY:
		case ERROR_INVALID_DRIVE:
			return false;
		default:
			handleLastErrorImpl(_path);
		}
	}
	return true;
}


bool FileImpl::canReadImpl() const
{
	DWORD attr = GetFileAttributes(_path.c_str());
	if (attr == 0xFFFFFFFF)
	{
		switch (GetLastError())
		{
		case ERROR_ACCESS_DENIED:
			return false;
		default:
			handleLastErrorImpl(_path);
		}
	}
	return true;
}


bool FileImpl::canWriteImpl() const
{
	DWORD attr = GetFileAttributes(_path.c_str());
	if (attr == 0xFFFFFFFF)
		handleLastErrorImpl(_path);
	return (attr & FILE_ATTRIBUTE_READONLY) == 0;
}


bool FileImpl::isFileImpl() const
{
	return !isDirectoryImpl() && !isDeviceImpl();
}


bool FileImpl::isDirectoryImpl() const
{
	DWORD attr = GetFileAttributes(_path.c_str());
	if (attr == 0xFFFFFFFF)
		handleLastErrorImpl(_path);
	return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
}


bool FileImpl::isLinkImpl() const
{
	return false;
}


bool FileImpl::isDeviceImpl() const
{
	FileHandle fh(_path, GENERIC_READ, 0, OPEN_EXISTING);
	DWORD type = GetFileType(fh.get());
	if (type == FILE_TYPE_CHAR)
		return true;
	else if (type == FILE_TYPE_UNKNOWN && GetLastError() != NO_ERROR)
		handleLastErrorImpl(_path);
	return false;
}


bool FileImpl::isHiddenImpl() const
{
	DWORD attr = GetFileAttributes(_path.c_str());
	if (attr == 0xFFFFFFFF)
		handleLastErrorImpl(_path);
	return (attr & FILE_ATTRIBUTE_HIDDEN) != 0;
}


UInt64 FileImpl::createdImpl() const
{
	WIN32_FILE_ATTRIBUTE_DATA fad;
	if (GetFileAttributesEx(_path.c_str(), GetFileExInfoStandard, &fad) == 0) 
		handleLastErrorImpl(_path);

	ULARGE_INTEGER epoch; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
	epoch.LowPart  = 0xD53E8000;
	epoch.HighPart = 0x019DB1DE;

	ULARGE_INTEGER ts;
	ts.LowPart  = fad.ftCreationTime.dwLowDateTime;
	ts.HighPart = fad.ftCreationTime.dwHighDateTime;
	ts.QuadPart -= epoch.QuadPart;
	return ts.QuadPart / 10000000;
}


UInt64 FileImpl::getLastModifiedImpl() const
{
	WIN32_FILE_ATTRIBUTE_DATA fad;
	if (GetFileAttributesEx(_path.c_str(), GetFileExInfoStandard, &fad) == 0) 
		handleLastErrorImpl(_path);

	ULARGE_INTEGER epoch; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
	epoch.LowPart  = 0xD53E8000;
	epoch.HighPart = 0x019DB1DE;

	ULARGE_INTEGER ts;
	ts.LowPart  = fad.ftLastWriteTime.dwLowDateTime;
	ts.HighPart = fad.ftLastWriteTime.dwHighDateTime;
	ts.QuadPart -= epoch.QuadPart;
	return ts.QuadPart / 10000000;
}


void FileImpl::setLastModifiedImpl(UInt64 ts)
{
	ULARGE_INTEGER epoch; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
	epoch.LowPart  = 0xD53E8000;
	epoch.HighPart = 0x019DB1DE;

	ULARGE_INTEGER _ts;
	_ts.QuadPart  = ts * 10000000;
	_ts.QuadPart += epoch.QuadPart;

	FILETIME ft;
	ft.dwLowDateTime  = _ts.LowPart;
	ft.dwHighDateTime = _ts.HighPart;
	FileHandle fh(_path, FILE_ALL_ACCESS, FILE_SHARE_READ | FILE_SHARE_WRITE, OPEN_EXISTING);
	if (SetFileTime(fh.get(), 0, &ft, &ft) == 0)
		handleLastErrorImpl(_path);
}


UInt64 FileImpl::getSizeImpl() const
{
	WIN32_FILE_ATTRIBUTE_DATA fad;
	if (GetFileAttributesEx(_path.c_str(), GetFileExInfoStandard, &fad) == 0) 
		handleLastErrorImpl(_path);
	LARGE_INTEGER li;
	li.LowPart  = fad.nFileSizeLow;
	li.HighPart = fad.nFileSizeHigh;
	return li.QuadPart;
}


void FileImpl::setSizeImpl(UInt64 size)
{
	FileHandle fh(_path, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, OPEN_EXISTING);
	LARGE_INTEGER li;
	li.QuadPart = size;
	if (SetFilePointer(fh.get(), li.LowPart, &li.HighPart, FILE_BEGIN) == (DWORD)-1)
		handleLastErrorImpl(_path);
	if (SetEndOfFile(fh.get()) == 0) 
		handleLastErrorImpl(_path);
}


void FileImpl::setWriteableImpl(bool flag)
{
	DWORD attr = GetFileAttributes(_path.c_str());
	if (attr == (DWORD)-1)
		handleLastErrorImpl(_path);
	if (flag)
		attr &= ~FILE_ATTRIBUTE_READONLY;
	else
		attr |= FILE_ATTRIBUTE_READONLY;
	if (SetFileAttributes(_path.c_str(), attr) == 0)
		handleLastErrorImpl(_path);
}


void FileImpl::setExecutableImpl(bool flag)
{
	// not supported
}


void FileImpl::copyToImpl(const std::string& path) const
{
	if (CopyFileA(_path.c_str(), path.c_str(), FALSE) != 0) 
	{
		FileImpl copy(path);
		copy.setWriteableImpl(true);
	}
	else handleLastErrorImpl(_path);
}


void FileImpl::renameToImpl(const std::string& path)
{
	if (MoveFileA(_path.c_str(), path.c_str()) == 0) 
		handleLastErrorImpl(_path);
}


void FileImpl::removeImpl()
{
	if (isDirectoryImpl())
	{
		if (RemoveDirectoryA(_path.c_str()) == 0) 
			handleLastErrorImpl(_path);
	}
	else
	{
		if (DeleteFileA(_path.c_str()) == 0)
			handleLastErrorImpl(_path);
	}
}


bool FileImpl::createFileImpl()
{
	HANDLE hFile = CreateFileA(_path.c_str(), GENERIC_WRITE, 0, 0, CREATE_NEW, 0, 0);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
		return true;
	}
	else if (GetLastError() == ERROR_FILE_EXISTS)
		return false;
	else
		handleLastErrorImpl(_path);
	return false;
}


bool FileImpl::createDirectoryImpl()
{
	if (existsImpl() && isDirectoryImpl())
		return false;
	if (CreateDirectoryA(_path.c_str(), 0) == 0)
		handleLastErrorImpl(_path);
	return true;
}


void FileImpl::handleLastErrorImpl(const std::string& path)
{
	/*
	switch (GetLastError())
	{
	case ERROR_FILE_NOT_FOUND:
		throw FileNotFoundException(path);
	case ERROR_PATH_NOT_FOUND:
	case ERROR_BAD_NETPATH:
	case ERROR_CANT_RESOLVE_FILENAME:
	case ERROR_INVALID_DRIVE:
		throw PathNotFoundException(path);
	case ERROR_ACCESS_DENIED:
		throw FileAccessDeniedException(path);
	case ERROR_ALREADY_EXISTS:
	case ERROR_FILE_EXISTS:
		throw FileExistsException(path);
	case ERROR_INVALID_NAME:
	case ERROR_DIRECTORY:
	case ERROR_FILENAME_EXCED_RANGE:
	case ERROR_BAD_PATHNAME:
		throw PathSyntaxException(path);
	case ERROR_FILE_READ_ONLY:
		throw FileReadOnlyException(path);
	case ERROR_CANNOT_MAKE:
		throw CreateFileException(path);
	case ERROR_DIR_NOT_EMPTY:
		throw FileException("directory not empty", path);
	case ERROR_WRITE_FAULT:
		throw WriteFileException(path);
	case ERROR_READ_FAULT:
		throw ReadFileException(path);
	case ERROR_SHARING_VIOLATION:
		throw FileException("sharing violation", path);
	case ERROR_LOCK_VIOLATION:
		throw FileException("lock violation", path);
	case ERROR_HANDLE_EOF:
		throw ReadFileException("EOF reached", path);
	case ERROR_HANDLE_DISK_FULL:
	case ERROR_DISK_FULL:
		throw WriteFileException("disk is full", path);
	case ERROR_NEGATIVE_SEEK:
		throw FileException("negative seek", path);
	default:
		throw FileException(path);
	}
	*/
	throw std::exception();
}

}

}
