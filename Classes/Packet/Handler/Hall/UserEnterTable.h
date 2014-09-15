#include "../../View/Table/Table.h"
HANDLER_CLASS(UserEnterTable, 0x07)
{
	if (pkt.HasRes())
	{
		if (pkt.Res() == 0)
		{
			std::vector<View::PlayerInfo> pInfo;
			View::_table.onPlayerEnter(pInfo);
		}
	}
	else
	{
		View::_table.onOhterPlayerEnter();
	}
}
HANDLER_END(UserEnterTable)
