#ifndef _LAYERMGR_H_
#define _LAYERMGR_H_

#define CL(__className__) [](){ return __className__::create();}


namespace View
{
	class LayerMgr
	{
		LayerMgr();
		virtual ~LayerMgr();

	};
}


#endif