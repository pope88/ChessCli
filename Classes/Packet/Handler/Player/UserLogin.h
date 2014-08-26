inline UInt8 hextov(char s)
{
	if(s >= '0' && s <= '9')
		return s - '0';
	if(s >= 'a' && s <= 'f')
		return s - ('a' - 10);
	if(s >= 'A' && s <= 'F')
		return s - ('A' - 10);
	return 0;
}

#include "cocos2d.h"
#include "View/Hall/Hall.h"
USING_NS_CC;
HANDLER_CLASS(UserLogin, 0x02)
{
	printf("on server user login ");
	if (pkt.Result() == 0)
	{
		// create a scene. it's an autorelease object
		auto scene = View::Hall::createScene();
		Director::getInstance()->runWithScene(scene);
	}
	else
	{

	}

}
HANDLER_END(UserLogin)
