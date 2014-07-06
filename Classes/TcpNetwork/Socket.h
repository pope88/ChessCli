#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "Utils.h"

namespace TcpNetWork
{

	/* Basic socket class to implement platform independent interfaces */
	class Socket
	{
	public:
		/* Constructors & desctructors */
		Socket();
		Socket(socket_t fd);
		Socket(int af, int type, int protocol);
		virtual ~Socket();
		bool init(int af, int type, int protocol);
		/* Bind to host:port */
		bool bind(const char * host, UInt16 port);
		/* Bind to addr:port */
		bool bind(UInt32 addr, UInt16 port);
		/* Bind to 0.0.0.0:port */
		bool bind(UInt16 port);
		/* Start listening */
		bool listen(int backlog);
		/* Shutdown (aka graceful close) */
		void shutdown(int sflag);
		/* Close (aka hard close, reset connection) */
		void close();

		/* set linger of socket */
		bool makeLinger(bool);
		/* set block of socket */
		bool makeBlock(bool);
		/* set nodelay */
		bool makeNoDelay(bool);
		/* get socket address */
		UInt32 getAddr();
		/* get socket remote address */
		UInt32 getRemoteAddr();
		/* select */
		bool select(int nTimeoutMS = 0);

	public:
		/* get last error */
		static int lastErr();
		/* resolve ip address from string */
		static UInt32 resolveAddress(const char *);

	public:
		inline socket_t getFD() { return _fd; }
		/* cast to fd */
		inline operator socket_t() { return _fd; }
		/* Check if fd is initilized */
		inline bool initialized() { return _fd >= 0; }
		/* Assign custom data */
		inline void setData(void * d) { _data = d; }
		/* Get custom data */
		template<typename T>
		inline T * getData() { return static_cast<T *>(_data); }

		/* Set session id */
		inline void setId(UInt32 id) { _id = id; }
		/* Get session id */
		inline UInt32 id() { return _id; }

	protected:
		socket_t _fd;

		/*send buffers*/
		UInt32 _id;
		void * _data;  
	};

}

#endif // _SOCKET_H_
