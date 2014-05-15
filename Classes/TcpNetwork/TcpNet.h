#ifndef _TcpNet_H_
#define _TcpNet_H_

#include "TcpSocket.h"

//max message size
#define MAX_MESSAGE_SIZE 5*1024      //������󳤶�
#define IN_MAX_MESSAGE_SIZE 10*1024  //���ܻ�������С
#define IN_MAX_POOL_SIZE 100*1024    //�ݴ�����С
#define PACKETHEADLEN 20             //��ͷ����

namespace TcpNetWork
{
	class TcpNet
	{
	public:
		enum TCPNETWORKEVENT
		{
			TCPNETWORK_CONNECTRESULT,  /*�����Ƿ����ɹ�*/
			TCPNETWORK_LOSTCONNECT,    /*ʧȥ����������*/
			TCPNETWORK_RECEIVEPKG,     /*���յ����ӷ�����������*/
		};

	 /*
	 *  typedef TCPNETWORK_EVENT_LISTENER
	 *  SKY Network�¼�����  
	 */
	 typedef void (*SKYNETWORK_EVENT_LISTENER)(TCPNETWORKEVENT evt,
										void* userpData,
										int param0, int param1, int param2);
	public:
		TcpNet();
		~TcpNet();
		bool connect(const char* ServerIP, int ServerPort, int nBlockSec, bool bKeepAlive = false);
		bool sendMsg(void* pBuf, int nSize);
		bool receiveMsg(void* pBuf, int& nSize);
		void runRecvMsg();
		void closeSocket(){ m_tcpsocket->close();}
		void drainDataBuf(int len);
		void copyDataBuf(UInt8 *dstSrc, int len);
		//bool OnNetMessage( const UInt16& nOpcode, const UInt8* pDataBuffer, UInt16 nDataSize );

	  /*
	   * ���������ص�
	   */
	    void setEventListener(SKYNETWORK_EVENT_LISTENER listener, void* pUserData);
		void callListener(TCPNETWORKEVENT evt, void* pUserData, int param0, int param1, int param2);
	private:
		// �������ݻ���
		UInt8	m_nOutBuff[MAX_MESSAGE_SIZE];	
		int		m_nOutbufLen;   //�α�

		UInt8	m_InputBuff[IN_MAX_MESSAGE_SIZE];  //���ܻ�����
		UInt8   m_cbDataBuf[IN_MAX_POOL_SIZE];     //�ݴ���
		int		m_nInbufLen;                       //���ܻ������е���Ч���ݳ���     
	private:	
		TcpSocket *m_tcpsocket;
		SKYNETWORK_EVENT_LISTENER  m_pEvent_listener;
		void* m_pUserData;
	protected:
		static Utils *utils;
	};
}
#endif