#ifndef _TIMERBAR_H_
#define _TIMERBAR_H_
#include "cocos2d.h"
#include "CCScale9Sprite.h"
USING_NS_CC;

static const std::string  s_pPathTimeGlowTable = "Images/Ftable/white_pill_glow_tablet.png";
static const std::string  s_pPathTimeGradient = "Images/Ftable/black_pill_gradient_tablet.png";
static const std::string  s_pPathTimeWite = "Images/White.png";
namespace View
{
	class TimerBar : public Node
	{
	public:
		CREATE_FUNC(TimerBar);
		TimerBar();
		void stopTimer();
		void update();
	protected:
	private:
		Sprite *bar;
	    cocos2d::extension::Scale9Sprite  *_underStroke;
		//ccc3();
	};
}
#endif // !
