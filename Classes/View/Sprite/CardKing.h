#include "CardBase.h"

class CardKing : public CardBase
{
public:
	CardKing(UInt8 cValue, UInt8 color);
	virtual ~CardKing();
	virtual bool init();
	virtual void drawCard();
	virtual void clearCard();
private:
	void setCardHuaP();
	void setCardGrainP();
private:
	Sprite *pSpriteHua;
	Sprite *pSpriteGrain;  //back ground

};