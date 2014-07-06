#include "Config.h"
#include <System/Event.h>


#if defined(SYSTEM_SYSTEM_WINDOWS)

    #include "Win32/EventImpl.cpp"

#else

    #include "Unix/EventImpl.cpp"

#endif

namespace System {


Event::Event(bool autoReset): myEventImpl(new priv::EventImpl(autoReset))
{
}


Event::~Event()
{
	delete myEventImpl;
}


void Event::set()
{
	myEventImpl->setImpl();
}


void Event::wait()
{
	myEventImpl->waitImpl();
}


void Event::wait(long milliseconds)
{
	if(!myEventImpl->waitImpl(milliseconds))
		throw std::exception(/*"Timeout"*/);
}


bool Event::tryWait(long milliseconds)
{
	return myEventImpl->waitImpl(milliseconds);
}


void Event::reset()
{
	myEventImpl->resetImpl();
}



} // namespace System
