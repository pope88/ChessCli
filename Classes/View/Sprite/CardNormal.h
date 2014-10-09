#ifndef _CARDNORMAL_H_
#define _CARDNORMAL_H_

#include "CardBase.h"

class CardNormal : public CardBase
{
public:
	CardNormal(UInt8 cValue, UInt8 color);
	CREATE_FUNC2(CardNormal, UInt8, UInt8);
	virtual ~CardNormal();
	bool init();
	void drawCard(); 
	virtual void clearCard();
private:
	void setCardZiP();
	void setCardHuaP();
	void setCardGrainP();
private:
	LS_PROPERTY_RETAIN(Sprite*, pSpriteZi, pSpriteZi);
	LS_PROPERTY_RETAIN(Sprite*, pSpriteHua, pSpriteHua);
	LS_PROPERTY_RETAIN(Sprite*, pSpriteGrain, pSpriteGrain);

};

#endif // !