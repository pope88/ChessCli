#include "Config.h"
#include "Table.h"
#include "../VisibleRect.h"

namespace View
{
	Table::Table()
	{
	}

	Scene* Table::creatScene()
	{
		auto scene = Scene::create();
		auto layer = Table::create();
		scene->addChild(layer);
		//layer->createCards();
		return scene;
	}

	void Table::onEnter()
	{
		Layer::onEnter();
	}

	void Table::initOhterPlayers(UInt8 others)
	{
		_votherSeats.resize(others);
		for (size_t i = 0; i < others; ++i)
		{
			VBasePlayer *ps = VBasePlayer::create();
			this->addChild(ps);
			_votherSeats[i] = ps;
			ps->setPosition(200, 200);
		}
	}


	//this must run after initOhterPlayers
	void Table::initOhterPos(UInt8 others)
	{
		float posPlus = 10.0;
		_votherPoints.resize(others);
		if (others == 6)
		{
			auto vSize = Director::getInstance()->getVisibleSize();
			float a = VisibleRect::left().x;
			float b = _votherSeats[0]->getContentSize().width;
			float c = VisibleRect::left().y;
			_votherPoints[0] = Point(_votherSeats[0]->getSeatSize().width/2 + posPlus, VisibleRect::left().y - vSize.height/3);
			_votherPoints[1] = Point(_votherSeats[0]->getSeatSize().width/2 + posPlus, VisibleRect::left().y);
			_votherPoints[2] = Point(_votherSeats[0]->getSeatSize().width/2 + posPlus, VisibleRect::left().y + vSize.height/3);
			_votherPoints[3] = Point(VisibleRect::right().x -_votherSeats[0]->getSeatSize().width/2 - posPlus, VisibleRect::right().y +  - vSize.height/3);
			_votherPoints[4] = Point(VisibleRect::right().x -_votherSeats[0]->getSeatSize().width/2 - posPlus, VisibleRect::left().y);
			_votherPoints[5] = Point(VisibleRect::right().x -_votherSeats[0]->getSeatSize().width/2 - posPlus, VisibleRect::left().y -  - vSize.height/3);
			for (size_t i = 0; i < others; ++i)
			{
				_votherSeats[i]->setPosition(_votherPoints[i]);
			}

		}
		else
		{

		}
	}

	bool Table::init()
	{
		if (!Layer::init())
		{
			return false;
		}

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = CC_CALLBACK_2(Table::onTouchBegan, this);
		listener->onTouchEnded = CC_CALLBACK_2(Table::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		auto vOrigin = Director::getInstance()->getVisibleOrigin();
		auto vSize = Director::getInstance()->getVisibleSize();
		Point pCenter = Point(vOrigin.x + vSize.width/2, vOrigin.y + vSize.height/2);
		_backGroud = Sprite::create(spTableBackGroud);
		_backGroud->setPosition(pCenter.x, pCenter.y);
		auto s = Sprite::create(spStest);
		s->setAnchorPoint(Point(0.5, 0.5));
		s->setPosition(VisibleRect::center().x, VisibleRect::center().y);
		this->addChild(_backGroud);
		this->addChild(s);

		initOhterPlayers(1);
		//initOhterPos(OTHER);

		//auto listener  = EventListenerTouchOneByOne::create();
		//listener->setSwallowTouches(true);
		//listener->onTouchBegan = CC_CALLBACK_2(Table::onTouchBegan, this);
		//listener->onTouchEnded = CC_CALLBACK_2(Table::onTouchEnded, this);

		//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		return true;
	}

	bool Table::onTouchBegan(Touch *touch, Event *unused_event)
	{
		return true;
	}

	void Table::onTouchEnded(Touch *touch, Event *unused_event)
	{
		UInt8 t = 0;
		++t;
	}
}