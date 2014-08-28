#include "Config.h"
#include "TcpNet.h"
#include "../Packet/Processor.h"
#include "../Packet/Handler/Handler.h"
#include "../Packet/PacketHead.h"

namespace TcpNetWork
{
TcpNet _tcpnet;

Utils *TcpNet::utils = new Utils;
TcpNet::TcpNet():m_nOutbufLen(0), m_nInbufLen(0), m_tcpsocket(NULL)
{
	memset(m_nOutBuff, 0, sizeof(m_nOutBuff));
	memset(m_InputBuff, 0, sizeof(m_InputBuff));
	//memset(m_cbDataBuf, 0, sizeof(m_cbDataBuf));
}

TcpNet::~TcpNet()
{
	//memset(m_nOutBuff, 0, sizeof(m_nOutBuff));
	memset(m_InputBuff, 0, sizeof(m_InputBuff));
	if (m_tcpsocket != NULL)
	{
		SAFE_DELETE(m_tcpsocket);
	}
	if (_thread != NULL)
	{
		SAFE_DELETE(_thread);
	}
}

bool TcpNet::connect(const char* ServerIP, int ServerPort, int nBlockSec, bool bKeepAlive)
{
	// ������
	if(ServerIP == NULL || strlen(ServerIP) > 15)
	{
		return false;
	}

	if (m_tcpsocket != NULL)
	{
		SAFE_DELETE(m_tcpsocket);
	}

	m_tcpsocket = new TcpSocket();
	if (!m_tcpsocket->initialized())
	{
		SAFE_DELETE(m_tcpsocket);
	}

	m_tcpsocket->makeBlock(true);

	if (m_tcpsocket->connect(ServerIP, ServerPort))
	{
		std::cout<< "client connect"<< std::endl;

		m_tcpsocket->makeLinger(true);

		m_tcpsocket->makeBlock(false);

		m_tcpsocket->makeNoDelay(true);

		timeval timeout;
		timeout.tv_sec	= nBlockSec;
		timeout.tv_usec	= 0;
		fd_set writeset, exceptset;
		FD_ZERO(&writeset);
		FD_ZERO(&exceptset);
		FD_SET(m_tcpsocket->getFD(), &writeset);
		FD_SET(m_tcpsocket->getFD(), &exceptset);

		int ret = select(FD_SETSIZE, NULL, &writeset, &exceptset, &timeout);
		if (ret == 0 || ret < 0) 
		{
			closeSocket();
			return false;
		} 
		else // ret > 0
		{
			ret = FD_ISSET(m_tcpsocket->getFD(), &exceptset);
			if(ret)		// or (!FD_ISSET(m_sockClient, &writeset)
			{
				closeSocket();
				return false;
			}
		}
	}
	else
	{
		SAFE_DELETE(m_tcpsocket);
		return false;
	}
	
	_thread = new System::Thread(&TcpNet::runRecvMsg, this);
	_thread->Launch();

	return true;
}

bool  TcpNet::sendMsg(void* pBuf, int nSize)
{
	if(pBuf ==  NULL|| nSize <= 0) 
	{ 
		return false; 
	} 

	if (m_tcpsocket == NULL || m_tcpsocket->getFD() == INVALID_SOCKET)
	{ 
		return false; 
	} 

	// ���ͨѶ��Ϣ������ 
	int packsize = 0; 
	packsize = nSize; 

	if ( packsize <= 0 || packsize > MAX_MESSAGE_SIZE )
	{
		return false;
	}
	else
	{
		m_tcpsocket->write(pBuf, packsize);
	}
	return true; 
}



void TcpNet::runRecvMsg()
{
	if (m_tcpsocket == NULL || m_tcpsocket->getFD() == INVALID_SOCKET)
	{
		return;
	}
	
	for (;;)
	{
		// ��������
		if (m_tcpsocket == NULL)
		{
			return;
		}
		_mutex.Lock();
		int nRecvSize = m_tcpsocket->read((char*)(m_InputBuff+m_nInbufLen), sizeof(m_InputBuff)-m_nInbufLen);
		// �����Ѿ��������ݵĴ�С
		if (nRecvSize > 0)
		{
			m_nInbufLen += nRecvSize;
		}
		_mutex.Unlock();

		if (nRecvSize <= 0 && ( m_tcpsocket->lastErr() != WEINPROGRESS &&  m_tcpsocket->lastErr() != WEWOULDBLOCK))
		{
			//std::cout << "�����������Ͽ�����!" << std::endl;
			break;
		}
		else if (nRecvSize <= 0 && ( m_tcpsocket->lastErr() == WEINPROGRESS || m_tcpsocket->lastErr() == WEWOULDBLOCK) )
		{
			//std::cout << "�ȴ���������!" << std::endl;
			continue;;
		}

		// ���յ������ݹ�����һ����ͷ�ĳ���
		while (m_nInbufLen >= PACKETHEADLEN)
		{
			UInt8 hdr[10] = {0};
			// ��ȡ��ͷ
			memcpy(hdr, m_InputBuff, PACKETHEADLEN);
			Packet::packhead.Unpack(hdr, PACKETHEADLEN);
			
			UInt16 nPacketSize = (Packet::packhead.Getlen() & 0x00FFFFFF) + PACKETHEADLEN;

			// �ж��Ƿ��ѽ��յ��㹻һ��������������
			if (m_nInbufLen < nPacketSize)
			{
				// ������ƴ�ճ�һ��������
				break;
			}

			//�ַ���
			// 

			// �������ݰ�����Ӧ�ò�����߼�����
		   // pHead = (PktHdr*) (m_cbDataBuf);
			//const UInt16 nDataSize = nPacketSize - (UInt16)sizeof(PktHdr);
			//OnNetMessage(pHead->op, m_cbDataBuf+sizeof(PktHdr), nDataSize);

			Packet::Processor::Instance().parseInit(m_InputBuff, nPacketSize, 0, 0);

			_mutex.Lock();
			// �ӽ��ջ����Ƴ�
			MoveMemory(m_InputBuff, m_InputBuff+nPacketSize, sizeof(m_InputBuff) - nPacketSize);
			m_nInbufLen -= nPacketSize;
			_mutex.Unlock();
		}
		Sleep(10);
	}
}

void TcpNet::drainDataBuf(int len)
{
	if (len > 0)
	{
		_mutex.Lock();
		memset(m_InputBuff, 0, len);
		memmove(m_InputBuff, m_InputBuff + len, sizeof(m_InputBuff) - len);
		_mutex.Unlock();
	}
}

void TcpNet::copyDataBuf(UInt8 *dstSrc, int len)
{
	_mutex.Lock();
	memmove(dstSrc, m_InputBuff, len);
	_mutex.Unlock();
}

//void TcpNet::setEventListener(TcpNet::SKYNETWORK_EVENT_LISTENER  listener,void* pUserData)
//{
//	//GameThreadMutex_lock(m_commMutex);
//	m_pEvent_listener = listener;
//	m_pUserData = pUserData;
//	//GameThreadMutex_unlock(m_commMutex);
//}
//
//
//void TcpNet::callListener(TCPNETWORKEVENT evt, void* pUserData, int param0, int param1, int param2)
//{
//
//}

void TcpNet::close()
{
	closeSocket();
	if (_thread)
	{
		SAFE_DELETE(_thread);
	}
}

}


