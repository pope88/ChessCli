#include "Config.h"
#include "CardGeneral.h"
#include "../../Utils/MobileLog.h"
#include "../GameResources.h"

CardGeneral::CardGeneral(UInt8 cValue, UInt8 color):CardBase(cValue, color),pSpriteZi(NULL), pSpriteHua(NULL), pSpriteGrain(NULL)
{
	drawCard();
}

CardGeneral::~CardGeneral()
{
	clearCard();
}

void CardGeneral::setCardZiP()
{
	if (pSpriteZi)
	{
		pSpriteZi->setAnchorPoint(Point(0, 0));         //set anchor point
		pSpriteZi->setPosition(Point(8,125));            //set position
	}
}

void CardGeneral::setCardHuaP()
{
	if (pSpriteHua)
	{
		pSpriteHua->setAnchorPoint(Point(0, 0));         //set anchor point
		pSpriteHua->setPosition(Point(6,85));            //set position
	}
}

void CardGeneral::setCardGrainP()
{
	if (pSpriteGrain)
	{
		pSpriteGrain->setAnchorPoint(Point(0, 0));         //set anchor point
		pSpriteGrain->setPosition(Point(20,0));            //set position
	}
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
		pSpriteGrain = Sprite::createWithSpriteFrameName(s_pNameListRedGGrain[gid].c_str());
		backGround->addChild(pSpriteGrain);
		setCardGrainP();

		pSpriteZi = Sprite::createWithSpriteFrameName(s_pNameListNormalCardBlackZi[_keyValue].c_str());
		backGround->addChild(pSpriteZi);
		//set zi position
		setCardZiP();

		//draw hua
		pSpriteHua = Sprite::createWithSpriteFrameName(s_pNameListHua[cardColor].c_str());
		backGround->addChild(pSpriteHua);
		setCardHuaP();
	}
	else if (cardColor == 1 || cardColor == 3)
	{
		//draw card background
		pSpriteGrain = Sprite::createWithSpriteFrameName(s_pNameListBlueGGrain[gid].c_str());
		setCardGrainP();
		backGround->addChild(pSpriteGrain);

		pSpriteZi = Sprite::createWithSpriteFrameName(s_pNameListNormalCardRedZi[_keyValue].c_str());
		//set zi position
		setCardZiP();
		backGround->addChild(pSpriteZi);

		//draw hua
		pSpriteHua = Sprite::createWithSpriteFrameName(s_pNameListHua[cardColor].c_str());
		setCardHuaP();
		backGround->addChild(pSpriteHua);
	}
	else
	{
		LOGERROR<<"card Color error";
	}
}

void CardGeneral::clearCard()
{
	this->removeChild(pSpriteZi, true);
	this->removeChild(pSpriteHua, true);
	this->removeChild(pSpriteGrain, true);
}