#ifndef _PACKETHEAD_H_
#define _PACKETHEAD_H_
#include "SsuObject.h"

#define CLIENTHLEN  10
#define GATEWAYHLEN 10	

namespace Packet
{
	class PacketHead : public ::ssu::Object
	{
	public:
		inline PacketHead(): _op(0), _len(0) {}
		virtual ~PacketHead() { }

	public:
		virtual unsigned char * PackBuffer(unsigned char * buf)
		{
			buf = ::ssu::Utils::PackFixed32Tag(buf, 1, _op);
			buf = ::ssu::Utils::PackFixed32Tag(buf, 2, _len);
			return buf;
		}

		virtual bool UnpackBuffer(const unsigned char *& buf, size_t& leftSize)
		{
			unsigned int tag_; unsigned char type_;
			while(leftSize > 0)
			{
				if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_))
					return false;
				switch(tag_)
				{
				case 1:
					if(!::ssu::Utils::UnpackFixed32(buf, leftSize, _op))
						return false;
					break;
				case 2:
					if(!::ssu::Utils::UnpackFixed32(buf, leftSize, _len))
						return false;
					break;
				default: break;
				}
			}
			return true;
		}
		virtual size_t Size() const
		{
			return 1 + ::ssu::Utils::SizeFixed32(_op) + 1 + ::ssu::Utils::SizeFixed32(_len);
		}

	public:
		inline  int Getop() const { return _op; }
		inline void Setop(int op) { _op = op; }

		inline  int Getlen() const { return _len; }
		inline void Setlen(int len) { _len = len; }

	protected:
		int _op;
		int _len;
	};
	static PacketHead packhead;

	class GPacketHead : public PacketHead
	{
	public:
		GPacketHead():_count(0) {}
	public:
		virtual unsigned char* PackBuffer(unsigned char *buf)
		{
			buf = ::ssu::Utils::PackFixed32Tag(buf, 1, _count);
			buf = ::ssu::Utils::PackFixed32Tag(buf, 2, _op);
			buf = ::ssu::Utils::PackFixed32Tag(buf, 3, _len);
			return buf;
		}

		virtual bool UnpackBuffer(const unsigned char *& buf, size_t &leftSize)
		{
			unsigned int tag_; unsigned char type_;
			while(leftSize > 0)
			{
				if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_))
					return false;
				switch(tag_)
				{
				case 1:
					if(!::ssu::Utils::UnpackFixed32(buf, leftSize, _count))
						return false;
					break;
				case 2:
					if(!::ssu::Utils::UnpackFixed32(buf, leftSize, _op))
						return false;
					break;
				case 3:
					if(!::ssu::Utils::UnpackFixed32(buf, leftSize, _len))
						return false;
					break;
				default: break;
				}
			}
			return true;
		}
		virtual size_t Size() const
		{
			return 1 + ::ssu::Utils::SizeFixed32(_count) + 1 + ::ssu::Utils::SizeFixed32(_op) + 1 + ::ssu::Utils::SizeFixed32(_len);
		}

		inline int GetCount()const { return _count; }
		inline void SetCount(int c) { _count = c; }
	protected:
		int _count;
	};
}
#endif