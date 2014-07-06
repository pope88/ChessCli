#ifndef System_DirectoryIterator_UNIX_INCLUDED
#define System_DirectoryIterator_UNIX_INCLUDED

#include <dirent.h>

namespace System {

namespace priv {

class  DirectoryIteratorImpl
{
public:
	DirectoryIteratorImpl(const std::string& path);
	~DirectoryIteratorImpl();
	
	void duplicate();
	void release();
	
	const std::string& get() const;
	const std::string& next();
	
private:
	DIR*        _pDir;
	std::string _current;
	int _rc;
};


//
// inlines
//
const std::string& DirectoryIteratorImpl::get() const
{
	return _current;
}


inline void DirectoryIteratorImpl::duplicate()
{
	++_rc;
}


inline void DirectoryIteratorImpl::release()
{
	if (--_rc == 0)
		delete this;
}

}

}

#endif // System_DirectoryIterator_UNIX_INCLUDED
