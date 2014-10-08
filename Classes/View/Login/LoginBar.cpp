#include "Config.h"
#include "LoginBar.h"
#include "TcpNetwork/TcpNet.h"
#include "../Packet/Builder.h"

namespace View
{
	LoginBar::LoginBar() : bConnect(false)
	{
		LS_P_INIT(loginButton);
	}

	LoginBar::~LoginBar()
	{
		LS_P_RELEASE(loginButton);
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

		Button *lb = Button::create(spLoginBtn);
		setloginButton(lb);
		addChild(getloginButton());
		lb->setPosition(pCenter);

		getloginButton()->addTouchEventListener(CC_CALLBACK_2(LoginBar::onClickLoginBtn, this));

		bConnect = TcpNetWork::_tcpnet.connect("127.0.0.1", 7771, 50);

		return true;
	}

	void LoginBar::onClickLoginBtn(Ref* sender, Button::TouchEventType event)
	{
		if (bConnect)
		{
			Packet::UserLogin ulogin;
			ulogin.SetUsername("chess2@pope");
			ulogin.SetPwd("123456");
			ulogin.send();
		}
	}
}