#include <windows.h>

namespace System {

namespace priv {

class FileImpl
{
	friend class ::System::File;
protected:
	FileImpl();
	FileImpl(const std::string& path);
	virtual ~FileImpl();
	void swapImpl(FileImpl& file);
	void setPathImpl(const std::string& path);
	const std::string& getPathImpl() const;
	bool existsImpl() const;
	bool canReadImpl() const;
	bool canWriteImpl() const;
	bool canExecuteImpl() const;
	bool isFileImpl() const;
	bool isDirectoryImpl() const;
	bool isLinkImpl() const;
	bool isDeviceImpl() const;
	bool isHiddenImpl() const;
	UInt64 createdImpl() const;
	UInt64 getLastModifiedImpl() const;
	void setLastModifiedImpl(UInt64 ts);
	UInt64 getSizeImpl() const;
	void setSizeImpl(UInt64 size);
	void setWriteableImpl(bool flag = true);		
	void setExecutableImpl(bool flag = true);		
	void copyToImpl(const std::string& path) const;
	void renameToImpl(const std::string& path);
	void removeImpl();
	bool createFileImpl();
	bool createDirectoryImpl();
	static void handleLastErrorImpl(const std::string& path);
	
private:
	std::string _path;
	
	friend class FileHandle;
	friend class DirectoryIteratorImpl;
};


//
// inlines
//
inline const std::string& FileImpl::getPathImpl() const
{
	return _path;
}

}

} // namespace System
