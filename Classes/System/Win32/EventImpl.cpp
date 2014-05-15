#include "EventImpl.h"


namespace System {
namespace priv {

EventImpl::EventImpl(bool autoReset)
{
	_event = CreateEventW(NULL, autoReset ? FALSE : TRUE, FALSE, NULL);
	if (!_event)
		throw std::exception(/*"cannot create event"*/);
}


EventImpl::~EventImpl()
{
	CloseHandle(_event);
}


void EventImpl::waitImpl()
{
	switch (WaitForSingleObject(_event, INFINITE))
	{
	case WAIT_OBJECT_0:
		return;
	default:
		throw std::exception(/*"wait for event failed"*/);
	}
}


bool EventImpl::waitImpl(long milliseconds)
{
	switch (WaitForSingleObject(_event, milliseconds + 1))
	{
	case WAIT_TIMEOUT:
		return false;
	case WAIT_OBJECT_0:
		return true;
	default:
		throw std::exception(/*"wait for event failed"*/);		
	}
}

}
} // namespace System
