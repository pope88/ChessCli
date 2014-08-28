#include "Config.h"
#include "Hall.h"
#include "../../Packet/Builder.h"

namespace View
{

	Scene* Hall::createScene()
	{
		auto scene = Scene::create();
		auto layer = Hall::create();
		scene->addChild(layer);
		return scene;
	}

	bool Hall::init()
	{
		if (!Layer::init())
		{
			return false;
		}


		auto vOrigin = Director::getInstance()->getVisibleOrigin();
		auto vSize = Director::getInstance()->getVisibleSize();
		Point pCenter = Point(vOrigin.x + vSize.width/2, vOrigin.y + vSize.height/2);
		_hbackGround = Sprite::create(spHallBackGround);
		this->addChild(_hbackGround);
		_hbackGround->setPosition(pCenter.x, pCenter.y);

		auto pQuikStartB = MenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(View::Hall::onButtonQuickStart, this));
		
		menu = Menu::create(pQuikStartB, NULL);
		this->addChild(menu);
		menu->setPosition(Point(500, 500));
		menu->setEnabled(true);
		return true;
	}

	void Hall::onButtonQuickStart(Ref *psender)
	{
		Packet::UserPlayNow upn;
		upn.send();
	}
}