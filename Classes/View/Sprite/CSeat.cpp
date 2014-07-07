#include "Config.h"
#include "CSeat.h"
#include "../GameResources.h"
namespace View
{
	CSeat::CSeat()
	{
		auto pBGround = CCSprite::create(s_pPathSeat);
		addChild(pBGround);
	}

}