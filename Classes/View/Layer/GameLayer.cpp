#include "Config.h"
#include "GameLayer.h"
namespace View
{

void GameLayer::onEnter()
{
	Layer::onEnter();
}

bool GameLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Layer::init();
	spBackGround = Sprite::create("Game/background/table_BG.png");
	spBackGround->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(spBackGround);

	return true;
}

Scene* GameLayer::creatScene()
{
	auto scene = Scene::create();
	auto layer = GameLayer::create();
	scene->addChild(layer);
	return scene;
}

}