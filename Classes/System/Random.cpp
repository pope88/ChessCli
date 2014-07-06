#include "Config.h"
#include "Random.h"
#include <ctime>
#include <cassert>

#if defined(_WIN32) || defined(__WIN32__)
#include <WinCrypt.h>
#else
#include <fcntl.h>
#include "SHA1Engine.h"
#endif

extern "C"
{
#include "TinyMT/tinymt64.c"
};

namespace System
{

Random::Random()
{
	initState(getRandSeed());
}


Random::Random(UInt64 seed)
{
	initState(seed);
}


Random::~Random()
{
	free((tinymt64_t *)randState);
}

UInt64 Random::getRandSeed()
{
	UInt64 result;
#if defined(_WIN32) || defined(__WIN32__)
	HCRYPTPROV hProvider = 0;
	CryptAcquireContext(&hProvider, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
	CryptGenRandom(hProvider, (DWORD)sizeof(UInt64), (BYTE*)&result);
	CryptReleaseContext(hProvider, 0);
#else
	int n = 0;
	int fd = open("/dev/urandom", O_RDONLY, 0);
	if (fd >= 0)
	{
		n = read(fd, &result, sizeof(UInt64));
		close(fd);
	}
	if (n <= 0)
	{
		static UInt64 x = 0;
		SHA1Engine engine;
		UInt32 t = (UInt32) std::time(NULL);
		engine.update(&t, sizeof(t));
		void* p = this;
		engine.update(&p, sizeof(p));
		UInt32 junk[32];
		engine.update(junk, sizeof(junk));
		DigestEngine::Digest d = engine.digest();
		memcpy(&result, &d[0], sizeof(UInt64));
		x += result;
		result = x;
	}
#endif
	return result;
}

void Random::initState(UInt64 seed)
{
	tinymt64_t * tinymt = (tinymt64_t *)malloc(sizeof(tinymt64_t));
	tinymt->mat1 = 0x7a840f50;
	tinymt->mat2 = 0xf3d8fcf6;
	tinymt->tmat = 0x9746beffffbffffeULL;
	tinymt64_init(tinymt, seed);
	randState = tinymt;
}

UInt64 Random::next64()
{
	return tinymt64_generate_uint64((tinymt64_t *)randState);
}

double Random::nextDouble()
{
	return tinymt64_generate_double01((tinymt64_t *)randState);
}

}
