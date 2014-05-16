#ifndef _CARDBASE_H_
#define _CARDBASE_H_

#include "cocos2d.h"
USING_NS_CC;
class CardBase : public Node//, public TargetedTouchDelegate
{
public:
	CardBase(UInt8 cValue, UInt8 color); //card value , card color
	virtual ~CardBase();
public:
	virtual void drawCard();
	virtual void clearCard();
	inline Sprite* getCardBackGround() { return backGround; }
	inline UInt8 getCardValue() { return cardValue; }
	inline UInt8 getCardColor() { return cardColor; }
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(Touch* touch, Event* event);
	virtual void ccTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void ccTouchEnded(Touch *pTouch, Event *pEvent);
protected:
	Sprite *backGround;
	Sprite *shadow;
protected:
	UInt8 cardValue;
	UInt8 cardColor;
};

#endif