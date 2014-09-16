#include "Config.h"
#include "VOtherPlayer.h"

namespace View
{

	VBasePlayer::VBasePlayer():_pos(0)
	{
		baseFloor = Sprite::create(spathSitOpen);
		this->addChild(baseFloor);

		nameLabel = LabelTTF::create("", "LubalinGraphStd-Medium", 28);
		this->addChild(nameLabel);

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


	VOtherPlayer::VOtherPlayer()
	{
		defaultFloor = Sprite::create(spathSitIn);
		this->addChild(defaultFloor);
	}
}