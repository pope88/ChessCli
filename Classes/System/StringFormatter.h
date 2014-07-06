#ifndef _STRINGFORMATTER_H_
#define _STRINGFORMATTER_H_

#include <sstream>
#include <cctype>
#ifdef SYSTEM_USE_TYPED_FORMAT
#include "Any.h"
#endif

namespace std
{
#ifdef _MSC_VER
	template<> inline
		basic_ostream<char, char_traits<char> >& operator<<(
		basic_ostream<char, char_traits<char> >& _Ostr, UInt8 _Ch)
	{	// insert an unsigned char
		return (_Ostr << static_cast<UInt32>(_Ch));
	}
#else
	inline ostream&
	operator<<(ostream& __out, const unsigned char __c)
	{
		basic_ostream<char, char_traits<char> >& ostr = (basic_ostream<char, char_traits<char> >&)__out;
		ostr << static_cast<UInt32>(__c);
		return __out;
	}
#endif
}

namespace System
{

namespace
{

#ifdef SYSTEM_USE_TYPED_FORMAT
inline void parseFlags(std::ostream& ostr, std::string::const_iterator& fmtStr, const std::string::const_iterator& fmtEnd)
{
	bool isFlag = true;
	while (isFlag && fmtStr != fmtEnd)
	{
		switch (*fmtStr)
		{
		case '-': ostr.setf(std::ios::left); ++fmtStr; break;
		case '+': ostr.setf(std::ios::showpos); ++fmtStr; break;
		case '0': ostr.fill('0'); ++fmtStr; break;
		case '#': ostr.setf(std::ios::showpoint | std::ios_base::showbase); ++fmtStr; break;
		default:  isFlag = false; break;
		}
	}
}


inline void parseWidth(std::ostream& ostr, std::string::const_iterator& fmtStr, const std::string::const_iterator& fmtEnd)
{
	int width = 0;
	while (fmtStr != fmtEnd && std::isdigit(*fmtStr))
	{
		width = 10*width + *fmtStr - '0';
		++fmtStr;
	}
	if (width != 0) ostr.width(width);
}


inline void parsePrec(std::ostream& ostr, std::string::const_iterator& fmtStr, const std::string::const_iterator& fmtEnd)
{
	if (fmtStr != fmtEnd && *fmtStr == '.')
	{
		++fmtStr;
		int prec = 0;
		while (fmtStr != fmtEnd && std::isdigit(*fmtStr))
		{
			prec = 10*prec + *fmtStr - '0';
			++fmtStr;
		}
		if (prec != 0) ostr.precision(prec);
	}
}

inline char parseMod(std::string::const_iterator& fmtStr, const std::string::const_iterator& fmtEnd)
{
	char mod = 0;
	if (fmtStr != fmtEnd)
	{
		switch (*fmtStr)
		{
		case 'l':
		case 'h':
		case 'L': 
		case '?': mod = *fmtStr++; break;
		}
	}
	return mod;
}

inline void prepareFormat(std::ostream& str, char type)
{
	switch (type)
	{
	case 'd':
	case 'i': str << std::dec; break;
	case 'o': str << std::oct; break;
	case 'x': str << std::hex; break;
	case 'X': str << std::hex << std::uppercase; break;
	case 'e': str << std::scientific; break;
	case 'E': str << std::scientific << std::uppercase; break;
	case 'f': str << std::fixed; break;
	}
}

template <typename T>
inline void writeAnyInt(std::ostream& ostr, const T& any)
{
	if (typeid(T) == typeid(char))
		ostr << static_cast<int>(AnyCast<char>(any));
	else if (typeid(T) == typeid(signed char))
		ostr << static_cast<int>(AnyCast<signed char>(any));
	else if (typeid(T) == typeid(unsigned char))
		ostr << static_cast<unsigned>(AnyCast<unsigned char>(any));
	else if (typeid(T) == typeid(short))
		ostr << AnyCast<short>(any);
	else if (typeid(T) == typeid(unsigned short))
		ostr << AnyCast<unsigned short>(any);
	else if (typeid(T) == typeid(int))
		ostr << AnyCast<int>(any);
	else if (typeid(T) == typeid(unsigned int))
		ostr << AnyCast<unsigned int>(any);
	else if (typeid(T) == typeid(long))
		ostr << AnyCast<long>(any);
	else if (typeid(T) == typeid(unsigned long))
		ostr << AnyCast<unsigned long>(any);
	else if (typeid(T) == typeid(Int64))
		ostr << AnyCast<Int64>(any);
	else if (typeid(T) == typeid(UInt64))
		ostr << AnyCast<UInt64>(any);
	else if (typeid(T) == typeid(bool))
		ostr << AnyCast<bool>(any);
}

template <typename T>
inline void _typedFormat(std::ostream& ostr, std::string::const_iterator& fmtStr, const std::string::const_iterator& fmtEnd, const T& arg)
{
	parseFlags(ostr, fmtStr, fmtEnd);
	parseWidth(ostr, fmtStr, fmtEnd);
	parsePrec(ostr, fmtStr, fmtEnd);
	char mod = parseMod(fmtStr, fmtEnd);
	if (fmtStr == fmtEnd)
		return;
	char type = *fmtStr++;
	prepareFormat(ostr, type);
	switch (type)
	{
	case 'b':
		ostr << AnyCast<bool>(arg);
		break;
	case 'c':
		ostr << AnyCast<char>(arg);
		break;
	case 'd':
	case 'i':
		switch (mod)
		{
		case 'l': ostr << AnyCast<long>(arg); break;
		case 'L': ostr << AnyCast<Int64>(arg); break;
		case 'h': ostr << AnyCast<short>(arg); break;
		case '?': writeAnyInt(ostr, arg); break;
		default:  ostr << AnyCast<int>(arg); break;
		}
		break;
	case 'o':
	case 'u':
	case 'x':
	case 'X':
		switch (mod)
		{
		case 'l': ostr << AnyCast<unsigned long>(arg); break;
		case 'L': ostr << AnyCast<UInt64>(arg); break;
		case 'h': ostr << AnyCast<unsigned short>(arg); break;
		case '?': writeAnyInt(ostr, arg); break;
		default:  ostr << AnyCast<unsigned>(arg); break;
		}
		break;
	case 'e':
	case 'E':
	case 'f':
		switch (mod)
		{
		case 'l': ostr << AnyCast<long double>(arg); break;
		case 'L': ostr << AnyCast<long double>(arg); break;
		case 'h': ostr << AnyCast<float>(arg); break;
		default:  ostr << AnyCast<double>(arg); break;
		}
		break;
	case 's':
		ostr << RefAnyCast<std::string>(arg);
		break;
	case 'z':
		ostr << AnyCast<std::size_t>(arg); 
		break;
	case 'I':
	case 'D':
	default:
		ostr << type;
	}
}
#endif

template <typename T>
inline void _format(std::ostream& ostr, std::string::const_iterator& fmtStr, const std::string::const_iterator& fmtEnd, const T& arg)
{
	while(fmtStr != fmtEnd)
	{
		switch(*fmtStr)
		{
#ifdef SYSTEM_USE_TYPED_FORMAT
		case '%':
			++fmtStr;
			if(fmtStr == fmtEnd)
				return;
			if(*fmtStr == '%')
			{
				++fmtStr;
				ostr << '%';
				break;
			}
			_typedFormat(ostr, fmtStr, fmtEnd, arg);
			return;
#endif
		case '?':
			++ fmtStr;
			if(fmtStr != fmtEnd && *fmtStr == '?')
			{
				++ fmtStr;
				ostr << '?';
				break;
			}
			ostr << arg;
			return;
		default:
			ostr << *fmtStr;
			++ fmtStr;
			break;
		}
	}
}

}

template <typename T0>
void formatString(std::string& result, const std::string& fmtStr, const T0& arg0)
{
	std::string::const_iterator it = fmtStr.begin();
	std::ostringstream ostr;
	_format(ostr, it, fmtStr.end(), arg0);
	if(it != fmtStr.end()) ostr << std::string(it, fmtStr.end());
	result += ostr.str();
}

template <typename T0, typename T1>
void formatString(std::string& result, const std::string& fmtStr, const T0& arg0, const T1& arg1)
{
	std::string::const_iterator it = fmtStr.begin();
	std::ostringstream ostr;
	_format(ostr, it, fmtStr.end(), arg0);
	_format(ostr, it, fmtStr.end(), arg1);
	if(it != fmtStr.end()) ostr << std::string(it, fmtStr.end());
	result += ostr.str();
}

template <typename T0, typename T1, typename T2>
void formatString(std::string& result, const std::string& fmtStr, const T0& arg0, const T1& arg1, const T2& arg2)
{
	std::string::const_iterator it = fmtStr.begin();
	std::ostringstream ostr;
	_format(ostr, it, fmtStr.end(), arg0);
	_format(ostr, it, fmtStr.end(), arg1);
	_format(ostr, it, fmtStr.end(), arg2);
	if(it != fmtStr.end()) ostr << std::string(it, fmtStr.end());
	result += ostr.str();
}

template <typename T0, typename T1, typename T2, typename T3>
void formatString(std::string& result, const std::string& fmtStr, const T0& arg0, const T1& arg1, const T2& arg2, const T3& arg3)
{
	std::string::const_iterator it = fmtStr.begin();
	std::ostringstream ostr;
	_format(ostr, it, fmtStr.end(), arg0);
	_format(ostr, it, fmtStr.end(), arg1);
	_format(ostr, it, fmtStr.end(), arg2);
	_format(ostr, it, fmtStr.end(), arg3);
	if(it != fmtStr.end()) ostr << std::string(it, fmtStr.end());
	result += ostr.str();
}

template <typename T0, typename T1, typename T2, typename T3, typename T4>
void formatString(std::string& result, const std::string& fmtStr, const T0& arg0, const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4)
{
	std::string::const_iterator it = fmtStr.begin();
	std::ostringstream ostr;
	_format(ostr, it, fmtStr.end(), arg0);
	_format(ostr, it, fmtStr.end(), arg1);
	_format(ostr, it, fmtStr.end(), arg2);
	_format(ostr, it, fmtStr.end(), arg3);
	_format(ostr, it, fmtStr.end(), arg4);
	if(it != fmtStr.end()) ostr << std::string(it, fmtStr.end());
	result += ostr.str();
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
void formatString(std::string& result, const std::string& fmtStr, const T0& arg0, const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5)
{
	std::string::const_iterator it = fmtStr.begin();
	std::ostringstream ostr;
	_format(ostr, it, fmtStr.end(), arg0);
	_format(ostr, it, fmtStr.end(), arg1);
	_format(ostr, it, fmtStr.end(), arg2);
	_format(ostr, it, fmtStr.end(), arg3);
	_format(ostr, it, fmtStr.end(), arg4);
	_format(ostr, it, fmtStr.end(), arg5);
	if(it != fmtStr.end()) ostr << std::string(it, fmtStr.end());
	result += ostr.str();
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
void formatString(std::string& result, const std::string& fmtStr, const T0& arg0, const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6)
{
	std::string::const_iterator it = fmtStr.begin();
	std::ostringstream ostr;
	_format(ostr, it, fmtStr.end(), arg0);
	_format(ostr, it, fmtStr.end(), arg1);
	_format(ostr, it, fmtStr.end(), arg2);
	_format(ostr, it, fmtStr.end(), arg3);
	_format(ostr, it, fmtStr.end(), arg4);
	_format(ostr, it, fmtStr.end(), arg5);
	_format(ostr, it, fmtStr.end(), arg6);
	if(it != fmtStr.end()) ostr << std::string(it, fmtStr.end());
	result += ostr.str();
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
void formatString(std::string& result, const std::string& fmtStr, const T0& arg0, const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6, const T7& arg7)
{
	std::string::const_iterator it = fmtStr.begin();
	std::ostringstream ostr;
	_format(ostr, it, fmtStr.end(), arg0);
	_format(ostr, it, fmtStr.end(), arg1);
	_format(ostr, it, fmtStr.end(), arg2);
	_format(ostr, it, fmtStr.end(), arg3);
	_format(ostr, it, fmtStr.end(), arg4);
	_format(ostr, it, fmtStr.end(), arg5);
	_format(ostr, it, fmtStr.end(), arg6);
	_format(ostr, it, fmtStr.end(), arg7);
	if(it != fmtStr.end()) ostr << std::string(it, fmtStr.end());
	result += ostr.str();
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
void formatString(std::string& result, const std::string& fmtStr, const T0& arg0, const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6, const T7& arg7, const T8& arg8)
{
	std::string::const_iterator it = fmtStr.begin();
	std::ostringstream ostr;
	_format(ostr, it, fmtStr.end(), arg0);
	_format(ostr, it, fmtStr.end(), arg1);
	_format(ostr, it, fmtStr.end(), arg2);
	_format(ostr, it, fmtStr.end(), arg3);
	_format(ostr, it, fmtStr.end(), arg4);
	_format(ostr, it, fmtStr.end(), arg5);
	_format(ostr, it, fmtStr.end(), arg6);
	_format(ostr, it, fmtStr.end(), arg7);
	_format(ostr, it, fmtStr.end(), arg8);
	if(it != fmtStr.end()) ostr << std::string(it, fmtStr.end());
	result += ostr.str();
}

template <typename T0>
std::string format(const std::string& fmtStr, const T0& arg0)
{
	std::string result;
	formatString(result, fmtStr, arg0);
	return result;
}

template <typename T0, typename T1>
std::string format(const std::string& fmtStr, const T0& arg0, const T1& arg1)
{
	std::string result;
	formatString(result, fmtStr, arg0, arg1);
	return result;
}

template <typename T0, typename T1, typename T2>
std::string format(const std::string& fmtStr, const T0& arg0, const T1& arg1, const T2& arg2)
{
	std::string result;
	formatString(result, fmtStr, arg0, arg1, arg2);
	return result;
}

template <typename T0, typename T1, typename T2, typename T3>
std::string format(const std::string& fmtStr, const T0& arg0, const T1& arg1, const T2& arg2, const T3& arg3)
{
	std::string result;
	formatString(result, fmtStr, arg0, arg1, arg2, arg3);
	return result;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4>
std::string format(const std::string& fmtStr, const T0& arg0, const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4)
{
	std::string result;
	formatString(result, fmtStr, arg0, arg1, arg2, arg3, arg4);
	return result;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
std::string format(const std::string& fmtStr, const T0& arg0, const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5)
{
	std::string result;
	formatString(result, fmtStr, arg0, arg1, arg2, arg3, arg4, arg5);
	return result;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
std::string format(const std::string& fmtStr, const T0& arg0, const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6)
{
	std::string result;
	formatString(result, fmtStr, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
	return result;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
std::string format(const std::string& fmtStr, const T0& arg0, const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6, const T7& arg7)
{
	std::string result;
	formatString(result, fmtStr, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	return result;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
std::string format(const std::string& fmtStr, const T0& arg0, const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6, const T7& arg7, const T8& arg8)
{
	std::string result;
	formatString(result, fmtStr, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	return result;
}

}

#endif // _STRINGFORMATTER_H_
