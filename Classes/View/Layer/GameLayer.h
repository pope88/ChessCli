#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_
#include "cocos2d.h"
USING_NS_CC;

namespace View
{
	class GameLayer : public Layer
	{
		enum TAG_BG
		{
			TAG_BG_NEAR_LAYER = 0,
			TAG_BG_FAR_LAYER = 1
		};
	public:
	    CREATE_FUNC(GameLayer);
		static Scene* creatScene();
	public:
		virtual void onEnter();
		bool init();
	private:
		Sprite *spBackGround;


	};
}
#endif