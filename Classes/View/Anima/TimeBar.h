#ifndef _TIMERBAR_H_
#define _TIMERBAR_H_
#include "cocos2d.h"
USING_NS_CC;

static const std::string  s_pPathTimerBar = 
namespace View
{
	class TimerBar : public Node
	{
	public:
		void stopTimer();
		void update();
		void init();
	protected:
	private:
		Sprite *bar;
		ccc3()
	};
}
#endif // !
