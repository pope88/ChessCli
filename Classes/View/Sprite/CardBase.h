#ifndef _CARDBASE_H_
#define _CARDBASE_H_

#include "cocos2d.h"
USING_NS_CC;
#include "../PreConfig.h"
class CardBase : public Node
{
	enum 
	{
		BACKGROUND = 1,
	};
public:
	CardBase(UInt8 cValue, UInt8 color); //card value , card color
	virtual ~CardBase();
	CREATE_FUNC2(CardBase, UInt8, UInt8);
public:
	virtual bool init();
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
	LS_PROPERTY_RETAIN(Sprite*, backGround, backGround);
protected:
	UInt8 cardValue;
	UInt8 cardColor;
};

#endif 