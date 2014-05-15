
#include "Config.h"
#include "Handler.h"
#include "../Processor.h"
namespace Packet
{
Handler::Handler(UInt16 op, UInt8 type)
{
	_processor.addHandler(op, type, this);
}

}
