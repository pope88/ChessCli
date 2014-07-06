#ifndef _CSVPARSER_H_
#define _CSVPARSER_H_

namespace System
{
	
	class CsvParser
	{
	public:
		class Row
		{
			friend class CsvParser;
		public:
			inline Row() {}
			inline size_t cols() const { return _fields.size(); }
			inline const std::string& operator[](size_t idx) const
			{
				static const std::string empty__;
				if(idx >= _fields.size())
					return empty__;
				return _fields[idx];
			}
			Int64 asInt64(size_t idx) const;
			UInt64 asUInt64(size_t idx) const;
			Int32 asInt32(size_t idx) const;
			UInt32 asUInt32(size_t idx) const;
			Int16 asInt16(size_t idx) const;
			UInt16 asUInt16(size_t idx) const;
			Int8 asInt8(size_t idx) const;
			UInt8 asUInt8(size_t idx) const;
			double asDouble(size_t idx) const;
			float asFloat(size_t idx) const;
		private:
			std::vector<std::string> _fields;
		};
	public:
		CsvParser(char seperator, char quote);
		~CsvParser();
		bool load(const char * filename);
		
		inline void resetCursor() { _cur = 0; }
		inline void clear() { _rows.clear(); _cur = 0; }
		inline const Row& row(size_t idx)
		{
			static const Row empty__;
			if(idx >= _rows.size())
				return empty__;
			return _rows[idx];
		}
		inline void skip(size_t l = 1)
		{
			_cur += l;
		}
		inline const Row * next()
		{
			if(_cur >= _rows.size())
				return NULL;
			return &_rows[_cur ++];
		}
	private:
		std::vector< Row > _rows;
		char _sep, _quote;
		size_t _cur;
	};

}

#endif
