#ifndef _VOTHERPLAYER_H_
#define _VOTHERPLAYER_H_
#include "cocos2d.h"
#include "../Sprite/CardBase.h"
#include "../../Common/CCard.h"
#include "../Sprite/CCardSprite.h"
#include "../PreConfig.h"
USING_NS_CC;
namespace View
{

	static const std::string spathSitOpen = "flump/table_player/sit_open.png";
	class VBaseSeat : public Node
	{
	public:
		CREATE_FUNC(VBaseSeat);
		VBaseSeat();
		~VBaseSeat();
		const Size& getSeatSize();
		//bool onTouchBegan(Touch *touch, Event *event);
		//void onTouchEnded(Touch *touch, Event *event);
		//bool touchHits(Touch  *touch);
		inline UInt8 getPos() { return _pos; }
		inline void setPos(UInt8 c) { _pos = c; }
	protected:
		Sprite *baseFloor;
		UInt8 _pos;
	};

   // static const std::string spathSitOpen = "flump/table_player/sit_open.png";
	class VBasePlayer : public Node
	{
	public:
		CREATE_FUNC(VBasePlayer);
		VBasePlayer();
		virtual ~VBasePlayer();
		bool init();
		void reInit();
		const Size& getSeatSize();
		bool onTouchBegan(Touch *touch, Event *event);
		void onTouchEnded(Touch *touch, Event *event);
		bool touchHits(Touch  *touch);
		inline UInt8 getPos() { return _pos; }
		inline void setPos(UInt8 c) { _pos = c; }
		void setNickName(std::string nickname);
		void setChips(std::string chips);
		virtual void clearCards();
		void renDerCards(const std::vector<CCard> &hcVec);
 	protected:
		LS_PROPERTY_RETAIN(CCardSprite*, _handCards0, _handCards0);
		LS_PROPERTY_RETAIN(CCardSprite*, _handCards1, _handCards1);
		LS_PROPERTY_RETAIN(Sprite*, baseFloor, baseFloor);
		LS_PROPERTY_RETAIN(Label*, nameLabel, nameLabel);
		LS_PROPERTY_RETAIN(Label*, chipLabel, chipLabel);
		UInt8 _pos;
	};

	//static const std::string spathSitIn = "flump/table_player/sit_in.png";
	class VOtherPlayer : public VBasePlayer
	{
	public:
		CREATE_FUNC(VOtherPlayer);
	};

	static const std::string spathSitIn = "flump/table_player/sit_in.png";
	class VPlayer : public VBasePlayer
	{
	public:
		CREATE_FUNC(VPlayer);
	};
}
#endif // !_VOTHERPLAYER_H_
