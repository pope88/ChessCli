#ifndef _CARDBASE_H_
#define _CARDBASE_H_

#include "cocos2d.h"
USING_NS_CC;
class CardBase : public CCNode, public CCTargetedTouchDelegate
{
public:
	CardBase(UInt8 cValue, UInt8 color); //card value , card color
	virtual ~CardBase();
public:
	virtual void drawCard();
	virtual void clearCard();
	inline CCSprite* getCardBackGround() { return backGround; }
	inline UInt8 getCardValue() { return cardValue; }
	inline UInt8 getCardColor() { return cardColor; }
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
protected:
	CCSprite *backGround;
	CCSprite *shadow;
protected:
	UInt8 cardValue;
	UInt8 cardColor;
};

#endif