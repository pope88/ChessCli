#include "Config.h"
#include "CardKing.h"
#include "../../Utils/MobileLog.h"
#include "../GameResources.h"


CardKing::CardKing(UInt8 cValue, UInt8 color):CardBase(cValue, color)
{
	init();
}

CardKing::~CardKing()
{
	clearCard();
}

bool CardKing::init()
{
	drawCard();
	return true;
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
		Sprite *pSGrain = Sprite::createWithSpriteFrameName(s_pNameListKingGrain[cardColor].c_str());
		setpSpriteGrain(pSGrain);
		getbackGround()->addChild(getpSpriteGrain());
		setCardGrainP();

		//draw hua
		Sprite *pSHua = Sprite::createWithSpriteFrameName(s_pNameListKingHua[cardColor].c_str());
		setpSpriteHua(pSHua);
		getbackGround()->addChild(getpSpriteHua());
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
	getbackGround()->removeChild(getpSpriteHua(), true);
	getbackGround()->removeChild(getpSpriteGrain(), true);
	removeChild(getbackGround(), true);

	if (this->getParent() != NULL)
	{
		this->getParent()->removeChild(this, true);
	}
}

void CardKing::setCardHuaP()
{
	if (getpSpriteHua())
	{
		getpSpriteHua()->setAnchorPoint(Point(0, 0));         //set anchor point
		getpSpriteHua()->setPosition(Point(6, 80));            //set position
	}
}

void CardKing::setCardGrainP()
{
	if (getpSpriteGrain())
	{
		getpSpriteGrain()->setAnchorPoint(Point(0, 0));         //set anchor point
		getpSpriteGrain()->setPosition(Point(20,0));            //set position
	}
}