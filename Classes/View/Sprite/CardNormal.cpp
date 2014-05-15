#include "Config.h"
#include "CardNormal.h"
#include "../../Utils/MobileLog.h"
#include "../GameResources.h"

CardNormal::CardNormal(UInt8 cValue, UInt8 color):CardBase(cValue, color),pSpriteZi(NULL), pSpriteHua(NULL), pSpriteGrain(NULL)
{
	drawCard();
}

CardNormal::~CardNormal()
{
	clearCard();
}

void CardNormal::setCardZiP()
{
	if (pSpriteZi)
	{
		pSpriteZi->setAnchorPoint(CCPoint(0, 0));         //set anchor point
		pSpriteZi->setPosition(CCPoint(8,125));            //set position
	}
}

void CardNormal::setCardHuaP()
{
	if (pSpriteHua)
	{
		pSpriteHua->setAnchorPoint(CCPoint(0, 0));         //set anchor point
		pSpriteHua->setPosition(CCPoint(6,85));            //set position
	}
}

void CardNormal::setCardGrainP()
{
	if (pSpriteGrain)
	{
		pSpriteGrain->setAnchorPoint(CCPoint(0, 0));         //set anchor point
		pSpriteGrain->setPosition(CCPoint(40,30));            //set position
	}
}

void CardNormal::drawCard()
{
	UInt8 _keyValue = 0;
	if (cardValue >= 3 && cardValue <= 10)
	{
		_keyValue = cardValue-1;
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
		pSpriteZi = CCSprite::createWithSpriteFrameName(s_pNameListNormalCardBlackZi[_keyValue].c_str());
		backGround->addChild(pSpriteZi);
		//set zi position
		setCardZiP();


	}
	else if (cardColor == 1 || cardColor == 3)
	{
		pSpriteZi = CCSprite::createWithSpriteFrameName(s_pNameListNormalCardRedZi[_keyValue].c_str());
		backGround->addChild(pSpriteZi);
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
		pSpriteHua = CCSprite::createWithSpriteFrameName(s_pNameListHua[cardColor].c_str());
		setCardHuaP();
		backGround->addChild(pSpriteHua);

		//draw card background
		pSpriteGrain = CCSprite::createWithSpriteFrameName(s_pNameListNormalGrain[cardColor].c_str());
		setCardGrainP();
		backGround->addChild(pSpriteGrain);
	}
	else
	{
		//Logger
		LOGERROR<<"card Color error";
		return;
	}
	
	addChild(shadow);
}
void CardNormal::clearCard()
{
	this->removeChild(pSpriteZi, true);
	this->removeChild(pSpriteHua, true);
	this->removeChild(pSpriteGrain, true);
}