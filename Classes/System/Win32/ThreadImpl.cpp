////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <System/Win32/ThreadImpl.h>
#include <System/Thread.h>
#include <System/Err.h>
#include <process.h>


namespace System
{
namespace priv
{
////////////////////////////////////////////////////////////
ThreadImpl::ThreadImpl(Thread* owner)
{
    myThread = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, &ThreadImpl::EntryPoint, owner, 0, NULL));

    if (!myThread)
        Err() << "Failed to create thread" << std::endl;
}


////////////////////////////////////////////////////////////
ThreadImpl::~ThreadImpl()
{
    if (myThread)
        CloseHandle(myThread);
}


////////////////////////////////////////////////////////////
void ThreadImpl::Wait()
{
    if (myThread)
        WaitForSingleObject(myThread, INFINITE);
}


////////////////////////////////////////////////////////////
void ThreadImpl::Terminate()
{
    if (myThread)
        TerminateThread(myThread, 0);
}


////////////////////////////////////////////////////////////
unsigned int __stdcall ThreadImpl::EntryPoint(void* userData)
{
    // The Thread instance is stored in the user data
    Thread* owner = static_cast<Thread*>(userData);

    // Forward to the owner
    owner->Run();

    // Optional, but it is cleaner
    _endthreadex(0);

    return 0;
}

} // namespace priv

} // namespace System
