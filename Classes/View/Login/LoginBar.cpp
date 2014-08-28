#include "Config.h"
#include "LoginBar.h"
#include "TcpNetwork/TcpNet.h"
#include "../Packet/Builder.h"

namespace View
{
	LoginBar::LoginBar()
	{

	}

	Scene* LoginBar::createScene()
	{
		auto scene = Scene::create();
		auto layer = LoginBar::create();
		scene->addChild(layer);
		return scene;
	}

	bool LoginBar::init()
	{
		if (!Layer::init())
		{
			return false;
		}

		auto vOrigin = Director::getInstance()->getVisibleOrigin();
		auto vSize = Director::getInstance()->getVisibleSize();
		Point pCenter = Point(vOrigin.x + vSize.width/2, vOrigin.y + vSize.height/2);
		_lbackGround = Sprite::create(spLoginBackGround);
		_lbackGround->setPosition(pCenter.x, pCenter.y);
		this->addChild(_lbackGround);

		bool bConnect = false;
		bConnect = TcpNetWork::_tcpnet.connect("127.0.0.1", 7771, 50);
		if (bConnect)
		{

			Packet::UserLogin ulogin;
			ulogin.SetUsername("chess@pope");
			ulogin.SetPwd("123456");
			ulogin.send();

			//Packet::UserPlayNow upn;
			//upn.send();

		}

		return true;
	}
}