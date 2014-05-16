#include "Config.h"
#include "CardKing.h"
#include "../../Utils/MobileLog.h"
#include "../GameResources.h"


CardKing::CardKing(UInt8 cValue, UInt8 color):CardBase(cValue, color), pSpriteHua(NULL), pSpriteGrain(NULL)
{
	drawCard();
}

CardKing::~CardKing()
{
	clearCard();
}

void CardKing::drawCard()
{
	UInt8 _keyValue = 0;

	if (cardValue >= 16 && cardValue <= 17)
	{
		_keyValue = cardValue - 16;
	}
	else
	{
		//Logger
		LOGERROR<<"card Value error";
		return;
	}

	if (cardColor >= 0 && cardColor <= 1)
	{
		//draw card background
		pSpriteGrain = Sprite::createWithSpriteFrameName(s_pNameListKingGrain[cardColor].c_str());
		backGround->addChild(pSpriteGrain);
		setCardGrainP();

		//draw hua
		pSpriteHua = Sprite::createWithSpriteFrameName(s_pNameListKingHua[cardColor].c_str());
		backGround->addChild(pSpriteHua);
		setCardHuaP();
	}
	else
	{
		//Logger
		LOGERROR<<"card Color error";
		return;
	}
}
void CardKing::clearCard()
{

}

void CardKing::setCardHuaP()
{
	if (pSpriteHua)
	{
		pSpriteHua->setAnchorPoint(Point(0, 0));         //set anchor point
		pSpriteHua->setPosition(Point(6, 80));            //set position
	}
}

void CardKing::setCardGrainP()
{
	if (pSpriteGrain)
	{
		pSpriteGrain->setAnchorPoint(Point(0, 0));         //set anchor point
		pSpriteGrain->setPosition(Point(20,0));            //set position
	}
}