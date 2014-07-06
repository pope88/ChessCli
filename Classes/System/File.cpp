#include "Config.h"
#include "File.h"
#include "Path.h"
#include "DirectoryIterator.h"

#if defined(SYSTEM_SYSTEM_WINDOWS)

#include "Win32/FileImpl.cpp"

#else

#include "Unix/FileImpl.cpp"

#endif

namespace System {


	File::File(): impl(new priv::FileImpl())
	{
	}


	File::File(const std::string& path): impl(new priv::FileImpl(path))
	{
	}


	File::File(const char* path): impl(new priv::FileImpl(std::string(path)))
	{
	}

	File::File(const Path& path): impl(new priv::FileImpl(path.toString()))
	{
	}

	File::File(const File& file): impl(new priv::FileImpl(file.impl->getPathImpl()))
	{
	}


	File::~File()
	{
		if(impl) delete impl;
	}


	File& File::operator = (const File& file)
	{
		impl->setPathImpl(file.impl->getPathImpl());
		return *this;
	}


	File& File::operator = (const std::string& path)
	{
		impl->setPathImpl(path);
		return *this;
	}


	File& File::operator = (const char* path)
	{
		impl->setPathImpl(path);
		return *this;
	}


	File& File::operator = (const Path& path)
	{
		impl->setPathImpl(path.toString());
		return *this;
	}


	void File::swap(File& file)
	{
		impl->swapImpl(*file.impl);
	}


	bool File::exists() const
	{
		return impl->existsImpl();
	}


	bool File::canRead() const
	{
		return impl->canReadImpl();
	}


	bool File::canWrite() const
	{
		return impl->canWriteImpl();
	}


	bool File::isFile() const
	{
		return impl->isFileImpl();
	}


	bool File::isDirectory() const
	{
		return impl->isDirectoryImpl();
	}


	bool File::isLink() const
	{
		return impl->isLinkImpl();
	}


	bool File::isDevice() const
	{
		return impl->isDeviceImpl();
	}


	bool File::isHidden() const
	{
		return impl->isHiddenImpl();
	}


	UInt64 File::created() const
	{
		return impl->createdImpl();
	}


	UInt64 File::getLastModified() const
	{
		return impl->getLastModifiedImpl();
	}


	void File::setLastModified(UInt64 ts)
	{
		impl->setLastModifiedImpl(ts);
	}


	File::FileSize File::getSize() const
	{
		return impl->getSizeImpl();
	}


	void File::setSize(FileSize size)
	{
		impl->setSizeImpl(size);
	}


	void File::setWriteable(bool flag)
	{
		impl->setWriteableImpl(flag);
	}


	void File::setReadOnly(bool flag)
	{
		impl->setWriteableImpl(!flag);
	}


	void File::setExecutable(bool flag)
	{
		impl->setExecutableImpl(flag);
	}


	void File::copyTo(const std::string& path) const
	{
		Path src(impl->getPathImpl());
		Path dest(path);
		File destFile(path);
		if ((destFile.exists() && destFile.isDirectory()) || dest.isDirectory())
		{
			dest.makeDirectory();
			dest.setFileName(src.getFileName());
		}
		if (isDirectory())
			copyDirectory(dest.toString());
		else
			impl->copyToImpl(dest.toString());
	}


	void File::copyDirectory(const std::string& path) const
	{
		File target(path);
		target.createDirectories();

		Path src(impl->getPathImpl());
		src.makeFile();
		DirectoryIterator it(src);
		DirectoryIterator end;
		for (; it != end; ++it)
		{
			it->copyTo(path);
		}
	}


	void File::moveTo(const std::string& path)
	{
		copyTo(path);
		remove(true);
		impl->setPathImpl(path);
	}


	void File::renameTo(const std::string& path)
	{
		impl->renameToImpl(path);
		impl->setPathImpl(path);
	}


	void File::remove(bool recursive)
	{
		if (recursive && !isLink() && isDirectory())
		{
			std::vector<File> files;
			list(files);
			for (std::vector<File>::iterator it = files.begin(); it != files.end(); ++it)
			{
				it->remove(true);
			}
		}
		impl->removeImpl();
	}


	bool File::createFile()
	{
		return impl->createFileImpl();
	}


	bool File::createDirectory()
	{
		return impl->createDirectoryImpl();
	}


	void File::createDirectories()
	{
		if (!exists())
		{
			Path p(impl->getPathImpl());
			p.makeDirectory();
			if (p.depth() > 1)
			{
				p.makeParent();
				File f(p);
				f.createDirectories();
			}
			impl->createDirectoryImpl();
		}
	}


	void File::list(std::vector<std::string>& files) const
	{
		files.clear();
		DirectoryIterator it(*this);
		DirectoryIterator end;
		while (it != end)
		{
			files.push_back(it.name());
			++it;
		}
	}

	void File::list(std::vector<File>& files) const
	{
		files.clear();
		DirectoryIterator it(*this);
		DirectoryIterator end;
		while (it != end)
		{
			files.push_back(*it);
			++it;
		}
	}


	void File::handleLastError(const std::string& path)
	{
		priv::FileImpl::handleLastErrorImpl(path);
	}


	const std::string& File::path() const
	{
		return impl->getPathImpl();
	}


	bool File::operator == (const File& file) const
	{
		return impl->getPathImpl() == file.impl->getPathImpl();
	}


	bool File::operator != (const File& file) const
	{
		return impl->getPathImpl() != file.impl->getPathImpl();
	}


	bool File::operator < (const File& file) const
	{
		return impl->getPathImpl() < file.impl->getPathImpl();
	}


	bool File::operator <= (const File& file) const
	{
		return impl->getPathImpl() <= file.impl->getPathImpl();
	}


	bool File::operator > (const File& file) const
	{
		return impl->getPathImpl() > file.impl->getPathImpl();
	}


	bool File::operator >= (const File& file) const
	{
		return impl->getPathImpl() >= file.impl->getPathImpl();
	}


	void swap(File& f1, File& f2)
	{
		f1.swap(f2);
	}

} // namespace System
