#ifndef _TIMERBAR_H_
#define _TIMERBAR_H_
#include "cocos2d.h"
#include "CCScale9Sprite.h"
#include "../PreConfig.h"

USING_NS_CC;


namespace View
{

    static const float YELLOW_START = 1 - 0.75;
    static const float	 YELLOW_FINISH = 1 - 0.60;
    static const float	 RED_START = 1 - 0.40;
    static const float	 RED_FINISH = 1 - 0.25;
	static const std::string  s_pPathTimeGlowTable = "Images/Ftable/white_pill_glow_tablet.png";
	static const std::string  s_pPathTimeGradient = "Images/Ftable/black_pill_gradient_tablet.png";
	static const std::string  s_pPathTimeWite = "Images/white.png";

	static const UInt8 GREEN[3] = {0x5c, 0xff, 0x00};
	static const UInt8 YELLOW[3] = {0xff,0xf7,0x00};
	static const UInt8 RED[3] = {0xff, 0x1e, 0x00};
	static UInt32 timecout = 0;

	class TimerBar : public Node
	{
	public:
		CREATE_FUNC(TimerBar);
		TimerBar();
		~TimerBar();
		bool init();
		void stopTimer();
		void update(float dt);
	    RepeatForever* makePulseAction();
		static Color3B gimmyColor(const UInt8 c[], UInt8 n);
		static UInt8 inTerp(UInt8 c0, UInt8 c1, float c2);
		static Color3B gimmyInterpolatedColor(const UInt8 *c0, const UInt8 *c1, float c2);
		void startTimer(UInt8 time);
	protected:
	private:
		UInt32 _timeElapsed;
		UInt32 _totalSeconds;
		UInt32 _secondsLeft;
		UInt32 _pathLength;
		Size _pathSize;
		float _timePct;
		std::string _currentTimerLabel;
		Color3B _clockColor;
		LS_PROPERTY_RETAIN(Sprite*, bar, bar);
		LS_PROPERTY_RETAIN(cocos2d::extension::Scale9Sprite*, underStroke, underStroke);
		LS_PROPERTY_RETAIN(cocos2d::extension::Scale9Sprite*, glowOutStroke, glowOutStroke);
		LS_PROPERTY_RETAIN(cocos2d::extension::Scale9Sprite*, gradientPill, gradientPill);
	
		LS_PROPERTY_RETAIN(LabelTTF*, timerLabel, timerLabel);
		LS_PROPERTY_RETAIN(MotionStreak*, ribbon, ribbon);
	    float _segments[5];
		//ccc3();
	};
}
#endif // !
