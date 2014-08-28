#ifndef _HALL_H_
#define _HALL_H_
#include "cocos2d.h"
USING_NS_CC;

namespace View
{
	static const std::string spHallBackGround = "flump/hall/hall0.jpg";
	class Hall : public Layer
	{
	public:
		CREATE_FUNC(Hall);
		static Scene* createScene();
	    bool init();
		void onButtonQuickStart(Ref *psender);
	private:
		Sprite *_hbackGround;
		//MenuItemSprite* pQuikStartB;
		Menu *menu;
	};
}

#endif