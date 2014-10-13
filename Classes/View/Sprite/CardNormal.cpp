#include "Config.h"
#include "CardNormal.h"
#include "../../Utils/MobileLog.h"
#include "../GameResources.h"

CardNormal::CardNormal(UInt8 cValue, UInt8 color):CardBase(cValue, color)
{
	LS_P_INIT(pSpriteZi);
	LS_P_INIT(pSpriteHua);
	LS_P_INIT(pSpriteGrain);
}

CardNormal::~CardNormal()
{
	LS_P_RELEASE(pSpriteZi);
	LS_P_RELEASE(pSpriteHua);
	LS_P_RELEASE(pSpriteGrain);
}

bool CardNormal::init()
{
	if (!CardBase::init())
		return false;
	drawCard();
	return true;
}

void CardNormal::setCardZiP()
{
	if (getpSpriteZi() != NULL)
	{
		getpSpriteZi()->setAnchorPoint(Point(0, 0));         //set anchor point
		getpSpriteZi()->setPosition(Point(8,55));            //set position
	}
}

void CardNormal::setCardHuaP()
{
	if (getpSpriteHua() != NULL)
	{
		getpSpriteHua()->setAnchorPoint(Point(0, 0));         //set anchor point
		getpSpriteHua()->setPosition(Point(6,85));            //set position
	}
}

void CardNormal::setCardGrainP()
{
	if (getpSpriteGrain() != NULL)
	{
		getpSpriteGrain()->setAnchorPoint(Point(0, 0));         //set anchor point
		getpSpriteGrain()->setPosition(Point(25,30));           //set position
	}
}

void CardNormal::drawCard()
{
	UInt8 _keyValue = 0;
	if (cardValue >= 3 && cardValue <= 10)
	{
		_keyValue = cardValue - 1;
	}
	else if (cardValue >= 14 && cardValue <= 15)
	{
		_keyValue = cardValue - 14;
	}
	else
	{
		//Logger
		LOGERROR<<"card Value error";
		return;

	}
	//draw card zi
	if (cardColor == 0 || cardColor == 2)
	{
		Sprite* pZi = Sprite::createWithSpriteFrameName(s_pNameListNormalCardBlackZi[_keyValue].c_str());
		setpSpriteZi(pZi);
		getbackGround()->addChild(getpSpriteZi());
		
		//set zi position
		setCardZiP();
	}
	else if (cardColor == 1 || cardColor == 3)
	{
		Sprite* pZi = Sprite::createWithSpriteFrameName(s_pNameListNormalCardRedZi[_keyValue].c_str());
		setpSpriteZi(pZi);
		getbackGround()->addChild(getpSpriteZi());
		
		//set zi position
		setCardZiP();
	}
	else
	{
		LOGERROR<<"card Color error";
	}

	if (cardColor >= 0 && cardColor <= 3)
	{
		//draw hua
		Sprite* spHua = Sprite::createWithSpriteFrameName(s_pNameListHua[cardColor].c_str());
		setpSpriteHua(spHua);
		setCardHuaP();
		getbackGround()->addChild(getpSpriteHua());

		//draw card background
		Sprite *spGrain = Sprite::createWithSpriteFrameName(s_pNameListNormalGrain[cardColor].c_str());
	    setpSpriteGrain(spGrain);
		setCardGrainP();
		getbackGround()->addChild(spGrain);
	}
	else
	{
		//Logger
		LOGERROR<<"card Color error";
		return;
	}
}

void CardNormal::clearCard()
{
	getbackGround()->removeChild(getpSpriteZi(), true);
	getbackGround()->removeChild(getpSpriteHua(), true);
	getbackGround()->removeChild(getpSpriteGrain(), true);
	removeChild(getbackGround(), true);
	if (this->getParent() != NULL)
	{
		this->getParent()->removeChild(this, true);
	}
}