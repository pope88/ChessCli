#include "DirectoryIteratorImpl.h"
#include "../Path.h"

namespace System {

namespace priv {

DirectoryIteratorImpl::DirectoryIteratorImpl(const std::string& path): _fh(INVALID_HANDLE_VALUE), _rc(1)
{
	Path p(path);
	p.makeDirectory();
	std::string findPath = p.toString();
	findPath.append("*");

	_fh = FindFirstFile(findPath.c_str(), &_fd);
	if (_fh == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() != ERROR_NO_MORE_FILES)
			File::handleLastError(path);
	}
	else
	{
		_current = _fd.cFileName;
		if (_current == "." || _current == "..")	
			next();
	}
}


DirectoryIteratorImpl::~DirectoryIteratorImpl()
{
	if (_fh != INVALID_HANDLE_VALUE)
		FindClose(_fh);
}


const std::string& DirectoryIteratorImpl::next()
{
	do
	{
		if (FindNextFile(_fh, &_fd) != 0)
			_current = _fd.cFileName;
		else
			_current.clear();
	}
	while (_current == "." || _current == "..");
	return _current;
}

}

}
