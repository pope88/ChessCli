#include "Config.h"
#include "GameLayer.h"
#include "../Sprite/CardNormal.h"
#include "../GameResources.h"
#include "../../Packet/Builder.h"

#include "View/Sprite/CSeat.h"
#include "View/Anima/TimeBar.h"

#include "View/Sprite/CCardSprite.h"


namespace View
{

GameLayer::GameLayer(): _angle(0.0)
{

}
void GameLayer::onEnter()
{
	Layer::onEnter();
}

bool GameLayer::init()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_pPlistDDZcards);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Layer::init();

	spBackGround = Sprite::create(s_pPathTabeBackG);

	spBackGround->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(spBackGround);

	//forTest();
	forTestCard();

	return true;
}

Scene* GameLayer::creatScene()
{
	auto scene = Scene::create();
	auto layer = GameLayer::create();
	scene->addChild(layer);
	//layer->createCards();
	return scene;
}

void GameLayer::createCards()
{
	//for (int i = 0; i < 7; ++i)
	//{
	//	CardBase *pcard = new CardNormal(3+i, 0);
	//	this->addChild(pcard);
	//	pcard->setPosition(100+30*i, 100);
	//	cardsList.push_back(pcard);
	//}
}

void GameLayer::clearCards()
{
	for (size_t i = 0; i < cardsList.size(); ++i)
	{
		this->removeChild(cardsList[i]);
		delete cardsList[i];
	}
	cardsList.clear();
}

bool GameLayer::onTouchBegan(Touch* touch, Event  *event)
{
	return true;
}

void GameLayer::onTouchEnded(Touch* touch, Event  *event)
{
	//clearCards();
	//return true;
}

void GameLayer::forTestCard()
{
	CCardSprite *hc0 = CCardSprite::create(3, 2);
	//CardNormal *hc0 = CardNormal::create(3, 2);
	
	//Sprite * hc0 = Sprite::createWithSpriteFrameName("bcardbigking.png");
	this->addChild(hc0);
	hc0->setPosition(100, 100);

	auto timerbar = TimerBar::create();
	this->addChild(timerbar);
	timerbar->setPosition(300, 600);
	timerbar->startTimer(30);


	Button *lb = Button::create("Images/Login/loginbtn.png");
	this->addChild(lb);
	this->setPosition(300,300);
	lb->addTouchEventListener(CC_CALLBACK_2(GameLayer::onClickBtnTest, this));
}

void GameLayer::onClickBtnTest(Ref* sender, Button::TouchEventType event)
{

		Packet::UserLogin ulogin;
		ulogin.SetUsername("chess1@pope");
		ulogin.SetPwd("123456");
		ulogin.send();
}

void GameLayer::forTest()
{
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();


	auto bigPot = Sprite::create(s_pPathTablePot);
	this->addChild(bigPot);
	bigPot->setPosition(Point(visibleSize.width/2, 200));

	//auto seat1 = Sprite::create(s_pPathSeat);
    auto seat1 = View::CSeat::create();
	seat1->setPosition(Point(400, 400));
	this->addChild(seat1);


	auto timebar = View::TimerBar::create();
	timebar->setPosition(Point(300, 300));
	this->addChild(timebar);


	auto pButton1 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameLayer::onButtonClick1, this));
	pButton1->setPosition(Point(0, 0));

	auto pButton2 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameLayer::onButtonClick2, this));
	pButton2->setPosition(Point(50, 0));


	auto pButton3 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameLayer::onButtonClick3, this));
	pButton3->setPosition(Point(100, 0));

	auto pButton4 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameLayer::onButtonClick4, this));
	pButton4->setPosition(Point(150, 0));

	auto pButton5 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameLayer::onButtonClick5, this));
	pButton5->setPosition(Point(200, 0));

	auto menu = Menu::create();
	menu->addChild(pButton1);
	menu->addChild(pButton2);
	menu->addChild(pButton3);
	menu->addChild(pButton4);
	menu->addChild(pButton5);

	this->addChild(menu);
	menu->setPosition(Point(50, 300));

	auto label = LabelTTF::create("Hello World", "Arial", 20);
	label->setTag(101);

	// position the label on the center of the screen
	label->setPosition(Point(origin.x + visibleSize.width/2 + visibleSize.width/3,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// create the streak object and add it to the scene
	this->scheduleUpdate();

}

void GameLayer::update(float ft)
{
}

void GameLayer::onButtonClick1(Ref* pSender)
{
	dynamic_cast<LabelTTF*>(this->getChildByTag(101))->setString("User Register");

	Packet::UserRegister urg;
	urg.SetUsername("chess@pope");
	urg.SetPwd("123456");
	urg.send();

}

void GameLayer::onButtonClick2(Ref* pSender)
{
	dynamic_cast<LabelTTF*>(this->getChildByTag(101))->setString("User Login");

	//Packet::UserLogin ulogin;
	//ulogin.SetUsername("chess@pope");
	//ulogin.SetPwd("123456");
	//ulogin.send();
}

void GameLayer::onButtonClick3(Ref* pSender)
{
	dynamic_cast<LabelTTF*>(this->getChildByTag(101))->setString("fuck you 3");

	Packet::UserEnterRoom uer;
	uer.SetRoomid(0);
	uer.send();
}

void GameLayer::onButtonClick4(Ref* psender)
{
	dynamic_cast<LabelTTF*>(this->getChildByTag(101))->setString("fuck you 4");
	
	Packet::UserEnterTable uet;
	uet.SetTableno(0);
	uet.send();
}

void GameLayer::onButtonClick5(Ref* psender)
{
	dynamic_cast<LabelTTF*>(this->getChildByTag(101))->setString("fuck you 5");

	Packet::UserPlayNow upn;
	upn.send();
}

}