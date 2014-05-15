////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <System/Unix/Platform.h>
#include <unistd.h>
#include <sys/time.h>


namespace System
{
namespace priv
{
////////////////////////////////////////////////////////////
double Platform::GetSystemTime()
{
    timeval time = {0, 0};
    gettimeofday(&time, NULL);

    return time.tv_sec + time.tv_usec / 1000000.;
}


////////////////////////////////////////////////////////////
void Platform::Sleep(UInt32 time)
{
    usleep(time * 1000);
}

} // namespace priv

} // namespace System
