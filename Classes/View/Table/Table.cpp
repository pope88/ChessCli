#include "Config.h"
#include "Table.h"
#include "../VisibleRect.h"

namespace View
{
	Table _table;
	 Scene *tableScene;
	Table::Table(): mBaseChip(0), mBankerPos(0), mBigBlindPos(0), mSmallBlindPos(0), mGameFlag(0), onwerCharid(0), mCallChips(0)
	{
		LS_P_INIT(backGroud);
		LS_P_INIT(bossSprite);
		LS_P_INIT(pMy);
		LS_P_INIT(pMySeat);
		LS_P_INIT(baseChipLabel);
		LS_P_INIT(allChipLabel);

		LS_P_INIT(foldButton);
		LS_P_INIT(callButton);	
		LS_P_INIT(checkButton);
		LS_P_INIT(betButton);
		LS_P_INIT(timebar);
	}

	Table::~Table()
	{
		LS_P_RELEASE(backGroud);
		LS_P_RELEASE(bossSprite);
		LS_P_RELEASE(pMy);
		LS_P_RELEASE(pMySeat);
		LS_P_RELEASE(baseChipLabel);
		LS_P_RELEASE(allChipLabel);

		LS_P_RELEASE(foldButton);
		LS_P_RELEASE(callButton);

		LS_P_RELEASE(checkButton);
		LS_P_RELEASE(betButton);
		LS_P_RELEASE(timebar);
	}

	Scene* Table::creatScene()
	{
		if (tableScene == NULL)
		{
			tableScene = Scene::create();
			//auto layer = Table::create();
			tableScene->addChild(&_table);
			_table.init();
			//layer->createCards();
			return tableScene;
		}
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
			VBaseSeat *ps = VBaseSeat::create();
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
		if (others == OTHER)
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

	void Table::initBossPos()
	{
		_bossPos.resize(MAXPLAYER);
		_bossPos[0] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
		_bossPos[1] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
		_bossPos[2] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
		_bossPos[3] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
		_bossPos[4] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
		_bossPos[5] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
		_bossPos[6] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
	}

	void Table::initCardsPos()
	{
		_cardsPos.resize(MAXPLAYER*2);

		_cardsPos[0] = Point(VisibleRect::bottom().x - 30, VisibleRect::bottom().y + 50);
		_cardsPos[1] = Point(VisibleRect::bottom().x + 30, VisibleRect::bottom().y + 50);

		_cardsPos[2] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
		_cardsPos[3] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);

		_cardsPos[4] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
		_cardsPos[5] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);

		_cardsPos[6] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
		_cardsPos[7] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);

		_cardsPos[8] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
		_cardsPos[9] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);

		_cardsPos[10] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
		_cardsPos[11] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);

		_cardsPos[12] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
		_cardsPos[13] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
	}

	void Table::initCommonCardPos()
	{
		if (_commonCardPos.empty())
		{
			_commonCardPos.resize(5);
		}
		_commonCardPos[0] == Point(Point(VisibleRect::center().x - 200, VisibleRect::center().y - 100));
		_commonCardPos[1] == Point(Point(VisibleRect::center().x - 100, VisibleRect::center().y - 100));
		_commonCardPos[2] == Point(Point(VisibleRect::center().x, VisibleRect::center().y - 100));
		_commonCardPos[3] == Point(Point(VisibleRect::center().x + 100, VisibleRect::center().y - 100));
		_commonCardPos[4] == Point(Point(VisibleRect::center().x + 200, VisibleRect::center().y - 100));
	}

	void Table::initTimeBarPos()
	{
		if (_timeBarPos.empty())
		{
			_timeBarPos.resize(MAXPLAYER);
			_timeBarPos[0] = Point(VisibleRect::rightTop().x-50, VisibleRect::rightTop().y -50);
			_timeBarPos[1] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
			_timeBarPos[2] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
			_timeBarPos[3] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
			_timeBarPos[4] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
			_timeBarPos[5] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y);
			_timeBarPos[6] = Point(VisibleRect::center().x, VisibleRect::center().y);
		}
	}

	void Table::initThrowChipsPos()
	{
	    float posPlus = 100;
		auto vSize = Director::getInstance()->getVisibleSize();
		if (_throwChipPos.empty())
		{
			_throwChipPos.resize(MAXPLAYER);

			_throwChipPos[0] = Point(VisibleRect::bottom().x, VisibleRect::bottom().y + 100);
			_throwChipPos[1] = Point(_votherSeats[0]->getSeatSize().width/2 + posPlus, VisibleRect::left().y - vSize.height/3);
			_throwChipPos[2] = Point(_votherSeats[0]->getSeatSize().width/2 + posPlus, VisibleRect::left().y);
			_throwChipPos[3] = Point(_votherSeats[0]->getSeatSize().width/2 + posPlus, VisibleRect::left().y + vSize.height/3);
			_throwChipPos[4] = Point(VisibleRect::right().x -_votherSeats[0]->getSeatSize().width/2 - posPlus, VisibleRect::right().y +  - vSize.height/3);
			_throwChipPos[5] = Point(VisibleRect::right().x -_votherSeats[0]->getSeatSize().width/2 - posPlus, VisibleRect::left().y);
			_throwChipPos[6] = Point(VisibleRect::right().x -_votherSeats[0]->getSeatSize().width/2 - posPlus, VisibleRect::left().y -  - vSize.height/3);
		}
	}

	void Table::initMySelf()
	{
		auto vSize = Director::getInstance()->getVisibleSize();
		VBaseSeat* _pMs =  VBaseSeat::create();
		setpMySeat(_pMs);
		this->addChild(getpMySeat());
		getpMySeat()->setPosition(Point(VisibleRect::bottom().x, VisibleRect::left().y - vSize.height/3));

		VPlayer *pmy = VPlayer::create();
		setpMy(pmy);
		this->addChild(getpMy());
		getpMy()->setPosition(Point(VisibleRect::bottom().x, VisibleRect::left().y - vSize.height/3));
	}

	bool Table::init()
	{
		if (!Layer::init())
		{
			return false;
		}

		initOtherSeats(OTHER);
		initOtherPlayers(OTHER);
		initOtherPos(OTHER);
		initCardBacks(OTHER);

		initBossPos();
		initCardsPos();
		initCommonCardPos();
		initThrowChipsPos();
		initTimeBarPos();

		initMySelf();

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = CC_CALLBACK_2(Table::onTouchBegan, this);
		listener->onTouchEnded = CC_CALLBACK_2(Table::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		auto vOrigin = Director::getInstance()->getVisibleOrigin();
		auto vSize = Director::getInstance()->getVisibleSize();
		Point pCenter = Point(vOrigin.x + vSize.width/2, vOrigin.y + vSize.height/2);
	
		Sprite* bg = Sprite::create(spTableBackGroud);
		setbackGroud(bg);
		getbackGroud()->setPosition(pCenter.x, pCenter.y);
		
		auto s = Sprite::create(spStest);
		s->setAnchorPoint(Point(0.5, 0.5));
		s->setPosition(VisibleRect::center().x, VisibleRect::center().y);
		this->addChild(getbackGroud(), -1);
		this->addChild(s);

		Label *bcl = Label::create("", "LubalinGraphStd-Medium", 28);
		setbaseChipLabel(bcl);
		this->addChild(getbaseChipLabel());
		getbaseChipLabel()->setPosition(VisibleRect::top().x - 30, VisibleRect::top().y - 30);
		getbaseChipLabel()->setString("BASECHIP:");

		Label *acl = Label::create("", "LubalinGraphStd-Medium", 28);
		setallChipLabel(acl);
		this->addChild(getallChipLabel());
		getallChipLabel()->setPosition(VisibleRect::top().x - 25, VisibleRect::top().y - 60);
		getallChipLabel()->setString("ALLCHIP:");

		Sprite* bSp = Sprite::create(spBoss);
		setbossSprite(bSp);
		this->addChild(getbossSprite());
		getbossSprite()->setPosition(_bossPos[0]);
		getbossSprite()->setVisible(false);

		Button *fbtn = Button::create(spFold);
		setfoldButton(fbtn);
		getfoldButton()->setPosition(Point(VisibleRect::bottom().x - 160 , VisibleRect::bottom().y + vSize.height/3));
		this->addChild(getfoldButton());
		getfoldButton()->addTouchEventListener(CC_CALLBACK_2(Table::onTouchFoldEnd, this));
		getfoldButton()->setVisible(false);

		Button *callbtn = Button::create(spCall);
		setcallButton(callbtn);
		getcallButton()->setPosition(Point(VisibleRect::bottom().x , VisibleRect::bottom().y + vSize.height/3));
		this->addChild(getcallButton());
		getcallButton()->addTouchEventListener(CC_CALLBACK_2(Table::onTouchCallEnd, this));
		getcallButton()->setVisible(false);

		Button *cbtn = Button::create(spCheck);
		setcheckButton(cbtn);
		getcheckButton()->setPosition(Point(VisibleRect::bottom().x - 160 , VisibleRect::bottom().y + vSize.height/3));
		this->addChild(getcheckButton());
		getcheckButton()->addTouchEventListener(CC_CALLBACK_2(Table::onTouchCheckEnd,this));
		getcheckButton()->setVisible(false);

		Button *betbtn = Button::create(spRaise);
		setbetButton(betbtn);
		getbetButton()->setPosition(Point(VisibleRect::bottom().x + 160, VisibleRect::bottom().y + vSize.height/3));
		this->addChild(getbetButton());
		getbetButton()->addTouchEventListener(CC_CALLBACK_2(Table::onTouchBetEnd,this));
		getbetButton()->setVisible(false);


		SpriteFrameCache *cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile(s_pPlistDDZcards);


		this->scheduleUpdate();
		//auto listener  = EventListenerTouchOneByOne::create();
		//listener->setSwallowTouches(true);
		//listener->onTouchBegan = CC_CALLBACK_2(Table::onTouchBegan, this);
		//listener->onTouchEnded = CC_CALLBACK_2(Table::onTouchEnded, this);

		//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		return true;
	}

	void Table::reInit()
	{
		char bchipstr[30];
		sprintf(bchipstr, "BASECHIP: %d", mBaseChip);
		std::string bchipStr(bchipstr);
		getbaseChipLabel()->setString(bchipStr);
		getallChipLabel()->setString("ALLCHIP: 0");
	}

	void Table::newRound()
	{
		reInit();
		mBaseChip = 0;
		mBankerPos = 0;
		mBigBlindPos = 0;
		mSmallBlindPos = 0;
		mGameFlag = 0;
		mCallChips = 0;
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

	void Table::onTouchCheckEnd(Ref* sender, Button::TouchEventType event)
	{
		onMyOperate(CHECK, 0);
	}

	void Table::onTouchBetEnd(Ref* sender, Button::TouchEventType event)
	{
		onMyOperate(ADDCHIPS, 200);
		getpMy()->putChips(200);
		this->addChild(getpMy()->getthrowchips());
		getpMy()->getthrowchips()->setPosition(_throwChipPos[0]);
	}

	void Table::onTouchFoldEnd(Ref* sender, Button::TouchEventType event)
	{
		onMyOperate(GIVEUP, 0);
	}

	void Table::onTouchCallEnd(Ref* sender, Button::TouchEventType event)
	{
		onMyOperate(CALL, 100);
		getpMy()->putChips(100);
		this->addChild(getpMy()->getthrowchips());
		getpMy()->getthrowchips()->setPosition(_throwChipPos[0]);
	}

	void Table::onCommonCards(UInt8 stage, const std::vector<CCard> &cards)
	{
	    if (stage == 1)
		{
			if (cards.size() != 3)
				return;
			else
			{
				if(!_commonCards.empty())
					clearCommonCards();

				int i = 0;
				for (auto it = cards.begin(); it != cards.end(); ++it)
				{
					CCardSprite *cs = CCardSprite::create(it->m_nValue, it->m_nColor);
					_commonCards.push_back(cs);
					this->addChild(cs);
					cs->setPosition(_commonCardPos[i]);
					++i;
				}
			}
		}
		else if (stage == 2 || stage == 3 )
		{
			if (cards.size() != 1)
				return;
			CCardSprite *cs = CCardSprite::create(cards[0].m_nValue, cards[0].m_nColor);
			_commonCards.push_back(cs);
			this->addChild(cs);
			cs->setPosition(_commonCardPos[stage+1]);
		}
	}

	void Table::askMyOperate(UInt8 opcode, UInt32 chips)
	{
		showOperateButton(opcode, true);
	}

	void Table::onMyOperate(UInt8 opcode, UInt32 chips)
	{
		Packet::PlayerOperate po;
		po.SetOpcode(opcode);
		if (chips > 0)
		{
			po.SetChips(chips);
		}
		po.send();
	}

	void Table::onPlayerOperateAck(UInt8 opcode, UInt32 chips)
	{

	}

	void Table::onPokerStart(UInt32 mChip, UInt8 bBlindPos, UInt8 sBlindPos)
	{
		mGameFlag = GAMEBEGIN;
		mBaseChip = mChip;
		mBigBlindPos = bBlindPos;
		mSmallBlindPos = sBlindPos;
		reInit();
	}

	void Table::dealingCard()
	{
		float posPlus = 50;
		auto vSize = Director::getInstance()->getVisibleSize();
		MoveTo *move0 = MoveTo::create(DEALINGTIME, ccp(_votherSeats[0]->getSeatSize().width/2 + posPlus, VisibleRect::left().y - vSize.height/3));
		MoveTo *move1 = MoveTo::create(DEALINGTIME, ccp(_votherSeats[0]->getSeatSize().width/2 + posPlus, VisibleRect::left().y));
		MoveTo *move2 = MoveTo::create(DEALINGTIME, ccp(_votherSeats[0]->getSeatSize().width/2 + posPlus, VisibleRect::left().y + vSize.height/3));
		MoveTo *move3 = MoveTo::create(DEALINGTIME, ccp(VisibleRect::right().x -_votherSeats[0]->getSeatSize().width/2 - posPlus, VisibleRect::right().y +  - vSize.height/3));
		MoveTo *move4 = MoveTo::create(DEALINGTIME, ccp(VisibleRect::right().x -_votherSeats[0]->getSeatSize().width/2 - posPlus, VisibleRect::left().y));
		MoveTo *move5 = MoveTo::create(DEALINGTIME, ccp(VisibleRect::right().x -_votherSeats[0]->getSeatSize().width/2 - posPlus, VisibleRect::left().y -  - vSize.height/3));
		_cardBacks[0]->runAction(move0);
		_cardBacks[1]->runAction(move1);
		_cardBacks[2]->runAction(move2);
		_cardBacks[3]->runAction(move3);
		_cardBacks[4]->runAction(move4);
		_cardBacks[5]->runAction(move5);
	}

	void Table::renderCardByPos(UInt8 pos, const std::vector<CCard> &cards)
	{
		if (pos >= MAXPLAYER)
		{
			return;
		}
		if (pos == 0)
		{
			if (getpMy() != NULL)
			{
				getpMy()->renDerCards(cards);
				this->addChild(getpMy()->get_handCards0());
				getpMy()->get_handCards0()->setPosition(_cardsPos[0]);
				this->addChild(getpMy()->get_handCards1());
				getpMy()->get_handCards1()->setPosition(_cardsPos[1]);
			}
		}
		else
		{
			if (_votherPlayers[pos-1] != NULL)
			{
				_votherPlayers[pos-1]->renDerCards(cards);
				this->addChild(_votherPlayers[pos-1]->get_handCards0());
				_votherPlayers[pos-1]->get_handCards0()->setPosition(_cardsPos[pos*2]);
				this->addChild(_votherPlayers[pos-1]->get_handCards1());
				_votherPlayers[pos-1]->get_handCards1()->setPosition(_cardsPos[pos*2+1]);
			}
		}
	}

	void Table::initCardBacks(UInt8 others)
	{
		auto vSize = Director::getInstance()->getVisibleSize();
		_cardBacks.resize(others);
		for (size_t i = 0; i < 3; ++i)
		{
			Sprite *sb0 = Sprite::create(spCardBacks[i]);
			Sprite *sb1 = Sprite::create(spCardBacks[i]);
			this->addChild(sb0);
			sb1->setScaleX(-1);
			this->addChild(sb1);
			sb0->setPosition(Point(vSize.width/2-sb0->getContentSize().width/2, sb0->getContentSize().height));
			sb1->setPosition(Point(vSize.width/2-sb1->getContentSize().width/2, sb1->getContentSize().height));
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

	void Table::initAni()
	{

	}

	void Table::initUI()
	{

	}

	void Table::update(float fDelta)
	{
		printf("update!!%d", fDelta);
	}

	void Table::addPlayer()
	{

	}

	void Table::getPlayer()
	{

	}

	void Table::setLeftTime(int nChair, int nPeriod)
	{

	}

	void Table::playSound(int mSound)
	{

	}

	void Table::clearAllButton()
	{

	}

	int Table::S2CPos(char cChair)
	{
		if (onwerCharid == cChair)
		{
			return 0;
		}
		return (cChair + MAXPLAYER - onwerCharid) % MAXPLAYER;
	}

	int Table::C2SPos(char cChair)
	{
		if (cChair == 0)
		{
			return onwerCharid;
		}
		return (onwerCharid + cChair) % MAXPLAYER;
	}

	void Table::initPos()
	{

	}

	void Table::onOhterPlayerEnter(const PlayerInfo &pi)
	{
		UInt8 chairid = 0;
		chairid = S2CPos(pi.chairid);
		_votherPlayers[chairid-1]->setNickName(pi.nickname);

		char chipStr[30];
		sprintf(chipStr, "%d", pi.allchips);
		_votherPlayers[chairid-1]->setChips(chipStr);
	}

	void Table::onOtherPlayerLeave(UInt8 chairid)
	{
		UInt8 clichairid = 0;
		clichairid = S2CPos(clichairid);
		_votherPlayers[clichairid]->setNickName("");
		_votherPlayers[clichairid]->setChips("");
	}

	void Table::onPlayerEnter(const std::vector<PlayerInfo> &pInfos)
	{
		for (size_t i = 0; i < pInfos.size(); ++i)
		{
			if (i == 0) // mine chairid of server
			{ 
				onwerCharid = pInfos[0].chairid;
				getpMy()->setNickName(pInfos[0].nickname);
				char chipStr[30];
				sprintf(chipStr, "%d", pInfos[i].allchips);
				getpMy()->setChips(chipStr);
			}
			else
			{
				UInt8 pos = S2CPos(pInfos[i].chairid);
				if (pos < MAXPLAYER)
				{
					_votherPlayers[pos-1]->setNickName(pInfos[i].nickname);

					char chipStr[30];
					sprintf(chipStr, "%d", pInfos[i].allchips);
					_votherPlayers[pos-1]->setChips(chipStr);
				}
			}
		}
	}

	void Table::clearCommonCards()
	{
		for(int i = 0; i < _commonCards.size(); ++i)
		{
			_commonCards[i]->clearCard();
		}
		_commonCards.clear();
	}

	void Table::showOperateButton(UInt32 opcode, bool bshow)
	{
		if ((opcode & GIVEUP) > 0)
		{
			getfoldButton()->setVisible(bshow);
		}

		if ((opcode & CALL) > 0)
		{
			getcallButton()->setVisible(bshow);
		}

		if ((opcode & CHECK) > 0)
		{
			getcheckButton()->setVisible(bshow);
		}

		if ((opcode & ADDCHIPS) > 0)
		{
			getbetButton()->setVisible(bshow);
		}
	}

	void Table::startTimer(UInt16 seconds, UInt8 pos)
	{
		if (gettimebar() == NULL)
		{
			auto tb = TimerBar::create();
			settimebar(tb);
			gettimebar()->startTimer(seconds, 0);
			if (true)
			{
				gettimebar()->setVisible(true);
				gettimebar()->setPosition(_timeBarPos[0]);
				this->addChild(gettimebar());
			}
		}
		else
		{
			gettimebar()->startTimer(seconds, 0);
			if (true)
			{
				gettimebar()->setVisible(true);
				gettimebar()->setPosition(_timeBarPos[0]);
			}
		}
	}

	void Table::onTimer(UInt8 time, UInt8 pos)
	{
		if (gettimebar() != NULL)
		{
			gettimebar()->setVisible(false);
		}
	}


}