#ifndef _VOTHERPLAYER_H_
#define _VOTHERPLAYER_H_
#include "cocos2d.h"
USING_NS_CC;
namespace View
{

    static const std::string spathSitOpen = "flump/table_player/sit_open.png";
	class VBasePlayer : public Node
	{
	public:
		CREATE_FUNC(VBasePlayer);
		VBasePlayer();
		const Size& getSeatSize();
		bool onTouchBegan(Touch *touch, Event *event);
		void onTouchEnded(Touch *touch, Event *event);
		bool touchHits(Touch  *touch);

	protected:
		Sprite *baseFloor;
	};

	static const std::string spathSitIn = "flump/table_player/sit_in.png";
	class VOtherPlayer : public VBasePlayer
	{
	public:
		CREATE_FUNC(VOtherPlayer);
		VOtherPlayer();
	private:
		Sprite *defaultFloor;
	};
}
#endif // !_VOTHERPLAYER_H_
