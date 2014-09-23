#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H



////////////////////////////////////////////////////////////
// Identify the operating system
////////////////////////////////////////////////////////////
#if defined(_WIN32) || defined(__WIN32__) ||defined(_WINDOWS)

// Windows
#define SYSTEM_SYSTEM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <winsock2.h>
#define strcasecmp _stricmp
#define strncasecmp _strnicmp

#elif defined(linux) || defined(__linux)

// Linux
#define SYSTEM_SYSTEM_LINUX

#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)

// MacOS
#define SYSTEM_SYSTEM_MACOS

#elif defined(__ANDROID__)

// Android
#define SYSTEM_SYSTEM_ANDRIOD

#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

// FreeBSD
#define SYSTEM_SYSTEM_FREEBSD

#else

// Unsupported system
#error This operating system is not supported by this library

#endif


////////////////////////////////////////////////////////////
// Identify the endianess
////////////////////////////////////////////////////////////
#if defined(__m68k__) || defined(mc68000) || defined(_M_M68K) || (defined(__MIPS__) && defined(__MISPEB__)) || \
	defined(__ppc__) || defined(__POWERPC__) || defined(_M_PPC) || defined(__sparc__) || defined(__Ha__)

// Big endian
#define SYSTEM_ENDIAN_BIG

#else

// Little endian
#define SYSTEM_ENDIAN_LITTLE

#endif


#include <climits>
#include <cstdio>
#include <cstdlib>
#undef __STRICT_ANSI__
#include <cstring>
#define __STRICT_ANSI__
#include <ctime>
#include <cassert>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <queue>
#include <list>
#include <memory>
#include <string>
#include <algorithm>
#include <functional>


#ifdef _MSC_VER

#pragma warning(disable : 4251)

#if _MSC_VER < 1600
namespace std
{
	using namespace std::tr1;
	template <typename T>
	inline T& move(T& t) { return t; }
}
#define unique_ptr auto_ptr
#endif
#define strtoull _strtoui64
#define strtoll _strtoi64

#define ATTR_PACKED()
#define FINLINE

#else

#define ATTR_PACKED() __attribute__((packed))

#if defined(__MINGW32__)
#define FINLINE inline
#else
#define FINLINE inline __attribute__((always_inline))
#endif

#endif

#if defined(_WIN32) || defined(__WIN32__)

#define I64_FMT "I64"
#define snprintf				           _snprintf
#define vsnprintf                          _vsnprintf

#include <io.h>

#else

#if defined(__LP64__)

#define I64_FMT "l"

#elif defined(__APPLE__)

#define I64_FMT "q"

#else

#define I64_FMT "ll"

#endif
#include <unistd.h>

#endif

// 8 bits integer types
#if UCHAR_MAX == 0xFF
typedef signed   char Int8;
typedef unsigned char UInt8;
#else
#error No 8 bits integer type for this platform
#endif

// 16 bits integer types
#if USHRT_MAX == 0xFFFF
typedef signed   short Int16;
typedef unsigned short UInt16;
#elif UINT_MAX == 0xFFFF
typedef signed   int Int16;
typedef unsigned int UInt16;
#elif ULONG_MAX == 0xFFFF
typedef signed   long Int16;
typedef unsigned long UInt16;
#else
#error No 16 bits integer type for this platform
#endif

// 32 bits integer types
#if USHRT_MAX == 0xFFFFFFFF
typedef signed   short Int32;
typedef unsigned short UInt32;
#elif UINT_MAX == 0xFFFFFFFF
typedef signed   int Int32;
typedef unsigned int UInt32;
#elif ULONG_MAX == 0xFFFFFFFF
typedef signed   long Int32;
typedef unsigned long UInt32;
#else
#error No 32 bits integer type for this platform
#endif

// 64 bits integer types
#if USHRT_MAX == 0xFFFFFFFFFFFFFFFFull
typedef signed   short Int64;
typedef unsigned short UInt64;
#elif UINT_MAX == 0xFFFFFFFFFFFFFFFFull
typedef signed   int Int64;
typedef unsigned int UInt64;
#elif ULONG_MAX == 0xFFFFFFFFFFFFFFFFull
typedef signed   long Int64;
typedef unsigned long UInt64;
#elif ULLONG_MAX == 0xFFFFFFFFFFFFFFFFull
typedef signed   long long Int64;
typedef unsigned long long UInt64;
#else
#error No 64 bits integer type for this platform
#endif

#define SAFE_DELETE(obj) do { delete(obj); obj = NULL; } while(0)

#endif // SYSTEM_CONFIG_H
