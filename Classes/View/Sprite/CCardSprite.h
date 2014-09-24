#ifndef _CCARDSPRITE_H_
#define _CCARDSPRITE_H_
#include "CardNormal.h"
#include "CardGeneral.h"
#include "CardKing.h"
#include "../../Common/CCard.h"
#include "../PreConfig.h"

class CCardSprite : public CCard, public CCNode
{
public:
	CREATE_FUNC2(CCardSprite, int, int);
	CCardSprite() :CCard(), cardSprite(NULL) {}
	CCardSprite(int nColor, int nValue) : CCard(nColor, nValue)
	{
		if ((m_nValue >= 3 && m_nValue <= 10) || m_nValue == 14 || m_nValue == 15 )
		{
			cardSprite = CardNormal::create(m_nValue, m_nColor);
		}
		else if (m_nValue>= 11 && m_nValue<= 13)
		{
			cardSprite = CardGeneral::create(m_nValue, m_nColor);
		}
		else if (m_nValue == 16 || m_nValue == 17)
		{
			cardSprite = CardKing::create(m_nValue, m_nColor);
		}
	}

	bool CCardSprite::init()
	{
		if (!CCNode::init())
		{
			return false;
		}
		if (cardSprite != NULL)
		{
			this->addChild(cardSprite);
		}
		return true;
	}

	CCardSprite (const CCardSprite &srcCard)
	{
		if(this == &srcCard)
			return;
		m_nColor = srcCard.m_nColor;
		m_nValue = srcCard.m_nValue;
		cardSprite = srcCard.cardSprite;
	}
	CCardSprite& operator = (const CCardSprite &srcCard)
	{
		if (this == &srcCard)
			return *this;
		m_nColor = srcCard.m_nColor;
		m_nValue = srcCard.m_nValue;
		cardSprite = srcCard.cardSprite;
		return *this;
	}
	bool operator == (const CCardSprite &srcCard)
	{
		return (m_nColor == srcCard.m_nColor && m_nValue == srcCard.m_nValue && cardSprite == srcCard.cardSprite);
	}
public:
	void clearCard()
	{
		if (cardSprite != NULL)
		{
			cardSprite->clearCard();
		}
		if (this->getParent() != NULL)
		{
			this->getParent()->removeChild(this, true);
		}
	}
public:
	char m_nColor;  //花色,-1表示没有任意花色
	char m_nValue;  //数值,-1表示还没有牌
private:
	CardBase *cardSprite;
};

#endif