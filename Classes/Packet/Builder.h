#ifndef _BUILDER_H_
#define _BUILDER_H_

#include "PacketsCtoS.h"
#include "../Game/Player.h"

using namespace Game;
namespace Packet
{
	using namespace game::net::data::CtoS;

	class Builder
	{
	public:
		typedef bool (*broadcastFilter)(Player *player);
	public:
		inline Builder(int o): op(o), _isGateWay(false) {}
		virtual ~Builder() {}
		void send();
		void sendMulti(void *multi);
		void sendNolock(Player *player);
		/*void sendNolock(Object::GPlayer *gplayer);*/
		void sendNolock(UInt32 sid, UInt32 gid);
		void sendLock();
		void sendUnlock();
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

#define DefBuilder(t, o) typedef BuilderT<CS##t##_##o, o> t
#include "Builder.inl"

}

#endif