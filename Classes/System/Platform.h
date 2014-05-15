#ifndef SYSTEM_PLATFORM_H
#define SYSTEM_PLATFORM_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Config.h>


#if defined(SYSTEM_SYSTEM_WINDOWS)

    #include <System/Win32/Platform.h>

#else

    #include <System/Unix/Platform.h>

#endif


#endif // SYSTEM_PLATFORM_H
