////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <System/Unix/ThreadImpl.h>
#include <System/Thread.h>
#include <iostream>


namespace System
{
namespace priv
{
////////////////////////////////////////////////////////////
ThreadImpl::ThreadImpl(Thread* owner) :
myIsActive(true)
{
    myIsActive = pthread_create(&myThread, NULL, &ThreadImpl::EntryPoint, owner) == 0;

    if (!myIsActive)
        std::cerr << "Failed to create thread" << std::endl;
}


////////////////////////////////////////////////////////////
void ThreadImpl::Wait()
{
    if (myIsActive)
        pthread_join(myThread, NULL);
}


////////////////////////////////////////////////////////////
void ThreadImpl::Terminate()
{
    if (myIsActive)
        pthread_cancel(myThread);
}


////////////////////////////////////////////////////////////
void* ThreadImpl::EntryPoint(void* userData)
{
    // The Thread instance is stored in the user data
    Thread* owner = static_cast<Thread*>(userData);

    // Tell the thread to handle cancel requests immediatly
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    // Forward to the owner
    owner->Run();

    return NULL;
}

} // namespace priv

} // namespace System
