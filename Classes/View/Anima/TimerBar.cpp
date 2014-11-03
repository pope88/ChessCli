
#include "Config.h"
#include "TimeBar.h"
#include "../Table/Table.h"

namespace View
{
	TimerBar::TimerBar(): _timeElapsed(0), _totalSeconds(10), _secondsLeft(0), _pathLength(0), _timePct(0.0), _pos(0xFF)
	{
		LS_P_INIT(bar);
		LS_P_INIT(underStroke);
		LS_P_INIT(glowOutStroke);
		LS_P_INIT(gradientPill);
		LS_P_INIT(timerLabel);
		LS_P_INIT(ribbon);
	
		memset(_segments, 0.0, sizeof(_segments));
	}
	TimerBar::~TimerBar()
	{
		LS_P_RELEASE(bar);
		LS_P_RELEASE(underStroke);
		LS_P_RELEASE(glowOutStroke);
		LS_P_RELEASE(gradientPill);
		LS_P_RELEASE(timerLabel);
		LS_P_RELEASE(ribbon);
	}

	bool TimerBar::init()
	{
		if (!Node::init())
			return false;

		_clockColor = gimmyColor(GREEN, 3);
		//CCScale9Sprite
		auto glowBounds = CCRectMake(0,0,86,68);
		auto glowCenter = CCRectMake(34,18,18,32);
		auto gradientBounds = CCRectMake(0,0,54,33);
		auto gradientCenter = CCRectMake(18,2,18,29);
		
		cocos2d::extension::Scale9Sprite *understroke = cocos2d::extension::Scale9Sprite::create(s_pPathTimeGlowTable, glowBounds, glowCenter);
		setunderStroke(understroke);
		addChild(getunderStroke());
		getunderStroke()->setColor(ccc3(0x5c, 0xff, 0x00));


		cocos2d::extension::Scale9Sprite *glowoutstroke = cocos2d::extension::Scale9Sprite::create(s_pPathTimeGlowTable,glowBounds, glowCenter);
		setglowOutStroke(glowoutstroke);
		addChild(getglowOutStroke());

		MotionStreak *ribbon = MotionStreak::create(100, 0.5, 10, ccc3(66, 66, 66), s_pPathTimeWite);
		setribbon(ribbon);
		addChild(getribbon(), 10);

		cocos2d::extension::Scale9Sprite *gradientpill = cocos2d::extension::Scale9Sprite::create(s_pPathTimeGradient, gradientBounds, gradientCenter);
		setgradientPill(gradientpill);
		addChild(getgradientPill(), 20);

		LabelTTF *timerlabel = LabelTTF::create("", "LubalinGraphStd-Medium", 28);
		settimerLabel(timerlabel);
        gettimerLabel()->setPosition(0, 0);

		if (true)  //
		{
			gettimerLabel()->setAnchorPoint(Point(0.5, 0.5));
		}
		else
		{
			gettimerLabel()->setAnchorPoint(Point(0.5, 0.7));
		}
		addChild(gettimerLabel(), 30);
		gettimerLabel()->setString("fuck you");

		return true;
	}

	RepeatForever* TimerBar::makePulseAction()
	{
		auto pulseIn = FadeIn::create(0.3);
	    auto pulseOut = FadeOut::create(0.3); 
		return RepeatForever::create(Sequence::createWithTwoActions(pulseIn, pulseOut));
	}

    Color3B TimerBar::gimmyColor(const UInt8 c[], UInt8 n)
	{
		return ccc3(c[0], c[1], c[2]);
    }

	UInt8 TimerBar::inTerp(UInt8 c0, UInt8 c1, float c2)
	{
		return c0 + c2*(c1-c0);
    }

    Color3B TimerBar::gimmyInterpolatedColor(const UInt8 *c0, const UInt8 *c1, float c2)
	{
		return ccc3(inTerp(c0[0], c1[0], c2), inTerp(c0[1], c1[1], c2), inTerp(c0[2],c1[2], c2));
	}

	void TimerBar::update(float dt)
	{
		std::stringstream ss;
		ss<<timecout;
		timecout++;
		gettimerLabel()->setString(ss.str());
		_timeElapsed += dt;
		getglowOutStroke()->runAction(makePulseAction());
		float timePct  = (float)_timeElapsed  / (_totalSeconds) ;
		if (timePct < YELLOW_START)
		{
			_clockColor = gimmyColor(GREEN, 3);
		}
		else if(timePct < YELLOW_FINISH)
		{
			_clockColor = gimmyInterpolatedColor(GREEN, YELLOW, (timePct-YELLOW_START) / (YELLOW_FINISH - YELLOW_START) );
		}
		else if (timePct < RED_START)
		{
			_clockColor = gimmyColor(YELLOW,3);
		}
		else if (timePct < RED_FINISH)
		{
			_clockColor = gimmyInterpolatedColor(YELLOW, RED, (timePct-RED_START) / (RED_FINISH - RED_START) );
		}
		else if (timePct < 1)
		{
			_clockColor = gimmyColor(RED,3);
		}
	//	_pathLength 

		 float _x = 0;
		 float xLoc = 0.0;
		 float yLoc = 0.0;
		 _x = _pathLength *timePct;
		if (_x < _segments[0])
		{
			xLoc = _x;
			yLoc = 0;
		}
		else if (_x < _segments[1])
		{
			float segmentLoc = _x - _segments[0];
			float theta = segmentLoc/(_pathSize.height/2);
			xLoc = sin(theta) * (_pathSize.height/2) + _pathSize.width/2;
			yLoc = cos(theta) * (_pathSize.height/2) - _pathSize.height/2;
		}
		else if(_x < _segments[2])
		{
			xLoc = _pathSize.width/2 - (_x-_segments[1]);
		    yLoc = -_pathSize.height;
		}
		else if(_x < _segments[3])
		{
			float segmentLoc = _x - _segments[2];
			float theta = segmentLoc/(_pathSize.height/2);
			xLoc = -sin(theta) * (_pathSize.height/2) - _pathSize.width/2;
			yLoc = -cos(theta) * (_pathSize.height/2) - _pathSize.height/2;
		}
		else if (_x < _segments[4])
		{
			float segmentLoc = _x - _segments[3];
			xLoc = -_pathSize.width/2 + segmentLoc;
			yLoc = 0;
		}
		else
		{
			return;
		}


		getunderStroke()->setColor(_clockColor);
		getglowOutStroke()->setColor(_clockColor);
		getgradientPill()->setColor(_clockColor);
		gettimerLabel()->setColor(_clockColor);


		getribbon()->setPosition(Point(xLoc, yLoc) );

		if (_timeElapsed >= _totalSeconds)
		{
			View::_table.onTimer(_totalSeconds, _pos);
			_timeElapsed = 0;
			_totalSeconds = 0;
			this->unscheduleUpdate();
		}
	}

	void TimerBar::startTimer(UInt8 time, UInt8 pos)
	{
		_pos = pos;
		_totalSeconds = time;
		this->scheduleUpdate();

		_secondsLeft = time;
		_currentTimerLabel = "5000000";//util.formatChipAmount(TableTools.getPlayersBySeat(pb_table_state)[pb_table_state.speaking].stack);
       if (_totalSeconds == 0)
       {
		   _timePct = 0;
       }
	   else
	   {
		   _timePct = _secondsLeft/_totalSeconds;
	   }
		
		gettimerLabel()->setString(_currentTimerLabel);
		auto timeSize = gettimerLabel()->getContentSize();

		auto timerContentWidth = timeSize.width;
		auto timerContentHeight = timeSize.height;
		getunderStroke()->setContentSize(timeSize);

		auto tx = gettimerLabel()->getPositionX();
		auto ty = gettimerLabel()->getPositionY();
		getunderStroke()->setPosition(tx, ty);

		getglowOutStroke()->setContentSize(timeSize);
		getglowOutStroke()->setPosition(tx, ty);
		getglowOutStroke()->stopAllActions();
		getglowOutStroke()->setOpacity(0);

		getgradientPill()->setContentSize(timeSize);
		getgradientPill()->setPosition(tx, ty);

		_pathSize = Size(timerContentWidth, timerContentHeight);
		getribbon()->setPosition(Point(tx, ty+_pathSize.height/2));
		_pathLength = _pathSize.width*2 + M_PI * _pathSize.height;

		_segments[0] = _pathSize.width / 2;
		_segments[1] = _segments[0] + (_pathSize.height/2)*M_PI;
		_segments[2] = _segments[1] + _pathSize.width;
		_segments[3] = _segments[2] + (_pathSize.height/2)*M_PI;
		_segments[4] = _segments[3] + _pathSize.width/2;
	}

}

