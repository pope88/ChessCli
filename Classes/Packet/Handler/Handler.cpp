
#include "Config.h"
#include "Handler.h"
#include "../Processor.h"
namespace Packet
{
Handler::Handler(UInt16 op, UInt8 type)
{
	Processor::Instance().addHandler(op, type, this);
}

}
