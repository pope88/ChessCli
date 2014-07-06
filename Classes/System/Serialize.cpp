#include "Config.h"
#include "Serialize.h"

namespace System
{

	static char table64[64] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
		'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
	};

	static char table128[128] = {
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1,  0, -1, -1,
		-1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
		-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
		41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1
	};

	SerializeInfo::SerializeInfo(UInt8 version): buffer(1024)
	{
		buffer.resize(3);
		buffer.push_back(version);
	}

	SerializeInfo& SerializeInfo::operator << (UInt32 val)
	{
		if(val < 0x80) {
			buffer.push_back(val);
		} else if(val < 0x4000) {
			buffer.push_back((val & 0x3f) | 0x80);
			buffer.push_back(val >> 6);
		} else if(val < 0x200000) {
			buffer.push_back((val & 0x1f) | 0xc0);
			buffer.push_back(val >> 5);
			buffer.push_back(val >> 13);
		} else if(val < 0x10000000) {
			buffer.push_back((val & 0xf) | 0xe0);
			buffer.push_back(val >> 4);
			buffer.push_back(val >> 12);
			buffer.push_back(val >> 20);
		} else {
			buffer.push_back(0xff);
			buffer.push_back(val);
			buffer.push_back(val >> 8);
			buffer.push_back(val >> 16);
			buffer.push_back(val >> 24);
		}
		return *this;
	}

	SerializeInfo& SerializeInfo::operator << (Int32 val) 
	{
		UInt32 val1 = (UInt32)val;
		return (*this) << val1;
	}

	SerializeInfo& SerializeInfo::operator << (UInt64 val)
	{
		UInt32 val1 = val & 0xffffffff;
		UInt32 val2 = val >> 32;
		return (*this) << val1 << val2;
	}

	SerializeInfo& SerializeInfo::operator << (Int64 val)
	{
		UInt64 val1 = (UInt64)val;
		return (*this) << val1;
	}

	SerializeInfo& SerializeInfo::operator << (UInt16 val) 
	{
		UInt32 val1 = (UInt32)val;
		return (*this) << val1;
	}

	SerializeInfo& SerializeInfo::operator << (Int16 val) 
	{
		UInt32 val1 = (UInt32)val;
		return (*this) << val1;
	}

	SerializeInfo& SerializeInfo::operator << (UInt8 val) 
	{
		UInt32 val1 = (UInt32)val;
		return (*this) << val1;
	}

	SerializeInfo& SerializeInfo::operator << (Int8 val) 
	{
		UInt32 val1 = (UInt32)val;
		return (*this) << val1;
	}

	SerializeInfo& SerializeInfo::operator << (Serializable* val)
	{
		val->Serialize(*this);
		return *this;
	}

	void SerializeInfo::ToString(std::string& str)
	{
		size_t len = buffer.size() - 4;
		str = "";
		str.reserve(1024);
		buffer[0] = len & 0xff;
		buffer[1] = (len >> 8) & 0xff;
		buffer[2] = 0;
		size_t i = 0;
		for(i = 4; i < buffer.size(); i ++)
			buffer[2] += buffer[i];
		for(i = 0; i < buffer.size() - 3; i += 3)
		{
			str.push_back(table64[buffer[i] & 0x3f]);
			str.push_back(table64[(((UInt32)buffer[i] >> 6) & 0x3) | (((UInt32)buffer[i + 1] & 0xf) << 2)]);
			str.push_back(table64[(((UInt32)buffer[i + 1] >> 4) & 0xf) | (((UInt32)buffer[i + 2] & 0x3) << 4)]);
			str.push_back(table64[((UInt32)buffer[i + 2] >> 2) & 0x3f]);
		}
		if(buffer.size() % 3 == 1)
		{
			str.push_back(table64[buffer[i] & 0x3f]);
			str.push_back(table64[(((UInt32)buffer[i] >> 6) & 0x3)]);
			str.push_back('=');
			str.push_back('=');
		}
		else if(buffer.size() % 3 == 2)
		{
			str.push_back(table64[buffer[i] & 0x3f]);
			str.push_back(table64[(((UInt32)buffer[i] >> 6) & 0x3) | (((UInt32)buffer[i + 1] & 0xf) << 2)]);
			str.push_back(table64[(((UInt32)buffer[i + 1] >> 4) & 0xf)]);
			str.push_back('=');
		}
		else
		{
			str.push_back(table64[buffer[i] & 0x3f]);
			str.push_back(table64[(((UInt32)buffer[i] >> 6) & 0x3) | (((UInt32)buffer[i + 1] & 0xf) << 2)]);
			str.push_back(table64[(((UInt32)buffer[i + 1] >> 4) & 0xf) | (((UInt32)buffer[i + 2] & 0x3) << 4)]);
			str.push_back(table64[((UInt32)buffer[i + 2] >> 2) & 0x3f]);
		}
	}

	DeserializeInfo::DeserializeInfo(const std::string& restore_): valid(false), pbuf(0)
	{
		size_t len = restore_.length();
		if((len % 4) || (len < 4))
		{
			current = NULL;
			return;
		}
		pbuf = new UInt8[len / 4 * 3];
		current = pbuf;
		size_t sz = 0;
		UInt8 * restore = (UInt8 *)&restore_[0];
		for(size_t i = 0; i < len; i += 4)
		{
			if(restore[i] >= 128 || restore[i + 1] >= 128 || restore[i + 2] >= 128 || restore[i + 3] >= 128 ||
				table128[restore[i]] == -1 || table128[restore[i + 1]] == -1 || table128[restore[i + 2]] == -1 || table128[restore[i + 3]] == -1)
				return;
			if(restore[i + 2] == '=')
				sz += 1;
			else if(restore[i + 3] == '=')
				sz += 2;
			else
				sz += 3;
			UInt32 val1 = table128[restore[i]];
			UInt32 val2 = table128[restore[i + 1]];
			UInt32 val3 = table128[restore[i + 2]];
			UInt32 val4 = table128[restore[i + 3]];
			current[0] = val1 | ((val2 & 0x3) << 6);
			current[1] = ((val2 >> 2) & 0xf) | ((val3 & 0xf) << 4);
			current[2] = ((val3 >> 4) & 0x3) | (val4 << 2);
			current += 3;
		}
		if((size_t)*(UInt16*)pbuf != sz - 4)
			return;
		pend = pbuf + sz;
		UInt8 check = 0;
		for(size_t i = 4; i < sz; ++i)
			check += pbuf[i];
		if(check != pbuf[2])
			return;
		valid = true;
		current = &pbuf[4];
	}

	DeserializeInfo::~DeserializeInfo()
	{
		if(pbuf)
			delete pbuf;
	}

	bool DeserializeInfo::isValid()
	{
		return valid;
	}

	bool DeserializeInfo::isEnd()
	{
		return current >= pend;
	}

	UInt8 DeserializeInfo::GetVersion()
	{
		return pbuf[3];
	}

	DeserializeInfo& DeserializeInfo::operator >> (UInt32& val)
	{
		if(current[0] < 0x80) {
			if(current + 1 > pend)
			{ current = pend; val = 0; return *this; }
			val = current[0];
			current += 1;
		} else if(current[0] < 0xc0) {
			if(current + 2 > pend)
			{ current = pend; val = 0; return *this; }
			val = ((UInt32)current[0] & 0x3f) | ((UInt32)current[1] << 6);
			current += 2;
		} else if(current[0] < 0xe0) {
			if(current + 3 > pend)
			{ current = pend; val = 0; return *this; }
			val = ((UInt32)current[0] & 0x1f) | ((UInt32)current[1] << 5) | ((UInt32)current[2] << 13);
			current += 3;
		} else if(current[0] < 0xf0) {
			if(current + 4 > pend)
			{ current = pend; val = 0; return *this; }
			val = ((UInt32)current[0] & 0x0f) | ((UInt32)current[1] << 4) | ((UInt32)current[2] << 12) | ((UInt32)current[3] << 20);
			current += 4;
		} else {
			if(current + 5 > pend)
			{ current = pend; val = 0; return *this; }
			val = *((UInt32*)(current + 1));
			current += 5;
		}
		return *this;
	}

	DeserializeInfo& DeserializeInfo::operator >> (UInt64& val)
	{
		UInt32 val1, val2;
		(*this) >> val1 >> val2;
		val = (UInt64)val1 | ((UInt64)val2 << 32);
		return *this;
	}

	DeserializeInfo& DeserializeInfo::operator >> (Int64& val)
	{
		UInt32 val1, val2;
		(*this) >> val1 >> val2;
		val = (UInt64)val1 | ((UInt64)val2 << 32);
		return *this;
	}

	DeserializeInfo& DeserializeInfo::operator >> (Int32& val)
	{
		UInt32 val1;
		(*this) >> val1;
		val = val1;
		return *this;
	}

	DeserializeInfo& DeserializeInfo::operator >> (UInt16& val)
	{
		UInt32 val1;
		(*this) >> val1;
		val = val1;
		return *this;
	}

	DeserializeInfo& DeserializeInfo::operator >> (Int16& val)
	{
		UInt32 val1;
		(*this) >> val1;
		val = val1;
		return *this;
	}

	DeserializeInfo& DeserializeInfo::operator >> (UInt8& val)
	{
		UInt32 val1;
		(*this) >> val1;
		val = val1;
		return *this;
	}

	DeserializeInfo& DeserializeInfo::operator >> (Int8& val)
	{
		UInt32 val1;
		(*this) >> val1;
		val = val1;
		return *this;
	}

	DeserializeInfo& DeserializeInfo::operator >> (Serializable* val)
	{
		val->Deserialize(*this);
		return *this;
	}

}
