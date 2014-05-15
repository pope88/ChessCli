#ifndef _MSGQUEUE_H_
#define _MSGQUEUE_H_

#include "Mutex.h"
#include "Event.h"

namespace System
{

template<class T>
class MsgQueue
{
public:
	inline bool tryWaitEvent(UInt32 milli)
	{
		if(!_event.tryWait(milli)) return false;
		_event.reset();
		return true;
	}

protected:
	inline MsgQueue<T>(): _currQueue(0), _event(false) {}
	virtual ~MsgQueue<T>() {}
	inline void pushLock()
	{
		_queueMutex.Lock();
	}
	inline void pushMsgNoLock(T data)
	{
		_msgQueue[_currQueue].push_back(data);
	}
	inline void pushUnlock()
	{
		_queueMutex.Unlock();
	}
	inline void pushMsg(T data)
	{
		System::Mutex::ScopedLock lk(_queueMutex);
		_msgQueue[_currQueue].push_back(data);
		_event.set();
	}
	inline std::vector<T> * fetchMsg(UInt32 milli)
	{
		if(!_event.tryWait(milli))
			return NULL;
		std::vector<T> * r = fetchMsg();
		_event.reset();
		return r;
	}
	inline std::vector<T> * fetchMsg()
	{
		System::Mutex::ScopedLock lk(_queueMutex);
		if(_msgQueue[_currQueue].empty())
			return NULL;
		_currQueue = 1 - _currQueue;
		return &_msgQueue[1 - _currQueue];
	}
	inline void fetchEnd(std::vector<T>* q)
	{
		q->clear();
	}
private:
	int _currQueue;
	Event _event;
	Mutex _queueMutex;
	std::vector<T> _msgQueue[2];
};

}

#endif // _MSGQUEUE_H_
