#include "CardBase.h"
class CardGeneral : public CardBase
{
public:
	CardGeneral(UInt8 cValue, UInt8 color);
	virtual ~CardGeneral();
	virtual void drawCard();
	virtual void clearCard();
private:
	void setCardZiP();
	void setCardHuaP();
	void setCardGrainP();
private:
	Sprite *pSpriteZi;
	Sprite *pSpriteHua;
	Sprite *pSpriteGrain;  //back ground

};