#ifndef _LOGGER_H_
#define _LOGGER_H_

namespace System
{

#ifdef _WIN32
#ifdef _MSC_VER
#define localtime_r(t,m)                   localtime_s(m,t)
#else
#define localtime_r(t,m)                   *m = *localtime(t)
#endif
#endif

enum LogLevel
{
	LogFatal = 0,
	LogError,
	LogInfo,
	LogDebug,
	LogTrace,
};

class Logger
{
public:
	Logger(const char * filename = NULL);
	~Logger();
	void reopen(struct tm&);
	Logger& prolog(LogLevel ll);
	template <typename T>
	inline Logger& operator<<(const T& val)
	{
		*_ostr << val;
		return *this;
	}
private:
	std::string _filename;
	int _lastDay;
	std::ostream * _ostr;
	bool _isFirst;
};

}

#endif // _LOGGER_H_
