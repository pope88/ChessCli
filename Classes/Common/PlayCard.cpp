/*
CopyRight(c)2006 by Banding,Shanghai, All Right Reserved.

@Date:	        2009/4/20
@Created:	    10:37
@Filename: 		PlayCard.cpp
@File path:		BDLeyoyoV2\DDZV2\Common 
@Author:		leiliang

@Description:	�������ݽṹ,Ŀǰ����������ͬ��ͨ�����������ѡ����
�����㷨Ϊ�ϱ�����٣����׶������ڿ���ģʽƥ���㷨�Ľ�
*/

#include "Config.h"
#include "PlayCard.h"
#include "Rule.h"

template<class T> 
inline const T& (min)(const T& _Left, const T& _Right)
{	// return smaller of _Left and _Right using _Pred
	return _Left < _Right ? _Right : _Left;
}


CPlayCards::CPlayCards()
{
	NewRound();
}

CPlayCards::~CPlayCards()
{
}

// �ͻ�������ϴ�ƣ�����С˳����
void CPlayCards::CleanUp()
{
    for(size_t i = 0; i < m_cCards.size(); i++)
    {
        for(size_t j = i+1; j < m_cCards.size(); j++)
        {
            int nIValue = m_cCards[i].m_nValue;
            if (nIValue == m_nBaoValue)
            {
                nIValue = 20;
            }
            int nJValue = m_cCards[j].m_nValue;
            if (nJValue == m_nBaoValue)
            {
                nJValue = 20;
            }
            if( (nIValue * 4 + m_cCards[i].m_nColor) < (nJValue * 4 + m_cCards[j].m_nColor))
            {
                std::swap(m_cCards[i], m_cCards[j]);
            }
        }
    }
}
void CPlayCards::SortByValue()     //Ϊ��˳�ӣ���˳����˳
{
    //�Ȱ�ʵ�ʴ�С����
    for(size_t i = 0; i < m_cChoosingCards.size(); i++)
    {
        for(size_t j = i+1; j < m_cChoosingCards.size(); j++)
        {
            int nIValue = m_cChoosingCards[i].m_nValue;

            int nJValue = m_cChoosingCards[j].m_nValue;

            if( (nIValue * 4 + m_cChoosingCards[i].m_nColor) > (nJValue * 4 + m_cChoosingCards[j].m_nColor))
            {
                std::swap(m_cChoosingCards[i], m_cChoosingCards[j]);
            }
        }
    }

    //��������������
    int nScanTable[MAXTYPENUM];
    memset(nScanTable, 0, sizeof(nScanTable));
    for(size_t i = 0; i < m_cChoosingCards.size(); i++)
    {
        if(m_cChoosingCards[i].m_nValue > 0 && m_cChoosingCards[i].m_nValue < 17)
        {
            nScanTable[m_cChoosingCards[i].m_nValue]++;
        }
    }

    VECCARD vecCard;
    //�����С����һ��,�ȳ����
    if(nScanTable[17] == 2)
    {
        for(size_t i = 0; i < m_cCards.size(); i++)
        {
            if(m_cChoosingCards[i].m_nValue == 17)
            {
                vecCard.push_back(m_cChoosingCards[i]);
            }
        }
        nScanTable[17] = 0;
    }

    if(nScanTable[16] == 2)
    {
        for(size_t i = 0; i < m_cCards.size(); i++)
        {
            if(m_cChoosingCards[i].m_nValue == 16)
            {
                vecCard.push_back(m_cChoosingCards[i]);
            }
        }
        nScanTable[16] = 0;
    }

    //���γ�ȡ8��7��6��5��4,3,2,1����
    for(int k = 4; k > 0; k--)
    {
        for(int i = 3; i <=17; i++)
        {
            if(nScanTable[i] == k)		//������������
            {
                for(size_t j = 0; j < m_cChoosingCards.size(); j++)
                {
                    if(m_cChoosingCards[j].m_nValue == i)
                    {
                        vecCard.push_back(m_cChoosingCards[j]);
                    }
                }
                nScanTable[i] = 0;
            }
        }
    }
    m_cChoosingCards = vecCard;
}
void CPlayCards::SortByLValue()      //Ϊ�����ƴ�����ʾbug���ӵ�
{
     //�Ȱ�ʵ�ʴ�С����
    for(size_t i = 0; i < m_cChoosingCards.size(); i++)
    {
        for(size_t j = i+1; j < m_cChoosingCards.size(); j++)
        {
            int nIValue = m_cChoosingCards[i].m_nValue;

            int nJValue = m_cChoosingCards[j].m_nValue;

            if( (nIValue * 4 + m_cChoosingCards[i].m_nColor) < (nJValue * 4 + m_cChoosingCards[j].m_nColor))
            {
                std::swap(m_cChoosingCards[i], m_cChoosingCards[j]);
            }
        }
    }

    //��������������
    int nScanTable[MAXTYPENUM];
    memset(nScanTable, 0, sizeof(nScanTable));
    for(size_t i = 0; i < m_cChoosingCards.size(); i++)
    {
        if(m_cChoosingCards[i].m_nValue > 0 && m_cChoosingCards[i].m_nValue < 17)
        {
            nScanTable[m_cChoosingCards[i].m_nValue]++;
        }
    }

    VECCARD vecCard;
    //�����С����һ��,�ȳ����
    if(nScanTable[16] == 2)
    {
        for(size_t i = 0; i < m_cCards.size(); i++)
        {
            if(m_cChoosingCards[i].m_nValue == 16)
            {
                vecCard.push_back(m_cChoosingCards[i]);
            }
        }
        nScanTable[16] = 0;
    }

    //���γ�ȡ4,3,2,1����
    for(int k = 4; k > 0; k--)
    {
        for(int i = 16; i >= 3; i--)
        {
            if(nScanTable[i] == k)		//������������
            {
                for(size_t j = 0; j < m_cChoosingCards.size(); j++)
                {
                    if(m_cChoosingCards[j].m_nValue == i)
                    {
                        vecCard.push_back(m_cChoosingCards[j]);
                    }
                }
                nScanTable[i] = 0;
            }
        }
    }
    m_cChoosingCards = vecCard;
}
void CPlayCards::SortChoosingCards()
{
    //�Ȱ�ʵ�ʴ�С����
	for(size_t i = 0; i < m_cChoosingCards.size(); i++)
	{
		for(size_t j = i+1; j < m_cChoosingCards.size(); j++)
		{
			int nIValue = m_cChoosingCards[i].m_nValue;
			if (nIValue == m_nBaoValue)
			{
				nIValue = 20;
			}
			int nJValue = m_cChoosingCards[j].m_nValue;
			if (nJValue == m_nBaoValue)
			{
				nJValue = 20;
			}
			if( (nIValue * 4 + m_cChoosingCards[i].m_nColor) < (nJValue * 4 + m_cChoosingCards[j].m_nColor))
			{
				std::swap(m_cChoosingCards[i], m_cChoosingCards[j]);
			}
		}
	}
}

// �ͻ�������ϴ�ƣ���4��3��2��1��
void CPlayCards::CleanUp2()
{	
	int nScanTable[MAXTYPENUM];
	memset(nScanTable, 0, sizeof(nScanTable));
	for(size_t i = 0; i < m_cCards.size(); i++)
	{
		if(m_cCards[i].m_nValue > 0 && m_cCards[i].m_nValue < 17)
		{
			nScanTable[m_cCards[i].m_nValue]++;
		}
	}

	VECCARD vecCard;
	//�����С����һ��,�ȳ����
	if(nScanTable[16] == 2)
	{
		for(size_t i = 0; i < m_cCards.size(); i++)
		{
			if(m_cCards[i].m_nValue == 16)
			{
				vecCard.push_back(m_cCards[i]);
			}
		}
		nScanTable[16] = 0;
	}

	//���γ�ȡ4,3,2,1����
	for(int k = 4; k > 0; k--)
	{
		for(int i = 16; i >= 3; i--)
		{
			if(nScanTable[i] == k)		//������������
			{
				for(size_t j = 0; j < m_cCards.size(); j++)
				{
					if(m_cCards[j].m_nValue == i)
					{
						vecCard.push_back(m_cCards[j]);
					}
				}
				nScanTable[i] = 0;
			}
		}
	}

	m_cCards = vecCard;
}

void CPlayCards::EraseCards(VECCARD& vecCards)
{
	for(size_t i = 0; i < vecCards.size(); i++)
	{
		for(size_t j = 0; j < m_cCards.size(); j++)
		{
			if(m_cCards[j] == vecCards[i])
			{
				m_cCards.erase(m_cCards.begin()+j);
				break;
			}
		}
	}
}

//�ж��Ƿ��ǵ�˳(������),�˺����ʺ�5-12�������; 
int CPlayCards::IsSeries()
{
	//if(m_dwRule & RULESERIES)
	//	return 0;

	int nCardsCounter = 0;
	int	nMinValue = 17;
	int nTypeValue = 0;		//���Ƶ���ʼ��С;
	int nCounter = 0;		//�������Ƶĸ���;

	// 2,��С�����ܲμӵ�˳
	if(m_nBaoValue != 15)
	{
		if(m_nDiscardingCardsTable[15] != 0)
		{
			return 0;
		}
	}
	
	for(int i = 16; i < 17; i++)
	{
		if(m_nDiscardingCardsTable[i] != 0)
		{
			return 0;
		}
	}	

	for(int i = 14; i > 2; i--)
	{
		nCardsCounter += m_nDiscardingCardsTable[i];
		if(m_nDiscardingCardsTable[i] > 0)
		{
			nMinValue = i;
		}
	}
	nCardsCounter += m_nDiscardingCardsTable[BAO];
	if(nCardsCounter <= (15 - nMinValue))
	{
		for(int i = 3; i < 15; i++)
		{
			nCounter = 0;
			if(m_nDiscardingCardsTable[i] == 1)		 //������һ�ŵ���,����ȥɨ��;
			{
				nTypeValue = i;
				for(int j = i; j < 15; j++)				//�ӵ�i���ƿ�ʼɨ��;
				{				
					if(m_nDiscardingCardsTable[j] == 1)     //�������������Ϊ����,���������������һ;
					{					
						nCounter++;
					}
					else if(m_nDiscardingCardsTable[j] == 0)	//���������Ϊ����;
					{
						if(CheckTigerValue(1))
						{
							nCounter++;
						}
						else
						{
							for(int k = j; k < 15; k++)   //���֮�������ǿ�,�򷵻�0;
							{
								if(m_nDiscardingCardsTable[k] != 0)
								{							
									return 0;
								}
							}

							if(nCounter >= 5)   //�����������>=3,��Ϊ˫˳;
							{				
								return nTypeValue;
							}	
							else
							{
								return 0;
							}
						}					
					}
					else      //��Ϊ��Ҳ��Ϊ����,����0;
					{					
						return 0;
					}
				}
				break;
			}
			else if(m_nDiscardingCardsTable[i] != 0)
			{
				return 0;
			}
		}	

		if(nCounter >= 5)   //�����������>=5,��Ϊ��˳;
		{			
			return nTypeValue;
		}
		else				//��Ϊ����,����0
		{			
			return 0;
		}
	}
	else if(nCardsCounter > (15 - nMinValue) && (15 + m_nDiscardingCardsTable[BAO] - nCardsCounter - nMinValue >= 0))
	{
		for(int i = nMinValue; i < 15; i++)
		{
			if(m_nDiscardingCardsTable[i] > 1)
			{
				return 0;
			}
		}
		return (15 - nCardsCounter);
	}
	else
	{
		return 0;
	}
}

//�ж��Ƿ���˫˳;�˺����ʺ�6-20�������;
int CPlayCards::IsDoubleSeries()
{
	//if(m_dwRule & RULEDOUBLESERIES)
	//	return 0;

	int nTypeValue = 0;		//���Ƶ���ʼ��С;
	int nCounter = 0;		//�������Ƶĸ���;

	if(m_nBaoValue != 15)
	{
		if(m_nDiscardingCardsTable[15] != 0)
		{
			return 0;
		}
	}

	for(int i = 16; i < 17; i++)
	{
		if(m_nDiscardingCardsTable[i] != 0)
		{
			return 0;
		}
	}

	for(int i = 3; i < 15; i++)
	{
		nCounter = 0;
		if(m_nDiscardingCardsTable[i] == 2 || (m_nDiscardingCardsTable[i] == 1 && CheckTigerValue(1)))
		{
			nCounter++;
			nTypeValue = i;
			for(int j = i + 1; j < 15; j++)    //�ӵ�i���ƿ�ʼɨ��;
			{
				if(m_nDiscardingCardsTable[j] == 2)   //�������������Ϊ����,���������������һ;
				{
					nCounter++;					
				}
				else if(m_nDiscardingCardsTable[j] == 0)	//���������Ϊ����;
				{
					if(CheckTigerValue(2))
					{
						nCounter++;						
					}
					else
					{
						for(int k = j + 1; k < 15; k++)   //���֮�������ǿ�,�򷵻�0;
						{
							if(m_nDiscardingCardsTable[k] != 0)
							{							
								return 0;
							}
						}
						
						if(nCounter >= 3)   //�����������>=3,��Ϊ˫˳;
						{				
							return nTypeValue;
						}	
						else
						{
							return 0;
						}
					}										
				}
				else if(m_nDiscardingCardsTable[j] == 1)
				{
					if(CheckTigerValue(1))
					{
						nCounter++;						
					}
					else
					{
						return 0;
					}
				}
				else      //��Ϊ��Ҳ��Ϊ����,����0;
				{					
					return 0;
				}
			}
			break;
		}
		else if(m_nDiscardingCardsTable[i] != 0)
		{
			return 0;
		}		
	}	
	if(nCounter >= 3)   //�����������>=5,��Ϊ��˳;
	{			
		return nTypeValue;
	}
	else				//��Ϊ����,����0
	{			
		return 0;
	}
}

//�ж��Ƿ�����˳;�˺����ʺ�6-18�������;
int CPlayCards::IsThreeSeries()
{
	//if(m_dwRule & RULETHREESERIES)
	//	return 0;

	int nTypeValue = 0;	//��˳����ʼ��С;
	int nCounter = 0;	//�������ŵĸ���;

	if(m_nBaoValue != 15)
	{
		if(m_nDiscardingCardsTable[15] != 0)
		{
			return 0;
		}
	}

	for(int i = 15; i < 17; i++)
	{
		if(m_nDiscardingCardsTable[i] != 0)
		{
			return 0;
		}
	}

	for(int i = 3; i < 15; i++)
	{
		nCounter = 0;
		if(m_nDiscardingCardsTable[i] == 3 ||
		  (m_nDiscardingCardsTable[i] == 2 && CheckTigerValue(1)) ||
		  (m_nDiscardingCardsTable[i] == 1 && CheckTigerValue(2)))
		{
			nCounter++;
			nTypeValue = i;
			for(int j = i + 1; j < 15; j++)					//�ӱ��i�ʼɨ��;
			{
				if(m_nDiscardingCardsTable[j] == 3)			//�������������Ϊ����,���������������һ;
				{
					nCounter++;					
				}
				else if(m_nDiscardingCardsTable[j] == 0)	//���������Ϊ����,
				{
					if(CheckTigerValue(3))
					{
						nCounter++;
					}
					else
					{
						for(int k = j + 1; k < 15; k++)   //���֮�������ǿ�,�򷵻�0;
						{
							if(m_nDiscardingCardsTable[k] != 0)
							{							
								return 0;
							}
						}

						if(nCounter >= 1)   //�����������>=3,��Ϊ˫˳;
						{				
							return nTypeValue;
						}	
						else
						{
							return 0;
						}
					}													
				}
				else if(m_nDiscardingCardsTable[j] == 2)
				{
					if(CheckTigerValue(1))
					{
						nCounter++;
					}
					else
					{
						return 0;
					}
				}
				else if(m_nDiscardingCardsTable[j] == 1)
				{
					if(CheckTigerValue(2))
					{
						nCounter++;
					}
					else
					{
						return 0;
					}
				}
				else      //��Ϊ��Ҳ��Ϊ����,����0;
				{					
					return 0;
				}
			}
			break;
		}
		else if(m_nDiscardingCardsTable[i] != 0)
		{
			return 0;
		}
	}	
	if(nCounter >= 1)   //�����������>=5,��Ϊ��˳;
	{
		return nTypeValue;
	}
	else				//��Ϊ����,����0
	{			
		return 0;
	}
}

//�ж��Ƿ���һ����;
int CPlayCards::Is2()
{
	//if(m_dwRule & RULE2)
	//	return 0;

	for(int i = 17; i >= 3; i--)
	{
		if(m_nDiscardingCardsTable[i] == 2)
		{
			if(i == 17)
			{
				return m_nBaoValue;
			}
			else
			{
				return i;
			}			
		}
		else if(i < 16 && m_nDiscardingCardsTable[i] == 1 && CheckTigerValue(1))
		{
			return i;
		}		
	}
   // glog.log("ok%d",m_nDiscardingCardsTable[17]);
	return 0;    //����,Ϊ���Ʊ�;
}

//�ж��Ƿ�������;
int CPlayCards::Is3()
{
	//if(m_dwRule & RULE3)
	//	return 0;

	for(int i = 15; i >= 3; i--)
	{
		if(m_nDiscardingCardsTable[i] == 3)
		{
            return i;
		}
		else if(m_nDiscardingCardsTable[i] == 2 && CheckTigerValue(1) && i < 16)
		{
			return i;
		}	
		else if(m_nDiscardingCardsTable[i] == 1 && CheckTigerValue(2) && i < 16)
		{
			return i;
		}
	}
	return 0;
}

//�ж��Ƿ�������(��ը��); 
int CPlayCards::IsSoftBomb()
{
	//if(m_dwRule & RULE4)
	//	return 0;

	for(int i = 3; i < 16; i++)
	{
		if(m_nDiscardingCardsTable[i] == 3 && CheckTigerValue(1))
		{
			return i;
		}
		else if(m_nDiscardingCardsTable[i] == 2 && CheckTigerValue(2))
		{
			return i;
		}
		else if(m_nDiscardingCardsTable[i] == 1 && CheckTigerValue(3))
		{
			return i;
		}		
	}
	return 0;
}

//�ж��Ƿ�������(ը��); 
int CPlayCards::IsHardBomb()
{
	//if(m_dwRule & RULE4)
	//	return 0;

	for(int i = 3; i < 18; i++)
	{
		if(m_nDiscardingCardsTable[i] == 4)
		{
			if(i == 17)
			{
				return m_nBaoValue;
			}
			else
			{
				return i;
			}			
		}
		else if(m_nDiscardingCardsTable[i] != 0)
		{
			return 0;
		}
	}
	return 0;
}

//�ж��Ƿ�������һ��;
int CPlayCards::Is31()
{
	//if(m_dwRule & RULE31)
	//	return 0;

	for(int i = 15; i >= 3; i--)
	{
		if(m_nDiscardingCardsTable[i] == 3)
		{
			return i;
		}
		else if(m_nDiscardingCardsTable[i] == 2 && CheckTigerValue(1))
		{
			return i;
		}
		else if(m_nDiscardingCardsTable[i] == 1 && CheckTigerValue(2))
		{
			return i;
		}
	}
	return 0;
}

//�ж��Ƿ�������һ��;
int CPlayCards::Is32()
{
	//if(m_dwRule & RULE32)
	//	return 0;

	int nTypeValue = 0;
	int Pair = 0;
	
	if(m_nDiscardingCardsTable[BAO] == 3 )
	{
		nTypeValue = m_nBaoValue;
		for(int j = 3; j < 17; j++)
		{
			if (m_nDiscardingCardsTable[j] == 2)				
			{
				return nTypeValue;
			}	
		}
	}		

	for(int i = 15; i >= 3; i--)
	{
		if(m_nDiscardingCardsTable[i] == 3 ||
		  (m_nDiscardingCardsTable[i] == 2 && CheckTigerValue(1)) ||
		  (m_nDiscardingCardsTable[i] == 1 && CheckTigerValue(2)))
		{
			nTypeValue = i;
			for(int j = 3; j < 17; j++)
			{
				if(m_nDiscardingCardsTable[j] == 2 || (m_nDiscardingCardsTable[j] == 1 && CheckTigerValue(1)))
				{
					Pair = j;
					if(i != Pair)
					{
						return nTypeValue;
					}
				}
			}
            //�ڲ�������������ʱ
            if (CheckTigerValue(2))
            {
                return nTypeValue;
            }
		}
	}
	return 0;
}

//�жϳ������Ƿ���n���Ƶ������
bool CPlayCards::IsNotHaveN(int n)
{
    for (int i = 3; i < 16;i++)
    {
        if(m_nDiscardingCardsTable[i] == n)
            return false;
    }
    return true;
}

//�ж��Ƿ����Ĵ�����;
int CPlayCards::Is411()
{
	//if(m_dwRule & RULE411)
	//	return 0;

	int nTypeValue = 0;
	int nCounter = 0;

	if(m_nDiscardingCardsTable[BAO] == 4)
	{
		nTypeValue = m_nBaoValue;
		int nNum = 0;
		for(int j = 3; j < 17; j++)
		{
			if(m_nDiscardingCardsTable[j] == 1)
			{
				nNum++;
			}
		}
		if(nNum == 2)
		{
			return nTypeValue;
		}
	}

	for(int i = 15; i >= 3; i--)
	{
		if(m_nDiscardingCardsTable[i] == 4 ||
		  (m_nDiscardingCardsTable[i] == 3 && CheckTigerValue(1)) ||
		  (m_nDiscardingCardsTable[i] == 2 && IsNotHaveN(3) && CheckTigerValue(2)) ||
		  (m_nDiscardingCardsTable[i] == 1 && IsNotHaveN(4) && CheckTigerValue(3)))
		{
			nTypeValue = i;
			int nNum = 0;
			for(int j = 3; j < 17; j++)
			{
				if(m_nDiscardingCardsTable[j] == 1 && (i != j) || CheckTigerValue(1))
				{
					nNum++;
				}
			}
			if(nNum == 2)
			{
				return nTypeValue;
			}
		}
	}
	return 0;
}

//�ж��Ƿ�����˳������;
int CPlayCards::Is3311()
{
	//if(m_dwRule & RULE3311)
	//	return 0;

	int nTypeValue = 0;
	for(int i = 3; i < 14; i++)
	{
		if(m_nDiscardingCardsTable[i] == 3 ||
		  (m_nDiscardingCardsTable[i] == 2 && CheckTigerValue(1)) ||
		  (m_nDiscardingCardsTable[i] == 1 && CheckTigerValue(2)) ||(m_nDiscardingCardsTable[i]==0 && CheckTigerValue(3)))
		{
			nTypeValue = i;
			if(m_nDiscardingCardsTable[i+1] == 3 ||
			  (m_nDiscardingCardsTable[i+1] == 2 && CheckTigerValue(1)) ||
			  (m_nDiscardingCardsTable[i+1] == 1 && CheckTigerValue(2)) || (m_nDiscardingCardsTable[i+1]==0 && CheckTigerValue(3)))
			{
				int nNum = 0;
				for(int j = 3; j < 17; j++)
				{
					if(m_nDiscardingCardsTable[j] == 1 || CheckTigerValue(1))
					{
						if(j != i && (j != i+1))
						{
							nNum++;
						}
					}
				}
				if(nNum == 2)
				{
					return nTypeValue;
				}
			}
		}
		RevertTigerValue();
	}	

	return 0;
}

//�ж��Ƿ����Ĵ�����;
int CPlayCards::Is422()
{
	//if(m_dwRule & RULE422)
	//	return 0;

	int nTypeValue = 0;

	if(m_nDiscardingCardsTable[BAO] == 4)
	{
		nTypeValue = m_nBaoValue;
		int nNum = 0;
		for(int j = 3; j < 16; j++)
		{
			if(m_nDiscardingCardsTable[j] == 2)
			{
				nNum++;
			}
		}
		if(nNum == 2)
		{
			return nTypeValue;
		}
	}		

	for(int i = 15; i >= 3; i--)
	{
		if(m_nDiscardingCardsTable[i] == 4 ||
		  (m_nDiscardingCardsTable[i] == 3 && CheckTigerValue(1)) ||
		  (m_nDiscardingCardsTable[i] == 2 && IsNotHaveN(3) && CheckTigerValue(2) ) ||
		  (m_nDiscardingCardsTable[i] == 1 && IsNotHaveN(4) && CheckTigerValue(3)))
		{
			nTypeValue = i;
			int nNum = 0;
			for(int j = 3; j < 16; j++)
			{
				if(m_nDiscardingCardsTable[j] == 2 || (m_nDiscardingCardsTable[j] == 1 && CheckTigerValue(1)) || CheckTigerValue(2))
				{
					if(i != j)
					{
						nNum++;
					}
				}
			}
			if(nNum == 2)
			{
				return nTypeValue;
			}
		}		
	}	
	return 0;
}

//�ж��Ƿ�����˳������;	
int CPlayCards::Is3322()
{
	//if(m_dwRule & RULE3322)
	//	return 0;

	int nTypeValue = 0;

	for (int i = 3; i < 14; i++)
	{
		if(m_nDiscardingCardsTable[i] == 3 ||
		  (m_nDiscardingCardsTable[i] == 2 && CheckTigerValue(1)) ||
		  (m_nDiscardingCardsTable[i] == 1 && CheckTigerValue(2)) ||m_nDiscardingCardsTable[i]==0 && CheckTigerValue(3))
		{
			nTypeValue = i;
			if(m_nDiscardingCardsTable[i+1] == 3 ||
			  (m_nDiscardingCardsTable[i+1] == 2 && CheckTigerValue(1)) ||
			  (m_nDiscardingCardsTable[i+1] == 1 && CheckTigerValue(2)) ||(m_nDiscardingCardsTable[i+1]==0 && CheckTigerValue(3)))
			{
				int nNum = 0;
				for(int j = 3; j < 17; j++)
				{
					if(m_nDiscardingCardsTable[j] == 2 || (m_nDiscardingCardsTable[j] == 1 && CheckTigerValue(1))||CheckTigerValue(2))
					{
						if(j != i && (j != i+1))
						{
							nNum++;
						}
					}
				}
				if(nNum == 2)
				{
					return nTypeValue;
				}
			}
		}
		RevertTigerValue();
	}	

	return 0;
}

//�ж��Ƿ�����˳������;
int CPlayCards::Is333111()
{
	//if(m_dwRule & RULE333111)
	//	return 0;

	int nTypeValue = 0;

	for (int i = 3; i < 14; i++)
	{
		if(m_nDiscardingCardsTable[i] == 3 ||
		  (m_nDiscardingCardsTable[i] == 2 && CheckTigerValue(1)) ||
		  (m_nDiscardingCardsTable[i] == 1 && CheckTigerValue(2)) || (m_nDiscardingCardsTable[i]==0 && CheckTigerValue(3)))
		{
			nTypeValue = i;
			if(m_nDiscardingCardsTable[i+1] == 3 ||
			  (m_nDiscardingCardsTable[i+1] == 2 && CheckTigerValue(1)) ||
			  (m_nDiscardingCardsTable[i+1] == 1 && CheckTigerValue(2)) || (m_nDiscardingCardsTable[i+1]==0 && CheckTigerValue(3)))
			{
				if(m_nDiscardingCardsTable[i+2] == 3 ||
				  (m_nDiscardingCardsTable[i+2] == 2 && CheckTigerValue(1)) ||
				  (m_nDiscardingCardsTable[i+2] == 1 && CheckTigerValue(2)) || (m_nDiscardingCardsTable[i+2]==0 && CheckTigerValue(3)))
				{
					int nNum = 0;
					for(int j = 3; j < 17; j++)
					{
						if(m_nDiscardingCardsTable[j] == 1 || CheckTigerValue(1))
						{
							if(j != i && (j != i+1) && (j != i+2))
							{
								nNum++;
							}
						}
					}
					if(nNum == 3)
					{
						return nTypeValue;
					}
				}	
			}
		}
		RevertTigerValue();
	}	
	return 0;
}

//�ж��Ƿ�����˳������;
int CPlayCards::Is333222()	
{
	//if(m_dwRule & RULE333222)
	//	return 0;

	int nTypeValue = 0;
	
	for (int i = 3; i < 14; i++)
	{
		if(m_nDiscardingCardsTable[i] == 3 ||
		  (m_nDiscardingCardsTable[i] == 2 && CheckTigerValue(1)) ||
		  (m_nDiscardingCardsTable[i] == 1 && CheckTigerValue(2)) || (m_nDiscardingCardsTable[i]==0 && CheckTigerValue(3)))
		{
			nTypeValue = i;
			if(m_nDiscardingCardsTable[i+1] == 3 ||
			  (m_nDiscardingCardsTable[i+1] == 2 && CheckTigerValue(1)) ||
			  (m_nDiscardingCardsTable[i+1] == 1 && CheckTigerValue(2)) || (m_nDiscardingCardsTable[i+1]==0 && CheckTigerValue(3)))
			{
				if(m_nDiscardingCardsTable[i+2] == 3 ||
				  (m_nDiscardingCardsTable[i+2] == 2 && CheckTigerValue(1)) ||
				  (m_nDiscardingCardsTable[i+2] == 1 && CheckTigerValue(2)) || (m_nDiscardingCardsTable[i+2]==0 && CheckTigerValue(3)))
				{
					int nNum = 0;
					for(int j = 3; j < 17; j++)
					{
						if(m_nDiscardingCardsTable[j] == 2 || (m_nDiscardingCardsTable[j] == 1 && CheckTigerValue(1)) || CheckTigerValue(2))
						{
							if(j != i && (j != i+1) && (j != i+2))
							{
								nNum++;
							}
						}
					}
					if(nNum == 3)
					{
						return nTypeValue;
					}
				}	
			}
		}
		RevertTigerValue();
	}	

	return 0;
}

//�ж��Ƿ�����˳���ĵ�;
int CPlayCards::Is33331111()
{
	//if(m_dwRule & RULE33331111)
	//	return 0;

	int nTypeValue = 0;

	for(int i = 3; i < 14; i++)
	{
		if(m_nDiscardingCardsTable[i] == 3 ||
		  (m_nDiscardingCardsTable[i] == 2 && CheckTigerValue(1)) ||
		  (m_nDiscardingCardsTable[i] == 1 && CheckTigerValue(2)) || (m_nDiscardingCardsTable[i]==0 && CheckTigerValue(3)))
		{
			nTypeValue = i;
			if(m_nDiscardingCardsTable[i+1] == 3 ||
			  (m_nDiscardingCardsTable[i+1] == 2 && CheckTigerValue(1)) ||
			  (m_nDiscardingCardsTable[i+1] == 1 && CheckTigerValue(2)) || (m_nDiscardingCardsTable[i+1]==0 && CheckTigerValue(3)))
			{
				if(m_nDiscardingCardsTable[i+2] == 3 ||
				  (m_nDiscardingCardsTable[i+2] == 2 && CheckTigerValue(1)) ||
				  (m_nDiscardingCardsTable[i+2] == 1 && CheckTigerValue(2)) || (m_nDiscardingCardsTable[i+2]==0 && CheckTigerValue(3)))
				{
					if(m_nDiscardingCardsTable[i+3] == 3 ||
					  (m_nDiscardingCardsTable[i+3] == 2 && CheckTigerValue(1)) ||
					  (m_nDiscardingCardsTable[i+3] == 1 && CheckTigerValue(2)) || (m_nDiscardingCardsTable[i+3]==0 && CheckTigerValue(3)))
					{
						int nNum = 0;
						for(int j = 3; j < 17; j++)
						{
							if(m_nDiscardingCardsTable[j] == 1)
							{
								if(j != i && (j != i+1) && (j != i+2) && (j != i+3))
								{
									nNum++;
								}
							}
						}
						if(nNum == 4)
						{
							return nTypeValue;
						}
					}					
				}				
			}
		}
		RevertTigerValue();
	}	
	return 0;
}

void CPlayCards::NewRound()
{
	m_nBaoValue = 0;
	m_dwRule = 0/*RULE32|RULE422*/;
	memset(&m_cDiscardingType, 0, sizeof(m_cDiscardingType));
	memset(m_nDiscardingCardsTable, 0, sizeof(m_nDiscardingCardsTable));
    memset(m_nPutCardsTable, 0, sizeof(m_nPutCardsTable));
	m_cCards.clear();
	m_cChoosingCards.clear();
	m_cDiscarding.clear();
	m_vecTipsCards.clear();
    m_vecBaoArray.clear();
    m_vecHuaSeArray.clear();
    trueCards.clear();
    nChoose = 0;
}
/*
* �������ܣ�����ѡ���Ƿ��б���
* ����ֵ �� ���б���ʱ����1,û�б���ʱ����0;
*/
bool CPlayCards::IfHaveBao()
{
    for (size_t i = 0; i < m_cChoosingCards.size(); i++)
    {
        if (m_cChoosingCards[i].m_nValue == m_nBaoValue)
        {
            return true;
        }
    }
    return false;
}

/*
* �������ܣ��ҳ�������ٴ�����ϵĺϸ�ĳ���
* ����ֵ �� ���аٴ���ʱ����1,û�аٴ���ʱ����0;
*/
int CPlayCards::FindBaiArray(bool m_bfirst,CCardsType& cCardsType)
{
    ScanPutCardsTable();
    m_vecBaoArray.clear();
    m_vecHuaSeArray.clear();
    switch(m_cChoosingCards.size())
    {
    case 0:
    case 1:
    case 2:
    case 3:
        return 0;
    case 4:
        if (!m_bfirst)   //��ʾ�״γ���
        {
            Search31(m_bfirst,cCardsType);
            Search4(m_bfirst,cCardsType);
        }
        else if (cCardsType.m_nTypeNum == 31)
        {
            Search31(m_bfirst,cCardsType);
            Search4(m_bfirst,cCardsType);
        }
        else if (cCardsType.m_nTypeNum == 4)
        {
            Search4(m_bfirst,cCardsType);
        }
        break;
    case 5:
        Search32(m_bfirst,cCardsType);
        Search5(m_bfirst,cCardsType);
        break;
    case 6:
        Search411(m_bfirst,cCardsType);
        Search33(m_bfirst,cCardsType);
        Search222(m_bfirst,cCardsType);
        Search6(m_bfirst,cCardsType);
        break;
    case 7:
        Search7(m_bfirst,cCardsType);
        break;
    case 8:
        Search422(m_bfirst,cCardsType);
        Search3311(m_bfirst,cCardsType);
        Search2222(m_bfirst,cCardsType);
        Search8(m_bfirst,cCardsType);
        break;
    case 9:
        Search333(m_bfirst,cCardsType);
        Search9(m_bfirst,cCardsType);
        break;
    case 10:
        Search10(m_bfirst,cCardsType);
        Search3322(m_bfirst,cCardsType);
        Search22222(m_bfirst,cCardsType);
        break;
    case 11:
        Search11(m_bfirst,cCardsType);
        break;
    case 12:
        Search333111(m_bfirst,cCardsType);
        Search222222(m_bfirst,cCardsType);
        Search12(m_bfirst,cCardsType);
        break;
    default:
        return 0;
    }
	return 0;
}
int CPlayCards::Search31(bool m_bfirst,CCardsType& cCardsType)
{
    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 31)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }

    for(int i = nBegin; i < 16; i++)
    {
        int nBaoCount = m_nPutCardsTable[m_nBaoValue];
        if(i == m_nBaoValue)
        {
            nBaoCount = 0;
        }
        if(m_nPutCardsTable[i] + nBaoCount >= 3)
        {
            CCard card;		
            VECCARD vecCard;
            std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
            card.m_nValue = i;
            for(int j = 0; j < min(3,m_nPutCardsTable[i]); j++)
            {
                vecCard.push_back(card);
                if (i == m_nBaoValue)
                {               
                    vecHuaSe.push_back(vecCard.size()-1);
                }
            }
            int nUsedCatCount = min(nBaoCount, 3 - m_nPutCardsTable[i]);
            for (int k = 0; k < nUsedCatCount; k++)
            {
                card.m_nValue = i;     //���ٴ��Ƶ�ֵ��Ϊ��Ӧ�õ�ֵ
                vecCard.push_back(card);      
                vecHuaSe.push_back(vecCard.size()-1);
            }
            for(int j = 3; j < 17; j++)
            {
                if(m_nPutCardsTable[j] == 1 && (i!=j) || ((j ==m_nBaoValue) && (m_nBaoValue!=i) && nBaoCount-nUsedCatCount == 1))
                {
                    CCard card;					
                    card.m_nValue = j;
                    vecCard.push_back(card);

                    if (j == m_nBaoValue)
                    {
                        vecHuaSe.push_back(vecCard.size()-1);
                    }


                    if(m_nPutCardsTable[i] != 0)
                    {
                        m_vecBaoArray.push_back(vecCard);
                        m_vecHuaSeArray.push_back(vecHuaSe);
                        break;
                    }
                }
            }
        }
    }
    return 0;
}
int CPlayCards::Search32(bool m_bfirst,CCardsType& cCardsType)
{
    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 32)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }

    for(int i = nBegin; i < 16; i++)
    {
        int nBaoCount = m_nPutCardsTable[m_nBaoValue];
        if(i == m_nBaoValue)
        {
            if (nBaoCount-3 >0)
            {
                nBaoCount = nBaoCount -3;
            }
            else
            {
                nBaoCount = 0;
            }
        }

        if(m_nPutCardsTable[i] + nBaoCount >= 3 && m_nPutCardsTable[i] != 0)
        {
            CCard card;		
            VECCARD vecCard;
            std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
            card.m_nValue = i;
            for(int j = 0; j < min(3,m_nPutCardsTable[i]); j++)
            {
                vecCard.push_back(card);
                if ( i == m_nBaoValue)
                {
                    vecHuaSe.push_back(vecCard.size()-1);
                }
            }
            int nUsedCatCount = min(nBaoCount, 3 - m_nPutCardsTable[i]);
            for (int k = 0; k < nUsedCatCount; k++)
            {
                card.m_nValue = i;     //���ٴ��Ƶ�ֵ��Ϊ��Ӧ�õ�ֵ
                vecCard.push_back(card);                 
                vecHuaSe.push_back(vecCard.size()-1);             
            }

            nBaoCount -= nUsedCatCount; 
            for (int j = 3; j < 17; j++)
            {
                if (m_nPutCardsTable[j] == 2 && (i!=j) && j != m_nBaoValue)
                {
                    CCard card;					
                    card.m_nValue = j;
                    vecCard.push_back(card);

                    card.m_nValue = j;
                    vecCard.push_back(card);

                    if(m_nPutCardsTable[i] != 0)
                    {
                        m_vecBaoArray.push_back(vecCard);
                        m_vecHuaSeArray.push_back(vecHuaSe);
                        break;
                    }
                }
                else if (m_nPutCardsTable[j] == 1 && (i!=j) && m_nPutCardsTable[j]+nBaoCount ==2 && j != m_nBaoValue)
                {
                    CCard card;					
                    card.m_nValue = j;
                    vecCard.push_back(card);

                    //�ڶ����Ǳ���			
                    card.m_nValue = j;
                    vecCard.push_back(card);
                    vecHuaSe.push_back(vecCard.size()-1);

                    if(m_nPutCardsTable[i] != 0)
                    {
                        m_vecBaoArray.push_back(vecCard);
                        m_vecHuaSeArray.push_back(vecHuaSe);
                        break;
                    }
                }
                else if (nBaoCount == 2)
                {
                    CCard card;					
                    card.m_nValue = m_nBaoValue;
                    vecCard.push_back(card);
                    vecHuaSe.push_back(vecCard.size()-1);
		
                    card.m_nValue = m_nBaoValue;
                    vecCard.push_back(card);
                    vecHuaSe.push_back(vecCard.size()-1);

                    if(m_nPutCardsTable[i] != 0)
                    {
                        m_vecBaoArray.push_back(vecCard);
                        m_vecHuaSeArray.push_back(vecHuaSe);
                        break;
                    }
                }
            }
        }
    }
   return 0; 
}


int CPlayCards::Search4(bool m_bfirst,CCardsType& cCardsType)
{
    int nBegin = 3;
    if (cCardsType.m_nTypeBomb == 1)
    {
        if (cCardsType.m_nTypeNum != 4)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }

    for(int i = nBegin; i < 16; i++)
    {
        int nBaoCount = m_nPutCardsTable[m_nBaoValue];
        if(i == m_nBaoValue)
        {
            nBaoCount = 0;
        }
        if(m_nPutCardsTable[i] + nBaoCount >= 4)
        {
            CCard card;
            VECCARD vecCard;
            std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
            card.m_nValue = i;
            for(int j = 0; j < min(4,m_nPutCardsTable[i]); j++)
            {
                vecCard.push_back(card);
            }
            int nUsedCatCount = min(nBaoCount, 4 - m_nPutCardsTable[i]);
            for(int k = 0; k < nUsedCatCount; k++)
            {
                card.m_nValue = i;
                vecCard.push_back(card);
                vecHuaSe.push_back(vecCard.size()-1);
            }				
            if(m_nPutCardsTable[i] != 0)
            {
                m_vecBaoArray.push_back(vecCard);
                m_vecHuaSeArray.push_back(vecHuaSe);
            }			
        }		
    }
    return 0;
}
int CPlayCards::Search5(bool m_bfirst,CCardsType& cCardsType)
{
    int nCount = 0;
    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 5)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }
    for(int i = nBegin; i < 11; i++)
    {
        int nTmpCatTable = m_nPutCardsTable[m_nBaoValue];

        //   if(m_nPutCardsTable[i] >= 1)
        {
            nCount = 0;
            CCard card;
            VECCARD vecCard;
            std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
            for(int j = 0; j < 5; j++)
            {
                int nBaoCount = m_nPutCardsTable[m_nBaoValue];
                if((i + j) == m_nBaoValue)
                {
                    nBaoCount = 0;
                }
                if(m_nPutCardsTable[i + j] + nBaoCount >= 1)
                {
                    card.m_nValue = i + j;
                    for(int k = 0; k < min(1,m_nPutCardsTable[i + j]); k++)
                    {
                        vecCard.push_back(card);
                        if ((i+j) == m_nBaoValue)
                        {
                            m_nPutCardsTable[m_nBaoValue]--;
                            vecHuaSe.push_back(vecCard.size()-1);//����ֵΪ�Լ�ֵ
                        }
                    }
                    if(m_nPutCardsTable[i + j] < 1)
                    {
                        int nUsedCatCount = min(nBaoCount, 1 - m_nPutCardsTable[i + j]);
                        for(int k = 0; k < nUsedCatCount; k++)
                        {
                            card.m_nValue = i+j;
                            vecCard.push_back(card);
                            vecHuaSe.push_back(vecCard.size()-1);
                        }
                        m_nPutCardsTable[m_nBaoValue] -= nUsedCatCount;
                    }
                    nCount++;
                }
                else if (nCount !=0 )
                {
                    break;
                }
            }
            if(nCount == 5)
            {
                m_vecBaoArray.push_back(vecCard);
                m_vecHuaSeArray.push_back(vecHuaSe);
            }
        }
        m_nPutCardsTable[m_nBaoValue] = nTmpCatTable;
    }
    return 0;
}
int CPlayCards::Search411(bool m_bfirst,CCardsType& cCardsType)
{

    if (m_nPutCardsTable[m_nBaoValue] == 4 && m_nBaoValue > cCardsType.m_nTypeValue)
    {
        VECCARD vecCard;
        CCard card;	
        std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
         int nCount = 0;
         card.m_nValue = m_nBaoValue;
        for (int i = 0; i <  4; i++)
        {
            vecCard.push_back(card);
            vecHuaSe.push_back(i);
        }
        for(int j = 3; j < 16; j++)
        {
            if(m_nPutCardsTable[j] == 1)
            {
                CCard card;					
                card.m_nValue = j;
                vecCard.push_back(card);
                if(++nCount >= 2)
                {
                    if(m_nPutCardsTable[j] != 0)
                    {
                        m_vecBaoArray.push_back(vecCard);
                        m_vecHuaSeArray.push_back(vecHuaSe);
                        return 1;
                    }	
                }
            }
        }
        return 0;
    }


    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 411)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }
    for(int i = 14; i >=nBegin; i--)
    {
        VECCARD vecCard;
        CCard card;	
        std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
        int nBaoCount = m_nPutCardsTable[m_nBaoValue];
        if(i == m_nBaoValue)
        {
            nBaoCount = 0;
        }		
        if(m_nPutCardsTable[i] + nBaoCount >= 4)
        {
            card.m_nValue = i;
            for(int j = 0; j < min(4,m_nPutCardsTable[i]); j++)
            {
                vecCard.push_back(card);
                if( i== m_nBaoValue )
                {
                    vecHuaSe.push_back(vecCard.size()-1);
                }
            }
            int nUsedCatCount = min(nBaoCount, 4 - m_nPutCardsTable[i]);
            for(int k = 0; k < nUsedCatCount; k++)
            {
                card.m_nValue = i;
                vecCard.push_back(card);
                vecHuaSe.push_back(vecCard.size()-1);        
            }
            int nCount = 0;
            for(int j = 3; j < 16; j++)
            {
                if(m_nPutCardsTable[j] == 1 && (i!=j) && (j != m_nBaoValue) || (j == m_nBaoValue)&&(nBaoCount-nUsedCatCount == 1) )
                {
                    CCard card;					
                    card.m_nValue = j;
                    vecCard.push_back(card);

                    if (j == m_nBaoValue)
                    {               
                        vecHuaSe.push_back(vecCard.size()-1);
                        nUsedCatCount++;
                    }

                    if(++nCount >= 2)
                    {
                        if(m_nPutCardsTable[j] != 0)
                        {
                            m_vecBaoArray.push_back(vecCard);
                            m_vecHuaSeArray.push_back(vecHuaSe);
                            return 1;
                        }	
                       
                    }
                }
            }
        }
    }
    return 0;
}

int CPlayCards::Search422(bool m_bfirst,CCardsType& cCardsType)
{ 
    CCard card;

    if (m_nPutCardsTable[m_nBaoValue] == 4 && m_nBaoValue > cCardsType.m_nTypeValue)
    {
        VECCARD vecCard;
        std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
        int nCount = 0;
        card.m_nValue = m_nBaoValue;
        for (int i = 0; i < 4; i++)
        {
            vecCard.push_back(card);
            vecHuaSe.push_back(i);
        }
        for(int j = 3; j < 16; j++)
        {
            if(m_nPutCardsTable[j] == 2)
            {
                CCard card;					
                card.m_nValue = j;
                vecCard.push_back(card);
                card.m_nValue = j;
                vecCard.push_back(card);
                if(++nCount >= 2)
                {
                    m_vecBaoArray.push_back(vecCard);
                    m_vecHuaSeArray.push_back(vecHuaSe);
                    return 1;	
                }
            }
        }
        return 0;
    }


    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 422)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }
    for(int i = 14; i >= nBegin; i--)
    {
        VECCARD vecCard;
        std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
        int nBaoCount = m_nPutCardsTable[m_nBaoValue];
        if(i == m_nBaoValue)
        {
            nBaoCount = 0;
        }		
        if(m_nPutCardsTable[i] + nBaoCount >= 4 && m_nPutCardsTable[i] >= 2)
        {
            card.m_nValue = i;
            for(int j = 0; j < min(4,m_nPutCardsTable[i]); j++)
            {
                vecCard.push_back(card);
                if( i== m_nBaoValue )
                {
                    vecHuaSe.push_back(vecCard.size()-1);
                }
            }
            int nUsedCatCount = min(nBaoCount, 4 - m_nPutCardsTable[i]);
            for(int k = 0; k < nUsedCatCount; k++)
            {
                card.m_nValue = i;
                vecCard.push_back(card);
                vecHuaSe.push_back(vecCard.size()-1);  
                nBaoCount--;
            }
            int copynBaoCount = nBaoCount;

            int nCount = 0;
            for(int j = 3; j < 16; j++)
            {
                if(m_nPutCardsTable[j] == 2 && (i!=j) && (j!=m_nBaoValue)  ||
                    m_nPutCardsTable[j] == 1 && (i!=j) && (j!=m_nBaoValue) &&(nBaoCount))
                {
                    if (m_nPutCardsTable[j] == 2 && (i!=j) && (j!=m_nBaoValue))
                    {
                        CCard card;					
                        card.m_nValue = j;
                        vecCard.push_back(card);

                        if (j == m_nBaoValue)
                        {               
                            vecHuaSe.push_back(vecCard.size()-1);
                            nBaoCount--;
                        }

                        card.m_nValue = j;
                        vecCard.push_back(card);

                        if (j == m_nBaoValue)
                        {               
                            vecHuaSe.push_back(vecCard.size()-1);
                            nBaoCount--;
                        }
                        nCount++;
                    }
                    else if (m_nPutCardsTable[j] == 1 && (i!=j) && (j!=m_nBaoValue) &&(nBaoCount))
                    {
                        CCard card;					
                        card.m_nValue = j;
                        vecCard.push_back(card);

                        card.m_nValue = j;
                        vecCard.push_back(card);
                        vecHuaSe.push_back(vecCard.size()-1);
                        nBaoCount--;
                        nCount++;
                    }

                    if(nCount == 2)
                    {
                        m_vecBaoArray.push_back(vecCard);
                        m_vecHuaSeArray.push_back(vecHuaSe);
                        return 1;	
                    }
                }
            }

            nCount = 0;
            nBaoCount = copynBaoCount;
            for(int j = 3; j < 16; j++)
            {
                if (m_nPutCardsTable[j] == 2 && (i!=j) && (j!=m_nBaoValue) || (j == m_nBaoValue)&&(nBaoCount == 2))
                {
                    CCard card;					
                    card.m_nValue = j;
                    vecCard.push_back(card);

                    if (j == m_nBaoValue)
                    {               
                        vecHuaSe.push_back(vecCard.size()-1);
                        nBaoCount--;
                    }

                    card.m_nValue = j;
                    vecCard.push_back(card);

                    if (j == m_nBaoValue)
                    {               
                        vecHuaSe.push_back(vecCard.size()-1);
                        nBaoCount--;
                    }
                    nCount++;


                    if(nCount == 2)
                    {
                       m_vecBaoArray.push_back(vecCard);
                       m_vecHuaSeArray.push_back(vecHuaSe);
                       return 1;
                    }
                }
            }
    
        }
    }
    return 0;
}

int CPlayCards::Search3322(bool m_bfirst,CCardsType& cCardsType)
{
    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 3322)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }

    for(int i = nBegin; i < 14; i++)
    {
        bool bContinue = true;
        VECCARD vecCard;
        std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
        int nTmpCatTable = m_nPutCardsTable[m_nBaoValue];
        int usebao = 0;
        for(int j = 0; j < 2; j++)
        {
            int nBaoCount = m_nPutCardsTable[m_nBaoValue]-usebao;
            if((i + j) == m_nBaoValue)
            {
                nBaoCount -= usebao;
            }
            if(m_nPutCardsTable[i+j] + nBaoCount >= 3)
            {
                CCard card;
                card.m_nValue = i + j;
                for(int k = 0; k < min(3,m_nPutCardsTable[i+j]); k++)
                {
                    vecCard.push_back(card);
                    if( i+j == m_nBaoValue )
                    {
                        vecHuaSe.push_back(vecCard.size()-1);
                        usebao++;
                    }
                }
                if(m_nPutCardsTable[i+j] < 3)
                {
                    int nUsedCatCount = min(nBaoCount, 3 - m_nPutCardsTable[i + j]);
                    for(int k = 0; k < nUsedCatCount; k++)
                    {
                        card.m_nValue = i + j;
                        vecCard.push_back(card);
                        vecHuaSe.push_back(vecCard.size()-1);
                        usebao++;
                    }
                  //  m_nPutCardsTable[m_nBaoValue] -= nUsedCatCount;					
                }				
            }
            else
            {
                bContinue = false;
                vecCard.clear();
                vecHuaSe.clear();
                break;
            }
        }
        m_nPutCardsTable[m_nBaoValue] = nTmpCatTable;

        if(bContinue)
        {
            int nCount = 0;
            for(int k = 3; k < 17; k++)
            {
                if(m_nPutCardsTable[k] == 2 && (i!=k) && (k != i+1) && (k != m_nBaoValue) || (k == m_nBaoValue) &&(nTmpCatTable-usebao == 2) || (m_nPutCardsTable[k] == 1 &&(nTmpCatTable-usebao) ))
                {
                    CCard card;
                    card.m_nValue = k;
                    vecCard.push_back(card);
                    if (k == m_nBaoValue)
                    {
                        vecHuaSe.push_back(vecCard.size()-1);
                        usebao++;
                    }
                    vecCard.push_back(card);
                    if (k == m_nBaoValue)
                    {
                        vecHuaSe.push_back(vecCard.size()-1);
                        usebao++;
                    }
                    if(++nCount >= 2)
                    {
                        m_vecBaoArray.push_back(vecCard);
                        m_vecHuaSeArray.push_back(vecHuaSe);
                        break;
                    }
                }
            }
        }
    }
    return 0;
}
int CPlayCards::Search3311(bool m_bfirst,CCardsType& cCardsType)
{
    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 3311)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }

    for(int i = nBegin; i < 14; i++)
    {
        bool bContinue = true;
        VECCARD vecCard;
        std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
        int nTmpCatTable = m_nPutCardsTable[m_nBaoValue];
        int usebao = 0;
        for(int j = 0; j < 2; j++)
        {
            int nBaoCount = m_nPutCardsTable[m_nBaoValue]-usebao;
            if((i + j) == m_nBaoValue)
            {
                nBaoCount -= usebao;
            }
            if(m_nPutCardsTable[i+j] + nBaoCount >= 3)
            {
                CCard card;						
                card.m_nValue = i + j;
                for(int k = 0; k < min(3,m_nPutCardsTable[i + j]); k++)
                {
                    vecCard.push_back(card);
                    if( i+j == m_nBaoValue )
                    {
                        vecHuaSe.push_back(vecCard.size()-1);
                        usebao++;
                    }
                }
                if(m_nPutCardsTable[i + j] < 3)
                {
                    int nUsedCatCount = min(nBaoCount, 3 - m_nPutCardsTable[i + j]);
                    for(int k = 0; k < nUsedCatCount; k++)
                    {
                        card.m_nValue = i + j;
                        vecCard.push_back(card);
                        vecHuaSe.push_back(vecCard.size()-1);
                        usebao++;
                    }
                    //m_nPutCardsTable[m_nBaoValue] -= nUsedCatCount;					
                }				
            }
            else
            {				
                bContinue = false;
                vecCard.clear();
                break;
            }
        }
        m_nPutCardsTable[m_nBaoValue] = nTmpCatTable;

        if(bContinue)
        {
            int nCount = 0;
            for(int k = 3; k < 17; k++)
            {
                if(m_nPutCardsTable[k] == 1 && (i!=k) && (k != i+1) && (k != m_nBaoValue) || (k == m_nBaoValue) &&(nTmpCatTable-usebao == 1)&& (i!=k) && (k != i+1))
                {
                    CCard card;					
                    card.m_nValue = k;
                    vecCard.push_back(card);
                    if (k == m_nBaoValue)
                    {
                        usebao++;
                        vecHuaSe.push_back(vecCard.size()-1);
                    }
                    if(++nCount >= 2)
                    {
                        m_vecBaoArray.push_back(vecCard);
                        m_vecHuaSeArray.push_back(vecHuaSe);
                        break;
                    }
                }
            }
        }
    }
    return 0;
}
int CPlayCards::Search333111(bool m_bfirst,CCardsType& cCardsType)
{
    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 333111)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }

    for(int i = nBegin; i < 14; i++)
    {
        bool bContinue = true;
        VECCARD vecCard;
        std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
        int nTmpCatTable = m_nPutCardsTable[m_nBaoValue];
        int usebao = 0;
        for(int j = 0; j < 3; j++)
        {
            int nBaoCount = m_nPutCardsTable[m_nBaoValue]-usebao;
            if((i + j) == m_nBaoValue)
            {
                nBaoCount = 0;
                usebao++;
            }
            if(m_nPutCardsTable[i+j] + nBaoCount >= 3)
            {
                CCard card;						
                card.m_nValue = i + j;
                for(int k = 0; k < min(3,m_nPutCardsTable[i + j]); k++)
                {
                    vecCard.push_back(card);
                    if( i+j == m_nBaoValue )
                    {
                        vecHuaSe.push_back(vecCard.size()-1);
                        usebao++;
                    }
                }
                if(m_nPutCardsTable[i + j] < 3)
                {
                    int nUsedCatCount = min(nBaoCount, 3 - m_nPutCardsTable[i + j]);
                    for(int k = 0; k < nUsedCatCount; k++)
                    {
                        card.m_nValue = i + j;
                        vecCard.push_back(card);
                        vecHuaSe.push_back(vecCard.size()-1);
                    }
                    m_nPutCardsTable[m_nBaoValue] -= nUsedCatCount;					
                }				
            }
            else
            {				
                bContinue = false;
                vecCard.clear();
                break;
            }
        }
        m_nPutCardsTable[m_nBaoValue] = nTmpCatTable;

        if(bContinue)
        {
            int nCount = 0;
            for(int k = 3; k < 17; k++)
            {
                if(m_nPutCardsTable[k] >= 1 && (i!=k) && (k != i+1) && (k !=i+2)&& (k != m_nBaoValue)|| (k == m_nBaoValue) &&(nTmpCatTable-usebao == 1)&& (i!=k) && (k != i+1) && (k !=i+2))
                {
                    CCard card;					
                    card.m_nValue = k;
                    vecCard.push_back(card);
                    if (k == m_nBaoValue)
                    {
                        usebao++;
                        vecCard.push_back(card);
                    }
                    if(++nCount >= 3)
                    {
                        m_vecBaoArray.push_back(vecCard);
                        m_vecHuaSeArray.push_back(vecHuaSe);
                        break;
                    }
                }
            }
        }
    }
    return 0;
}
int CPlayCards::Search6(bool m_bfirst,CCardsType& cCardsType)
{
    int nCount = 0;
    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 6)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }
    for(int i = nBegin; i < 10; i++)
    {
        int nTmpCatTable = m_nPutCardsTable[m_nBaoValue];
         
    //   if(m_nPutCardsTable[i] >= 1)
        {
            nCount = 0;
            CCard card;
            VECCARD vecCard;
            std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
            for(int j = 0; j < 6; j++)
            {
                int nBaoCount = m_nPutCardsTable[m_nBaoValue];
                if((i + j) == m_nBaoValue)
                {
                    nBaoCount = 0;
                }
                if(m_nPutCardsTable[i + j] + nBaoCount >= 1)
                {
                    card.m_nValue = i + j;
                    for(int k = 0; k < min(1,m_nPutCardsTable[i + j]); k++)
                    {
                        vecCard.push_back(card);
                        if ((i+j) == m_nBaoValue)
                        {
                            m_nPutCardsTable[m_nBaoValue]--;
                            vecHuaSe.push_back(vecCard.size()-1);//����ֵΪ�Լ�ֵ
                        }
                    }
                    if(m_nPutCardsTable[i + j] < 1)
                    {
                        int nUsedCatCount = min(nBaoCount, 1 - m_nPutCardsTable[i + j]);
                        for(int k = 0; k < nUsedCatCount; k++)
                        {
                            card.m_nValue = i+j;
                            vecCard.push_back(card);
                            vecHuaSe.push_back(vecCard.size()-1);
                        }
                        m_nPutCardsTable[m_nBaoValue] -= nUsedCatCount;
                    }
                    nCount++;
                }
                else if (nCount !=0 )
                {
                    break;
                }
            }
            if(nCount == 6)
            {
                m_vecBaoArray.push_back(vecCard);
                m_vecHuaSeArray.push_back(vecHuaSe);
            }
        }
        m_nPutCardsTable[m_nBaoValue] = nTmpCatTable;
    }
    return 0;
}

int CPlayCards::Search7(bool m_bfirst,CCardsType& cCardsType)
{
    int nCount = 0;
    int nBegin = 3;
    if (m_bfirst)
    {
        nBegin = cCardsType.m_nTypeValue + 1;
    }
    for(int i = nBegin; i < 9; i++)
    {
        int nTmpCatTable = m_nPutCardsTable[m_nBaoValue];

        //   if(m_nPutCardsTable[i] >= 1)
        {
            nCount = 0;
            CCard card;
            VECCARD vecCard;
            std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
            for(int j = 0; j < 7; j++)
            {
                int nBaoCount = m_nPutCardsTable[m_nBaoValue];
                if((i + j) == m_nBaoValue)
                {
                    nBaoCount = 0;
                }
                if(m_nPutCardsTable[i + j] + nBaoCount >= 1)
                {
                    card.m_nValue = i + j;
                    for(int k = 0; k < min(1,m_nPutCardsTable[i + j]); k++)
                    {
                        vecCard.push_back(card);
                        if ((i+j) == m_nBaoValue)
                        {
                            m_nPutCardsTable[m_nBaoValue]--;
                            vecHuaSe.push_back(vecCard.size()-1);//����ֵΪ�Լ�ֵ
                        }
                    }
                    if(m_nPutCardsTable[i + j] < 1)
                    {
                        int nUsedCatCount = min(nBaoCount, 1 - m_nPutCardsTable[i + j]);
                        for(int k = 0; k < nUsedCatCount; k++)
                        {
                            card.m_nValue = i+j;
                            vecCard.push_back(card);
                            vecHuaSe.push_back(vecCard.size()-1);
                        }
                        m_nPutCardsTable[m_nBaoValue] -= nUsedCatCount;
                    }
                    nCount++;
                }
                else if (nCount !=0 )
                {
                    break;
                }
            }
            if(nCount == 7)
            {
                m_vecBaoArray.push_back(vecCard);
                m_vecHuaSeArray.push_back(vecHuaSe);
            }
        }
        m_nPutCardsTable[m_nBaoValue] = nTmpCatTable;
    }
    return 0;
}
int CPlayCards::Search8(bool m_bfirst,CCardsType& cCardsType)
{
    int nCount = 0;
    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 8)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }
    for(int i = nBegin; i < 8; i++)
    {
        int nTmpCatTable = m_nPutCardsTable[m_nBaoValue];

        //   if(m_nPutCardsTable[i] >= 1)
        {
            nCount = 0;
            CCard card;
            VECCARD vecCard;
            std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
            for(int j = 0; j < 8; j++)
            {
                int nBaoCount = m_nPutCardsTable[m_nBaoValue];
                if((i + j) == m_nBaoValue)
                {
                    nBaoCount = 0;
                }
                if(m_nPutCardsTable[i + j] + nBaoCount >= 1)
                {
                    card.m_nValue = i + j;
                    for(int k = 0; k < min(1,m_nPutCardsTable[i + j]); k++)
                    {
                        vecCard.push_back(card);
                        if ((i+j) == m_nBaoValue)
                        {
                            m_nPutCardsTable[m_nBaoValue]--;
                            vecHuaSe.push_back(vecCard.size()-1);//����ֵΪ�Լ�ֵ
                        }
                    }
                    if(m_nPutCardsTable[i + j] < 1)
                    {
                        int nUsedCatCount = min(nBaoCount, 1 - m_nPutCardsTable[i + j]);
                        for(int k = 0; k < nUsedCatCount; k++)
                        {
                            card.m_nValue = i+j;
                            vecCard.push_back(card);
                            vecHuaSe.push_back(vecCard.size()-1);
                        }
                        m_nPutCardsTable[m_nBaoValue] -= nUsedCatCount;
                    }
                    nCount++;
                }
                else if (nCount !=0 )
                {
                    break;
                }
            }
            if(nCount == 8)
            {
                m_vecBaoArray.push_back(vecCard);
                m_vecHuaSeArray.push_back(vecHuaSe);
            }
        }
        m_nPutCardsTable[m_nBaoValue] = nTmpCatTable;
    }
    return 0;
}

int CPlayCards::Search9(bool m_bfirst,CCardsType& cCardsType)
{
    int nCount = 0;
    int nBegin = 3;
    if (m_bfirst)
    {
        nBegin = cCardsType.m_nTypeValue + 1;
    }
    for(int i = nBegin; i < 7; i++)
    {
        int nTmpCatTable = m_nPutCardsTable[m_nBaoValue];

        //   if(m_nPutCardsTable[i] >= 1)
        {
            nCount = 0;
            CCard card;
            VECCARD vecCard;
            std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
            for(int j = 0; j < 9; j++)
            {
                int nBaoCount = m_nPutCardsTable[m_nBaoValue];
                if((i + j) == m_nBaoValue)
                {
                    nBaoCount = 0;
                }
                if(m_nPutCardsTable[i + j] + nBaoCount >= 1)
                {
                    card.m_nValue = i + j;
                    for(int k = 0; k < min(1,m_nPutCardsTable[i + j]); k++)
                    {
                        vecCard.push_back(card);
                        if ((i+j) == m_nBaoValue)
                        {
                            m_nPutCardsTable[m_nBaoValue]--;
                            vecHuaSe.push_back(vecCard.size()-1);//����ֵΪ�Լ�ֵ
                        }
                    }
                    if(m_nPutCardsTable[i + j] < 1)
                    {
                        int nUsedCatCount = min(nBaoCount, 1 - m_nPutCardsTable[i + j]);
                        for(int k = 0; k < nUsedCatCount; k++)
                        {
                            card.m_nValue = i+j;
                            vecCard.push_back(card);
                            vecHuaSe.push_back(vecCard.size()-1);
                        }
                        m_nPutCardsTable[m_nBaoValue] -= nUsedCatCount;
                    }
                    nCount++;
                }
                else if (nCount !=0 )
                {
                    break;
                }
            }
            if(nCount == 9)
            {
                m_vecBaoArray.push_back(vecCard);
                m_vecHuaSeArray.push_back(vecHuaSe);
            }
        }
        m_nPutCardsTable[m_nBaoValue] = nTmpCatTable;
    }
    return 0;
}


int CPlayCards::Search10(bool m_bfirst,CCardsType& cCardsType)
{
    int nCount = 0;
    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 10)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }
    for(int i = nBegin; i < 6; i++)
    {
        int nTmpCatTable = m_nPutCardsTable[m_nBaoValue];

        //   if(m_nPutCardsTable[i] >= 1)
        {
            nCount = 0;
            CCard card;
            VECCARD vecCard;
            std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
            for(int j = 0; j < 10; j++)
            {
                int nBaoCount = m_nPutCardsTable[m_nBaoValue];
                if((i + j) == m_nBaoValue)
                {
                    nBaoCount = 0;
                }
                if(m_nPutCardsTable[i + j] + nBaoCount >= 1)
                {
                    card.m_nValue = i + j;
                    for(int k = 0; k < min(1,m_nPutCardsTable[i + j]); k++)
                    {
                        vecCard.push_back(card);
                        if ((i+j) == m_nBaoValue)
                        {
                            m_nPutCardsTable[m_nBaoValue]--;
                            vecHuaSe.push_back(vecCard.size()-1);//����ֵΪ�Լ�ֵ
                        }
                    }
                    if(m_nPutCardsTable[i + j] < 1)
                    {
                        int nUsedCatCount = min(nBaoCount, 1 - m_nPutCardsTable[i + j]);
                        for(int k = 0; k < nUsedCatCount; k++)
                        {
                            card.m_nValue = i+j;
                            vecCard.push_back(card);
                            vecHuaSe.push_back(vecCard.size()-1);
                        }
                        m_nPutCardsTable[m_nBaoValue] -= nUsedCatCount;
                    }
                    nCount++;
                }
                else if (nCount !=0 )
                {
                    break;
                }
            }
            if(nCount == 10)
            {
                m_vecBaoArray.push_back(vecCard);
                m_vecHuaSeArray.push_back(vecHuaSe);
            }
        }
        m_nPutCardsTable[m_nBaoValue] = nTmpCatTable;
    }
    return 0;
}

int CPlayCards::Search11(bool m_bfirst,CCardsType& cCardsType)
{
    int nCount = 0;
    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 11)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }
    for(int i = nBegin; i < 5; i++)
    {
        int nTmpCatTable = m_nPutCardsTable[m_nBaoValue];

        //   if(m_nPutCardsTable[i] >= 1)
        {
            nCount = 0;
            CCard card;
            VECCARD vecCard;
            std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
            for(int j = 0; j < 11; j++)
            {
                int nBaoCount = m_nPutCardsTable[m_nBaoValue];
                if((i + j) == m_nBaoValue)
                {
                    nBaoCount = 0;
                }
                if(m_nPutCardsTable[i + j] + nBaoCount >= 1)
                {
                    card.m_nValue = i + j;
                    for(int k = 0; k < min(1,m_nPutCardsTable[i + j]); k++)
                    {
                        vecCard.push_back(card);
                        if ((i+j) == m_nBaoValue)
                        {
                            m_nPutCardsTable[m_nBaoValue]--;
                            vecHuaSe.push_back(vecCard.size()-1);//����ֵΪ�Լ�ֵ
                        }
                    }
                    if(m_nPutCardsTable[i + j] < 1)
                    {
                        int nUsedCatCount = min(nBaoCount, 1 - m_nPutCardsTable[i + j]);
                        for(int k = 0; k < nUsedCatCount; k++)
                        {
                            card.m_nValue = i+j;
                            vecCard.push_back(card);
                            vecHuaSe.push_back(vecCard.size()-1);
                        }
                        m_nPutCardsTable[m_nBaoValue] -= nUsedCatCount;
                    }
                    nCount++;
                }
                else if (nCount !=0 )
                {
                    break;
                }
            }
            if(nCount == 11)
            {
                m_vecBaoArray.push_back(vecCard);
                m_vecHuaSeArray.push_back(vecHuaSe);
            }
        }
        m_nPutCardsTable[m_nBaoValue] = nTmpCatTable;
    }
    return 0;
}
int CPlayCards::Search12(bool m_bfirst,CCardsType& cCardsType)
{
    int nCount = 0;
    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 12)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }
    for(int i = nBegin; i < 4; i++)
    {
        int nTmpCatTable = m_nPutCardsTable[m_nBaoValue];

        //   if(m_nPutCardsTable[i] >= 1)
        {
            nCount = 0;
            CCard card;
            VECCARD vecCard;
            std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
            for(int j = 0; j < 12; j++)
            {
                int nBaoCount = m_nPutCardsTable[m_nBaoValue];
                if((i + j) == m_nBaoValue)
                {
                    nBaoCount = 0;
                }
                if(m_nPutCardsTable[i + j] + nBaoCount >= 1)
                {
                    card.m_nValue = i + j;
                    for(int k = 0; k < min(1,m_nPutCardsTable[i + j]); k++)
                    {
                        vecCard.push_back(card);
                        if ((i+j) == m_nBaoValue)
                        {
                            m_nPutCardsTable[m_nBaoValue]--;
                            vecHuaSe.push_back(vecCard.size()-1);//����ֵΪ�Լ�ֵ
                        }
                    }
                    if(m_nPutCardsTable[i + j] < 1)
                    {
                        int nUsedCatCount = min(nBaoCount, 1 - m_nPutCardsTable[i + j]);
                        for(int k = 0; k < nUsedCatCount; k++)
                        {
                            card.m_nValue = i+j;
                            vecCard.push_back(card);
                            vecHuaSe.push_back(vecCard.size()-1);
                        }
                        m_nPutCardsTable[m_nBaoValue] -= nUsedCatCount;
                    }
                    nCount++;
                }
                else if (nCount !=0 )
                {
                    break;
                }
            }
            if(nCount == 12)
            {
                m_vecBaoArray.push_back(vecCard);
                m_vecHuaSeArray.push_back(vecHuaSe);
            }
        }
        m_nPutCardsTable[m_nBaoValue] = nTmpCatTable;
    }
    return 0;
}

int CPlayCards::Search222(bool m_bfirst,CCardsType& cCardsType)
{
    int nCount = 0;
    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 222)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }

    for(int i = nBegin; i < 13; i++)
    {
        bool bContinue = true;
        VECCARD vecCard;
        std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
        int nTmpCatTable = m_nPutCardsTable[m_nBaoValue];
        int usebao = 0; //������Ϊ�䱾����ֵʱ��
        for(int j = 0; j < 3; j++)
        {
            int nBaoCount = m_nPutCardsTable[m_nBaoValue] - usebao;
            if((i + j) == m_nBaoValue)
            {
                nBaoCount = 0;
                usebao = 2;
            }
            if(m_nPutCardsTable[i+j] + nBaoCount >= 2)
            {
                CCard card;						
                card.m_nValue = i + j;
                for(int k = 0; k < min(2,m_nPutCardsTable[i + j]); k++)
                {
                    vecCard.push_back(card);
                    if ( (i+j) == m_nBaoValue )
                    {
                        vecHuaSe.push_back(vecCard.size()-1);
                    }
                }
                if(m_nPutCardsTable[i + j] < 2)
                {
                    int nUsedCatCount = min(nBaoCount, 2 - m_nPutCardsTable[i + j]);
                    for(int k = 0; k < nUsedCatCount; k++)
                    {
                        card.m_nValue = i + j;
                        vecCard.push_back(card);
                        vecHuaSe.push_back(vecCard.size()-1);
                    }
                    m_nPutCardsTable[m_nBaoValue] -= nUsedCatCount;					
                }				
            }
            else
            {				
                bContinue = false;
                vecCard.clear();
                vecHuaSe.clear();
                break;
            }
        }
        m_nPutCardsTable[m_nBaoValue] = nTmpCatTable;

        if(bContinue)
        {
            m_vecBaoArray.push_back(vecCard);
            m_vecHuaSeArray.push_back(vecHuaSe);
        }		
    }
    return 0;
}

int CPlayCards::Search2222(bool m_bfirst,CCardsType& cCardsType)
{
    int nCount = 0;
    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 2222)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }

    for(int i = nBegin; i < 12; i++)
    {
        bool bContinue = true;
        VECCARD vecCard;
        std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
        int nTmpCatTable = m_nPutCardsTable[m_nBaoValue];
        int usebao = 0; //������Ϊ�䱾����ֵʱ��
        for(int j = 0; j < 4; j++)
        {
            int nBaoCount = m_nPutCardsTable[m_nBaoValue] - usebao;
            if((i + j) == m_nBaoValue)
            {
                nBaoCount = 0;
                usebao = 2;
            }
            if(m_nPutCardsTable[i+j] + nBaoCount >= 2)
            {
                CCard card;						
                card.m_nValue = i + j;
                for(int k = 0; k < min(2,m_nPutCardsTable[i + j]); k++)
                {
                    vecCard.push_back(card);
                    if ( (i+j) == m_nBaoValue )
                    {
                        vecHuaSe.push_back(vecCard.size()-1);
                    }
                }
                if(m_nPutCardsTable[i + j] < 2)
                {
                    int nUsedCatCount = min(nBaoCount, 2 - m_nPutCardsTable[i + j]);
                    for(int k = 0; k < nUsedCatCount; k++)
                    {
                        card.m_nValue = i + j;
                        vecCard.push_back(card);
                        vecHuaSe.push_back(vecCard.size()-1);
                    }
                    m_nPutCardsTable[m_nBaoValue] -= nUsedCatCount;					
                }				
            }
            else
            {				
                bContinue = false;
                vecCard.clear();
                vecHuaSe.clear();
                break;
            }
        }
        m_nPutCardsTable[m_nBaoValue] = nTmpCatTable;

        if(bContinue)
        {
            m_vecBaoArray.push_back(vecCard);
            m_vecHuaSeArray.push_back(vecHuaSe);
        }		
    }
    return 0;
}

int CPlayCards::Search22222(bool m_bfirst,CCardsType& cCardsType)
{
    int nCount = 0;
    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 22222)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }

    for(int i = nBegin; i < 11; i++)
    {
        bool bContinue = true;
        VECCARD vecCard;
        std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
        int nTmpCatTable = m_nPutCardsTable[m_nBaoValue];
        int usebao = 0; //������Ϊ�䱾����ֵʱ��
        for(int j = 0; j < 5; j++)
        {
            int nBaoCount = m_nPutCardsTable[m_nBaoValue] - usebao;
            if((i + j) == m_nBaoValue)
            {
                nBaoCount = 0;
                usebao = 2;
            }
            if(m_nPutCardsTable[i+j] + nBaoCount >= 2)
            {
                CCard card;						
                card.m_nValue = i + j;
                for(int k = 0; k < min(2,m_nPutCardsTable[i + j]); k++)
                {
                    vecCard.push_back(card);
                    if ( (i+j) == m_nBaoValue )
                    {
                        vecHuaSe.push_back(vecCard.size()-1);
                    }
                }
                if(m_nPutCardsTable[i + j] < 2)
                {
                    int nUsedCatCount = min(nBaoCount, 2 - m_nPutCardsTable[i + j]);
                    for(int k = 0; k < nUsedCatCount; k++)
                    {
                        card.m_nValue = i + j;
                        vecCard.push_back(card);
                        vecHuaSe.push_back(vecCard.size()-1);
                    }
                    m_nPutCardsTable[m_nBaoValue] -= nUsedCatCount;					
                }				
            }
            else
            {				
                bContinue = false;
                vecCard.clear();
                vecHuaSe.clear();
                break;
            }
        }
        m_nPutCardsTable[m_nBaoValue] = nTmpCatTable;

        if(bContinue)
        {
            m_vecBaoArray.push_back(vecCard);
            m_vecHuaSeArray.push_back(vecHuaSe);
        }		
    }
    return 0;
}

int CPlayCards::Search222222(bool m_bfirst,CCardsType& cCardsType)
{
    int nCount = 0;
    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 222222)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }

    for(int i = nBegin; i < 10; i++)
    {
        bool bContinue = true;
        VECCARD vecCard;
        std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
        int nTmpCatTable = m_nPutCardsTable[m_nBaoValue];
        int usebao = 0; //������Ϊ�䱾����ֵʱ��
        for(int j = 0; j < 6; j++)
        {
            int nBaoCount = m_nPutCardsTable[m_nBaoValue] - usebao;
            if((i + j) == m_nBaoValue)
            {
                nBaoCount = 0;
                usebao = 2;
            }
            if(m_nPutCardsTable[i+j] + nBaoCount >= 2)
            {
                CCard card;						
                card.m_nValue = i + j;
                for(int k = 0; k < min(2,m_nPutCardsTable[i + j]); k++)
                {
                    vecCard.push_back(card);
                    if ( (i+j) == m_nBaoValue )
                    {
                        vecHuaSe.push_back(vecCard.size()-1);
                    }
                }
                if(m_nPutCardsTable[i + j] < 2)
                {
                    int nUsedCatCount = min(nBaoCount, 2 - m_nPutCardsTable[i + j]);
                    for(int k = 0; k < nUsedCatCount; k++)
                    {
                        card.m_nValue = i + j;
                        vecCard.push_back(card);
                        vecHuaSe.push_back(vecCard.size()-1);
                    }
                    m_nPutCardsTable[m_nBaoValue] -= nUsedCatCount;					
                }				
            }
            else
            {				
                bContinue = false;
                vecCard.clear();
                vecHuaSe.clear();
                break;
            }
        }
        m_nPutCardsTable[m_nBaoValue] = nTmpCatTable;

        if(bContinue)
        {
            m_vecBaoArray.push_back(vecCard);
            m_vecHuaSeArray.push_back(vecHuaSe);
        }		
    }
    return 0;
}

int CPlayCards::Search33(bool m_bfirst,CCardsType& cCardsType)
{
    int nCount = 0;
    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 33)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }

    for(int i = nBegin; i < 14; i++)
    {
        bool bContinue = true;
        VECCARD vecCard;
        std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
        int nTmpCatTable = m_nPutCardsTable[m_nBaoValue];
        int usebao = 0; //������Ϊ�䱾����ֵʱ
        for(int j = 0; j < 2; j++)
        {
            int nBaoCount = m_nPutCardsTable[m_nBaoValue] - usebao;
            if((i + j) == m_nBaoValue)
            {
                nBaoCount = 0;
                usebao = 3; 
            }
            if(m_nPutCardsTable[i+j] + nBaoCount >= 3)
            {
                CCard card;
                card.m_nValue = i + j;
                for(int k = 0; k < min(3,m_nPutCardsTable[i + j]); k++)
                {
                    vecCard.push_back(card);
                    if ( (i+j) == m_nBaoValue )
                    {
                        vecHuaSe.push_back(vecCard.size()-1);
                    }
                }
                if(m_nPutCardsTable[i + j] < 3)
                {
                    int nUsedCatCount = min(nBaoCount, 3 - m_nPutCardsTable[i + j]);
                    for(int k = 0; k < nUsedCatCount; k++)
                    {
                        card.m_nValue = i + j;
                        vecCard.push_back(card);
                        vecHuaSe.push_back(vecCard.size()-1);
                    }
                    m_nPutCardsTable[m_nBaoValue] -= nUsedCatCount;
                }
            }
            else
            {
                bContinue = false;
                vecCard.clear();
                vecHuaSe.clear();
                break;
            }
        }
        m_nPutCardsTable[m_nBaoValue] = nTmpCatTable;

        if(bContinue)
        {
            m_vecBaoArray.push_back(vecCard);
            m_vecHuaSeArray.push_back(vecHuaSe);
        }
    }
    return 0;
}

int CPlayCards::Search333(bool m_bfirst,CCardsType& cCardsType)
{
    int nCount = 0;
    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 333)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }

    for(int i = nBegin; i < 13; i++)
    {
        bool bContinue = true;
        VECCARD vecCard;
        std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
        int nTmpCatTable = m_nPutCardsTable[m_nBaoValue];
        int usebao = 0; //������Ϊ�䱾����ֵʱ

        for(int j = 0; j < 3; j++)
        {
            int nBaoCount = m_nPutCardsTable[m_nBaoValue];
            if((i + j) == m_nBaoValue)
            {
                usebao = 3;
                nBaoCount = 0;
            }
            if(m_nPutCardsTable[i+j] + nBaoCount >= 3)
            {
                CCard card;						
                card.m_nValue = i + j;
                for(int k = 0; k < min(3,m_nPutCardsTable[i + j]); k++)
                {
                    vecCard.push_back(card);
                    if ( (i+j) == m_nBaoValue )
                    {
                        vecHuaSe.push_back(vecCard.size()-1);
                    }
                }
                if(m_nPutCardsTable[i + j] < 3)
                {
                    int nUsedCatCount = min(nBaoCount, 3 - m_nPutCardsTable[i + j]);
                    for(int k = 0; k < nUsedCatCount; k++)
                    {
                        card.m_nValue = i + j;
                        vecCard.push_back(card);
                        vecHuaSe.push_back(vecCard.size()-1);
                    }
                    m_nPutCardsTable[m_nBaoValue] -= nUsedCatCount;
                }				
            }
            else
            {				
                bContinue = false;
                vecCard.clear();
                vecHuaSe.clear();
                break;
            }
        }
        m_nPutCardsTable[m_nBaoValue] = nTmpCatTable;

        if(bContinue)
        {
            m_vecBaoArray.push_back(vecCard);
            m_vecHuaSeArray.push_back(vecHuaSe);
        }
    }
    return 0;
}
int CPlayCards::Search3333(bool m_bfirst,CCardsType& cCardsType)
{
    int nCount = 0;
    int nBegin = 3;
    if (m_bfirst)
    {
        if (cCardsType.m_nTypeNum != 3333)
        {
            return 0;
        }
        else
        {
            nBegin = cCardsType.m_nTypeValue + 1;
        }
    }

    for(int i = nBegin; i < 14; i++)
    {
        bool bContinue = true;
        VECCARD vecCard;
        std::vector<int> vecHuaSe;   //��¼��һ���аٴ��Ƶĵ�λ��
        int nTmpCatTable = m_nPutCardsTable[m_nBaoValue];
        int usebao = 0; //������Ϊ�䱾����ֵʱ
        for(int j = 0; j < 4; j++)
        {
            int nBaoCount = m_nPutCardsTable[m_nBaoValue] - usebao;
            if((i + j) == m_nBaoValue)
            {
                nBaoCount = 0;
                usebao = 3; 
            }
            if(m_nPutCardsTable[i+j] + nBaoCount >= 3)
            {
                CCard card;
                card.m_nValue = i + j;
                for(int k = 0; k < min(3,m_nPutCardsTable[i + j]); k++)
                {
                    vecCard.push_back(card);
                    if ( (i+j) == m_nBaoValue )
                    {
                        vecHuaSe.push_back(vecCard.size()-1);
                    }
                }
                if(m_nPutCardsTable[i + j] < 3)
                {
                    int nUsedCatCount = min(nBaoCount, 3 - m_nPutCardsTable[i + j]);
                    for(int k = 0; k < nUsedCatCount; k++)
                    {
                        card.m_nValue = i + j;
                        vecCard.push_back(card);
                        vecHuaSe.push_back(vecCard.size()-1);
                    }
                    m_nPutCardsTable[m_nBaoValue] -= nUsedCatCount;
                }
            }
            else
            {
                bContinue = false;
                vecCard.clear();
                vecHuaSe.clear();
                break;
            }
        }
        m_nPutCardsTable[m_nBaoValue] = nTmpCatTable;

        if(bContinue)
        {
            m_vecBaoArray.push_back(vecCard);
            m_vecHuaSeArray.push_back(vecHuaSe);
        }
    }
    return 0;
}
//int CPlayCards::CheckChoosing(CCardsType type)
//{
//    int i = 0;
//    ScandCardTable();
//    int Table_Index;
//    if (type.m_nTypeNum == 0)
//    {
//        switch(m_cChoosingCards.size())
//        {
//        case 0:
//            m_cDiscardingType.SetValue(0,0,0);
//            return 0;
//        case 1:
//            if( m_cChoosingCards[0].m_nValue == 16 )
//                m_cDiscardingType.SetValue(0,1,m_cChoosingCards[0].m_nValue+m_cChoosingCards[0].m_nColor);
//            else
//                m_cDiscardingType.SetValue(0,1,m_cChoosingCards[0].m_nValue);
//            return 1;
//        case 2://�Ƿ���һ����;
//            if( (Table_Index = Is2()) != 0 )
//            {
//                //�Ǵ���,��Ϊը��;
//                if(Table_Index == 16)
//                    m_cDiscardingType.SetValue(2,4,Table_Index);	//����Ϊ2��ʾը��;
//                else
//                    m_cDiscardingType.SetValue(0,2,Table_Index);
//                return 1;
//            }
//            return 0;
//        case 3:
//            if( (Table_Index = Is3()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,3,Table_Index);
//                return 1;
//            }
//            return 0;
//        case 4:
//            if( (Table_Index = IsHardBomb()) != 0 )
//            {
//                if (m_vecBaoArray.size() >= 2 || nChoose == 1)
//                {
//                    m_cDiscardingType.SetValue(1,4,Table_Index);
//                    return 1;
//                }
//                else
//                {
//                    m_cDiscardingType.SetValue(2,4,Table_Index);
//                    return 1;
//                }
//                ;
//            }
//
//            if(m_vecBaoArray.size()<=1 && nChoose == 0)  //��m_vecBaoArray.size()���ڻ����2ʱ�����������ε���,�����ڷ���ˣ�m_Sandaiyi = 1ʱ������Ҳ�����ε��ġ�
//            {
//                RevertTigerValue();
//                if( (Table_Index = IsSoftBomb()) != 0 )
//                {
//                    m_cDiscardingType.SetValue(1,4,Table_Index);
//                    return 1;
//                }
//            }
//
//            RevertTigerValue();
//            if( (Table_Index = Is31()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,31,Table_Index);
//                return 1;
//            }
//            return 0;
//        case 5:
//            if( (Table_Index = Is32()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,32,Table_Index);
//                return 1;
//            }
//            RevertTigerValue();
//            if( (Table_Index = IsSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,5,Table_Index);
//                return 1;
//            }		
//            return 0;
//        case 6:
//            if( (Table_Index = Is411()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,411,Table_Index);
//                return 1;
//            }	 
//            RevertTigerValue();
//            if( (Table_Index = IsThreeSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,33,Table_Index);
//                return 1;
//            }
//            RevertTigerValue();		
//            if( (Table_Index = IsDoubleSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,222,Table_Index);
//                return 1;
//            }
//            RevertTigerValue();
//            if( (Table_Index = IsSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,6,Table_Index);
//                return 1;
//            }		
//            return 0;
//        case 7:	//��˳
//            if( (Table_Index = IsSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,7,Table_Index);
//                return 1;
//            }
//            return 0;
//        case 8:		
//            if( (Table_Index = Is422()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,422,Table_Index);
//                return 1;
//            }
//            RevertTigerValue();
//            if( (Table_Index = Is3311()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,3311,Table_Index);
//                return 1;
//            }
//            RevertTigerValue();
//            if( (Table_Index = IsDoubleSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,2222,Table_Index);
//                return 1;
//            }
//            RevertTigerValue();
//            if( (Table_Index = IsSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,8,Table_Index);
//                return 1;
//            }		
//            return 0;
//        case 9:
//            if( (Table_Index = IsThreeSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,333,Table_Index);
//                return 1;
//            }
//            RevertTigerValue();
//            if( (Table_Index = IsSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,9,Table_Index);
//                return 1;
//            }
//            return 0;
//        case 10:
//            if( (Table_Index = Is3322()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,3322,Table_Index);
//                return 1;
//            }
//            RevertTigerValue();
//            if( (Table_Index = IsDoubleSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,22222,Table_Index);
//                return 1;
//            }
//            RevertTigerValue();
//            if( (Table_Index = IsSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,10,Table_Index);
//                return 1;
//            }		
//            return 0;
//        case 11:		
//            if( (Table_Index = IsSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,11,Table_Index);
//                return 1;
//            }
//            return 0;
//        case 12:
//            if( (Table_Index = Is333111()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,333111,Table_Index);
//                return 1;
//            }
//            RevertTigerValue();
//            if( (Table_Index = IsThreeSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,3333,Table_Index);
//                return 1;
//            }
//            RevertTigerValue();
//            if( (Table_Index = IsDoubleSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,222222,Table_Index);
//                return 1;
//            }
//            RevertTigerValue();
//            if( (Table_Index = IsSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,12,Table_Index);
//                return 1;
//            }
//            return 0;
//        case 13:
//            return 0;
//        case 14:		
//            if( (Table_Index = IsDoubleSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,2222222,Table_Index);
//                return 1;
//            }
//            return 0;
//        case 15:	
//            if( (Table_Index = Is333222()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,333222,Table_Index);
//                return 1;
//            }
//            RevertTigerValue();
//            if( (Table_Index = IsThreeSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,33333,Table_Index);
//                return 1;
//            }		
//            return 0;
//        case 16:	
//            if( (Table_Index = Is33331111()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,33331111,Table_Index);
//                return 1;
//            }
//            RevertTigerValue();
//            if( (Table_Index = IsDoubleSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,22222222,Table_Index);
//                return 1;
//            }
//            return 0;
//        case 17:
//            return 0;
//        case 18:
//            if( (Table_Index = IsThreeSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,333333,Table_Index);
//                return 1;
//            }
//            RevertTigerValue();
//            if( (Table_Index = IsDoubleSeries()) != 0 )
//            {
//                m_cDiscardingType.SetValue(0,222222222,Table_Index);
//                return 1;
//            }		
//            return 0;	
//        }
//    }
//    else
//    {
//         switch(type.m_nTypeNum)
//         {
//         case 1:
//             if( m_cChoosingCards[0].m_nValue == 16 )
//                 m_cDiscardingType.SetValue(0,1,m_cChoosingCards[0].m_nValue+m_cChoosingCards[0].m_nColor);
//             else
//                 m_cDiscardingType.SetValue(0,1,m_cChoosingCards[0].m_nValue);
//             return 1;
//         case 2:
//             if( (Table_Index = Is2()) != 0 )
//             {
//                 //�Ǵ���,��Ϊը��;
//                 if(Table_Index == 16)
//                     m_cDiscardingType.SetValue(2,4,Table_Index);	//����Ϊ2��ʾը��;
//                 else
//                     m_cDiscardingType.SetValue(0,2,Table_Index);
//                 return 1;
//             }
//             return 0;
//         case 3:
//             if( (Table_Index = Is3()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,3,Table_Index);
//                 return 1;
//             }
//             return 0;
//         case 4:
//             if( (Table_Index = IsHardBomb()) != 0 )
//             {
//                 if (m_vecBaoArray.size() >= 2 || nChoose == 1)
//                 {
//                     m_cDiscardingType.SetValue(1,4,Table_Index);
//                     return 1;
//                 }
//                 else
//                 {
//                     m_cDiscardingType.SetValue(2,4,Table_Index);
//                     return 1;
//                 }
//             }
//
//             if(m_vecBaoArray.size()<=1 && nChoose == 0)  //��m_vecBaoArray.size()���ڻ����2ʱ�����������ε���,�����ڷ���ˣ�m_Sandaiyi = 1ʱ������Ҳ�����ε��ġ�
//             {
//                 RevertTigerValue();
//                 if( (Table_Index = IsSoftBomb()) != 0 )
//                 {
//                     m_cDiscardingType.SetValue(1,4,Table_Index);
//                     return 1;
//                 }
//             }
//
//             RevertTigerValue();
//             if( (Table_Index = Is31()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,31,Table_Index);
//                 return 1;
//             }
//             return 0;
//         case 5:
//             if( (Table_Index = IsSeries()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,5,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();	
//             return 0;
//         case 6:
//             if( (Table_Index = IsSeries()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,5,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();	
//             return 0;
//         case 7:
//             if( (Table_Index = IsSeries()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,5,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();	
//             return 0;
//         case 8:
//             if( (Table_Index = IsSeries()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,5,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();	
//             return 0;
//         case 9:
//             if( (Table_Index = IsSeries()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,5,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();	
//             return 0;
//         case 10:
//             if( (Table_Index = IsSeries()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,5,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();	
//             return 0;
//         case 11:
//             if( (Table_Index = IsSeries()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,5,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();	
//             return 0;
//         case 12:
//             if( (Table_Index = IsSeries()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,5,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();	
//             return 0;
//         case 13:
//             if( (Table_Index = IsSeries()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,5,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();	
//             return 0;
//         case 222:
//             if( (Table_Index = IsDoubleSeries()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,222,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();
//             return 0;
//         case 2222:
//             if( (Table_Index = IsDoubleSeries()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,222,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();
//             return 0;
//         case 22222:
//             if( (Table_Index = IsDoubleSeries()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,222,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();
//             return 0;
//         case 2222222:
//             if( (Table_Index = IsDoubleSeries()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,222,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();
//             return 0;
//         case 22222222:
//             if( (Table_Index = IsDoubleSeries()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,222,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();
//             return 0;
//         case 33:
//             if( (Table_Index = IsThreeSeries()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,33,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();
//             return 0;
//         case 333:
//             if( (Table_Index = IsThreeSeries()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,33,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();
//             return 0;
//         case 3333:
//             if( (Table_Index = IsThreeSeries()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,33,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();
//             return 0;
//         case 33333:
//             if( (Table_Index = IsThreeSeries()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,33,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();
//             return 0;
//         case 333333:
//             if( (Table_Index = IsThreeSeries()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,33,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();
//             return 0;
//         case 31:
//             if( (Table_Index = Is31()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,31,Table_Index);
//                 return 1;
//             }
//              RevertTigerValue();
//             return 0;
//         case 3311:
//             if( (Table_Index = Is3311()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,3311,Table_Index);
//                 return 1;
//             }
//              RevertTigerValue();
//             return 0;
//         case 333111:
//             if( (Table_Index = Is333111()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,333111,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();
//             return 0;
//         case 33331111:
//             if( (Table_Index = Is33331111()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,33331111,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();
//             return 0;
//         case 32:
//             if( (Table_Index = Is32()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,32,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();
//             return 0;
//         case 3322:
//             if( (Table_Index = Is3322()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,3322,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();
//             return 0;
//         case 333222:
//             if( (Table_Index = Is333222()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,333222,Table_Index);
//                 return 1;
//             }
//             RevertTigerValue();
//             return 0;
//         case 411:
//             if( (Table_Index = Is411()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,411,Table_Index);
//                 return 1;
//             }	 
//             RevertTigerValue();
//             return 0;
//         case 422:
//             if( (Table_Index = Is422()) != 0 )
//             {
//                 m_cDiscardingType.SetValue(0,422,Table_Index);
//                 return 1;
//             }	 
//             RevertTigerValue();
//             return 0;
//         }
//    }
//    return 0;
//}
/*
* �������ܣ������Ƶ��߼��Ϸ���;
* ����ֵ �� ƥ��ɹ�����1,���ɹ�����0;
*/
int CPlayCards::CheckChoosing()
{
	int i = 0;
	ScandCardTable();
	int Table_Index;

	switch(m_cChoosingCards.size())
	{
	case 0:
		m_cDiscardingType.SetValue(0,0,0);
		return 0;
	case 1:
		if( m_cChoosingCards[0].m_nValue == 16 )
			m_cDiscardingType.SetValue(0,1,m_cChoosingCards[0].m_nValue+m_cChoosingCards[0].m_nColor);
		else
			m_cDiscardingType.SetValue(0,1,m_cChoosingCards[0].m_nValue);
		return 1;
	case 2://�Ƿ���һ����;
		if( (Table_Index = Is2()) != 0 )
		{
			//�Ǵ���,��Ϊը��;
			if(Table_Index == 16)
				m_cDiscardingType.SetValue(2,4,Table_Index);	//����Ϊ2��ʾը��;
			else
				m_cDiscardingType.SetValue(0,2,Table_Index);
			return 1;
		}
		return 0;
	case 3:
		if( (Table_Index = Is3()) != 0 )
		{
			m_cDiscardingType.SetValue(0,3,Table_Index);
			return 1;
		}
		return 0;
	case 4:
		if( (Table_Index = IsHardBomb()) != 0 )
		{
            if (m_vecBaoArray.size() >= 2 || nChoose == 1)
            {
                m_cDiscardingType.SetValue(1,4,Table_Index);
                return 1;
            }
            else
            {
                m_cDiscardingType.SetValue(2,4,Table_Index);
                return 1;
            }
		}

        if(m_vecBaoArray.size()<=1 && nChoose == 0)  //��m_vecBaoArray.size()���ڻ����2ʱ�����������ε���,�����ڷ���ˣ�m_Sandaiyi = 1ʱ������Ҳ�����ε��ġ�
        {
            RevertTigerValue();
            if( (Table_Index = IsSoftBomb()) != 0 )
            {
                m_cDiscardingType.SetValue(1,4,Table_Index);
                return 1;
            }
        }

		RevertTigerValue();
		if( (Table_Index = Is31()) != 0 )
		{
			m_cDiscardingType.SetValue(0,31,Table_Index);
			return 1;
		}
		return 0;
	case 5:
		if( (Table_Index = Is32()) != 0 )
		{
			m_cDiscardingType.SetValue(0,32,Table_Index);
			return 1;
		}
		RevertTigerValue();
		if( (Table_Index = IsSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,5,Table_Index);
			return 1;
		}		
		return 0;
	case 6:
       // glog.log("lasttype:%d",lasttype);
        if (lasttype != 222)
        {
            if( (Table_Index = Is411()) != 0 )
            {
                m_cDiscardingType.SetValue(0,411,Table_Index);
   
                return 1;
            }	 
        }
		RevertTigerValue();
		if( (Table_Index = IsThreeSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,33,Table_Index);
			return 1;
		}
		RevertTigerValue();		
		if( (Table_Index = IsDoubleSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,222,Table_Index);
			return 1;
		}
		RevertTigerValue();
		if( (Table_Index = IsSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,6,Table_Index);
			return 1;
		}		
		return 0;
	case 7:	//��˳
		if( (Table_Index = IsSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,7,Table_Index);
			return 1;
		}
		return 0;
	case 8:		
        if (lasttype != 2222)
        {
            if( (Table_Index = Is422()) != 0 )
            {
                m_cDiscardingType.SetValue(0,422,Table_Index);
                return 1;
            } 
        }
		RevertTigerValue();

        if (lasttype != 2222)
        {
            if( (Table_Index = Is3311()) != 0 )
            {
                m_cDiscardingType.SetValue(0,3311,Table_Index);
                return 1;
            }
        }
		RevertTigerValue();

		if( (Table_Index = IsDoubleSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,2222,Table_Index);
			return 1;
		}
		RevertTigerValue();

		if( (Table_Index = IsSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,8,Table_Index);
			return 1;
		}		
		return 0;
	case 9:
		if( (Table_Index = IsThreeSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,333,Table_Index);
			return 1;
		}
		RevertTigerValue();
		if( (Table_Index = IsSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,9,Table_Index);
			return 1;
		}
		return 0;
	case 10:
		if( (Table_Index = Is3322()) != 0 )
		{
			m_cDiscardingType.SetValue(0,3322,Table_Index);
			return 1;
		}
		RevertTigerValue();
		if( (Table_Index = IsDoubleSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,22222,Table_Index);
			return 1;
		}
		RevertTigerValue();
		if( (Table_Index = IsSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,10,Table_Index);
			return 1;
		}		
		return 0;
	case 11:		
		if( (Table_Index = IsSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,11,Table_Index);
			return 1;
		}
		return 0;
	case 12:
		if( (Table_Index = Is333111()) != 0 )
		{
			m_cDiscardingType.SetValue(0,333111,Table_Index);
			return 1;
		}
		RevertTigerValue();
		if( (Table_Index = IsThreeSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,3333,Table_Index);
			return 1;
		}
		RevertTigerValue();
		if( (Table_Index = IsDoubleSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,222222,Table_Index);
			return 1;
		}
		RevertTigerValue();
		if( (Table_Index = IsSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,12,Table_Index);
			return 1;
		}
		return 0;
	case 13:
		return 0;
	case 14:		
		if( (Table_Index = IsDoubleSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,2222222,Table_Index);
			return 1;
		}
		return 0;
	case 15:	
		if( (Table_Index = Is333222()) != 0 )
		{
			m_cDiscardingType.SetValue(0,333222,Table_Index);
			return 1;
		}
		RevertTigerValue();
		if( (Table_Index = IsThreeSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,33333,Table_Index);
			return 1;
		}		
		return 0;
	case 16:	
		if( (Table_Index = Is33331111()) != 0 )
		{
			m_cDiscardingType.SetValue(0,33331111,Table_Index);
			return 1;
		}
		RevertTigerValue();
		if( (Table_Index = IsDoubleSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,22222222,Table_Index);
			return 1;
		}
		return 0;
	case 17:
		return 0;
	case 18:
		if( (Table_Index = IsThreeSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,333333,Table_Index);
			return 1;
		}
		RevertTigerValue();
		if( (Table_Index = IsDoubleSeries()) != 0 )
		{
			m_cDiscardingType.SetValue(0,222222222,Table_Index);
			return 1;
		}		
		return 0;	
	}	
	return 0;
}

int CPlayCards::CompareCards(CCardsType& cardType)
{
	if( m_cDiscardingType.m_nTypeNum == 0 )
		return 1;

	//��С�ж�;
	if( cardType.m_nTypeNum != 0 )
	{
		if( m_cDiscardingType.m_nTypeBomb > cardType.m_nTypeBomb )
		{
			return 1;
		}
		else if( m_cDiscardingType.m_nTypeBomb < cardType.m_nTypeBomb )
		{
			return 0;
		}
		else
		{
			if( m_cDiscardingType.m_nTypeNum != cardType.m_nTypeNum )
			{
				return 0;
			}
			else
			{	
				//���������ͬ;
				if( m_cDiscardingType.m_nTypeValue >  cardType.m_nTypeValue )
				{
					return 1;  //�Ϸ�;
				}
				else
				{
					return 0; //���Ϸ�;
				}
			}
		}
	}
	return 1;
}

void CPlayCards::ScandCardTable()
{
	//��ʼ��ɨ���
	memset(m_nDiscardingCardsTable, 0, sizeof(m_nDiscardingCardsTable));
	//ɨ�������
	for(size_t i = 0; i < m_cChoosingCards.size(); i++)
	{
		m_nDiscardingCardsTable[(int)m_cChoosingCards[i].m_nValue]++;
	}
	m_nDiscardingCardsTable[BAO] = m_nDiscardingCardsTable[m_nBaoValue];
	m_nDiscardingCardsTable[m_nBaoValue] = 0;
}

int CPlayCards::GetBomb()
{
	int nBomb = 0;
	TipScanCardTable();

	for(int i = 0; i < 16; i++)
	{
		if( m_nDiscardingCardsTable[i] == 4 )
			nBomb++;
	}
	if( m_nDiscardingCardsTable[16] == 2 )
		nBomb++;
	return nBomb;
}

void CPlayCards::TipScanCardTable()
{
	//��ʼ��ɨ���
	memset(m_nDiscardingCardsTable, 0, sizeof(m_nDiscardingCardsTable));
	//ɨ�������;
	for(size_t i = 0; i < m_cCards.size(); i++)
	{
		m_nDiscardingCardsTable[(int)m_cCards[i].m_nValue]++;
	}
}
void CPlayCards::ScanPutCardsTable()
{
    // m_nPutCardsTable
    //��ʼ��ɨ���
    memset(m_nPutCardsTable, 0, sizeof(m_nPutCardsTable));
    //ɨ�������
    for(size_t i = 0; i < m_cChoosingCards.size(); i++)
    {
        m_nPutCardsTable[(int)m_cChoosingCards[i].m_nValue]++;
    }
}

int CPlayCards::Tips()
{
	//��ʼ��ɨ���
	m_vecTipsCards.clear();
	TipScanCardTable();
	//�ӵ����ƿ�ʼ��ʾ
	for(int i = 1; i <= 4; i++)
	{
		for(int j = 0; j <= 16; j++)
		{
			if( m_nDiscardingCardsTable[j] == i || (j == 16 && m_nDiscardingCardsTable[j] == i && i == 1) )
			{
				VECCARD vecCard;
				CCard cCard(0,j);
				for(int n = 0; n < i; n++)
				{
					vecCard.push_back(cCard);
				}
				m_vecTipsCards.push_back(vecCard);
			}
		}
	}
	//2����
	if( m_nDiscardingCardsTable[16] == 2 )
	{
		CCard cCard(0,16);
		VECCARD vecCard;
		vecCard.push_back(cCard);
		vecCard.push_back(cCard);
		m_vecTipsCards.push_back(vecCard);
	}
	return 0;
}

int CPlayCards::Tips(CCardsType& cCardsType)
{
	int nRet = 0;
	m_vecTipsCards.clear();
	TipScanCardTable();

	switch(cCardsType.m_nTypeNum) 
	{
	case 1: nRet = TipsSearch1(cCardsType); break;
	case 2: nRet = TipsSearch2(cCardsType); break;
	case 3: nRet = TipsSearch3(cCardsType); break;
	case 4: nRet = TipsSearch4(cCardsType); break;
	case 5: nRet = TipsSearch5(cCardsType); break;
	case 6: nRet = TipsSearch6(cCardsType); break;
	case 7: nRet = TipsSearch7(cCardsType); break;
	case 8: nRet = TipsSearch8(cCardsType); break;
	case 9: nRet = TipsSearch9(cCardsType); break;
	case 10: nRet = TipsSearch10(cCardsType); break;
	case 11: nRet = TipsSearch11(cCardsType); break;
	case 12: nRet = TipsSearch12(cCardsType); break;
	case 31: nRet = TipsSearch31(cCardsType); break;
	case 32: nRet = TipsSearch32(cCardsType); break;
	case 33: nRet = TipsSearch33(cCardsType); break;
	case 222: nRet = TipsSearch222(cCardsType); break;
	case 333: nRet = TipsSearch333(cCardsType); break;
	case 411: nRet = TipsSearch411(cCardsType); break;
	case 422: nRet = TipsSearch422(cCardsType); break;
	case 2222: nRet = TipsSearch2222(cCardsType); break;
	case 3322: nRet = TipsSearch3322(cCardsType); break;
	case 3333: nRet = TipsSearch3333(cCardsType); break;
	case 3311: nRet = TipsSearch3311(cCardsType); break;
	case 22222: nRet = TipsSearch22222(cCardsType); break;
	case 33333: nRet = TipsSearch33333(cCardsType); break;
	case 222222: nRet = TipsSearch222222(cCardsType); break;
	case 333111: nRet = TipsSearch333111(cCardsType); break;
	case 333222: nRet = TipsSearch333222(cCardsType); break;
	case 333333: nRet = TipsSearch333333(cCardsType); break;
	case 2222222: nRet = TipsSearch2222222(cCardsType); break;
	case 22222222: nRet = TipsSearch22222222(cCardsType); break;
	case 33331111: nRet = TipsSearch33331111(cCardsType); break;
	case 222222222: nRet = TipsSearch222222222(cCardsType); break;
	default:
		break;
	}
	if( cCardsType.m_nTypeNum != 4 || (cCardsType.m_nTypeNum == 2 && cCardsType.m_nTypeValue != 16) )
	{
        int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
        //��ը��������һ������
        for (int i = 3 ; i < 16; i++)
        {
            if (m_nDiscardingCardsTable[i] == 3 && (i != m_nBaoValue) && nBaoCount>=1)
            {
                CCard card;
                VECCARD vecCard;
                card.m_nValue = i;
                vecCard.push_back(card);
                vecCard.push_back(card);
                vecCard.push_back(card);
                card.m_nValue = m_nBaoValue;
                vecCard.push_back(card);
                if(vecCard.size()==4)
                {
                    m_vecTipsCards.push_back(vecCard);
                } 
            }
        }
        //��ը����������������
        for (int i = 3 ; i < 16; i++)
        {
            if (m_nDiscardingCardsTable[i] == 2 &&(i != m_nBaoValue) && nBaoCount >=2)
            {
                CCard card;
                VECCARD vecCard;
                card.m_nValue = i;
                vecCard.push_back(card);
                vecCard.push_back(card);
                card.m_nValue = m_nBaoValue;
                vecCard.push_back(card);
                vecCard.push_back(card);
                if(vecCard.size()==4)
                {
                    m_vecTipsCards.push_back(vecCard);
                } 
            }
        }

        //��ը����һ��������
        for (int i = 3 ; i < 16; i++)
        {
            if (m_nDiscardingCardsTable[i] == 1 && nBaoCount >= 3)
            {
                CCard card;
                VECCARD vecCard;
                card.m_nValue = i;
                vecCard.push_back(card);
                card.m_nValue = m_nBaoValue;
                vecCard.push_back(card);
                vecCard.push_back(card);
                vecCard.push_back(card);
                if(vecCard.size()==4)
                {
                    m_vecTipsCards.push_back(vecCard);
                } 
            }
        }

		//ը��
		for(int i = 3; i < 16; i++)
		{
			if(m_nDiscardingCardsTable[i] >= 4)
			{
				CCard card;
				VECCARD vecCard;
				card.m_nValue = i;
				vecCard.push_back(card);
				vecCard.push_back(card);
				vecCard.push_back(card);
				vecCard.push_back(card);
                if(vecCard.size()==4)
                {
                    m_vecTipsCards.push_back(vecCard);
                } 
			}
		}
		//�Թ�
		if(m_nDiscardingCardsTable[16] == 2)
		{
			CCard card;
			VECCARD vecCard;
			card.m_nValue = 16;
			vecCard.push_back(card);
			vecCard.push_back(card);
			m_vecTipsCards.push_back(vecCard);
		}
	}
	return nRet;
}

// �ڿͻ���ʹ�ã�������Ϲ���ĸ������
int CPlayCards::TipsSearch1(CCardsType& cCardsType)
{	
	int nBegin = cCardsType.m_nTypeValue + 1;	
	
	if(cCardsType.m_nTypeValue == 16)
	{
		for(size_t i = 0; i < m_cCards.size(); i++)
		{
			if(m_cCards[i].m_nValue == 16 && m_cCards[i].m_nColor == 1)
			{
				CCard card;
				VECCARD vecCard;
				card.m_nValue = 16;
				vecCard.push_back(card);
				m_vecTipsCards.push_back(vecCard);
				return 0;
			}
		}
	}

	for(int i = nBegin; i < 17; i++)
	{
		if(m_nDiscardingCardsTable[i] == 1)
		{
			CCard card;
			VECCARD vecCard;
			card.m_nValue = i;
			vecCard.push_back(card);
			m_vecTipsCards.push_back(vecCard);
		}
	} 

	for(int i = nBegin; i < 17; i++)
	{
		if(m_nDiscardingCardsTable[i] > 1)
		{
			CCard card;
			VECCARD vecCard;
			card.m_nValue = i;
			vecCard.push_back(card);
			m_vecTipsCards.push_back(vecCard);
		}
	}
	return 0;
}

int CPlayCards::TipsSearch2(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;

	for(int i = nBegin; i < 16; i++)
	{
		int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
		if(i == m_nBaoValue)
		{
			nBaoCount = 0;
		}
		if(m_nDiscardingCardsTable[i] + nBaoCount >= 2)
		{
			CCard card;	
			VECCARD vecCard;
			card.m_nValue = i;
			for(int j = 0; j < min(2,m_nDiscardingCardsTable[i]); j++)
			{
				vecCard.push_back(card);
			}
			if(m_nDiscardingCardsTable[i] == 1)
			{
				int nUsedCatCount = min(nBaoCount, 2 - m_nDiscardingCardsTable[i]);
				for(int k = 0; k < nUsedCatCount; k++)
				{
					card.m_nValue = m_nBaoValue;
					vecCard.push_back(card);
				}					
			}
			if(m_nDiscardingCardsTable[i] != 0)
			{
				m_vecTipsCards.push_back(vecCard);
			}			
		}		
	}
	return 0;
}

int CPlayCards::TipsSearch3(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;

	for(int i = nBegin; i < MAXTYPENUM; i++)
	{
		int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
		if(i == m_nBaoValue)
		{
			nBaoCount = 0;
		}
		if(m_nDiscardingCardsTable[i] + nBaoCount >= 3)
		{
			CCard card;		
			VECCARD vecCard;
			card.m_nValue = i;
			for(int j = 0; j < min(3,m_nDiscardingCardsTable[i]); j++)
			{
				vecCard.push_back(card);
			}
			int nUsedCatCount = min(nBaoCount, 3 - m_nDiscardingCardsTable[i]);
			for(int k = 0; k < nUsedCatCount; k++)
			{
				card.m_nValue = m_nBaoValue;
				vecCard.push_back(card);
			}
			if(m_nDiscardingCardsTable[i] != 0)
			{
				m_vecTipsCards.push_back(vecCard);
			}			
		}		
	}
	return 0;
}

int CPlayCards::TipsSearch4(CCardsType& cCardsType)
{   
	int nBegin = cCardsType.m_nTypeValue + 1;
	if(cCardsType.m_nTypeNum == 4)
	{		
		if(cCardsType.m_nTypeBomb == 1)
		{
			for(int i = 3; i < nBegin; i++)
			{
				if(m_nDiscardingCardsTable[i] >= 4)
				{
					CCard card;
					VECCARD vecCard;
					card.m_nValue = i;
					vecCard.push_back(card);
					vecCard.push_back(card);
					vecCard.push_back(card);
					vecCard.push_back(card);
					m_vecTipsCards.push_back(vecCard);
				}
			}

			for(int i = nBegin; i < 16; i++)
			{
				int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
				if(i == m_nBaoValue)
				{
					nBaoCount = 0;
				}
				if(m_nDiscardingCardsTable[i] + nBaoCount >= 4)
				{
					CCard card;
					VECCARD vecCard;
					card.m_nValue = i;
					for(int j = 0; j < min(4,m_nDiscardingCardsTable[i]); j++)
					{
						vecCard.push_back(card);
					}
					int nUsedCatCount = min(nBaoCount, 4 - m_nDiscardingCardsTable[i]);
					for(int k = 0; k < nUsedCatCount; k++)
					{
						card.m_nValue = m_nBaoValue;
						vecCard.push_back(card);
					}				
					if(m_nDiscardingCardsTable[i] != 0)
					{
						m_vecTipsCards.push_back(vecCard);
					}			
				}		
			}
		}
		else if(cCardsType.m_nTypeBomb == 2)
		{
			for(int i = nBegin; i < 16; i++)
			{
				if(m_nDiscardingCardsTable[i] >= 4)
				{
					CCard card;
					VECCARD vecCard;
					card.m_nValue = i;
					vecCard.push_back(card);
					vecCard.push_back(card);
					vecCard.push_back(card);
					vecCard.push_back(card);
					m_vecTipsCards.push_back(vecCard);
				}
			}

            //�Թ�
            if(m_nDiscardingCardsTable[16] == 2)
            {
                CCard card;
                VECCARD vecCard;
                card.m_nValue = 16;
                vecCard.push_back(card);
                vecCard.push_back(card);
                m_vecTipsCards.push_back(vecCard);
            }
		}
	}
	else
	{
		for(int i = 3; i < 16; i++)
		{
			int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
			if(i == m_nBaoValue)
			{
				nBaoCount = 0;
			}
			if(m_nDiscardingCardsTable[i] + nBaoCount >= 4)
			{
				CCard card;		
				VECCARD vecCard;
				card.m_nValue = i;
				for(int j = 0; j < min(4,m_nDiscardingCardsTable[i]); j++)
				{
					vecCard.push_back(card);
				}
				int nUsedCatCount = min(nBaoCount, 4 - m_nDiscardingCardsTable[i]);
				for(int k = 0; k < nUsedCatCount; k++)
				{
					card.m_nValue = m_nBaoValue;
					vecCard.push_back(card);
				}
				if(m_nDiscardingCardsTable[i] != 0)
				{
					m_vecTipsCards.push_back(vecCard);		
				}
			}
		}
	}

	//�Թ�
	if(m_nDiscardingCardsTable[16] == 2)
	{
		CCard card;
		VECCARD vecCard;
		card.m_nValue = 16;
		vecCard.push_back(card);
		vecCard.push_back(card);
		m_vecTipsCards.push_back(vecCard);
	}

	return 0;
}

//����һ
int CPlayCards::TipsSearch31(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 16; i++)
	{
		int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
		if(i == m_nBaoValue)
		{
			nBaoCount = 0;
		}
		if(m_nDiscardingCardsTable[i] + nBaoCount >= 3)
		{
			CCard card;		
			VECCARD vecCard;
			card.m_nValue = i;
			for(int j = 0; j < min(3,m_nDiscardingCardsTable[i]); j++)
			{
				vecCard.push_back(card);
			}
			int nUsedCatCount = min(nBaoCount, 3 - m_nDiscardingCardsTable[i]);
			for (int k = 0; k < nUsedCatCount; k++)
			{
				card.m_nValue = m_nBaoValue;
				vecCard.push_back(card);
			}
			for(int j = 3; j < 17; j++)
			{
				if(m_nDiscardingCardsTable[j] >= 1 && (i!=j) && (j != m_nBaoValue))
				{
					CCard card;					
					card.m_nValue = j;
					vecCard.push_back(card);
					if(m_nDiscardingCardsTable[i] != 0)
					{
						m_vecTipsCards.push_back(vecCard);
						break;
					}
				}
			}
		}
	}
	return 0;
}

//��˳��
int CPlayCards::TipsSearch5(CCardsType& cCardsType)
{
	int nCount = 0;
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 11; i++)
	{
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
        int usebao = 0;
		if(m_nDiscardingCardsTable[i] >= 1)
		{
			nCount = 0;
			CCard card;
			VECCARD vecCard;
			for(int j = 0; j < 5; j++)
			{
				int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue] - usebao;
				if((i + j) == m_nBaoValue)
				{
					nBaoCount = 0;
                    usebao = 1;
				}
				if(m_nDiscardingCardsTable[i + j] + nBaoCount >= 1)
				{
					card.m_nValue = i + j;
					for(int k = 0; k < min(1,m_nDiscardingCardsTable[i + j]); k++)
					{
						vecCard.push_back(card);
					}
					if(m_nDiscardingCardsTable[i + j] < 1)
					{
						int nUsedCatCount = min(nBaoCount, 1 - m_nDiscardingCardsTable[i + j]);
						for(int k = 0; k < nUsedCatCount; k++)
						{
							card.m_nValue = m_nBaoValue;
							vecCard.push_back(card);
						}
						m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;
					}
					nCount++;
				}
			}
			if(nCount == 5)
			{
				m_vecTipsCards.push_back(vecCard);
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;
	}
	return 0;
}

//������
int CPlayCards::TipsSearch32(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 16; i++)
	{
		int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
		if(i == m_nBaoValue)
		{
			nBaoCount = 0;
		}
		if(m_nDiscardingCardsTable[i] + nBaoCount >= 3)
		{
			CCard card;
			VECCARD vecCard;
			card.m_nValue = i;
			for(int j = 0; j < min(3,m_nDiscardingCardsTable[i]); j++)
			{
				vecCard.push_back(card);
			}
			int nUsedCatCount = min(nBaoCount, 3 - m_nDiscardingCardsTable[i]);
			for(int k = 0; k < nUsedCatCount; k++)
			{
				card.m_nValue = m_nBaoValue;
				vecCard.push_back(card);
			}
			for(int j = 3; j < 17; j++)
			{
				if(m_nDiscardingCardsTable[j] >= 2 && (i!=j) && (j != m_nBaoValue))
				{
					CCard card;
					card.m_nValue = j;
					vecCard.push_back(card);
					vecCard.push_back(card);
					if (m_nDiscardingCardsTable[i] != 0)
					{
						m_vecTipsCards.push_back(vecCard);
						break;
					}
				}
			}
		}
	}

	return 0;
}

//��˳��
int CPlayCards::TipsSearch6(CCardsType& cCardsType)
{
	int nCount = 0;
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 10; i++)
	{
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
        int usebao = 0;
		if(m_nDiscardingCardsTable[i] >= 1)
		{
			nCount = 0;
			CCard card;
			VECCARD vecCard;
			for(int j = 0; j < 6; j++)
			{
				int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue] - usebao;
				if((i + j) == m_nBaoValue)
				{
					nBaoCount = 0;
                    usebao = 1;
				}
				if(m_nDiscardingCardsTable[i + j] + nBaoCount >= 1)
				{
					card.m_nValue = i + j;
					for(int k = 0; k < min(1,m_nDiscardingCardsTable[i + j]); k++)
					{
						vecCard.push_back(card);
					}
					if(m_nDiscardingCardsTable[i + j] < 1)
					{
						int nUsedCatCount = min(nBaoCount, 1 - m_nDiscardingCardsTable[i + j]);
						for(int k = 0; k < nUsedCatCount; k++)
						{
							card.m_nValue = m_nBaoValue;
							vecCard.push_back(card);
						}
						m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;
					}
					nCount++;
				}
			}
			if(nCount == 6)
			{
				m_vecTipsCards.push_back(vecCard);
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;
	}
	return 0;
}

int CPlayCards::TipsSearch222(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 13; i++)
	{
		bool bContinue = true;
		VECCARD vecCard;
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
        int usebao = 0;
		for(int j = 0; j < 3; j++)
		{
			int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue] - usebao;
			if((i + j) == m_nBaoValue)
			{
                if (nBaoCount >=2 )
                {
                    usebao = 2;
                }
                else if (nBaoCount >= 1)
                {
                    usebao = 1;
                }
				nBaoCount = 0;
			}
			if(m_nDiscardingCardsTable[i+j] + nBaoCount >= 2)
			{
				CCard card;						
				card.m_nValue = i + j;
				for(int k = 0; k < min(2,m_nDiscardingCardsTable[i + j]); k++)
				{
					vecCard.push_back(card);
				}
				if(m_nDiscardingCardsTable[i + j] < 2)
				{
					int nUsedCatCount = min(nBaoCount, 2 - m_nDiscardingCardsTable[i + j]);
					for(int k = 0; k < nUsedCatCount; k++)
					{
						card.m_nValue = m_nBaoValue;
						vecCard.push_back(card);
					}
					m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;					
				}				
			}
			else
			{				
				bContinue = false;
				vecCard.clear();
				break;
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;
		
		if(bContinue)
		{
			m_vecTipsCards.push_back(vecCard);
		}		
	}
	return 0;
}

// ����
int CPlayCards::TipsSearch33(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 14; i++)
	{
		bool bContinue = true;
		VECCARD vecCard;
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
		for(int j = 0; j < 2; j++)
		{
			int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
			if((i + j) == m_nBaoValue)
			{
				nBaoCount = 0;
			}
			if(m_nDiscardingCardsTable[i+j] + nBaoCount >= 3)
			{
				CCard card;
				card.m_nValue = i + j;
				for(int k = 0; k < min(3,m_nDiscardingCardsTable[i + j]); k++)
				{
					vecCard.push_back(card);
				}
				if(m_nDiscardingCardsTable[i + j] < 3)
				{
					int nUsedCatCount = min(nBaoCount, 3 - m_nDiscardingCardsTable[i + j]);
					for(int k = 0; k < nUsedCatCount; k++)
					{
						card.m_nValue = m_nBaoValue;
						vecCard.push_back(card);
					}
					m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;
				}
			}
			else
			{
				bContinue = false;
				vecCard.clear();
				break;
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;

		if(bContinue)
		{
			m_vecTipsCards.push_back(vecCard);
		}
	}
	return 0;
}

// �Ĵ�����
int CPlayCards::TipsSearch411(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 16; i++)
	{
		int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
		if(i == m_nBaoValue)
		{
			nBaoCount = 0;
		}		
		if(m_nDiscardingCardsTable[i] + nBaoCount >= 4)
		{			
			VECCARD vecCard;
			CCard card;		
			card.m_nValue = i;
			for(int j = 0; j < min(4,m_nDiscardingCardsTable[i]); j++)
			{
				vecCard.push_back(card);
			}
			int nUsedCatCount = min(nBaoCount, 4 - m_nDiscardingCardsTable[i]);
			for(int k = 0; k < nUsedCatCount; k++)
			{
				card.m_nValue = m_nBaoValue;
				vecCard.push_back(card);
			}
			int nCount = 0;
			for(int j = 3; j < 16; j++)
			{
				if(m_nDiscardingCardsTable[j] >= 1 && (i!=j) && (j != m_nBaoValue))
				{
					CCard card;					
					card.m_nValue = j;
					vecCard.push_back(card);
					if(++nCount >= 2)
					{
						if(m_nDiscardingCardsTable[i] != 0)
						{
							m_vecTipsCards.push_back(vecCard);
						}	
						break;
					}
				}
			}
		}
	}
	return 0;
}

// 7˳
int CPlayCards::TipsSearch7(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	int nCount = 0;
	for(int i = nBegin; i < 9; i++)
	{
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
        int usebao = 0;
		if(m_nDiscardingCardsTable[i] >= 1)
		{
			nCount = 0;
			CCard card;
			VECCARD vecCard;
			for(int j = 0; j < 7; j++)
			{
				int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue] - usebao;
				if((i + j) == m_nBaoValue)
				{
					nBaoCount = 0;
                    usebao = 1;
				}
				if(m_nDiscardingCardsTable[i + j] + nBaoCount >= 1)
				{
					card.m_nValue = i + j;
					for(int k = 0; k < min(1,m_nDiscardingCardsTable[i + j]); k++)
					{
						vecCard.push_back(card);
					}
					if(m_nDiscardingCardsTable[i + j] < 1)
					{
						int nUsedCatCount = min(nBaoCount, 1 - m_nDiscardingCardsTable[i + j]);
						for(int k = 0; k < nUsedCatCount; k++)
						{
							card.m_nValue = m_nBaoValue;
							vecCard.push_back(card);
						}
						m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;
					}
					nCount++;
				}
			}
			if(nCount == 7)
			{
				m_vecTipsCards.push_back(vecCard);
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;		
	}
	return 0;
}

// 8˳
int CPlayCards::TipsSearch8(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	int nCount = 0;
	for(int i = nBegin; i < 8; i++)
	{
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
        int usebao = 0;
		if(m_nDiscardingCardsTable[i] >= 1)
		{
			nCount = 0;
			CCard card;
			VECCARD vecCard;
			for(int j = 0; j < 8; j++)
			{
				int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue] - usebao;
				if((i + j) == m_nBaoValue)
				{
					nBaoCount = 0;
                    usebao = 1;
				}
				if(m_nDiscardingCardsTable[i + j] + nBaoCount >= 1)
				{
					card.m_nValue = i + j;
					for(int k = 0; k < min(1,m_nDiscardingCardsTable[i + j]); k++)
					{
						vecCard.push_back(card);
					}
					if(m_nDiscardingCardsTable[i + j] < 1)
					{
						int nUsedCatCount = min(nBaoCount, 1 - m_nDiscardingCardsTable[i + j]);
						for(int k = 0; k < nUsedCatCount; k++)
						{
							card.m_nValue = m_nBaoValue;
							vecCard.push_back(card);
						}
						m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;
					}
					nCount++;
				}
			}
			if(nCount == 8)
			{
				m_vecTipsCards.push_back(vecCard);
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;
	}
	return 0;
}

//�Ķ�
int CPlayCards::TipsSearch2222(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 12; i++)
	{
		bool bContinue = true;
		VECCARD vecCard;
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
        int usebao = 0;
		for(int j = 0; j < 4; j++)
		{
			int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue] - usebao;
			if((i + j) == m_nBaoValue)
			{
                if (nBaoCount >=2 )
                {
                    usebao = 2;
                }
                else if (nBaoCount >= 1)
                {
                    usebao = 1;
                }
				nBaoCount = 0;
			}
			if(m_nDiscardingCardsTable[i+j] + nBaoCount >= 2)
			{
				CCard card;						
				card.m_nValue = i + j;
				for(int k = 0; k < min(2,m_nDiscardingCardsTable[i + j]); k++)
				{
					vecCard.push_back(card);
				}
				if(m_nDiscardingCardsTable[i + j] < 2)
				{
					int nUsedCatCount = min(nBaoCount, 2 - m_nDiscardingCardsTable[i + j]);
					for(int k = 0; k < nUsedCatCount; k++)
					{
						card.m_nValue = m_nBaoValue;
						vecCard.push_back(card);
					}
					m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;					
				}				
			}
			else
			{				
				bContinue = false;
				vecCard.clear();
				break;
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;

		if(bContinue)
		{
			m_vecTipsCards.push_back(vecCard);
		}		
	}
	return 0;
}

int CPlayCards::TipsSearch3311(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 14; i++)
	{
		bool bContinue = true;
		VECCARD vecCard;
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
		for(int j = 0; j < 2; j++)
		{
			int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
			if((i + j) == m_nBaoValue)
			{
				nBaoCount = 0;
			}
			if(m_nDiscardingCardsTable[i+j] + nBaoCount >= 3)
			{
				CCard card;						
				card.m_nValue = i + j;
				for(int k = 0; k < min(3,m_nDiscardingCardsTable[i + j]); k++)
				{
					vecCard.push_back(card);
				}
				if(m_nDiscardingCardsTable[i + j] < 3)
				{
					int nUsedCatCount = min(nBaoCount, 3 - m_nDiscardingCardsTable[i + j]);
					for(int k = 0; k < nUsedCatCount; k++)
					{
						card.m_nValue = m_nBaoValue;
						vecCard.push_back(card);
					}
					m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;					
				}				
			}
			else
			{				
				bContinue = false;
				vecCard.clear();
				break;
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;

		if(bContinue)
		{
			int nCount = 0;
			for(int k = 3; k < 17; k++)
			{
				if(m_nDiscardingCardsTable[k] >= 1 && (i!=k) && (k != i+1) && (k != m_nBaoValue))
				{
					CCard card;					
					card.m_nValue = k;
					vecCard.push_back(card);
					if(++nCount >= 2)
					{
						if(m_nDiscardingCardsTable[i] != 0)
						{
							m_vecTipsCards.push_back(vecCard);
						}
						break;
					}
				}
			}
		}
	}
	return 0;
}

//���Ŵ�����
int CPlayCards::TipsSearch422(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 17; i++)
	{
		int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
		if(i == m_nBaoValue)
		{
			nBaoCount = 0;
		}		
		if(m_nDiscardingCardsTable[i] + nBaoCount >= 4)
		{			
			CCard card;		
			VECCARD vecCard;
			card.m_nValue = i;
			for(int j = 0; j < min(4,m_nDiscardingCardsTable[i]); j++)
			{
				vecCard.push_back(card);
			}
			int nUsedCatCount = min(nBaoCount, 4 - m_nDiscardingCardsTable[i]);
			for(int k = 0; k < nUsedCatCount; k++)
			{
				card.m_nValue = m_nBaoValue;
				vecCard.push_back(card);
			}	
			int nCount = 0;
			for(int m = 3; m < 17; m++)
			{
				if(m_nDiscardingCardsTable[m] >= 2 && (i!=m) && (m != m_nBaoValue))
				{
					CCard card;					
					card.m_nValue = m;
					vecCard.push_back(card);
					vecCard.push_back(card);
					if(++nCount >= 2)
					{
						if(m_nDiscardingCardsTable[i] != 0)
						{
							m_vecTipsCards.push_back(vecCard);
						}
						break;
					}
				}
			}
		}
	}
	return 0;
}

// 9˳
int CPlayCards::TipsSearch9(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	int nCount = 0;

	for(int i = nBegin; i < 7; i++)
	{
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];	
        int usebao = 0;
		if(m_nDiscardingCardsTable[i] >= 1)
		{
			nCount = 0;
			CCard card;
			VECCARD vecCard;
			for(int j = 0; j < 9; j++)
			{
				int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue] - usebao;
				if ((i + j) == m_nBaoValue)
				{
					nBaoCount = 0;
                    usebao = 1;
				}
				if(m_nDiscardingCardsTable[i + j] + nBaoCount >= 1)
				{										
					card.m_nValue = i + j;
					for(int k = 0; k < min(1,m_nDiscardingCardsTable[i + j]); k++)
					{
						vecCard.push_back(card);
					}
					if(m_nDiscardingCardsTable[i + j] < 1)
					{
						int nUsedCatCount = min(nBaoCount, 1 - m_nDiscardingCardsTable[i + j]);
						for (int k = 0; k < nUsedCatCount; k++)
						{
							card.m_nValue = m_nBaoValue;
							vecCard.push_back(card);
						}
						m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;										
					}				
					nCount++;
				}
			}
			if(nCount == 9)
			{
				m_vecTipsCards.push_back(vecCard);
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;		
	}
	return 0;
}

//����
int CPlayCards::TipsSearch333(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 13; i++)
	{
		bool bContinue = true;
		VECCARD vecCard;
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
		for(int j = 0; j < 3; j++)
		{
			int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
			if((i + j) == m_nBaoValue)
			{
				nBaoCount = 0;
			}
			if(m_nDiscardingCardsTable[i+j] + nBaoCount >= 3)
			{
				CCard card;						
				card.m_nValue = i + j;
				for(int k = 0; k < min(3,m_nDiscardingCardsTable[i + j]); k++)
				{
					vecCard.push_back(card);
				}
				if(m_nDiscardingCardsTable[i + j] < 3)
				{
					int nUsedCatCount = min(nBaoCount, 3 - m_nDiscardingCardsTable[i + j]);
					for(int k = 0; k < nUsedCatCount; k++)
					{
						card.m_nValue = m_nBaoValue;
						vecCard.push_back(card);
					}
					m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;
				}				
			}
			else
			{				
				bContinue = false;
				vecCard.clear();
				break;
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;

		if(bContinue)
		{
			m_vecTipsCards.push_back(vecCard);
		}
	}
	return 0;
}

// 10˳
int CPlayCards::TipsSearch10(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	int nCount = 0;

	for(int i = nBegin; i < 6; i++)
	{
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];	
        int usebao = 0;
		if(m_nDiscardingCardsTable[i] >= 1)
		{
			nCount = 0;
			CCard card;
			VECCARD vecCard;
			for(int j = 0; j < 10; j++)
			{
				int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue] - usebao;
				if((i + j) == m_nBaoValue)
				{
					nBaoCount = 0;
                    usebao = 1;
				}
				if(m_nDiscardingCardsTable[i + j] + nBaoCount >= 1)
				{										
					card.m_nValue = i + j;
					for(int k = 0; k < min(1,m_nDiscardingCardsTable[i + j]); k++)
					{
						vecCard.push_back(card);
					}
					if(m_nDiscardingCardsTable[i + j] < 1)
					{
						int nUsedCatCount = min(nBaoCount, 1 - m_nDiscardingCardsTable[i + j]);
						for(int k = 0; k < nUsedCatCount; k++)
						{
							card.m_nValue = m_nBaoValue;
							vecCard.push_back(card);
						}
						m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;										
					}
					nCount++;
				}
			}
			if(nCount == 10)
			{
				m_vecTipsCards.push_back(vecCard);
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;		
	}
	return 0;
}

//���
int CPlayCards::TipsSearch22222(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 11; i++)
	{
		bool bContinue = true;
		VECCARD vecCard;
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
        int usebao = 0;
		for(int j = 0; j < 5; j++)
		{
			int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue] - usebao;
			if((i + j) == m_nBaoValue)
			{
                if (nBaoCount >=2 )
                {
                    usebao = 2;
                }
                else if (nBaoCount >= 1)
                {
                    usebao = 1;
                }
				nBaoCount = 0;
			}
			if(m_nDiscardingCardsTable[i+j] + nBaoCount >= 2)
			{
				CCard card;
				card.m_nValue = i + j;
				for(int k = 0; k < min(2,m_nDiscardingCardsTable[i+j]); k++)
				{
					vecCard.push_back(card);
				}
				if(m_nDiscardingCardsTable[i+j] < 2)
				{
					int nUsedCatCount = min(nBaoCount, 2 - m_nDiscardingCardsTable[i+j]);
					for(int k = 0; k < nUsedCatCount; k++)
					{
						card.m_nValue = m_nBaoValue;
						vecCard.push_back(card);
					}
					m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;					
				}
			}
			else
			{
				bContinue = false;
				vecCard.clear();
				break;
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;

		if(bContinue)
		{
			m_vecTipsCards.push_back(vecCard);
		}
	}
	return 0;
}

//��������
int CPlayCards::TipsSearch3322(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 14; i++)
	{
		bool bContinue = true;
		VECCARD vecCard;
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
		for(int j = 0; j < 2; j++)
		{
			int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
			if((i + j) == m_nBaoValue)
			{
				nBaoCount = 0;
			}
			if(m_nDiscardingCardsTable[i+j] + nBaoCount >= 3)
			{
				CCard card;
				card.m_nValue = i + j;
				for(int k = 0; k < min(3,m_nDiscardingCardsTable[i+j]); k++)
				{
					vecCard.push_back(card);
				}
				if(m_nDiscardingCardsTable[i+j] < 3)
				{
					int nUsedCatCount = min(nBaoCount, 3 - m_nDiscardingCardsTable[i + j]);
					for(int k = 0; k < nUsedCatCount; k++)
					{
						card.m_nValue = m_nBaoValue;
						vecCard.push_back(card);
					}
					m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;					
				}				
			}
			else
			{
				bContinue = false;
				vecCard.clear();
				break;
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;

		if(bContinue)
		{
			int nCount = 0;
			for(int k = 3; k < 17; k++)
			{
				if(m_nDiscardingCardsTable[k] >= 2 && (i!=k) && (k != i+1) && (k != m_nBaoValue))
				{
					CCard card;
					card.m_nValue = k;
					vecCard.push_back(card);
					vecCard.push_back(card);
					if(++nCount >= 2)
					{
						if (m_nDiscardingCardsTable[i] != 0)
						{
							m_vecTipsCards.push_back(vecCard);
						}	
						break;
					}
				}
			}
		}
	}
	return 0;
}

int CPlayCards::TipsSearch11(CCardsType& cCardsType)
{
	int nCount = 0;
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 5; i++)
	{
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
        int usebao = 0;
		if(m_nDiscardingCardsTable[i] >= 1)
		{
			nCount = 0;
			CCard card;
			VECCARD vecCard;
			for(int j = 0; j < 11; j++)
			{
				int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue] - usebao;
				if((i + j) == m_nBaoValue)
				{
					nBaoCount = 0;
                    usebao = 1;
				}
				if(m_nDiscardingCardsTable[i + j] + nBaoCount >= 1)
				{
					card.m_nValue = i + j;
					for(int k = 0; k < min(1,m_nDiscardingCardsTable[i + j]); k++)
					{
						vecCard.push_back(card);
					}
					if(m_nDiscardingCardsTable[i + j] < 1)
					{
						int nUsedCatCount = min(nBaoCount, 1 - m_nDiscardingCardsTable[i + j]);
						for(int k = 0; k < nUsedCatCount; k++)
						{
							card.m_nValue = m_nBaoValue;
							vecCard.push_back(card);
						}
						m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;										
					}
					nCount++;
				}
			}
			if(nCount == 11)
			{
				m_vecTipsCards.push_back(vecCard);
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;		
	}
	return 0;
}

int CPlayCards::TipsSearch12(CCardsType& cCardsType)
{
	int nCount = 0;
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 4; i++)
	{
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
        int usebao = 0;
		if(m_nDiscardingCardsTable[i] >= 1)
		{
			nCount = 0;
			CCard card;
			VECCARD vecCard;
			for(int j = 0; j < 12; j++)
			{
				int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue] - usebao;
				if((i + j) == m_nBaoValue)
				{
					nBaoCount = 0;
                    usebao = 1;
				}
				if(m_nDiscardingCardsTable[i + j] + nBaoCount >= 1)
				{
					card.m_nValue = i + j;
					for(int k = 0; k < min(1,m_nDiscardingCardsTable[i + j]); k++)
					{
						vecCard.push_back(card);
					}
					if(m_nDiscardingCardsTable[i + j] < 1)
					{
						int nUsedCatCount = min(nBaoCount, 1 - m_nDiscardingCardsTable[i + j]);
						for(int k = 0; k < nUsedCatCount; k++)
						{
							card.m_nValue = m_nBaoValue;
							vecCard.push_back(card);
						}
						m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;										
					}				
					nCount++;
				}
			}
			if(nCount == 12)
			{
				m_vecTipsCards.push_back(vecCard);
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;		
	}
	return 0;
}

//����
int CPlayCards::TipsSearch222222(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 10; i++)
	{
		bool bContinue = true;
		VECCARD vecCard;
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
		for(int j = 0; j < 6; j++)
		{
			int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
			if((i + j) == m_nBaoValue)
			{
				nBaoCount = 0;
			}
			if(m_nDiscardingCardsTable[i+j] + nBaoCount >= 2)
			{
				CCard card;						
				card.m_nValue = i + j;
				for(int k = 0; k < min(2,m_nDiscardingCardsTable[i + j]); k++)
				{
					vecCard.push_back(card);
				}
				if(m_nDiscardingCardsTable[i + j] < 2)
				{
					int nUsedCatCount = min(nBaoCount, 2 - m_nDiscardingCardsTable[i + j]);
					for(int k = 0; k < nUsedCatCount; k++)
					{
						card.m_nValue = m_nBaoValue;
						vecCard.push_back(card);
					}
					m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;					
				}				
			}
			else
			{
				bContinue = false;
				vecCard.clear();
				break;
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;

		if(bContinue)
		{
			m_vecTipsCards.push_back(vecCard);
		}
	}
	return 0;
}

//�Ŀ�
int CPlayCards::TipsSearch3333(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 12; i++)
	{
		bool bContinue = true;
		VECCARD vecCard;
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
		for(int j = 0; j < 4; j++)
		{
			int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
			if((i + j) == m_nBaoValue)
			{
				nBaoCount = 0;
			}
			if(m_nDiscardingCardsTable[i+j] + nBaoCount >= 3)
			{
				CCard card;						
				card.m_nValue = i + j;
				for(int k = 0; k < min(3,m_nDiscardingCardsTable[i + j]); k++)
				{
					vecCard.push_back(card);
				}
				if(m_nDiscardingCardsTable[i + j] < 3)
				{
					int nUsedCatCount = min(nBaoCount, 3 - m_nDiscardingCardsTable[i + j]);
					for(int k = 0; k < nUsedCatCount; k++)
					{
						card.m_nValue = m_nBaoValue;
						vecCard.push_back(card);
					}
					m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;					
				}				
			}
			else
			{
				bContinue = false;
				vecCard.clear();
				break;
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;

		if(bContinue)
		{
			m_vecTipsCards.push_back(vecCard);
		}
	}
	return 0;
}

//������������
int CPlayCards::TipsSearch333111(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 13; i++)
	{
		bool bContinue = true;
		VECCARD vecCard;
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
		for(int j = 0; j < 3; j++)
		{
			int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
			if((i + j) == m_nBaoValue)
			{
				nBaoCount = 0;
			}
			if(m_nDiscardingCardsTable[i+j] + nBaoCount >= 3)
			{
				CCard card;						
				card.m_nValue = i + j;
				for(int k = 0; k < min(3,m_nDiscardingCardsTable[i + j]); k++)
				{
					vecCard.push_back(card);
				}
				if(m_nDiscardingCardsTable[i + j] < 3)
				{
					int nUsedCatCount = min(nBaoCount, 3 - m_nDiscardingCardsTable[i + j]);
					for(int k = 0; k < nUsedCatCount; k++)
					{
						card.m_nValue = m_nBaoValue;
						vecCard.push_back(card);
					}
					m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;					
				}				
			}
			else
			{				
				bContinue = false;
				vecCard.clear();
				break;
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;

		if(bContinue)
		{
			int nCount = 0;
			for(int k = 3; k < 17; k++)
			{
				if(m_nDiscardingCardsTable[k] >= 1 && (i!=k) && (k != i+1) && (k != i+2)&& (k != m_nBaoValue))
				{
					CCard card;					
					card.m_nValue = k;
					vecCard.push_back(card);
					if(++nCount >= 3)
					{
						if (m_nDiscardingCardsTable[i] != 0)
						{
							m_vecTipsCards.push_back(vecCard);
						}	
						break;
					}
				}
			}
		}
	}
	return 0;
}

//�߶�
int CPlayCards::TipsSearch2222222(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 9; i++)
	{
		bool bContinue = true;
		VECCARD vecCard;
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
		for(int j = 0; j < 7; j++)
		{
			int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
			if((i + j) == m_nBaoValue)
			{
				nBaoCount = 0;
			}
			if(m_nDiscardingCardsTable[i+j] + nBaoCount >= 2)
			{
				CCard card;						
				card.m_nValue = i + j;
				for (int k = 0; k < min(2,m_nDiscardingCardsTable[i + j]); k++)
				{
					vecCard.push_back(card);
				}
				if(m_nDiscardingCardsTable[i + j] < 2)
				{
					int nUsedCatCount = min(nBaoCount, 2 - m_nDiscardingCardsTable[i + j]);
					for(int k = 0; k < nUsedCatCount; k++)
					{
						card.m_nValue = m_nBaoValue;
						vecCard.push_back(card);
					}
					m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;					
				}				
			}
			else
			{				
				bContinue = false;
				vecCard.clear();
				break;
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;

		if(bContinue)
		{
			m_vecTipsCards.push_back(vecCard);
		}		
	}
	return 0;
}

int CPlayCards::TipsSearch33333(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 11; i++)
	{
		bool bContinue = true;
		VECCARD vecCard;
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
		for(int j = 0; j < 5; j++)
		{
			int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
			if((i + j) == m_nBaoValue)
			{
				nBaoCount = 0;
			}
			if(m_nDiscardingCardsTable[i+j] + nBaoCount >= 3)
			{
				CCard card;
				card.m_nValue = i + j;
				for(int k = 0; k < min(3,m_nDiscardingCardsTable[i + j]); k++)
				{
					vecCard.push_back(card);
				}
				if(m_nDiscardingCardsTable[i + j] < 3)
				{
					int nUsedCatCount = min(nBaoCount, 3 - m_nDiscardingCardsTable[i + j]);
					for(int k = 0; k < nUsedCatCount; k++)
					{
						card.m_nValue = m_nBaoValue;
						vecCard.push_back(card);
					}
					m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;
				}
			}
			else
			{
				bContinue = false;
				vecCard.clear();
				break;
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;

		if(bContinue)
		{
			m_vecTipsCards.push_back(vecCard);
		}
	}
	return 0;
}


int CPlayCards::TipsSearch22222222(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 8; i++)
	{
		bool bContinue = true;
		VECCARD vecCard;
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
		for(int j = 0; j < 8; j++)
		{
			int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
			if((i + j) == m_nBaoValue)
			{
				nBaoCount = 0;
			}
			if(m_nDiscardingCardsTable[i+j] + nBaoCount >= 2)
			{
				CCard card;
				card.m_nValue = i + j;
				for (int k = 0; k < min(2,m_nDiscardingCardsTable[i + j]); k++)
				{
					vecCard.push_back(card);
				}
				if(m_nDiscardingCardsTable[i + j] < 2)
				{
					int nUsedCatCount = min(nBaoCount, 2 - m_nDiscardingCardsTable[i + j]);
					for(int k = 0; k < nUsedCatCount; k++)
					{
						card.m_nValue = m_nBaoValue;
						vecCard.push_back(card);
					}
					m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;
				}
			}
			else
			{
				bContinue = false;
				vecCard.clear();
				break;
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;

		if(bContinue)
		{
			m_vecTipsCards.push_back(vecCard);
		}		
	}
	return 0;
}

//��������
int CPlayCards::TipsSearch333222(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 13; i++)
	{
		bool bContinue = true;
		VECCARD vecCard;
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
		for(int j = 0; j < 3; j++)
		{
			int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
			if((i + j) == m_nBaoValue)
			{
				nBaoCount = 0;
			}
			if(m_nDiscardingCardsTable[i+j] + nBaoCount >= 3)
			{
				CCard card;
				card.m_nValue = i + j;
				for(int k = 0; k < min(3,m_nDiscardingCardsTable[i + j]); k++)
				{
					vecCard.push_back(card);
				}
				if(m_nDiscardingCardsTable[i + j] < 3)
				{
					int nUsedCatCount = min(nBaoCount, 3 - m_nDiscardingCardsTable[i + j]);
					for(int k = 0; k < nUsedCatCount; k++)
					{
						card.m_nValue = m_nBaoValue;
						vecCard.push_back(card);
					}
					m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;					
				}
			}
			else
			{				
				bContinue = false;
				vecCard.clear();
				break;
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;

		if(bContinue)
		{
			int nCount = 0;
			for(int k = 3; k < 17; k++)
			{
				if(m_nDiscardingCardsTable[k] >= 2 && (i!=k) && (k != i+1) && (k != i+2) && (k != m_nBaoValue))
				{
					CCard card;					
					card.m_nValue = k;
					vecCard.push_back(card);
					vecCard.push_back(card);
					if(++nCount >= 3)
					{
						if(m_nDiscardingCardsTable[i] != 0)
						{
							m_vecTipsCards.push_back(vecCard);
						}
						break;
					}
				}
			}
		}
	}
	return 0;
}

int CPlayCards::TipsSearch222222222(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 7; i++)
	{
		bool bContinue = true;
		VECCARD vecCard;
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
		for(int j = 0; j < 9; j++)
		{
			int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
			if((i + j) == m_nBaoValue)
			{
				nBaoCount = 0;
			}
			if(m_nDiscardingCardsTable[i+j] + nBaoCount >= 2)
			{
				CCard card;
				card.m_nValue = i + j;
				for(int k = 0; k < min(2,m_nDiscardingCardsTable[i + j]); k++)
				{
					vecCard.push_back(card);
				}
				if (m_nDiscardingCardsTable[i + j] < 2)
				{
					int nUsedCatCount = min(nBaoCount, 2 - m_nDiscardingCardsTable[i + j]);
					for (int k = 0; k < nUsedCatCount; k++)
					{
						card.m_nValue = m_nBaoValue;
						vecCard.push_back(card);
					}
					m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;					
				}
			}
			else
			{
				bContinue = false;
				vecCard.clear();
				break;
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;

		if(bContinue)
		{
			m_vecTipsCards.push_back(vecCard);
		}
	}
	return 0;
}

int CPlayCards::TipsSearch33331111(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 12; i++)
	{
		bool bContinue = true;
		VECCARD vecCard;
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
		for(int j = 0; j < 4; j++)
		{
			int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
			if((i + j) == m_nBaoValue)
			{
				nBaoCount = 0;
			}
			if(m_nDiscardingCardsTable[i+j] + nBaoCount >= 3)
			{
				CCard card;
				card.m_nValue = i + j;
				for(int k = 0; k < min(3,m_nDiscardingCardsTable[i + j]); k++)
				{
					vecCard.push_back(card);
				}
				if(m_nDiscardingCardsTable[i + j] < 3)
				{
					int nUsedCatCount = min(nBaoCount, 3 - m_nDiscardingCardsTable[i + j]);
					for (int k = 0; k < nUsedCatCount; k++)
					{
						card.m_nValue = m_nBaoValue;
						vecCard.push_back(card);
					}
					m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;					
				}
			}
			else
			{
				bContinue = false;
				vecCard.clear();
				break;
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;

		if(bContinue)
		{
			int nCount = 0;
			for(int k = 3; k < 17; k++)
			{
				if(m_nDiscardingCardsTable[k] >= 1 && (i!=k) && (k != i+1) &&
					(k != i+2) && (k != i+3) && (k != m_nBaoValue))
				{
					CCard card;					
					card.m_nValue = k;
					vecCard.push_back(card);
					if(++nCount >= 4)
					{
						if(m_nDiscardingCardsTable[i] != 0)
						{
							m_vecTipsCards.push_back(vecCard);
						}
						break;
					}
				}
			}
		}
	}
	return 0;
}

int CPlayCards::TipsSearch333333(CCardsType& cCardsType)
{
	int nBegin = cCardsType.m_nTypeValue + 1;
	for(int i = nBegin; i < 10; i++)
	{
		bool bContinue = true;
		VECCARD vecCard;
		int nTmpCatTable = m_nDiscardingCardsTable[m_nBaoValue];
		for(int j = 0; j < 6; j++)
		{
			int nBaoCount = m_nDiscardingCardsTable[m_nBaoValue];
			if((i + j) == m_nBaoValue)
			{
				nBaoCount = 0;
			}
			if(m_nDiscardingCardsTable[i+j] + nBaoCount >= 3)
			{
				CCard card;
				card.m_nValue = i + j;
				for (int k = 0; k < min(3,m_nDiscardingCardsTable[i + j]); k++)
				{
					vecCard.push_back(card);
				}
				if(m_nDiscardingCardsTable[i + j] < 3)
				{
					int nUsedCatCount = min(nBaoCount, 3 - m_nDiscardingCardsTable[i + j]);
					for (int k = 0; k < nUsedCatCount; k++)
					{
						card.m_nValue = m_nBaoValue;
						vecCard.push_back(card);
					}
					m_nDiscardingCardsTable[m_nBaoValue] -= nUsedCatCount;					
				}
			}
			else
			{				
				bContinue = false;
				vecCard.clear();
				break;
			}
		}
		m_nDiscardingCardsTable[m_nBaoValue] = nTmpCatTable;

		if(bContinue)
		{
			m_vecTipsCards.push_back(vecCard);
		}		
	}
	return 0;
}

void CPlayCards::SetBaoValue(const CCard& card)
{
    //int nValue = card.m_nValue;
    //if(nValue == 15)
    //	m_nBaoValue = 3;
    //else if(nValue == 16 || nValue == 17)
    //	m_nBaoValue = 3;
    //else
    //	m_nBaoValue = nValue + 1;
    int nValue = card.m_nValue;          //���ñ��Ƶ�ֵ
    m_nBaoValue = nValue;
}

bool CPlayCards::CheckTigerValue(int nTigerCount)
{	
	if (m_nDiscardingCardsTable[BAO] >= nTigerCount)
	{
		m_nDiscardingCardsTable[BAO] -= nTigerCount;
		return true;
	}
	return false;
}

void CPlayCards::RevertTigerValue()
{
	m_nDiscardingCardsTable[BAO] = 0;	
	m_nDiscardingCardsTable[m_nBaoValue] = 0;

	//ɨ�������;
	for(size_t i = 0; i < m_cChoosingCards.size(); i++)
	{
		if((int)m_cChoosingCards[i].m_nValue == m_nBaoValue)
		{
			m_nDiscardingCardsTable[BAO]++;
		}
	}
}