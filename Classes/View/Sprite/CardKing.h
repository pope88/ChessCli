#include "CardBase.h"

class CardKing : public CardBase
{
public:
	CardKing(UInt8 cValue, UInt8 color);
	virtual ~CardKing();
	virtual void drawCard();
	virtual void clearCard();
private:
	void setCardHuaP();
	void setCardGrainP();
private:
	CCSprite *pSpriteHua;
	CCSprite *pSpriteGrain;  //back ground

};