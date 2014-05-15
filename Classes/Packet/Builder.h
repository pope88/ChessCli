#ifndef _BUILDER_H_
#define _BUILDER_H_
#include "PacketsCtoS.h"


namespace Packet
{
	using namespace game::net::data::CtoS;
	class Builder
	{
	public:
		inline Builder(UInt16 o):op(o){}
		virtual ~Builder() {}
		void send();
		const std::string& data();

		bool repack();
	protected:
		virtual void packContent() = 0;
	private:
		bool pack();
	protected:
		std::shared_ptr<std::string> stream;
	private:
		UInt16 op;
	};

	template<class T, UInt16 OP>
	class BuilderT: public Builder, public T
	{
	public:
		BuilderT<T, OP>():Builder(OP){}
		virtual void packContent()
		{
			T::Pack(*stream.get());
		}
	};

#define DefBuilder(t, o) typedef BuilderT<CS##t##_##o, o> t
#include "Builder.inl"
}

#endif