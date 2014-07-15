#ifndef _VOTHERPLAYER_H_
#define _VOTHERPLAYER_H_
#include "cocos2d.h"
USING_NS_CC;
namespace View
{
	static const std::string spathSitOpen = "flump/table_player/sit_open.png";
	static const UInt16 otherSitsX[6] = {100, 130, 160, 190, 210, 240};
	static const UInt16 otherSitsY[6] = {100, 130, 160, 190, 210, 240};
	class VBasePlayer : public Node
	{
	public:
		CREATE_FUNC(VBasePlayer);
		VBasePlayer();
	protected:
		Sprite *baseFloor;
	};
	class VOtherPlayer : public VBasePlayer
	{
	public:
		CREATE_FUNC(VOtherPlayer);
		VOtherPlayer();

	};
}
#endif // !_VOTHERPLAYER_H_
