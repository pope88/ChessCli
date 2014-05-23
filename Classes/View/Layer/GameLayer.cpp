#include "Config.h"
#include "GameLayer.h"
#include "../Sprite/CardNormal.h"
#include "../GameResources.h"
namespace View
{

void GameLayer::onEnter()
{
	Layer::onEnter();
}

bool GameLayer::init()
{
	SpriteFrameCache *cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(s_pPlistDDZcards);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Layer::init();
	spBackGround = Sprite::create(s_pPathBackGround1);
	spBackGround->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(spBackGround);

	return true;
}

Scene* GameLayer::creatScene()
{
	auto scene = Scene::create();
	auto layer = GameLayer::create();
	scene->addChild(layer);
	layer->createCards();
	return scene;
}

void GameLayer::createCards()
{
	CardBase *pcard = new CardNormal(3, 0);
	this->addChild(pcard);
	pcard->setPosition(100, 100);
	cardsList.push_back(pcard);
}

void GameLayer::clearCards()
{
	for (size_t i = 0; i < cardsList.size(); ++i)
	{
		delete cardsList[i];
	}
}

}