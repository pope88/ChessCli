#ifndef _MOBILELOG_H_
#define _MOBILELOG_H_
#include "System/Logger.h"
#include "Singleton.h"
namespace Utils
{
	class MobileLog
	{
	public:
		MobileLog()
		{
			if(_log == NULL)  
			{
				_log = new System::Logger("/log/mobile");
			}
		}
	   ~MobileLog() 
		{ 
			if(_log != NULL)
				delete _log;
		}
	public:
		System::Logger* getLog() { return _log; }
	private:
		DECLARE_SINGLETON_CLASS(MobileLog);
	private:
		System::Logger *_log;
	};
	typedef Singleton<MobileLog> _gamemanager;
}

#define LOGFATAL Utils::_gamemanager::instance()->getLog()->prolog(System::LogFatal)
#define LOGERROR Utils::_gamemanager::instance()->getLog()->prolog(System::LogError)
#define LOGDEBUG Utils::_gamemanager::instance()->getLog()->prolog(System::LogDebug)
#define LOGINFO  Utils::_gamemanager::instance()->getLog()->prolog(System::LogInfo)
#define LOGTRACE Utils::_gamemanager::instance()->getLog()->prolog(System::LogTrace)
#endif