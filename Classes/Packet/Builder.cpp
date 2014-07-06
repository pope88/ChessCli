#include "Config.h"
#include "Builder.h"
#include "Worker/Tcp.h"
#include "PacketHead.h"

namespace Packet
{
	
	void Builder::send()
	{
		if (stream.get() != NULL || pack())
		{
			TcpNetWork::_tcpnet.sendMsg(&(*stream)[0], static_cast<int>(stream->size()));
		}
	}

	void Builder::sendMulti(void *multi)
	{
		//if(stream.get() != NULL || pack())
		//	Worker::tcp.sendMulti(multi, stream);
	}


	void Builder::sendNolock(Player *player)
	{
		//if (player->online())
		//{
		//	sendNolock(player->sessionId(), player->gatewayId());
		//}
	}

	//void Builder::sendNolock(Object::GPlayer *gplayer)
	//{
	//	if (gplayer->online())
	//	{
	//		sendNolock(gplayer->sessionId(), gplayer->gatewayId());
	//	}
	//}

	void Builder::sendNolock(UInt32 sid, UInt32 gid)
	{
		//if (gid == 0xFFFFFFFF)
		//{
		//	_isGateWay = false;
		//}
		//if (stream.get() != NULL || pack())
		//{
		//	Worker::tcp.sendNolock(sid, gid, stream);
		//}
	}

	void Builder::sendLock()
	{
		//Worker::tcp.sendLock();
	}

	void Builder::sendUnlock()
	{
		//Worker::tcp.sendLock();
	}


	bool Builder::repack()
	{
		return pack();
	}

	bool Builder::pack()
	{
		if (_isGateWay)
		{
			std::string *s = new (std::nothrow) std::string(6, 0);
			if (s == NULL)
			{
				return false;
			}
			stream.reset(s);
			*(UInt16*)&((*s)[4]) = op; 
			packContent();
			size_t sz = s->size() - 6;
			memcpy(&(*s)[0], &sz, 3);
			return true;
		}
		else
		{
			std::string *s = new(std::nothrow) std::string(10, 0);
			if (s == NULL)
			{
				return false;
			}
			stream.reset(s);
			//*((UInt16*)&((*s)[4])) =  op;
			packContent();
			size_t sz = s->size() - 10;
			packhead.Setop(op);
			packhead.Setlen(sz);
			packhead.PackBuffer(reinterpret_cast<uint8_t*>(&((*s)[0])) );
			return true;
		}
	}

	const std::string& Builder::data()
	{
		static std::string empty;
		if (stream.get() != NULL || pack())
		{
			return *stream.get();
		}
		return empty;
	}
}