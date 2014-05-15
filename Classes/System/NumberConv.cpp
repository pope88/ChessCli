#include "Config.h"
#include "NumberConv.h"

namespace System
{
	
	inline int testRadix(const char *& str)
	{
		if(str[0] == '0')
		{
			if(str[1] == 'X' || str[1] == 'x')
			{
				str += 2;
				return 16;
			}
			str += 1;
			return 8;
		}
		return 10;
	}
	
	UInt64 toUInt64(const char * str)
	{
		const char * s = str;
		int radix = testRadix(s);
		return strtoull(s, NULL, radix);
	}

	Int64 toInt64(const char * str)
	{
		const char * s = str;
		int radix = testRadix(s);
		return strtoll(s, NULL, radix);
	}

	UInt32 toUInt32(const char * str)
	{
		const char * s = str;
		int radix = testRadix(s);
		return strtoul(s, NULL, radix);
	}

	Int32 toInt32(const char * str)
	{
		const char * s = str;
		int radix = testRadix(s);
		return strtol(s, NULL, radix);
	}

	UInt16 toUInt16(const char * str)
	{
		const char * s = str;
		int radix = testRadix(s);
		return static_cast<unsigned short>(strtoul(s, NULL, radix));
	}
	
	Int16 toInt16(const char * str)
	{
		const char * s = str;
		int radix = testRadix(s);
		return static_cast<unsigned short>(strtol(s, NULL, radix));
	}
	
	UInt8 toUInt8(const char * str)
	{
		const char * s = str;
		int radix = testRadix(s);
		return static_cast<unsigned char>(strtoul(s, NULL, radix));
	}
	
	Int8 toInt8(const char * str)
	{
		const char * s = str;
		int radix = testRadix(s);
		return static_cast<unsigned char>(strtol(s, NULL, radix));
	}

	double toDouble(const char * str)
	{
		return atof(str);
	}

	float toFloat(const char * str)
	{
		return static_cast<float>(atof(str));
	}
	
}
