#include "Config.h"
#include "VOtherPlayer.h"

namespace View
{
	VBaseSeat::VBaseSeat():_pos(0)
	{
		baseFloor = Sprite::create(spathSitOpen);
		this->addChild(baseFloor);
	}

	VBaseSeat::~VBaseSeat()
	{
	}

	const Size& VBaseSeat::getSeatSize()
	{
		return baseFloor->getContentSize();
	}

	VBasePlayer::VBasePlayer(): _pos(0)
	{
		LS_P_INIT(_handCards0);
		LS_P_INIT(_handCards1);
		LS_P_INIT(baseFloor);
		LS_P_INIT(nameLabel);
		LS_P_INIT(chipLabel);
	}

	VBasePlayer::~VBasePlayer()
	{
		LS_P_RELEASE(_handCards0);
		LS_P_RELEASE(_handCards1);
		LS_P_RELEASE(baseFloor);
		LS_P_RELEASE(nameLabel);
		LS_P_RELEASE(chipLabel);
	}

	bool VBasePlayer::init()
	{
		if (!Node::init())
		{
			return false;
		}
		Sprite *bf = Sprite::create(spathSitOpen);
		setbaseFloor(bf);
		this->addChild(getbaseFloor());

		Label *nl = Label::create("", "LubalinGraphStd-Medium", 28);
		setnameLabel(nl);
		this->addChild(nl);
		getnameLabel()->setPosition(Point(0, getbaseFloor()->getContentSize().height/2 + getnameLabel()->getDimensions().height + 10));
		getnameLabel()->setColor(Color3B(255,215,0));

		Label *cl = Label::create("", "LubalinGraphStd-Medium", 28);
		setchipLabel(cl);
		this->addChild(getchipLabel());
		getchipLabel()->setPosition(Point(0, -getbaseFloor()->getContentSize().height/2 - getchipLabel()->getDimensions().height - 10));
		getchipLabel()->setColor(Color3B(255,215,0));

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = CC_CALLBACK_2(VBasePlayer::onTouchBegan, this);
		listener->onTouchEnded = CC_CALLBACK_2(VBasePlayer::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		return true;
	}

	void VBasePlayer::reInit()
	{

	}

	const Size& VBasePlayer::getSeatSize()
	{
		return getbaseFloor()->getContentSize();
	}

	bool VBasePlayer::onTouchBegan(Touch *touch, Event *event)
	{
		CC_UNUSED_PARAM(event);
		const bool hits = touchHits(touch);
		if(hits)
			this->getbaseFloor()->setOpacity(GLubyte(255 * (1 - 0.5)));
		return true;
	}

	void VBasePlayer::onTouchEnded(Touch *touch, Event *event)
	{
		CC_UNUSED_PARAM(event);
		const bool hits = touchHits(touch);
		if(hits)
			this->getbaseFloor()->setOpacity(GLubyte(255 * (1 - 0)));
	}

	bool VBasePlayer::touchHits(Touch  *touch)
	{
		const Rect area(0, 0, getbaseFloor()->getContentSize().width, getbaseFloor()->getContentSize().height);
		return area.containsPoint(getbaseFloor()->convertToNodeSpace(touch->getLocation()));
	}

	void VBasePlayer::setNickName(std::string nickname)
	{
		if (getnameLabel() != NULL)
		{
			getnameLabel()->setString(nickname);
		}
	}

	void VBasePlayer::setChips(std::string chips)
	{
		if (getchipLabel() != NULL)
		{
			getchipLabel()->setString(chips);
		}
	}

	void VBasePlayer::clearCards()
	{
		if (get_handCards0() != NULL)
		{
			get_handCards0()->clearCard();
		}

		if (get_handCards1() != NULL)
		{
			get_handCards0()->clearCard();
		}
	}
	
	void VBasePlayer::renDerCards(const std::vector<CCard> &hcVec)
	{
		if (hcVec.size() != 2)
		{
			return;
		}
		clearCards();
		CCardSprite *hc0 = CCardSprite::create(hcVec[0].m_nValue, hcVec[0].m_nColor);
		set_handCards0(hc0);

		CCardSprite *hc1 = CCardSprite::create(hcVec[1].m_nValue, hcVec[1].m_nColor);
		set_handCards1(hc1);
	}


}