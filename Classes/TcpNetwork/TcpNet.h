#ifndef _TcpNet_H_
#define _TcpNet_H_

#include "TcpSocket.h"

//max message size
#define MAX_MESSAGE_SIZE 5*1024      //包的最大长度
#define IN_MAX_MESSAGE_SIZE 10*1024  //接受缓冲区大小
#define IN_MAX_POOL_SIZE 100*1024    //暂存区大小
#define PACKETHEADLEN 20             //包头长度

namespace TcpNetWork
{
	class TcpNet
	{
	public:
		enum TCPNETWORKEVENT
		{
			TCPNETWORK_CONNECTRESULT,  /*连接是否建立成功*/
			TCPNETWORK_LOSTCONNECT,    /*失去服务器连接*/
			TCPNETWORK_RECEIVEPKG,     /*接收到来子服务器的数据*/
		};

	 /*
	 *  typedef TCPNETWORK_EVENT_LISTENER
	 *  SKY Network事件侦听  
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
	   * 设置侦听回调
	   */
	    void setEventListener(SKYNETWORK_EVENT_LISTENER listener, void* pUserData);
		void callListener(TCPNETWORKEVENT evt, void* pUserData, int param0, int param1, int param2);
	private:
		// 发送数据缓冲
		UInt8	m_nOutBuff[MAX_MESSAGE_SIZE];	
		int		m_nOutbufLen;   //游标

		UInt8	m_InputBuff[IN_MAX_MESSAGE_SIZE];  //接受缓冲区
		UInt8   m_cbDataBuf[IN_MAX_POOL_SIZE];     //暂存区
		int		m_nInbufLen;                       //接受缓冲区中的有效数据长度     
	private:	
		TcpSocket *m_tcpsocket;
		SKYNETWORK_EVENT_LISTENER  m_pEvent_listener;
		void* m_pUserData;
	protected:
		static Utils *utils;
	};
}
#endif