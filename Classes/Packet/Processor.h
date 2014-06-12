#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_
#include "System/MsgQueue.h"
#include "cocos2d.h"
namespace Packet
{
	struct HandlerMsgHeader;
	class Handler;
	class Processor: public cocos2d::Node, public System::MsgQueue<HandlerMsgHeader *>
	{
	public:
		Processor()
		{
			this->onEnter();
			this->onEnterTransitionDidFinish();
			this->scheduleUpdate();
		}

		~Processor()
		{
			this->onExit();
		}

		static Processor& Instance()
		{
			static Processor _processor;
			return _processor;
		}


	public:
		bool parseInit(UInt8 *evbuf,  int len, UInt32 data, UInt32 addr);
		//bool parsePlayer(evbuffer *, Object::Player *) {}
		//bool parseGateway(evbuffer *, UInt32) {}
		//void pushDisconnect(UInt32, Object::Player *) {}
		void pushGatewayDisconnect(UInt32) {}
		void process();
		void processGatewayMsg(HandlerMsgHeader *) {}
		void addHandler(UInt16 op, UInt8 type, Handler * handler);
		void update(float delta);

	private:
		std::vector<Handler *> _initHandlers;
		std::vector<Handler *> _playerHandlers;
		int niub;
	};

}
#endif