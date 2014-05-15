#include "Config.h"
#include "CsvParser.h"
#include "NumberConv.h"

namespace System
{

	Int64 CsvParser::Row::asInt64( size_t idx ) const
	{
		return toInt64((*this)[idx].c_str());
	}

	UInt64 CsvParser::Row::asUInt64( size_t idx ) const
	{
		return toUInt64((*this)[idx].c_str());
	}

	Int32 CsvParser::Row::asInt32( size_t idx ) const
	{
		return toInt32((*this)[idx].c_str());
	}

	UInt32 CsvParser::Row::asUInt32( size_t idx ) const
	{
		return toUInt32((*this)[idx].c_str());
	}

	Int16 CsvParser::Row::asInt16( size_t idx ) const
	{
		return toInt16((*this)[idx].c_str());
	}

	UInt16 CsvParser::Row::asUInt16( size_t idx ) const
	{
		return toUInt16((*this)[idx].c_str());
	}

	Int8 CsvParser::Row::asInt8( size_t idx ) const
	{
		return toInt8((*this)[idx].c_str());
	}

	UInt8 CsvParser::Row::asUInt8( size_t idx ) const
	{
		return toUInt8((*this)[idx].c_str());
	}

	double CsvParser::Row::asDouble( size_t idx ) const
	{
		return toDouble((*this)[idx].c_str());
	}

	float CsvParser::Row::asFloat( size_t idx ) const
	{
		return toFloat((*this)[idx].c_str());
	}

	CsvParser::CsvParser(char seperator, char quote): _sep(seperator), _quote(quote), _cur(0) { }

	CsvParser::~CsvParser() {}

	bool CsvParser::load(const char * filename)
	{
		_cur = 0;
		_rows.clear();
		FILE * file = fopen(filename, "rb");
		if(file == NULL)
			return false;
		fseek(file, 0, SEEK_END);
		size_t sz = ftell(file);
		if(sz == 0)
		{
			fclose(file);
			return true;
		}
		fseek(file, 0, SEEK_SET);
		char * data = (char *)malloc(sz + 1);
		if(data == NULL)
		{
			fclose(file);
			return false;
		}
		fread(data, 1, sz, file);
		data[sz] = 0;
		fclose(file);

		int status = 0;
		size_t offset = 0, lastOff = 0;
		Row row;
		std::string curline;
		curline.reserve(1024);
		while(offset < sz)
		{
			char c = data[offset];
			if(c == '\r' || c == '\n')
			{
				if(lastOff < offset) curline.insert(curline.end(), data + lastOff, data + offset);
				row._fields.push_back(curline);
				curline.clear();
				curline.reserve(1024);
				_rows.push_back(row);
				row._fields.clear();
				do
				{
					c = data[++ offset];
				}
				while(c == '\r' || c == '\n');
				lastOff = offset;
				continue;
			}
			if(status == 0)
			{
				if(data[offset] == _sep)
				{
					if(lastOff < offset) curline.insert(curline.end(), data + lastOff, data + offset);
					row._fields.push_back(curline);
					curline.clear();
					curline.reserve(1024);
					lastOff = ++ offset;
					continue;
				}
				if(data[offset] == _quote)
				{
					if(lastOff < offset) curline.insert(curline.end(), data + lastOff, data + offset);
					status = 1;
					lastOff = ++ offset;
					continue;
				}
			}
			else
			{
				if(data[offset] == '\\' && data[offset + 1] == _quote)
				{
					if(lastOff < offset) curline.insert(curline.end(), data + lastOff, data + offset);
					curline.push_back(_quote);
					offset += 2;
					lastOff = offset;
					continue;
				}
				else if(data[offset] == _quote)
				{
					status = 0;
					if(lastOff < offset) curline.insert(curline.end(), data + lastOff, data + offset);
					lastOff = ++ offset;
					continue;
				}
			}
			++ offset;
			continue;
		}
		if(lastOff < offset)
		{
			curline.insert(curline.end(), data + lastOff, data + offset);
			row._fields.push_back(std::move(curline));
		}
		if(!row._fields.empty())
			_rows.push_back(row);
		free(data);
		return true;
	}

}
