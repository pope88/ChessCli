#include "CardBase.h"

class CardNormal : public CardBase
{
public:
	CardNormal(UInt8 cValue, UInt8 color);
	CREATE_FUNC2(CardNormal, UInt8, UInt8);
	virtual ~CardNormal();
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