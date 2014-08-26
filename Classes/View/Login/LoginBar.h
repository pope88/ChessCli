#ifndef _LOGINBAR_H_
#define _LOGINBAR_H_
#include "cocos2d.h"
USING_NS_CC;

namespace View
{
	static const std::string spLoginBackGround = "flump/login/login0.jpg";
	class LoginBar : public Layer
	{
	public:
		LoginBar();
		CREATE_FUNC(LoginBar);
		static Scene* createScene();
		bool init();
	private:
		Sprite *_lbackGround;
	};
}

#endif