#ifndef _TCPCLIENT_H_
#define _TCPCLIENT_H_

namespace TcpNetWork
{
//	/* Tcp socket event handler */
//	class TcpEventHandler
//	{
//	public:
//		virtual ~TcpEventHandler() {}
//		/* Destroy self, which is used to avoid destruction on static objects by leaving it empty */
//		virtual void destroy() {}
//		/* Called when accept a new client connection (used by server socket) */
//		virtual bool onAccept(TcpSocket *) { return false; }
//		/* Called when data inputs (used by client socket) */
//		virtual bool onRead(TcpSocket *, struct evbuffer *) { return false; }
//		/* Called when client socket disconnects (used by client socket) */
//		virtual void onDisconnect(TcpSocket *) {}
//		/* Indicates that if this socket accepts global broadcasts */
//		virtual bool accpetBroadcast(struct bufferevent*) { return false; }
//	};
//
//	/* Basic TCP-Client Class */
//class TcpClientBase
//{
//public:
//	/* Constructor
//	 *   if evBase is NULL, the class will create a event base and release it on destruction
//	 *   if evBase is not NULL, the class will use it handle server and incoming sockets
//	 *   threadSafe indicates wheather client sockets require thread safe functions in libevent2
//	 **/
//	TcpServerBase(struct event_base *evBase, bool threadSafe);
//	/* Destructor */
//	virtual ~TcpServerBase();
//
//	bool connect(const std::string& host, UInt16 port, UInt32 &sid);
//	/* start event loop, only used when event base is created by iteslef, Ohterwise please run
//	   event loop in the caller procedure*/
//	virtual int loop();
//
//	/* stop running the loop event*/
//	void stop();
//
//	/* Set the default handler which is used when a new connection is accepted */
//	inline void setDefaultHandler(TcpEventHandler *eh) { _defHandler = eh; }
//	/* Get the default handler */
//	inline TcpEventHandler * getDefaultHandler() { return _defHandler; }
//	/* Set a new handler for a connection */
//	void setHandler(UInt32 id, TcpEventHandler *eh);
//	/* Get current handler for the connection */
//	TcpEventHandler* getHandler(UInt32 id);
//
//	inline UInt32 size() { return _size; }
//
//protected:
//	static void _onClientEvent(struct bufferevent*, short, void*);
//protected:
//	struct event_base *_evBase;
//	TcpEventHandler *_defHandler;
//	bool _running;
//	bool _ownBase;
//	bool _threadSafe;
//	UInt32 _clientUniqueId;
//	UInt32 _size;
//protected:
//	/* Used by friend classes only */
//	void close2(UInt32);
//	void pendClose2(UInt32);
//	void send2(UInt32, const void*, int);
//	void send2(UInt32, const void*, int , const void*, int);
//	void send2(UInt32, const void*, int, const void*, int, const void*, int);
//protected:
//	static Utils * utils;
//};


}
#endif