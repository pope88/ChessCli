////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <System/Thread.h>


#if defined(SYSTEM_SYSTEM_WINDOWS)
    #include "Win32/ThreadImpl.cpp"
#else
    #include "Unix/ThreadImpl.cpp"
#endif


namespace System
{
////////////////////////////////////////////////////////////
Thread::~Thread()
{
    Wait();
    delete myFunction;
}


////////////////////////////////////////////////////////////
void Thread::Launch()
{
    Wait();
    myImpl = new priv::ThreadImpl(this);
}


////////////////////////////////////////////////////////////
void Thread::Wait()
{
    if (myImpl)
    {
        myImpl->Wait();
        delete myImpl;
        myImpl = NULL;
    }
}


////////////////////////////////////////////////////////////
void Thread::Terminate()
{
    if (myImpl)
    {
        myImpl->Terminate();
        delete myImpl;
        myImpl = NULL;
    }
}


////////////////////////////////////////////////////////////
void Thread::Run()
{
    myFunction->Run();
}

} // namespace System
