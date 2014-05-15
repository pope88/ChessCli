#include "Config.h"
#include "Socket.h"

#ifndef _WIN32
#include <fcntl.h>
#include <errno.h>
#endif

namespace TcpNetWork
{

Socket::Socket(): _fd(-1), _id(0), _data(NULL)
{
}

Socket::Socket( socket_t fd ): _fd(fd), _id(0), _data(NULL)
{
}

Socket::Socket( int af, int type, int protocol ): _fd(-1), _id(0), _data(NULL)
{
	init(af, type, protocol);
}

Socket::~Socket()
{
	close();
}

bool Socket::init( int af, int type, int protocol )
{
	_fd = ::socket(af, type, protocol);
	return _fd >= 0;
}

bool Socket::bind( const char * addr, UInt16 port )
{
	UInt32 ipaddr = resolveAddress(addr);
	if(ipaddr == 0xFFFFFFFF)
		return false;
	return bind(ipaddr, port);
}

bool Socket::bind( UInt32 ipaddr, UInt16 port )
{
	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(ipaddr);
	saddr.sin_port = htons(port);
	if(::bind(_fd, (const struct sockaddr *)&saddr, sizeof(saddr)) == SOCKET_ERROR)
		return false;
	return true;
}

bool Socket::bind( UInt16 port )
{
	return bind(static_cast<UInt32>(INADDR_ANY), port);
}

bool Socket::listen( int backlog )
{
	return ::listen(_fd, backlog) >= 0;
}

void Socket::shutdown( int sf )
{
	if(_fd < 0)
		return;
	::shutdown(_fd, sf);
}

void Socket::close()
{
	if(_fd < 0)
		return;
#ifdef _WIN32
	::closesocket(_fd);
#else
	::close(_fd);
#endif
		//	_fd = -1;
}

bool Socket::makeLinger( bool enabled )
{
	struct linger so_linger;
	so_linger.l_onoff = enabled ? 1 : 0;
	so_linger.l_linger = 0;
	if(setsockopt(_fd, SOL_SOCKET, SO_LINGER, (const char *)&so_linger, sizeof(so_linger)) == SOCKET_ERROR)
		return false;
	return true;
}

bool Socket::makeBlock( bool enabled )
{
#ifdef _WIN32
	u_long nonblocking = enabled ? 0 : 1;
	if (::ioctlsocket(_fd, FIONBIO, &nonblocking) == SOCKET_ERROR) {
		return false;
	}
#else
	int flags;
	if ((flags = ::fcntl(_fd, F_GETFL, NULL)) < 0) {
		return false;
	}
	if(enabled)
	{
		if (::fcntl(_fd, F_SETFL, flags & ~O_NONBLOCK) == -1) {
			return false;
		}
	}
	else
	{
		if (::fcntl(_fd, F_SETFL, flags | O_NONBLOCK) == -1) {
			return false;
		}
	}
#endif
	return true;
}

bool Socket::makeNoDelay( bool enabled )
{
	int yes = enabled ? 1 : 0;
	return setsockopt(_fd, IPPROTO_TCP, TCP_NODELAY, (const char *)&yes, sizeof(yes)) == -1;
}

int Socket::lastErr()
{
#ifdef _WIN32
	return WSAGetLastError();
#else
	return errno;
#endif
}

UInt32 Socket::resolveAddress( const char * addr )
{
	struct in_addr ina;
#ifdef _WIN32
	ina.s_addr = inet_addr(addr);
	if (ina.s_addr == INADDR_NONE) {
#else
	if (inet_aton(addr, &ina) == 0) {
#endif
		struct hostent *he;

		he = gethostbyname(addr);
		if (he == NULL) {
			return 0xFFFFFFFF;
		}
		return ntohl(*(UInt32 *)he->h_addr);
	}
	return ntohl(ina.s_addr);
}

UInt32 Socket::getAddr()
{
	struct sockaddr_in addr = {0};
	socklen_t len = sizeof(struct sockaddr_in);
	if(getsockname(_fd, (struct sockaddr *)&addr, &len) < 0)
		return 0xFFFFFFFF;
	return ntohl(addr.sin_addr.s_addr);
}

UInt32 Socket::getRemoteAddr()
{
	struct sockaddr_in addr = {0};
	socklen_t len = sizeof(struct sockaddr_in);
	if(getpeername(_fd, (struct sockaddr *)&addr, &len) < 0)
		return 0xFFFFFFFF;
	return ntohl(addr.sin_addr.s_addr);
}

}
