#ifndef _CHARACTERCONVER_H_
#define _CHARACTERCONVER_H_
#include "Singleton.h"
//#include "iconv/iconv.h"
namespace Utils
{
	class CharacterConver
	{
	public:
		void run(){}
		std::string u2a(const char *inbuf);
		std::string a2u(const char *inbuf);
	private:
		int code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen);

	private:
		CharacterConver(void) {}
		virtual ~CharacterConver(void){}

		DECLARE_SINGLETON_CLASS(CharacterConver);
	};

	typedef Singleton<CharacterConver> _characterconver;
}
#endif