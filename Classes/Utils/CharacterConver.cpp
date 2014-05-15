#include "Config.h"
#include "CharacterConver.h"
namespace Utils
{
	int CharacterConver::code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen)
	{
		iconv_t cd;
		const char *temp = inbuf;
		const char **pin = &temp;
		char **pout = &outbuf;
		memset(outbuf, 0, outlen);
		cd = iconv_open(to_charset,from_charset);
		if(cd==0) return -1;
		if(iconv(cd, pin, &inlen, pout, &outlen)==-1) 
			return -1;
		iconv_close(cd);
		return 0;
	}

	/*UTF8 to GB2312*/
	std::string CharacterConver::u2a(const char *inbuf)
	{
		size_t inlen = strlen(inbuf);
		char *outbuf = new char[inlen*2+2];
		std::string strRet;
		if(code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
		{
			strRet = outbuf;
		}
		delete[] outbuf;
		return strRet;
	}

	/*GB2312 to UTF8*/
	std::string CharacterConver::a2u(const char *inbuf)
	{
		size_t inlen = strlen(inbuf);
		char * outbuf = new char[inlen * 2 + 2];
		std::string strRet;
		if(code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, inlen * 2 + 2) ==0)
		{
			strRet = outbuf;
		}
		delete[] outbuf;
		return strRet;
	}
}