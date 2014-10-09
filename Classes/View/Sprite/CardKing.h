#ifndef _CARDKING_H_
#define _CARDKING_H_

#include "CardBase.h"

class CardKing : public CardBase
{
public:
	CardKing(UInt8 cValue, UInt8 color);
	virtual ~CardKing();
	bool init();
	void drawCard();
	void clearCard();
private:
	void setCardHuaP();
	void setCardGrainP();
private:
	LS_PROPERTY_RETAIN(Sprite*, pSpriteHua, pSpriteHua);
	LS_PROPERTY_RETAIN(Sprite*, pSpriteGrain, pSpriteGrain);
};

#endif // !