#include <winsock2.h>
//#include <event2/thread.h>

namespace TcpNetWork
{

namespace priv
{

class UtilsImpl
{
public:
	UtilsImpl();
	~UtilsImpl();
};

UtilsImpl::UtilsImpl()
{
	/* WSA Startup */
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	/* Enable thread support on windows */
	//evthread_use_windows_threads();
}

UtilsImpl::~UtilsImpl()
{
	/* WSA Cleanup */
	WSACleanup();
}

}

}
