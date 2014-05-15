#ifndef SYSTEM_MUTEX_H
#define SYSTEM_MUTEX_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Config.h>
#include <System/NonCopyable.h>
#include <System/Lock.h>

namespace System
{
namespace priv
{
    class MutexImpl;
}

////////////////////////////////////////////////////////////
/// \brief Blocks concurrent access to shared resources
///        from multiple threads
///
////////////////////////////////////////////////////////////
class Mutex : NonCopyable
{
public :
    typedef ::System::Lock ScopedLock;

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    Mutex();

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~Mutex();

    ////////////////////////////////////////////////////////////
    /// \brief Lock the mutex
    ///
    /// If the mutex is already locked in another thread,
    /// this call will block the execution until the mutex
    /// is released.
    ///
    /// \see Unlock
    ///
    ////////////////////////////////////////////////////////////
    void Lock();

    ////////////////////////////////////////////////////////////
    /// \brief Unlock the mutex
    ///
    /// \see Lock
    ///
    ////////////////////////////////////////////////////////////
    void Unlock();

private :

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    priv::MutexImpl* myMutexImpl; ///< OS-specific implementation
};

} // namespace System


#endif // SYSTEM_MUTEX_H


////////////////////////////////////////////////////////////
/// \class System::Mutex
/// \ingroup system
///
/// Mutex stands for "MUTual EXclusion". A mutex is a
/// synchronization object, used when multiple threads are involved.
///
/// When you want to protect a part of the code from being accessed
/// simultaneously by multiple threads, you typically use a
/// mutex. When a thread is locked by a mutex, any other thread
/// trying to lock it will be blocked until the mutex is released
/// by the thread that locked it. This way, you can allow only
/// one thread at a time to access a critical region of your code.
///
/// Usage example:
/// \code
/// Database db; // this is a critical resource that needs some protection
/// System::Mutex mutex;
///
/// void thread1()
/// {
///     mutex.Lock(); // this call will block the thread if the mutex is already locked by thread2
///     db.write(...);
///     mutex.Unlock(); // if thread2 was waiting, it will now be unblocked
/// }
/// 
/// void thread2()
/// {
///     mutex.Lock(); // this call will block the thread if the mutex is already locked by thread1
///     db.write(...);
///     mutex.Unlock(); // if thread1 was waiting, it will now be unblocked
/// }
/// \endcode
///
/// Be very careful with mutexes. A bad usage can lead to bad problems,
/// like deadlocks (two threads are waiting for each other and the
/// application is stuck).
///
/// To make the usage of mutexes more robust, particularly in
/// environments where exceptions can be thrown, you should
/// use the helper class System::Lock to lock/unlock mutexes.
///
/// \see System::Lock
///
////////////////////////////////////////////////////////////
