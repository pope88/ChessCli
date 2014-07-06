#include "Config.h"
#include "Tcp.h"
#include "System/Sleep.h"

namespace Worker
{
	Tcp _tcp;
	Tcp::Tcp():_running(false), _serverPort(0), _tcpnet(NULL)
	{
	}
	
	Tcp::~Tcp()
	{
	}

	bool Tcp::init()
	{
		_tcpnet = new(std::nothrow) TcpNetWork::TcpNet();
		if (_tcpnet == NULL)
		{
			return false;
		}

		if (!_tcpnet->connect(_serverIp.c_str(), _serverPort, 50))
		{
			return false;
		}
		_running = true;
		return true;
	}

	void Tcp::uninit()
	{
		_running = false;
		SAFE_DELETE(_tcpnet);
	}

	void Tcp::loop()
	{
		if(init())
		{
			while(_running)
			{
				//do something
				_tcpnet->runRecvMsg();
				System::Sleep(50);
			}
		}
		uninit();
	}

	 bool Tcp::sendMsg(void* pBuf, int nSize)
	 {
		 if (_tcpnet != NULL)
		 {
			return _tcpnet->sendMsg(pBuf, nSize);
		 }
		 return false;
	 }

}
