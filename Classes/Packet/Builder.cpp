#include "Config.h"
#include "Builder.h"
#include "../TcpNetwork/TcpNet.h"
#include "../Worker/Tcp.h"
#include "Handler/Handler.h"

namespace Packet
{
void Builder::send()
{
	if (stream.get() != NULL || pack())
	{
		Worker::_tcp.sendMsg(&(*stream)[0], static_cast<int>(stream->size()));
	}
}

const std::string& Builder::data()
{
	static const std::string empty;
	if (stream.get() != NULL || pack())
	{
		return *stream.get();
	}
	return empty;
}

bool Builder::pack()
{
	std::string *s = new(std::nothrow) std::string(20, 0);
	if (s == NULL)
	{
		return false;
	}
	//stream.reset(s);
	//*((UInt16*)&((*s)[4])) =  op;
	//packContent();
	//size_t sz = s->size() - 6;
	//memcpy(&(*s)[0], &sz, 3);
	
	stream.reset(s);
	//*((UInt16*)&((*s)[4])) =  op;

	packContent();
	size_t sz = s->size() - 20;
	packhead.Setop(op);
	packhead.Setlen(sz);
	packhead.SetCliid(123);
	packhead.SetSvrid(321);
	packhead.PackBuffer(reinterpret_cast<uint8_t*>(&(*s)[0]) );

	return true;
}

bool Builder::repack()
{
	return pack();
}
}