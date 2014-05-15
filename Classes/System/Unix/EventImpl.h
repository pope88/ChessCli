#include <pthread.h>
#include <errno.h>


namespace System {
namespace priv {

class EventImpl
{
public:
	EventImpl(bool autoReset);		
	~EventImpl();
	void setImpl();
	void waitImpl();
	bool waitImpl(long milliseconds);
	void resetImpl();
	
private:
	bool            _auto;
	volatile bool   _state;
	pthread_mutex_t _mutex;
	pthread_cond_t  _cond;
};


//
// inlines
//
inline void EventImpl::setImpl()
{
	if (pthread_mutex_lock(&_mutex))	
		throw std::exception(/*"cannot signal event (lock)"*/);
	_state = true;
	if (pthread_cond_broadcast(&_cond))
	{
		pthread_mutex_unlock(&_mutex);
		throw std::exception(/*"cannot signal event"*/);
	}
	pthread_mutex_unlock(&_mutex);
}


inline void EventImpl::resetImpl()
{
	if (pthread_mutex_lock(&_mutex))	
		throw std::exception(/*"cannot reset event"*/);
	_state = false;
	pthread_mutex_unlock(&_mutex);
}

}
} // namespace System
