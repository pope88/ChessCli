#include "Config.h"
#include "TimeUtil.h"

#ifndef _WIN32
#include <sys/time.h>
#endif

UInt32 TimeUtil::_tzone = 0;

UInt64 TimeUtil::GetTick()
{
#ifdef _WIN32
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	ULARGE_INTEGER epoch; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
	epoch.LowPart  = 0xD53E8000;
	epoch.HighPart = 0x019DB1DE;

	ULARGE_INTEGER ts;
	ts.LowPart  = ft.dwLowDateTime;
	ts.HighPart = ft.dwHighDateTime;
	ts.QuadPart -= epoch.QuadPart;
	return ts.QuadPart / 10;
#else
	struct timeval tv;
	if(gettimeofday(&tv, NULL))
		return 0;
	return tv.tv_sec * 1000000 + tv.tv_usec;
#endif
}

TimeUtil::TimeUtil()
{
	tzset();
#if defined(__FreeBSD__)
	time_t tloc;
	struct tm result;
	tloc = time(NULL);
	_tzone = static_cast<UInt32>(localtime_r(&tloc, &result)->tm_gmtoff);
#else
	_tzone = static_cast<UInt32>(timezone);
#endif
	_nextDay = SharpDay(0, static_cast<UInt32>(time(NULL)));
	_Update();
	_testMonthDay = _monthDay;
}

bool TimeUtil::_Update()
{
	_now = static_cast<UInt32>(time(NULL));
	if(_now < _nextDay)
		return false;
	UInt32 days = (_now - _nextDay) / 86400;
	_thisDay = _nextDay + days * 86400;
	_nextDay = _thisDay + 86400;
	time_t curtime1 = _now;
	struct tm *local = localtime(&curtime1);
	_weekDay = static_cast<UInt8>(local->tm_wday);
	_monthDay =  static_cast<UInt8>(local->tm_mday);
	_month = static_cast<UInt8>(local->tm_mon);
	return true;
}
