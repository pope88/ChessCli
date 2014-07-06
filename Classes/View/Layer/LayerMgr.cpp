#include "Config.h"
#include "LayerMgr.h"
#include "GameLayer.h"

namespace View
{
	enum LAYERLIST
	{
		GAMELAYER = 0,
	};

	static std::function<Layer*()> createFunctions[] = 
	{
		CL(GameLayer),
	};
}
