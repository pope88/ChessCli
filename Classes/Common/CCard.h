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
	int m_nTypeBomb;	// 0:����ը�� 1:��ը�� 2:Ӳը��
	int m_nTypeNum;		//�Ƶ�����
	int m_nTypeValue;	//�Ƶ�ֵ
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
	char m_nColor;  //��ɫ,-1��ʾû�����⻨ɫ
	char m_nValue;  //��ֵ,-1��ʾ��û����
};

#endif