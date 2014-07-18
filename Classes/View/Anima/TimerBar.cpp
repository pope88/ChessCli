
#include "Config.h"
#include "TimeBar.h"

namespace View
{
	TimerBar::TimerBar(): _timeElapsed(0), _totalSeconds(10), _secondsLeft(0), _timePct(0.0)
	{
		_clockColor = gimmyColor(GREEN, 3);
		//CCScale9Sprite
		auto glowBounds = CCRectMake(0,0,86,68);
		auto glowCenter = CCRectMake(34,18,18,32);
	    auto gradientBounds = CCRectMake(0,0,54,34);
		auto gradientCenter = CCRectMake(18,2,18,30);
		_underStroke = cocos2d::extension::Scale9Sprite::create(s_pPathTimeGlowTable, glowBounds, glowCenter);
		addChild(_underStroke);
        _underStroke->setColor(ccc3(0x5c, 0xff, 0x00));


		_glowOutStroke = cocos2d::extension::Scale9Sprite::create(s_pPathTimeGlowTable,glowBounds, glowCenter);
		addChild(_glowOutStroke);

		_ribbon = MotionStreak::create(100, 5, 1, ccc3(66, 66, 66), s_pPathTimeWite);
		addChild(_ribbon, 10);

		_gradientPill = cocos2d::extension::Scale9Sprite::create(s_pPathTimeGradient, gradientBounds, gradientCenter);
		addChild(_gradientPill, 20);

		_timerLabel = LabelTTF::create("", "LubalinGraphStd-Medium", 28);
        _timerLabel:setPosition(0, 0);

		if (true)  //
		{
			_timerLabel->setAnchorPoint(Point(0.5, 0.5));
		}
		else
		{
			_timerLabel->setAnchorPoint(Point(0.5, 0.7));
		}
		addChild(_timerLabel, 30);
		_timerLabel->setString("fuck you");

		this->scheduleUpdate();

		reInit(20);
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
		_timerLabel->setString(ss.str());
		_timeElapsed += dt*60;
		_glowOutStroke->runAction(makePulseAction());
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


		_underStroke->setColor(_clockColor);
		_glowOutStroke->setColor(_clockColor);
		_gradientPill->setColor(_clockColor);
		_timerLabel->setColor(_clockColor);


		_ribbon->setPosition(Point(xLoc, yLoc) );
	}

	void TimerBar::reInit(UInt8 time)
	{
		_totalSeconds = time;
		_secondsLeft = time;
		_currentTimerLabel = "";
		_currentTimerLabel = "500";//util.formatChipAmount(TableTools.getPlayersBySeat(pb_table_state)[pb_table_state.speaking].stack);
        _timePct = _secondsLeft/_totalSeconds;
		_timerLabel->setString(_currentTimerLabel);
		auto timeSize = _timerLabel->getContentSize();

		auto timerContentWidth = timeSize.width;
		auto timerContentHeight = timeSize.height;
		_underStroke->setContentSize(timeSize);

		auto tx = _timerLabel->getPositionX();
		auto ty = _timerLabel->getPositionY();
		_underStroke->setPosition(tx, ty);

		_glowOutStroke->setContentSize(timeSize);
		_glowOutStroke->setPosition(tx, ty);
		_glowOutStroke->stopAllActions();
		_glowOutStroke->setOpacity(0);

		_gradientPill->setContentSize(timeSize);
		_gradientPill->setPosition(tx, ty);

		_pathSize = Size(timerContentWidth, timerContentHeight);
		_ribbon->setPosition(Point(tx, ty+_pathSize.height/2));
		_pathLength = _pathSize.width*2 + M_PI * _pathSize.height;

		_segments[0] = _pathSize.width / 2;
		_segments[1] = _segments[0] + (_pathSize.height/2)*M_PI;
		_segments[2] = _segments[1] + _pathSize.width;
		_segments[3] = _segments[2] + (_pathSize.height/2)*M_PI;
		_segments[4] = _segments[3] + _pathSize.width/2;
	}
}

