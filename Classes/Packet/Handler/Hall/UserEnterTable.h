#include "../../View/Table/Table.h"
HANDLER_CLASS(UserEnterTable, 0x07)
{
	if (pkt.HasRes())
	{
		if (pkt.Res() == 0)
		{
			std::vector<View::PlayerInfo> pInfo;

			for (size_t i = 0; i < pkt.PlayerinfosSize(); ++i)
			{
				View::PlayerInfo pi;
				pi.chairid = pkt.Playerinfos(i).Chairid();
				pi.nickname = pkt.Playerinfos(i).Nickname();
				pi.allchips = pkt.Playerinfos(i).Allchips();
				pInfo.push_back(pi);
			}

			View::_table.onPlayerEnter(pInfo);

		}
	}
	else
	{
		View::PlayerInfo pi;
		pi.chairid = pkt.Playerinfos(0).Chairid();
		pi.nickname = pkt.Playerinfos(0).Nickname();
		pi.allchips = pkt.Playerinfos(0).Allchips();

		View::_table.onOhterPlayerEnter(pi);
	}
}
HANDLER_END(UserEnterTable)
