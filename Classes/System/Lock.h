#ifndef SYSTEM_LOCK_H
#define SYSTEM_LOCK_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <System/NonCopyable.h>


namespace System
{
class Mutex;

////////////////////////////////////////////////////////////
/// \brief Automatic wrapper for locking and unlocking mutexes
///
////////////////////////////////////////////////////////////
class Lock : NonCopyable
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Construct the lock with a target mutex
    ///
    /// The mutex passed to System::Lock is automatically locked.
    ///
    /// \param mutex Mutex to lock
    ///
    ////////////////////////////////////////////////////////////
    Lock(Mutex& mutex);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    /// The destructor of System::Lock automatically unlocks its mutex.
    ///
    ////////////////////////////////////////////////////////////
    ~Lock();

private :

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Mutex& myMutex; ///< Mutex to lock / unlock
};

} // namespace System


#endif // SYSTEM_LOCK_H


////////////////////////////////////////////////////////////
/// \class System::Lock
/// \ingroup system
///
/// System::Lock is a RAII wrapper for System::Mutex. By unlocking
/// it in its destructor, it ensures that the mutex will
/// always be released when the current scope (most likely
/// a function) ends.
/// This is even more important when an exception or an early
/// return statement can interrupt the execution flow of the
/// function.
///
/// For maximum robustness, System::Lock should always be used
/// to lock/unlock a mutex.
///
/// Usage example:
/// \code
/// System::Mutex mutex;
/// 
/// void function()
/// {
///     System::Lock lock(mutex); // mutex is now locked
/// 
///     functionThatMayThrowAnException(); // mutex is unlocked if this function throws
/// 
///     if (someCondition)
///         return; // mutex is unlocked
/// 
/// } // mutex is unlocked
/// \endcode
///
/// Because the mutex is not explicitely unlocked in the code,
/// it may remain locked longer than needed. If the region
/// of the code that needs to be protected by the mutex is
/// not the entire function, a good practice is to create a
/// smaller, inner scope so that the lock is limited to this
/// part of the code.
///
/// \code
/// System::Mutex mutex;
/// 
/// void function()
/// {
///     {
///       System::Lock lock(mutex);
///       codeThatRequiresProtection();
/// 
///     } // mutex is unlocked here
/// 
///     codeThatDoesntCareAboutTheMutex();
/// }
/// \endcode
///
/// Having a mutex locked longer than required is a bad practice
/// which can lead to bad performances. Don't forget that when
/// a mutex is locked, other threads may be waiting doing nothing
/// until it is released.
///
/// \see System::Mutex
///
////////////////////////////////////////////////////////////
