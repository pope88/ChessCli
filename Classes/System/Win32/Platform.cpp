////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <System/Win32/Platform.h>
#include <windows.h>


namespace System
{
namespace priv
{
////////////////////////////////////////////////////////////
double Platform::GetSystemTime()
{
    static LARGE_INTEGER frequency;
    static BOOL          useHighPerformanceTimer = QueryPerformanceFrequency(&frequency);

    if (useHighPerformanceTimer)
    {
        // High performance counter available : use it
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);

        return static_cast<double>(currentTime.QuadPart) / frequency.QuadPart;
    }
    else
    {
        // High performance counter not available: use GetTickCount (less accurate)
        return GetTickCount() * 0.001;
    }
}


////////////////////////////////////////////////////////////
void Platform::Sleep(UInt32 time)
{
    ::Sleep(time);
}

} // namespace priv

} // namespace System
