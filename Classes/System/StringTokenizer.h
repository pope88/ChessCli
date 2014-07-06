#ifndef _STRINGTOKENIZER_H_
#define _STRINGTOKENIZER_H_

namespace System
{

class StringTokenizer
{
public:
	typedef std::vector<std::string>::iterator Iterator;
	typedef std::vector<std::string>::const_iterator ConstIterator;
public:
	StringTokenizer(const std::string& str, const std::string& tok, bool ignore_empty = false);
	inline ConstIterator begin() const { return _sepStrings.begin(); }
	inline ConstIterator end() const { return _sepStrings.end(); }
	inline Iterator begin() { return _sepStrings.begin(); }
	inline Iterator end() { return _sepStrings.end(); }
	inline size_t size() { return _sepStrings.size(); }
	inline std::string& operator[](size_t idx) { return _sepStrings[idx]; }
private:
	std::vector<std::string> _sepStrings;
};

}

#endif // _STRINGTOKENIZER_H_
