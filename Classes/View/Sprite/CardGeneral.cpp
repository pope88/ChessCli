#include "Config.h"
#include "CardGeneral.h"
#include "../../Utils/MobileLog.h"
#include "../GameResources.h"

CardGeneral::CardGeneral(UInt8 cValue, UInt8 color):CardBase(cValue, color)
{
	LS_P_INIT(pSpriteZi);
	LS_P_INIT(pSpriteHua);
	LS_P_INIT(pSpriteGrain);
	init();
}

CardGeneral::~CardGeneral()
{
	LS_P_RELEASE(pSpriteZi);
	LS_P_RELEASE(pSpriteHua);
	LS_P_RELEASE(pSpriteGrain);
}

void CardGeneral::setCardZiP()
{
	if (getpSpriteZi())
	{
		getpSpriteZi()->setAnchorPoint(Point(0, 0));         //set anchor point
		getpSpriteZi()->setPosition(Point(8,125));            //set position
	}
}

void CardGeneral::setCardHuaP()
{
	if (getpSpriteHua())
	{
		getpSpriteHua()->setAnchorPoint(Point(0, 0));         //set anchor point
		getpSpriteHua()->setPosition(Point(6,85));            //set position
	}
}

void CardGeneral::setCardGrainP()
{
	if (getpSpriteGrain())
	{
		getpSpriteGrain()->setAnchorPoint(Point(0, 0));         //set anchor point
		getpSpriteGrain()->setPosition(Point(20,0));            //set position
	}
}


bool CardGeneral::init()
{
	drawCard();
	return  true;
}

void CardGeneral::drawCard()
{
	UInt8 _keyValue = 0;
	UInt8 gid = 0;

	if (cardValue >= 11 && cardValue <= 13)
	{
		_keyValue = cardValue-1;

		gid = cardValue-11;
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
		//draw card background
	 	Sprite *pSGrain = Sprite::createWithSpriteFrameName(s_pNameListRedGGrain[gid].c_str());
		setpSpriteGrain(pSGrain);
		getbackGround()->addChild(getpSpriteGrain());
		setCardGrainP();

		Sprite *pSZi = Sprite::createWithSpriteFrameName(s_pNameListNormalCardBlackZi[_keyValue].c_str());
	    setpSpriteZi(pSZi);
		getbackGround()->addChild(getpSpriteZi());
		//set zi position
		setCardZiP();

		//draw hua
		Sprite *pSHua = Sprite::createWithSpriteFrameName(s_pNameListHua[cardColor].c_str());
		setpSpriteHua(pSHua);
		getbackGround()->addChild(getpSpriteHua());
		setCardHuaP();
	}
	else if (cardColor == 1 || cardColor == 3)
	{
		//draw card background
		Sprite *pSGrain = Sprite::createWithSpriteFrameName(s_pNameListBlueGGrain[gid].c_str());
		setpSpriteGrain(pSGrain);
		setCardGrainP();
		getbackGround()->addChild(getpSpriteGrain());

		Sprite *pSZi = Sprite::createWithSpriteFrameName(s_pNameListNormalCardRedZi[_keyValue].c_str());
		setpSpriteZi(pSZi);
		//set zi position
		setCardZiP();
		getbackGround()->addChild(getpSpriteZi());

		//draw hua
		Sprite *pSHua = Sprite::createWithSpriteFrameName(s_pNameListHua[cardColor].c_str());
		setpSpriteHua(pSHua);
		setCardHuaP();
		getbackGround()->addChild(getpSpriteHua());
	}
	else
	{
		LOGERROR<<"card Color error";
	}
}

void CardGeneral::clearCard()
{
	
	this->removeChild(getpSpriteZi(), true);
	this->removeChild(getpSpriteHua(), true);
	this->removeChild(getpSpriteGrain(), true);
	this->removeChild(getbackGround(), true);

	if (this->getParent() != NULL)
	{
		this->getParent()->removeChild(this, true);
	}
}