#ifndef _UTILS_H_
#define _UTILS_H_

#ifdef _WIN32

#include <winsock2.h>
#include <errno.h>
#ifndef WEWOULDBLOCK
#define WEWOULDBLOCK WSAEWOULDBLOCK
#define WEINPROGRESS WSAEINPROGRESS
#define WECONNRESET WSAECONNRESET
#define WENETRESET WSAENETRESET
#endif
#ifndef ENOMEM
#define EINTR WSAEINTR
#define EFAULT WSAEFAULT
#define ENOMEM WSA_NOT_ENOUGH_MEMORY
#define EAGAIN WSATRY_AGAIN
#endif

#ifndef HAVE_SOCKLEN_T
#define HAVE_SOCKLEN_T
typedef int socklen_t;
#endif

#ifdef _MSC_VER
#ifndef _SSIZE_T_
#define _SSIZE_T_
typedef long _ssize_t;

typedef _ssize_t ssize_t;
#endif
#endif

typedef intptr_t socket_t;

#else

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netdb.h>
#ifndef SOCKET_ERROR
#define SOCKET_ERROR (-1)
#endif

typedef int socket_t;

#endif

namespace TcpNetWork
{

	namespace priv
	{
		class UtilsImpl;
	}

	/* This class is written to initialize/uninitialize network layer */
	class Utils
	{
	public:
		Utils();
		~Utils();
	private:
		priv::UtilsImpl * utilsImpl;
	};

}

#endif // _UTILS_H_
