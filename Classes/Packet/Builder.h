#ifndef _BUILDER_H_
#define _BUILDER_H_

#include "PacketsStoC.h"

namespace Object
{
	class User;
}

namespace Packet
{
	using namespace game::net::data::StoC;

	class Builder
	{
	public:
		typedef bool (*broadcastFilter)(Object::User *user);
	public:
		inline Builder(int o): op(o), _isGateWay(true) {}
		virtual ~Builder() {}
		void send(Object::User *user);
	/*	void send(Object::GPlayer *gplayer);*/
		void send(UInt32 sid, UInt32 gid);
		void sendMulti(void *multi);
		void sendNolock(Object::User *user);
		/*void sendNolock(Object::GPlayer *gplayer);*/
		void sendNolock(UInt32 sid, UInt32 gid);
		void sendLock();
		void sendUnlock();
		void broadcast();
		void broadcast(broadcastFilter);
		//void broadcastCity(UInt16 cid, Object::User *user = NULL);
		const std::string& data();
		bool repack();
	protected:
		virtual void packContent() = 0;
	private:
		bool pack();

	protected:
		std::shared_ptr<std::string> stream;
	private:
		int op;
		bool _isGateWay;
	};

	template <class T, UInt16 OP>
	class BuilderT: public Builder, public T
	{
	public:
		BuilderT<T, OP>(): Builder(OP) {}
		virtual void packContent()
		{
			T::Pack(*stream.get());
		}
	};

#define DefBuilder(t, o) typedef BuilderT<SC##t##_##o, o> t
#include "Builder.inl"

}

#endif