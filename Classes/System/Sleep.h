#ifndef SYSTEM_SLEEP_H
#define SYSTEM_SLEEP_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Config.h>


namespace System
{
////////////////////////////////////////////////////////////
/// \ingroup system
/// \brief Make the current thread sleep for a given time
///
/// System::Sleep is the best way to block a program or one of its
/// threads, as it doesn't consume any CPU power.
///
/// \param duration Time to sleep, in seconds (must be positive)
///
////////////////////////////////////////////////////////////
void Sleep(UInt32 duration);

} // namespace System


#endif // SYSTEM_SLEEP_H
