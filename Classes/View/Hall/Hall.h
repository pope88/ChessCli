#ifndef _HALL_H_
#define _HALL_H_
#include "cocos2d.h"
USING_NS_CC;

namespace View
{
	static const std::string spHallBackGround = "flump/table_backgroud/table0.jpg";
	class Hall : public Layer
	{
	public:
		Hall();
		CREATE_FUNC(Hall);
		static Scene* createScene();
	    bool init();
	private:
		Sprite *_hbackGround;
	};
}

#endif