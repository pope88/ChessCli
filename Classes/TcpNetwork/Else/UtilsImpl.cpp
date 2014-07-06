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
	/* Enable thread support on POSIX systems */
	//evthread_use_pthreads();
}

UtilsImpl::~UtilsImpl()
{
}

}

}
