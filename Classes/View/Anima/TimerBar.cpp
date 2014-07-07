#include "Config.h"
#include "TimeBar.h"

namespace View
{
	TimerBar::TimerBar()
	{
		//CCScale9Sprite
		auto glowBounds = CCRectMake(0,0,86,68);
		auto glowCenter = CCRectMake(34,18,18,32);
		_underStroke = cocos2d::extension::Scale9Sprite::create(s_pPathTimeGlowTable,glowBounds, glowCenter);
		addChild(_underStroke);
	}


}