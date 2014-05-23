#ifndef _CARDBASE_H_
#define _CARDBASE_H_

#include "cocos2d.h"
USING_NS_CC;
class CardBase : public Node//, public TargetedTouchDelegate
{
	enum 
	{
		BACKGROUND = 1,
	};
public:
	CardBase(UInt8 cValue, UInt8 color); //card value , card color
	virtual ~CardBase();
public:
	virtual void drawCard();
	virtual void clearCard();
	inline UInt8 getCardValue() { return cardValue; }
	inline UInt8 getCardColor() { return cardColor; }
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(Touch* touch, Event* event);
	virtual void ccTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void ccTouchEnded(Touch *pTouch, Event *pEvent);
	//Sprite *shadow;
protected:
	Sprite *backGround;
protected:
	UInt8 cardValue;
	UInt8 cardColor;
};

#endif