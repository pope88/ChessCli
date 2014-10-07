#ifndef _LOGINBAR_H_
#define _LOGINBAR_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../PreConfig.h"


USING_NS_CC;
using namespace ui;

namespace View
{
	static const std::string spLoginBackGround = "flump/login/login0.jpg";
	class LoginBar : public Layer
	{
	public:
		LoginBar();
		~LoginBar();
		CREATE_FUNC(LoginBar);
		static Scene* createScene();
		bool init();
	private:
		Sprite *_lbackGround;
		LS_PROPERTY_RETAIN(Button*, loginButton, loginButton);
		bool bConnect;
	};
}

#endif