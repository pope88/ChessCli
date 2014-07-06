#ifndef _WORKER_BASE_H_
#define _WORKER_BASE_H_

#include "System/Logger.h"
#include "System/Thread.h"
#include "System/Random.h"

struct event_base;
struct event;

namespace Worker
{

class SimpleBase
{
public:
	SimpleBase();
	virtual ~SimpleBase();

	void start();
	void join();
	void stop();

public:
	static SimpleBase& current();
	static UInt32 getRandom();
	static double getRandomF();
	static System::Logger& getLogger(System::LogLevel);
	static inline UInt32 getRandom(UInt32 modulo) { return getRandom() % modulo; }
	static inline UInt32 getRandom(UInt32 a, UInt32 b) { return getRandom() % (b - a + 1) + a; }
	static System::Random& getRandomizer();

protected:
	virtual void loop() = 0;
	virtual const char * getLogFilename() { return NULL; }
	void run();

protected:
	bool _running;
	System::Thread * _thread;
	System::Logger * _logger;
	System::Random * _random;
};

//class Base: public SimpleBase
//{
//public:
//	Base();
//	virtual ~Base();
//
//	bool addTimer(int, UInt32, UInt32 = 0, void * = NULL);
//	bool delTimer(int);
//
//protected:
//	virtual bool init() { return true; }
//	virtual void uninit() {}
//	virtual void loop();
//	virtual void onTimer(int, void *) {}
//
//protected:
//	struct event_base * _evBase;
//
//private:
//	static void _onTimer(socket_t, short, void *);
//
//private:
//	std::unordered_map<int, WorkerTimerData *> _timers;
//};

#define Rand ::Worker::SimpleBase::getRandom
#define RandF ::Worker::SimpleBase::getRandomF
#define Randomizer ::Worker::SimpleBase::getRandomizer
#define LOG(n) ::Worker::SimpleBase::getLogger(System::Log##n)

}

#endif // _WORKER_BASE_H_
