#include "Config.h"
#include "Timer.h"
#include "TimeUtil.h"

namespace System
{

	struct TimerStruct
	{
		UInt32 timeNext;
		UInt32 interval;
		int count;
		void * data;
	};

	inline bool timerCompare(const void * td1, const void * td2)
	{
		return static_cast<const TimerStruct *>(td1)->timeNext > static_cast<const TimerStruct *>(td2)->timeNext;
	}

	Timer::~Timer()
	{
		std::for_each(_timers.begin(), _timers.end(), [](void * data) { delete static_cast<TimerStruct *>(data);});
	}

	void * Timer::add(UInt32 interval, void * data, int count)
	{
		return add(interval, interval, data, count);
	}

	void * Timer::add(UInt32 interval, UInt32 firstInterval, void * data, int count)
	{
		TimerStruct * td = new(std::nothrow) TimerStruct;
		if(td == NULL)
			return NULL;
		td->timeNext = TimeUtil::Now() + firstInterval;
		td->interval = interval;
		td->count = count;
		td->data = data;
		_timers.push_back(td);
		std::push_heap(_timers.begin(), _timers.end(), timerCompare);
		return td;
	}

	void Timer::remove(const void * timer)
	{
		static_cast<TimerStruct *>(const_cast<void *>(timer))->count = 0;
	}

	void Timer::process()
	{
		if(_timers.empty())
			return;
		UInt32 now = TimeUtil::Now();
		while(1)
		{
			TimerStruct * td = static_cast<TimerStruct *>(_timers.front());
			if(td->count == 0)
			{
				std::pop_heap(_timers.begin(), _timers.end(), timerCompare);
				_timers.erase(_timers.end() - 1);
				delete td;
				continue;
			}
			if(now >= td->timeNext)
			{
				if(td->count > 0) -- td->count;
				onTimer(td, td->data);
				std::pop_heap(_timers.begin(), _timers.end(), timerCompare);
				if(td->count == 0)
				{
					_timers.erase(_timers.end() - 1);
					delete td;
				}
				else
				{
					td->timeNext += td->interval;
					std::push_heap(_timers.begin(), _timers.end(), timerCompare);
				}
				continue;
			}
			break;
		}
	}

	UInt32 Timer::getNextTime( const void * timer ) const
	{
		return static_cast<const TimerStruct *>(timer)->timeNext;
	}

	UInt32 Timer::getInterval( const void * timer ) const
	{
		return static_cast<const TimerStruct *>(timer)->interval;
	}

	int Timer::getCount( const void * timer ) const
	{
		return static_cast<const TimerStruct *>(timer)->count;
	}

}
