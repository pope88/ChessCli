#ifndef _HANDLER_H_
#define _HANDLER_H_

#include "Packet/PacketsCtoS.h"

namespace Object
{
	class Player;
}


namespace Packet
{

	using namespace game::net::data::CtoS;
	class Handler;

	struct HandlerMsgHeader
	{
		HandlerMsgHeader():handler(NULL), size(0){}
		Handler *handler;
		UInt32 size;
	};

	struct HandlerMsgGPlayer
	{
		HandlerMsgHeader hdr;
		union
		{
			Object::Player *player;
			struct
			{
				UInt32 gpId;
				UInt16 op;
			}gateway;
		};
	};

	struct HandlerMsgPlayer
	{
		HandlerMsgHeader hdr;
		union
		{
			Object::Player * player;
			struct
			{
				UInt32 pId;
				UInt16 op;
			} gateway;
		};
	};


	struct HandlerMsgInit
	{
		HandlerMsgInit():sessionId(0), fromGateway(0), remoteAddr(0)
		{
		}
		HandlerMsgHeader hdr;
		UInt32 sessionId;
		UInt32 fromGateway;
		UInt32 remoteAddr;
	};

	class Handler
	{
	public:
		inline Handler() {}
		Handler(UInt16, UInt8);
		virtual void handle(HandlerMsgHeader *) = 0;
	};

	template<class T, class DT, UInt16 HOP, UInt8 TF = 1>
	class HandlerT: public Handler
	{
	public:
		HandlerT<T, DT, HOP, TF>(): Handler(HOP, TF) {}
	protected:
		virtual void handle(HandlerMsgHeader * hdr)
		{
			DT pktObj;
			if(pktObj.Unpack((UInt8 *)hdr + static_cast<T *>(this)->getDataBufferSize(), hdr->size))
				static_cast<T *>(this)->process(pktObj, hdr);
		}
	};

}

#define HANDLER_CLASS(n, o) \
	namespace Packet { \
class Handler##n: public HandlerT<Handler##n, CS##n##_##o, o> \
{ \
public: \
	inline size_t getDataBufferSize() { return sizeof(HandlerMsgPlayer); } \
	inline void process(CS##n##_##o& pkt, HandlerMsgHeader * hdr) \
{ \
	Object::Player * player = ((HandlerMsgPlayer *)hdr)->player; \
	if(player == NULL) return; \

//#define HANDLER_CLASS_GPLAYER(n, o) \
//	namespace Packet { \
//class Handler##n: public HandlerT<Handler##n, CS##n##_##o, o, 2> \
//{ \
//public: \
//	inline size_t getDataBufferSize() { return sizeof(HandlerMsgGPlayer); } \
//	inline void process(CS##n##_##o& pkt, HandlerMsgHeader * hdr) \
//{ \
//	Object::GPlayer * gplayer = ((HandlerMsgGPlayer *)hdr)->gplayer; \
//	if(gplayer == NULL) return; \


#define HANDLER_CLASS_INIT(n, o) \
	namespace Packet { \
class Handler##n: public HandlerT<Handler##n, CS##n##_##o, o, 3> \
{ \
public: \
	inline size_t getDataBufferSize() { return sizeof(HandlerMsgInit); } \
	inline void process(CS##n##_##o& pkt, HandlerMsgHeader * hdr) \
{ \
	HandlerMsgInit * msgInit__ = (HandlerMsgInit *)hdr; \
	UInt32 sessionId = msgInit__->sessionId; \
	UInt32 gatewayId = msgInit__->fromGateway; \
	UInt32 remoteAddr = msgInit__->remoteAddr; \

#define MSG_QUERY_ARGS(at, av)

#define HANDLER_END(n) \
} \
}; \
	static Handler##n __static_initializer_##n; \
}

#endif // _HANDLER_H_
