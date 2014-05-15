#include "Config.h"
#include "Logger.h"
#include <fstream>

namespace System
{

	Logger::Logger( const char * filename /*= NULL*/ ) : _filename(filename), _lastDay(-1), _ostr(NULL), _isFirst(true)
	{
	}

	Logger::~Logger()
	{
		if(_ostr != &std::cout)
			delete _ostr;
	}

	Logger& Logger::prolog( LogLevel ll )
	{
		time_t t = time(NULL);
		tm aTm;
		localtime_r(&t, &aTm);
		if(aTm.tm_mday != _lastDay)
		{
			reopen(aTm);
			_lastDay = aTm.tm_mday;
		}
		char fmtStr[512];
		snprintf(fmtStr, sizeof(fmtStr), " [%02d:%02d:%02d] ", aTm.tm_hour, aTm.tm_min, aTm.tm_sec);
		static const char * typeStrFromLogLevel[] = {"[FATAL]", "[ERROR]", "[INFO ]", "[DEBUG]", "[TRACE]"};
		if(_isFirst)
			_isFirst = false;
		else
			*_ostr << std::endl;
		*_ostr << typeStrFromLogLevel[ll] << fmtStr;
		return *this;
	}

	void Logger::reopen(struct tm& aTm)
	{
		if(_ostr != NULL && _ostr != &std::cout)
			delete _ostr;
		if(_filename.empty())
			_ostr = &std::cout;
		else
		{
			char vfn[256];
			snprintf(vfn, sizeof(vfn), "%s_%02d%02d%02d.log", _filename.c_str(), aTm.tm_year - 100, aTm.tm_mon + 1, aTm.tm_mday);
			try
			{
				_ostr = new std::ofstream(vfn, std::ios_base::app | std::ios_base::out);
			}
			catch(...)
			{}
		}
	}

}
