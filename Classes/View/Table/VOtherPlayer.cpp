#include "Config.h"
#include "VOtherPlayer.h"

namespace View
{
	VBasePlayer::VBasePlayer()
	{
		baseFloor = Sprite::create(spathSitOpen);
		this->addChild(baseFloor);
	}


	VOtherPlayer::VOtherPlayer()
	{

	}
}