#include "Config.h"
#include "Base.h"

#include "System/ThreadLocalPtr.h"
#include "System/File.h"
#include "../SsCfg.h"

namespace Worker
{

System::ThreadLocalPtr<SimpleBase> localWorker;


SimpleBase::SimpleBase(): _running(false), _thread(NULL), _logger(NULL), _random(NULL)
{

}

SimpleBase::~SimpleBase()
{
	if(_thread)
		delete _thread;
	if(_random)
		delete _random;
	if(_logger)
		delete _logger;
}

void SimpleBase::start()
{
	_thread = new System::Thread(&SimpleBase::run, this);
	_thread->Launch();
}

void SimpleBase::join()
{
	_thread->Wait();
}

void SimpleBase::stop()
{
	_running = false;
}

void SimpleBase::run()
{
	_random = new System::Random();
	const char * logFilename = getLogFilename();
	if(logFilename == NULL)
		_logger = new System::Logger();
	else
	{
		System::File f(sSCfg.logPath);
		f.createDirectories();
		_logger = new System::Logger((sSCfg.logPath + "/" + logFilename).c_str());
	}
	localWorker = this;
	_running = true;
	loop();
	_running = false;
}

SimpleBase& SimpleBase::current()
{
	return *localWorker;
}

UInt32 SimpleBase::getRandom( )
{
	return current()._random->next();
}

double SimpleBase::getRandomF()
{
	return current()._random->nextDouble();
}

System::Logger& SimpleBase::getLogger(System::LogLevel ll)
{
	return current()._logger->prolog(ll);
}

System::Random& SimpleBase::getRandomizer()
{
	return *current()._random;
}

//Base::Base(): _evBase(NULL)
//{
//}
//
//Base::~Base()
//{
//	std::for_each(_timers.begin(), _timers.end(), [](const std::pair<int, WorkerTimerData *>& p) {delete p.second;});
//}
//
//void Base::loop()
//{
//	_evBase = event_base_new();
//	if(init())
//	{
//		event_base_loop(_evBase, 0);
//	}
//	uninit();
//	for(std::unordered_map<int, WorkerTimerData *>::iterator it = _timers.begin(); it != _timers.end(); ++ it)
//	{
//		event_del(it->second->ev);
//		event_free(it->second->ev);
//		delete it->second;
//	}
//	_timers.clear();
//	event_base_free(_evBase);
//}
//
//void Base::_onTimer( socket_t, short, void * param )
//{
//	WorkerTimerData * wtd = static_cast<WorkerTimerData *>(param);
//	if(!wtd->worker->_running)
//	{
//		event_base_loopbreak(wtd->worker->_evBase);
//		return;
//	}
//	if(wtd->nextInt)
//	{
//		UInt32 interval = wtd->nextInt;
//		wtd->nextInt = 0;
//		struct timeval tv = {static_cast<long>(interval / 1000), static_cast<long>((interval % 1000) * 1000)};
//		event_assign(wtd->ev, wtd->worker->_evBase, -1, EV_PERSIST, _onTimer, wtd);
//		event_add(wtd->ev, &tv);
//	}
//	wtd->worker->onTimer(wtd->id, wtd->data);
//}
//
//bool Base::addTimer( int id, UInt32 interval, UInt32 firstInterval, void * data )
//{
//	if(_timers.find(id) != _timers.end())
//		return false;
//	WorkerTimerData *wtd = new(std::nothrow) WorkerTimerData;
//	if(wtd == NULL)
//		return false;
//	wtd->worker = this;
//	wtd->id = id;
//	wtd->data = data;
//	if(firstInterval)
//	{
//		wtd->ev = event_new(_evBase, -1, 0, _onTimer, wtd);
//		if(wtd->ev == NULL)
//		{
//			delete wtd;
//			return false;
//		}
//		_timers[id] = wtd;
//		wtd->nextInt = interval;
//		struct timeval tv = {static_cast<long>(firstInterval / 1000), static_cast<long>((firstInterval % 1000) * 1000)};
//		event_add(wtd->ev, &tv);
//	}
//	else
//	{
//		wtd->ev = event_new(_evBase, -1, EV_PERSIST, _onTimer, wtd);
//		if(wtd == NULL)
//		{
//			delete wtd;
//			return false;
//		}
//		_timers[id] = wtd;
//		wtd->nextInt = 0;
//		struct timeval tv = {static_cast<long>(interval / 1000), static_cast<long>((interval % 1000) * 1000)};
//		event_add(wtd->ev, &tv);
//	}
//	return true;
//}
//
//bool Base::delTimer( int id )
//{
//	std::unordered_map<int, WorkerTimerData *>::iterator it = _timers.find(id);
//	if(it == _timers.end())
//		return false;
//
//	event_del(it->second->ev);
//	event_free(it->second->ev);
//	delete it->second;
//
//	_timers.erase(it);
//
//	return true;
//}

}
