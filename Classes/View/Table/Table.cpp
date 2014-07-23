#include "Config.h"
#include "Table.h"
#include "../VisibleRect.h"

namespace View
{
	Table::Table(): mBaseChip(0), mBigBlindPos(0), mSmallBlindPos(0)
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

	void Table::initOtherSeats(UInt8 others)
	{
		_votherSeats.resize(others);
		for (size_t i = 0; i < others; ++i)
		{
			VBasePlayer *ps = VBasePlayer::create();
			this->addChild(ps);
			_votherSeats[i] = ps;
		}
	}

	void Table::initOtherPlayers(UInt8 others)
	{
		_votherPlayers.resize(others);
		for (size_t i = 0; i < others; ++i)
		{
			VOtherPlayer *ps  = VOtherPlayer::create();
			this->addChild(ps);
			_votherPlayers[i] = ps;
		}
	}


	//this must run after initOhterPlayers
	void Table::initOtherPos(UInt8 others)
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
				if (_votherPlayers[i] != NULL)
				{
					_votherPlayers[i]->setPosition(_votherPoints[i]);
				}
			}

		}
		else//
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

		initOtherSeats(OTHER);
		initOtherPlayers(OTHER);
		initOtherPos(OTHER);

		initCardBacks(OTHER);
		
		dealingCard();

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

	void Table::onPokerStart(UInt32 mChip, UInt8 bBlindPos, UInt8 sBlindPos)
	{
		mGameFlag = GAMEBEGIN;
		mBaseChip = mChip;
		mBigBlindPos = bBlindPos;
		mSmallBlindPos = sBlindPos;
	}

	void Table::dealingCard()
	{
		MoveTo *move = MoveTo::create(2.0f, ccp(300, 300));
		_cardBacks[0]->runAction(move);
	}

	void Table::initCardBacks(UInt8 others)
	{
		_cardBacks.resize(others);
		for (size_t i = 0; i < 3; ++i)
		{
			Sprite *sb0 = Sprite::create(spCardBacks[i]);
			Sprite *sb1 = Sprite::create(spCardBacks[i]);
			this->addChild(sb0);
			sb1->setScaleX(-1);
			this->addChild(sb1);
			_cardBacks[i] = sb0;
			_cardBacks[i+3] = sb1;
		}
	}
	
	void Table::initCardBacksPos()
	{
		_initCardBackPos[0] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
		_initCardBackPos[1] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
		_initCardBackPos[2] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
		_initCardBackPos[3] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
		_initCardBackPos[4] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
		_initCardBackPos[5] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);

		_endCardBackPos[0] = Point(VisibleRect::left().x, VisibleRect::left().y);
		_endCardBackPos[1] = Point(VisibleRect::left().x, VisibleRect::left().y);
		_endCardBackPos[2] = Point(VisibleRect::left().x, VisibleRect::left().y);
		_endCardBackPos[3] = Point(VisibleRect::right().x, VisibleRect::right().y);
		_endCardBackPos[4] = Point(VisibleRect::right().x, VisibleRect::right().y);
		_endCardBackPos[5] = Point(VisibleRect::right().x, VisibleRect::right().y);
	}

}