#ifndef _UNIQUEID_H_
#define _UNIQUEID_H_

#include "Mutex.h"

namespace System
{


template<typename T>
class UniqueID
{
	struct FreeID
	{
		inline bool operator < (const FreeID& other) const { return _min < other._min; }
		inline bool operator > (const FreeID& other) const { return _min > other._min; }
		inline bool operator == (const FreeID& other) const { return _min == other._min; }
		mutable T _min, _max;
	};
	typedef std::set<FreeID> FIDSet;
	typedef typename FIDSet::iterator FIDIterator;

public:
	inline UniqueID<T>(): _maxId(0) {}
	inline T next()
	{
		Mutex::ScopedLock lk(_mutex);
		FIDIterator it = _freeId.begin();
		if(it == _freeId.end())
		{
			return ++ _maxId;
		}
		T r = it->_min;
		if(it->_min == it->_max)
			_freeId.erase(it);
		else
			++ it->_min;
		return r;
	}
	inline void addFreeN(T lId, T hId)
	{
		FreeID fid = {lId, hId};
		_freeId.insert(fid);
	}
	inline void setMax(T id)
	{
		_maxId = id;
	}
	inline void addFree(T lId, T hId)
	{
		FreeID fid = {lId, hId};
		FIDIterator it = _freeId.upper_bound(fid);
		if(it == _freeId.begin())
		{
			if(it != _freeId.end() && hId + 1 >= it->_min)
			{
				it->_min = lId;
				return;
			}
		}
		else if(it == _freeId.end())
		{
			-- it;
			if(it->_max + 1 >= lId)
			{
				it->_max = hId;
				return;
			}
		}
		else
		{
			if(hId + 1 >= it->_min)
			{
				FIDIterator it2 = it;
				-- it2;
				if(it2->_max + 1 >= lId)
				{
					it2->_max = it->_max;
					_freeId.erase(it);
					return;
				}
				else
				{
					it->_min = lId;
					return;
				}
			}
			else
			{
				-- it;
				if(it->_max + 1 >= lId)
				{
					it->_max = hId;
					return;
				}
			}
		}
		_freeId.insert(fid);
	}
	void test()
	{
		for(FIDIterator it = _freeId.begin(); it != _freeId.end(); ++ it)
		{
			printf(" [%u,%u]", it->_min, it->_max);
		}
		printf("\n");
	}
private:
	T _maxId;
	FIDSet _freeId;
	Mutex _mutex;
};

}

#endif // _UNIQUEID_H_
