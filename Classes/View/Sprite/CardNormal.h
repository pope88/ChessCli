#include "CardBase.h"

class CardNormal : public CardBase
{
public:
	CardNormal(UInt8 cValue, UInt8 color);
	virtual ~CardNormal();
	virtual void drawCard(); 
	virtual void clearCard();
private:
	void setCardZiP();
	void setCardHuaP();
	void setCardGrainP();
private:
	Sprite *pSpriteZi;
	Sprite *pSpriteHua;
	Sprite *pSpriteGrain;

};