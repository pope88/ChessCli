#ifndef _TIMER_H_
#define _TIMER_H_

namespace System
{

	class Timer
	{
	public:
		virtual ~Timer();
		void * add(UInt32 interval, void * data, int count = -1);
		void * add(UInt32 interval, UInt32 firstInterval, void * data, int count = -1);
		void remove(const void * timer);

	public:
		void process();

	protected:
		UInt32 getNextTime(const void * timer) const;
		UInt32 getInterval(const void * timer) const;
		int getCount(const void * timer) const;

	protected:
		virtual void onTimer(const void * timer, void * data) = 0;

	private:
		std::vector<void *> _timers;
	};

}

#endif
