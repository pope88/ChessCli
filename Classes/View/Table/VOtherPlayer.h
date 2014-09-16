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
		void reInit();
		const Size& getSeatSize();
		bool onTouchBegan(Touch *touch, Event *event);
		void onTouchEnded(Touch *touch, Event *event);
		bool touchHits(Touch  *touch);
		inline UInt8 getPos() { return _pos; }
		inline void setPos(UInt8 c) { _pos = c; }
		void setNickName(std::string nickname);
 	protected:
		Sprite *baseFloor;
		LabelTTF *nameLabel;
		UInt8 _pos;
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
