#ifndef _CCARD_H_
#define _CCARD_H_


struct CCardsType
{
public:
	CCardsType()
	{
		m_nTypeBomb = 0;
		m_nTypeNum = 0;
		m_nTypeValue = 0;
	}
	void SetValue(int nBomb, int nNum, int nValue)
	{
		m_nTypeBomb = nBomb;
		m_nTypeNum = nNum;
		m_nTypeValue = nValue;
	}
public:
	int m_nTypeBomb;	// 0:不是炸弹 1:软炸弹 2:硬炸弹
	int m_nTypeNum;		//牌的数量
	int m_nTypeValue;	//牌的值
};

class CCard
{
public:
	CCard() : m_nColor(-1), m_nValue(-1) {}
	CCard(int nColor, int nValue) : m_nColor(nColor), m_nValue(nValue) {}
	CCard (const CCard &srcCard)
	{
		if(this == &srcCard)
			return;
		m_nColor = srcCard.m_nColor;
		m_nValue = srcCard.m_nValue;
	}
	CCard& operator = (const CCard &srcCard)
	{
		if (this == &srcCard)
			return *this;
		m_nColor = srcCard.m_nColor;
		m_nValue = srcCard.m_nValue;
		return *this;
	}
	bool operator == (const CCard &srcCard)
	{
		return (m_nColor == srcCard.m_nColor && m_nValue == srcCard.m_nValue);
	}
public:
	char m_nColor;  //花色,-1表示没有任意花色
	char m_nValue;  //数值,-1表示还没有牌
};

#endif