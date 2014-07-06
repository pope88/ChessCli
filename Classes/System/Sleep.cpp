////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Config.h"
#include <System/Sleep.h>
#include <System/Platform.h>


namespace System
{
////////////////////////////////////////////////////////////
void Sleep(UInt32 duration)
{
    priv::Platform::Sleep(duration);
}

} // namespace System
