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

		_lbackGround = Sprite::create(spLoginBackGround);
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