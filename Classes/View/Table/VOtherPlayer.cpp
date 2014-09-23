#include "Config.h"
#include "VOtherPlayer.h"

namespace View
{
	VBaseSeat::VBaseSeat():_pos(0)
	{
		baseFloor = Sprite::create(spathSitOpen);
		this->addChild(baseFloor);
	}

	const Size& VBaseSeat::getSeatSize()
	{
		return baseFloor->getContentSize();
	}

	VBasePlayer::VBasePlayer(): _pos(0)
	{
		_handCards[0] = NULL;
		_handCards[1] = NULL;

		baseFloor = Sprite::create(spathSitOpen);
		this->addChild(baseFloor);

		nameLabel = Label::create("", "LubalinGraphStd-Medium", 28);
		this->addChild(nameLabel);
		nameLabel->setPosition(Point(0, baseFloor->getContentSize().height/2 + nameLabel->getDimensions().height + 10));
		nameLabel->setColor(Color3B(255,215,0));

		chipLabel = Label::create("", "LubalinGraphStd-Medium", 28);
		this->addChild(chipLabel);
		chipLabel->setPosition(Point(0, -baseFloor->getContentSize().height/2 - chipLabel->getDimensions().height - 10));
		chipLabel->setColor(Color3B(255,215,0));

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = CC_CALLBACK_2(VBasePlayer::onTouchBegan, this);
		listener->onTouchEnded = CC_CALLBACK_2(VBasePlayer::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	}

	void VBasePlayer::reInit()
	{

	}

	const Size& VBasePlayer::getSeatSize()
	{
		return baseFloor->getContentSize();
	}

	bool VBasePlayer::onTouchBegan(Touch *touch, Event *event)
	{
		CC_UNUSED_PARAM(event);
		const bool hits = touchHits(touch);
		if(hits)
			this->baseFloor->setOpacity(GLubyte(255 * (1 - 0.5)));
		return true;
	}

	void VBasePlayer::onTouchEnded(Touch *touch, Event *event)
	{
		CC_UNUSED_PARAM(event);
		const bool hits = touchHits(touch);
		if(hits)
			this->baseFloor->setOpacity(GLubyte(255 * (1 - 0)));
	}

	bool VBasePlayer::touchHits(Touch  *touch)
	{
		const Rect area(0, 0, baseFloor->getContentSize().width, baseFloor->getContentSize().height);
		return area.containsPoint(baseFloor->convertToNodeSpace(touch->getLocation()));
	}

	void VBasePlayer::setNickName(std::string nickname)
	{
		if (nameLabel != NULL)
		{
			nameLabel->setString(nickname);
		}
	}

	void VBasePlayer::setChips(std::string chips)
	{
		if (chipLabel != NULL)
		{
			chipLabel->setString(chips);
		}
	}

	void VBasePlayer::clearCards()
	{
		if (_handCards[0] != NULL)
		{
			_handCards[0]->clearCard();
		}

		if (_handCards[1] != NULL)
		{
			_handCards[1]->clearCard();
		}
	}
	
	void VBasePlayer::renDerCards(const std::vector<CCard> &hcVec)
	{
		//_handCards[0] = new 
	}


}