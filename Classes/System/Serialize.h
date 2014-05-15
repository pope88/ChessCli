#ifndef _SERIALIZE_H_
#define _SERIALIZE_H_

#include <vector>

namespace System
{

	class Serializable;

	class SerializeInfo
	{
	public:
		SerializeInfo(UInt8 version);

		SerializeInfo& operator << (UInt64 val);
		SerializeInfo& operator << (UInt32 val);
		SerializeInfo& operator << (UInt16 val);
		SerializeInfo& operator << (UInt8 val);
		SerializeInfo& operator << (Int64 val);
		SerializeInfo& operator << (Int32 val);
		SerializeInfo& operator << (Int16 val);
		SerializeInfo& operator << (Int8 val);
		SerializeInfo& operator << (Serializable* val);

		void ToString(std::string& str);

	private:
		std::vector<UInt8> buffer;
	};

	class DeserializeInfo
	{
	public:
		explicit DeserializeInfo(const std::string& restore);
		virtual ~DeserializeInfo();

		bool isValid();
		bool isEnd();
		UInt8 GetVersion();
		
		DeserializeInfo& operator >> (UInt64& val);
		DeserializeInfo& operator >> (UInt32& val);
		DeserializeInfo& operator >> (UInt16& val);
		DeserializeInfo& operator >> (UInt8& val);
		DeserializeInfo& operator >> (Int64& val);
		DeserializeInfo& operator >> (Int32& val);
		DeserializeInfo& operator >> (Int16& val);
		DeserializeInfo& operator >> (Int8& val);
		DeserializeInfo& operator >> (Serializable* val);

	private:
		bool valid;
		UInt8* pbuf;
		UInt8* pend;
		UInt8* current;
	};

	class Serializable
	{
	public:
		virtual void Serialize(SerializeInfo&) = 0;
		virtual void Deserialize(DeserializeInfo&) = 0;
	};

}
#endif
