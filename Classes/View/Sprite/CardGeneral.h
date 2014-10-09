#ifndef _CARDGENERAL_H_
#define _CARDGENERAL_H_


#include "CardBase.h"
class CardGeneral : public CardBase
{
public:
	CardGeneral(UInt8 cValue, UInt8 color);
	CREATE_FUNC2(CardGeneral, UInt8, UInt8);
	virtual ~CardGeneral();
	virtual bool init();
	virtual void drawCard();
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