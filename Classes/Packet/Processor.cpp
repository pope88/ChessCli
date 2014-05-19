#include "Config.h"
#include "Processor.h"
#include "Packet/Handler/Handler.h"
#include "../TcpNetwork/TcpNet.h"

namespace Packet
{
Processor _processor;
void decryptPacket(UInt32 key, UInt16& op, UInt32 size, UInt8 * buf)
{
	if(key < 2) return;
	UInt32 newkey = (((key - 2) * 33721) % 65537) % 251;
	UInt32 ch2 = newkey, ch = (ch2 * 97) % 251;
	op ^= (ch << 8) + ch2;
	for(UInt32 i = 0; i < size; ++ i)
	{
		ch = (ch * 97) % 251;
		buf[i] ^= ch;
	}
}

bool Processor::parseInit(UInt8 *evbuf, int len, UInt32 data, UInt32 addr)
{
	if (len < PACKETHEADLEN)
	{
		return false;
	}

	UInt8 hdr[10] = {0};
	memcpy((char*)&hdr, evbuf, PACKETHEADLEN);
	Packet::packhead.Unpack(hdr, PACKETHEADLEN);

	UInt32 sz = Packet::packhead.Getlen() & 0x00FFFFFF;
	if(static_cast<int>(sz) + PACKETHEADLEN > len)
		return false;
	UInt32 key = Packet::packhead.Getlen() >> 24;
	HandlerMsgInit * msg = (HandlerMsgInit *)malloc(sz + sizeof(HandlerMsgInit));
	if(msg == NULL)
	{
		//TcpNetWork::_tcpnet.drainDataBuf(sz + 6);
		return true;
	}
	msg->hdr.size = sz;
	msg->sessionId = data;
	msg->fromGateway = 0xFFFFFFFF;
	msg->remoteAddr = addr;
	//TcpNetWork::_TcpNet.drainDataBuf(6);	
	UInt8 *buf = ((UInt8*)msg) + sizeof(HandlerMsgInit);
	//TcpNetWork::_TcpNet.copyDataBuf(buf, sz);
	UInt16 op = Packet::packhead.Getop();
	decryptPacket(key, op, sz, buf);
	Handler * hdl = _initHandlers[op];
	if(hdl == NULL)
	{
		free(msg);
		return true;
	}
	msg->hdr.handler = hdl;
	pushMsg((HandlerMsgHeader *)msg);
	return true;
		
}

void Processor::addHandler(UInt16 op, UInt8 type, Handler *handler)
{
	if (type & 0x1)
	{
		if (_initHandlers.size() < op)
		{
			_initHandlers.resize(op+1);
			_initHandlers[op] = handler;
		}
	}
	else if(type & 0x2)
	{
		if (_playerHandlers.size() < op)
		{
			_playerHandlers.resize(op+1);
			_playerHandlers[op] = handler;
		}
	}
}

void Processor::process()
{

}

}