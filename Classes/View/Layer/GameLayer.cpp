#include "Config.h"
#include "GameLayer.h"
#include "../Sprite/CardNormal.h"
#include "../GameResources.h"
#include "../../Packet/Builder.h"

namespace View
{

void GameLayer::onEnter()
{
	Layer::onEnter();
}

bool GameLayer::init()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	SpriteFrameCache *cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(s_pPlistDDZcards);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Layer::init();
	spBackGround = Sprite::create(s_pPathBackGround1);
	spBackGround->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(spBackGround);

	forTest();

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
	for (int i = 0; i < 7; ++i)
	{
		CardBase *pcard = new CardNormal(3+i, 0);
		this->addChild(pcard);
		pcard->setPosition(100+30*i, 100);
		cardsList.push_back(pcard);
	}
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
}

void GameLayer::forTest()
{
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

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

	auto menu = Menu::create();
	menu->addChild(pButton1);
	menu->addChild(pButton2);
	menu->addChild(pButton3);

	this->addChild(menu);
	menu->setPosition(Point(50, 300));

	auto label = LabelTTF::create("Hello World", "Arial", 20);
	label->setTag(101);

	// position the label on the center of the screen
	label->setPosition(Point(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);
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

	Packet::UserLogin ulogin;
	ulogin.SetUsername("chess@pope");
	ulogin.SetPwd("123456");
	ulogin.send();
}

void GameLayer::onButtonClick3(Ref* pSender)
{
	dynamic_cast<LabelTTF*>(this->getChildByTag(101))->setString("fuck you 3");
}

}