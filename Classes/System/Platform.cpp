#include <Config.h>


#if defined(SYSTEM_SYSTEM_WINDOWS)

    #include "Win32/Platform.cpp"

#else

    #include "Unix/Platform.cpp"

#endif
