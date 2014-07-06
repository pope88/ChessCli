/*
 CopyRight(c)2006 by Banding,Shanghai, All Right Reserved.

 @Date:	        2009/4/20
 @Created:	    10:37
 @Filename: 	Playcard.h
 @File path:	BDLeyoyoV2\DDZV2\Common 
 @Author:		leiliang
	
 @Description:	�������ݽṹ,Ŀǰ����������ͬ��ͨ�����������ѡ����
				�����㷨Ϊ�ϱ�����٣����׶������ڿ���ģʽƥ���㷨�Ľ�
*/

#ifndef _PLAYCARD_H_
#define _PLAYCARD_H_

/*	���ͼ���ֵ����

����(Cards_Type)						��ֵ(Cards_Value)           ����:

����:		 1							CCard.Value(��ֵ)           1
һ��:		 2							CCard.Value(��ֵ)			2
����:		 3							CCard.Value(��ֵ)			3

����һ:		 31							���ŵ�Card.Value(��ֵ)		4
����:		 4							CCard.Value(��ֵ)			4

��˳:		 5							��С�Ƶ�Card.Value(��ֵ)    5
����һ��:	 32							���ŵ�Card.Value(��ֵ)		5		

��˳:		 6							��С�Ƶ�Card.Value(��ֵ)    6
˫˳:		 222						��С�Ƶ�Card.Value(��ֵ)    6
��˳:	     33							��С�Ƶ�Card.Value(��ֵ)    6
�Ĵ�����:	 411						���ŵ�Card.Value(��ֵ)		6	 

��˳:		 7							��С�Ƶ�Card.Value(��ֵ)    7

��˳:		 8							��С�Ƶ�Card.Value(��ֵ)    8
˫˳		 2222						��С�Ƶ�Card.Value(��ֵ)    8
��˳������:  3311						��С���ŵ�Card.Value(��ֵ)  8
�Ĵ�����:	 422						���ŵ�Card.Value(��ֵ)		8

��˳:		 9							��С�Ƶ�Card.Value(��ֵ)    9
��˳:		 333						��С���ŵ�Card.Value(��ֵ)  9

��˳:		 10							��С�Ƶ�Card.Value(��ֵ)    10
˫˳:		 22222						��С�Ƶ�Card.Value(��ֵ)    10
��˳������:  3322						��С���ŵ�Card.Value(��ֵ)  10

��˳:		 11							��С�Ƶ�Card.Value(��ֵ)    11

��˳:		 12							��С�Ƶ�Card.Value(��ֵ)    12
˫˳:		 222222						��С���Ƶ�Card.Value(��ֵ)  12
��˳:		 3333						��С���ŵ�Card.Value(��ֵ)  12
��˳����:	 333111						��С���ŵ�Card.Value(��ֵ)  12

˫˳		 2222222					��С���Ƶ�Card.Value(��ֵ)  14

��˳������:  333222						��С���ŵ�Card.Value(��ֵ)  15
��˳:		 33333						��С���ŵ�Card.Value(��ֵ)  15

˫˳		 22222222					��С���Ƶ�Card.Value(��ֵ)  16
��˳���ĵ�:  33331111					��С���ŵ�Card.Value(��ֵ)  16

˫˳		 222222222					��С���Ƶ�Card.Value(��ֵ)  18
��˳		 333333						��С���ŵ�Card.Value(��ֵ)  18

˫˳		 2222222222					��С���Ƶ�Card.Value(��ֵ)  20
��˳���嵥:	 3333311111					��С���ŵ�Card.Value(��ֵ)  20
��˳���Ķ�:  33332222					��С���ŵ�Card.Value(��ֵ)  20

*/
#define MAXCARDSNUM		20
#define MAXTYPENUM		17
#define BAO				17
#include "CCard.h"
class CPlayCards
{
	typedef std::vector<CCard> VECCARD;
    typedef std::vector<int>   VEHUASE;
public:
	CPlayCards();
	~CPlayCards();

	VECCARD m_cCards;					//δ������;
	VECCARD m_cChoosingCards;			//ѡ��Ҫ������
    VECCARD trueCards;                  //ʵ��Ҫ������(�������)

	VECCARD m_cDiscarding;				//�ͻ�����(�ճ�����)
    VECCARD willdiscarding;           

	std::vector<VECCARD> m_vecTipsCards;		//������ʾ
    std::vector<VECCARD> m_vecBaoArray;      //�ٴ������ʾ
    std::vector<VEHUASE> m_vecHuaSeArray;    //��¼�ٴɫλ��
    
    std::vector<int> vecHuaSe;       //���������       

	CCardsType m_cDiscardingType;		//�ճ��Ƶ�����
	int m_nDiscardingCardsTable[18];	//��¼�������͵�ɨ���
    int m_nPutCardsTable[18];           //��¼�������ɨ���

	unsigned long m_dwRule;				//��Ϸ����
	int	m_nBaoValue;					//���Ƶ�ֵ

public:
	void SetRule(unsigned long dwRule)
	{
		m_dwRule = dwRule;
	};

	int IsSoftBomb();	  //��ը�� 
	int IsHardBomb();	  //Ӳը���ж��Ƿ�������(ը��); 
	int Tips(CCardsType& cCardsType);	//��ʾ
	int Tips();	//�׼ҳ�����ʾ
public:
	int Is2();			  //�ж��Ƿ���һ����; 
	int Is3();			  //�ж��Ƿ�������;

	int IsSeries();		  //�ж��Ƿ��ǵ�˳(������),�˺����ʺ�5-12�������; 
	int IsDoubleSeries(); //�ж��Ƿ���˫˳;�˺����ʺ�6-20�������;
	int IsThreeSeries();  //�ж��Ƿ�����˳;�˺����ʺ�6-18�������;

	int Is31();			  //�ж��Ƿ�������һ��;
	int Is32();		      //�ж��Ƿ�������һ��;
	int Is411();		  //�ж��Ƿ����Ĵ�����;
	int Is3311();		  //�ж��Ƿ�����˳������;
	int Is422();		  //�ж��Ƿ����Ĵ�����;
	int Is3322();		  //�ж��Ƿ�����˳������;
	int Is333111();		  //�ж��Ƿ�����˳������;
	int Is333222();		  //�ж��Ƿ�����˳������;
	int Is33331111();	  //�ж��Ƿ�����˳���ĵ�;
    bool IsNotHaveN(int n);//�жϳ������Ƿ���n���Ƶ������
    bool IfHaveBao();    //�жϳ������Ƿ��б���
protected:
	int TipsSearch1(CCardsType& cCardsType);
	int TipsSearch2(CCardsType& cCardsType);
	int TipsSearch3(CCardsType& cCardsType);
	int TipsSearch4(CCardsType& cCardsType);
	int TipsSearch31(CCardsType& cCardsType);
	int TipsSearch5(CCardsType& cCardsType);
	int TipsSearch32(CCardsType& cCardsType);
	int TipsSearch6(CCardsType& cCardsType);
	int TipsSearch222(CCardsType& cCardsType);
	int TipsSearch33(CCardsType& cCardsType);
	int TipsSearch411(CCardsType& cCardsType);
	int TipsSearch7(CCardsType& cCardsType);
	int TipsSearch8(CCardsType& cCardsType);
	int TipsSearch2222(CCardsType& cCardsType);
	int TipsSearch3311(CCardsType& cCardsType);
	int TipsSearch422(CCardsType& cCardsType);
	int TipsSearch9(CCardsType& cCardsType);
	int TipsSearch333(CCardsType& cCardsType);
	int TipsSearch10(CCardsType& cCardsType);
	int TipsSearch22222(CCardsType& cCardsType);
	int TipsSearch3322(CCardsType& cCardsType);
	int TipsSearch11(CCardsType& cCardsType);
	int TipsSearch12(CCardsType& cCardsType);
	int TipsSearch222222(CCardsType& cCardsType);
	int TipsSearch3333(CCardsType& cCardsType);
	int TipsSearch333111(CCardsType& cCardsType);
	int TipsSearch2222222(CCardsType& cCardsType);
	int TipsSearch33333(CCardsType& cCardsType);
	int TipsSearch333222(CCardsType& cCardsType);
	int TipsSearch22222222(CCardsType& cCardsType);
	int TipsSearch33331111(CCardsType& cCardsType);
	int TipsSearch222222222(CCardsType& cCardsType);
	int TipsSearch333333(CCardsType& cCardsType);

    int Search31(bool m_bfirst,CCardsType& cCardsType);
    int Search4(bool m_bfirst,CCardsType& cCardsType);
    int Search32(bool m_bfirst,CCardsType& cCardsType);
    int Search3322(bool m_bfirst,CCardsType& cCardsType);
    int Search5(bool m_bfirst,CCardsType& cCardsType);
    int Search411(bool m_bfirst,CCardsType& cCardsType);
    int Search422(bool m_bfirst,CCardsType& cCardsType);
    int Search6(bool m_bfirst,CCardsType& CCardsType);
    int Search7(bool m_bfirst,CCardsType& CCardType);
    int Search8(bool m_bfirst,CCardsType& cCardsType);
    int Search9(bool m_bfirst,CCardsType& CCardType);
    int Search10(bool m_bfirst,CCardsType& CCardType);
    int Search11(bool m_bfirst,CCardsType& CCardType);
    int Search12(bool m_bfirst,CCardsType& CCardType);
    int Search222(bool m_bfirst,CCardsType& CCardsType);
    int Search33(bool m_bfirst,CCardsType& CCardsType);
    int Search333(bool m_bfirst,CCardsType& CCardsType);
    int Search3333(bool m_bfirst,CCardsType& CCardsType);
    int Search2222(bool m_bfirst,CCardsType& cCardsType);
    int Search22222(bool m_bfirst,CCardsType& cCardsType);
    int Search222222(bool m_bfirst,CCardsType& cCardsType);
    int Search3311(bool m_bfirst,CCardsType& cCardsType);
    int Search333111(bool m_bfirst,CCardsType& cCardsType);

public:
	void NewRound();	
	void ScandCardTable();
	void TipScanCardTable();
    void ScanPutCardsTable();

	void SetBaoValue(const CCard& card);		//���ñ���
	void CleanUp();								//���������ݽṹ���Ӵ�С����

	void CleanUp2();							//���������ݽ�������Ƶ������Ӷൽ������
	void SortChoosingCards();					//��ѡ�е�������
    void SortByLValue();
    void SortByValue();                         //Ϊ���޸�bug
	int CheckChoosing();						//�����Ƶ��߼��Ϸ���;
    //int CheckChoosing(CCardsType type);

    int FindBaiArray(bool m_bfirst,CCardsType& cCardsType);             //
	int CompareCards(CCardsType& cardType);		//�Ƚϴ�С
	void EraseCards(VECCARD& vecCards);			//ɾ����
	void RevertTigerValue();
	bool CheckTigerValue (int nTigerCount);
	int GetBomb();
    int nChoose;                               //���������
    int lasttype;                              //�ͻ��˷��������
};
#endif