#ifndef _HANDLER_H_
#define _HANDLER_H_
#include "SsuObject.h"
namespace Packet
{
	class Handler;


	class PacketHead : public ::ssu::Object
	{
	public:
		inline PacketHead(): _op(0), _len(0), _cliid(0), _svrid(0) {}
		virtual ~PacketHead() { }

	public:
		virtual unsigned char * PackBuffer(unsigned char * buf)
		{
			buf = ::ssu::Utils::PackFixed32Tag(buf, 1, _op);
			buf = ::ssu::Utils::PackFixed32Tag(buf, 2, _len);
			buf = ::ssu::Utils::PackFixed32Tag(buf, 3, _cliid);
			buf = ::ssu::Utils::PackFixed32Tag(buf, 4, _svrid);
			return buf;
		}
		virtual bool UnpackBuffer(const unsigned char *& buf, size_t& leftSize)
		{
			unsigned int tag_; unsigned char type_;
			while(leftSize > 0)
			{
				if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_))
					return false;
				switch(tag_)
				{
				case 1:
					if(!::ssu::Utils::UnpackFixed32(buf, leftSize, _op))
						return false;
					break;
				case 2:
					if(!::ssu::Utils::UnpackFixed32(buf, leftSize, _len))
						return false;
					break;
				case 3:
					if(!::ssu::Utils::UnpackFixed32(buf, leftSize, _cliid))
						return false;
					break;
				case 4:
					if(!::ssu::Utils::UnpackFixed32(buf, leftSize, _svrid))
						return false;
					break;
				default: break;
				}
			}
			return true;
		}
		virtual size_t Size() const
		{
			return 1 + ::ssu::Utils::SizeFixed32(_op) + 1 + ::ssu::Utils::SizeFixed32(_len) + 1 + ::ssu::Utils::SizeFixed32(_cliid) + 1 + ::ssu::Utils::SizeFixed32(_svrid);
		}

	public:
		inline unsigned int Getop() const { return _op; }
		inline void Setop( int op) { _op = op; }

		inline unsigned int Getlen() const { return _len; }
		inline void Setlen(int len) { _len = len; }

		inline unsigned int Getcliid() const { return _cliid; }
		inline void SetCliid(int chiid) { _cliid = chiid; }

		inline unsigned int Getsvrid() const { return _svrid; }
		inline void SetSvrid(int svrid) { _svrid = svrid; }
	protected:
		int _op;
		int _len;
		int _cliid;
		int _svrid;
	};
	static PacketHead packhead;

	struct HandlerMsgHeader
	{
		Handler *handler;
		UInt32 size;
	};

	struct HandlerMsgInit
	{
		HandlerMsgHeader hdr;
		UInt32 sessionId;
		UInt32 fromGateway;
		UInt32 remoteAddr;
	};

	struct HandlerMsgPlayer
	{
		HandlerMsgHeader hdr;
		union
		{
			//Object::Player * player;
			struct
			{
				UInt32 playerId;
				UInt16 op;
			} gateway;
		};
	};

	class Handler
	{
	public:
		inline Handler(UInt16 op, UInt8 type);
		virtual void handle(HandlerMsgHeader *) = 0;
	};

	template<class T, class DT, UInt16 HOP, UInt8 TF = 1>
	class HandlerT: public Handler
	{
	public: HandlerT<T, DT, HOP, TF>() : Handler(HOP, T) {}
	protected:
		virtual void handle(HandlerMsgHeader * hdr)
		{
			DT pktObj;
			if (pktObj.unpack(UInt8*)hdr + static_cast<T*>(this)->getDataBufferSize(), hdr->size)
			{
				static_cast<T *>(this)->process(pktObj, hdr);
			}
		}
	};

#define  HANDLER_CLASS(n, o) \
	namespace Packet { \
	class Handler##n: public HandlerT<Handler##n, SC##n##o, o> \
	{ \
	public: \
	inline size_t getDataBuffSize() { return sizeof(HandlerMsgPlayer); } \
	inline void process(SC##n##_##o &pkt, HandlerMsgHeader *hdr) \
	{ \
	    Object::Player *player = ((HandlerMsgPlayer *)hdr)->player; \
	    if(player == NULL) return; \


#define  HANDLER_CLASS_INIT(n, o) \
	namespace Packet { \
	class Handler##n: public Handler<Handler##n, SC##n##_##o, o, 2> \
	{ \
	public:\
	inline size_t getDataBuffSize() { return sizeof(HandlerMsgInit); } \
	inline void process(SC##n##_##o &pkt, HandlerMsgHeader *hdr) \
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
#endif