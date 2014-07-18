#include "Config.h"
#include "VOtherPlayer.h"

namespace View
{
	VBasePlayer::VBasePlayer()
	{
		baseFloor = Sprite::create(spathSitOpen);
		this->addChild(baseFloor);
		//auto listener = EventListenerTouchOneByOne::create();
		//listener->setSwallowTouches(true);
		//listener->onTouchBegan = CC_CALLBACK_2(VBasePlayer::onTouchBegan, this);
		//listener->onTouchEnded = CC_CALLBACK_2(VBasePlayer::onTouchEnded, this);
		//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}

	const Size& VBasePlayer::getSeatSize()
	{
		return baseFloor->getContentSize();
	}

	bool VBasePlayer::onTouchBegan(Touch *touch, Event *event)
	{
		this->baseFloor->setOpacity(GLubyte(255 * (1 - 0.5)));
		return true;
	}

	void VBasePlayer::onTouchEnded(Touch *touch, Event *event)
	{
		this->baseFloor->setOpacity(GLubyte(255 * (1 - 0)));
	}

	VOtherPlayer::VOtherPlayer()
	{

	}

}