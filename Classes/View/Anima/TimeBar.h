#ifndef _TIMERBAR_H_
#define _TIMERBAR_H_
#include "cocos2d.h"
#include "CCScale9Sprite.h"
USING_NS_CC;


namespace View
{

    static const float YELLOW_START = 1 - 0.75;
    static const float	 YELLOW_FINISH = 1 - 0.60;
    static const float	 RED_START = 1 - 0.40;
    static const float	 RED_FINISH = 1 - 0.25;
	static const std::string  s_pPathTimeGlowTable = "Images/Ftable/white_pill_glow_tablet.png";
	static const std::string  s_pPathTimeGradient = "Images/Ftable/black_pill_gradient_tablet.png";
	static const std::string  s_pPathTimeWite = "Images/White.png";

	static const UInt8 GREEN[3] = {0x5c, 0xff, 0x00};
	static const UInt8 YELLOW[3] = {0xff,0xf7,0x00};
	static const UInt8 RED[3] = {0xff, 0x1e, 0x00};

	class TimerBar : public Node
	{
	public:
		CREATE_FUNC(TimerBar);
		TimerBar();
		void stopTimer();
		void update(float dt);
	    RepeatForever* makePulseAction();
		static Color3B gimmyColor(const UInt8 c[], UInt8 n);
		static UInt8 inTerp(UInt8 c0, UInt8 c1, float c2);
		static Color3B gimmyInterpolatedColor(const UInt8 *c0, const UInt8 *c1, float c2);
		void reInit(UInt8 time);
	protected:
	private:
		UInt32 _timeElapsed;
		UInt32 _totalSeconds;
		UInt32 _secondsLeft;
		UInt32 _pathLength;
		float _timePct;
		std::string _currentTimerLabel;
		Color3B _clockColor;
		Sprite *bar;
	    cocos2d::extension::Scale9Sprite *_underStroke;
		cocos2d::extension::Scale9Sprite *_glowOutStroke;
		cocos2d::extension::Scale9Sprite *_gradientPill;
		LabelTTF *_timerLabel;
		MotionStreak *_ribbon;
	    float _segments[5];
		//ccc3();
	};
}
#endif // !
