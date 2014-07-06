#ifndef _TIMEUTIL_H_
#define _TIMEUTIL_H_

class TimeUtil
{
public:
	static inline bool Update() { return _GS()._Update(); }
	static inline UInt32 Now() { return _GS()._now; }
	static inline UInt8 WeekDay() { return _GS()._weekDay; }
	static inline UInt32 ThisDay() { return _GS()._thisDay; }
	static inline UInt32 NextDay() { return _GS()._nextDay; }
	static inline UInt32 SharpDay(int c = 0) { return _GS()._thisDay + c * 86400; }
	static inline UInt32 SharpDay(int c, UInt32 tm)
	{
		UInt32 tmptm = (tm + _tzone) / 86400 * 86400 + _tzone;
		if(tmptm > tm)
			tmptm -= 86400;
		else if(tmptm + 86400 <= tm)
			tmptm += 86400;
		return tmptm + c * 86400;
	}
	static inline UInt32 SharpHour(int c = 0) { return (Now() + c * 3600) / 3600 * 3600; }
	static inline UInt32 SharpFourtyMin(int c = 0) { return (Now() + c * 2400) / 2400 * 2400; }
	static inline UInt32 SharpMinute(int c = 0) { return (Now() + c * 60) / 60 * 60; }
	static UInt64 GetTick();
	static inline void forceWeekDay(UInt8 wd) { _GS()._weekDay = wd; }
	static inline UInt8 MonthDay() {return _GS()._monthDay;}
	static inline UInt8 Month() {return _GS()._month;}
	static inline UInt8 TestMonthDay() { return _GS()._testMonthDay; }
	static inline void forceMonth(UInt8 m) { _GS()._month = m;}
	static inline void forceMonthDay(UInt8 md) { _GS()._monthDay = md;}
private:
	TimeUtil();
	bool _Update();
	static inline TimeUtil& _GS()
	{
		static TimeUtil tu;
		return tu;
	}
	UInt32 _now;
	UInt32 _thisDay;
	UInt32 _nextDay;
	UInt8 _weekDay;
	UInt8 _monthDay;
	UInt8 _month;
	UInt8 _testMonthDay;
	static UInt32 _tzone;
};

#endif // _TIMEUTIL_H_

