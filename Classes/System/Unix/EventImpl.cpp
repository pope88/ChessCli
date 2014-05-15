#include "EventImpl.h"
#include <sys/time.h>


namespace System {
namespace priv {

EventImpl::EventImpl(bool autoReset): _auto(autoReset), _state(false)
{
	if (pthread_mutex_init(&_mutex, NULL))
		throw std::exception(/*"cannot create event (mutex)"*/);
	if (pthread_cond_init(&_cond, NULL))
		throw std::exception(/*"cannot create event (condition)"*/);
}


EventImpl::~EventImpl()
{
	pthread_cond_destroy(&_cond);
	pthread_mutex_destroy(&_mutex);
}


void EventImpl::waitImpl()
{
	if (pthread_mutex_lock(&_mutex))
		throw std::exception(/*"wait for event failed (lock)"*/); 
	while (!_state) 
	{
		if (pthread_cond_wait(&_cond, &_mutex))
		{
			pthread_mutex_unlock(&_mutex);
			throw std::exception(/*"wait for event failed"*/);
		}
	}
	if (_auto)
		_state = false;
	pthread_mutex_unlock(&_mutex);
}


bool EventImpl::waitImpl(long milliseconds)
{
	int rc = 0;
	struct timespec abstime;

	struct timeval tv;
	gettimeofday(&tv, NULL);
	abstime.tv_sec  = tv.tv_sec + milliseconds / 1000;
	abstime.tv_nsec = tv.tv_usec*1000 + (milliseconds % 1000)*1000000;
	if (abstime.tv_nsec >= 1000000000)
	{
		abstime.tv_nsec -= 1000000000;
		abstime.tv_sec++;
	}

	if (pthread_mutex_lock(&_mutex) != 0)
		throw std::exception(/*"wait for event failed (lock)"*/); 
	while (!_state) 
	{
		if ((rc = pthread_cond_timedwait(&_cond, &_mutex, &abstime)))
		{
			if (rc == ETIMEDOUT) break;
			pthread_mutex_unlock(&_mutex);
			throw std::exception(/*"cannot wait for event"*/);
		}
	}
	if (rc == 0 && _auto) _state = false;
	pthread_mutex_unlock(&_mutex);
	return rc == 0;
}

}
} // namespace System
