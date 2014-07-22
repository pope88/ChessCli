#ifndef _TABLE_H_
#define _TABLE_H_
#include "cocos2d.h"
USING_NS_CC;
#include "View/Table/VOtherPlayer.h"
namespace View
{
	static const std::string spTableBackGroud = "flump/table_backgroud/table0.jpg";
	static const std::string spStest = "CloseNormal.png";
	static const std::string spCardBack = "flump/table/CardBack.jpg";

    static const UInt8 OTHER = 6;
	enum GameFlag
	{
		GAMEBEGIN = 1,
		GAMEING = 2,
		GAMEEND = 3,
	};
	class Table : public Layer
	{
	public:
		Table();
		CREATE_FUNC(Table);
		static Scene* creatScene();
		virtual void onEnter();
		bool init();
		void initOtherPos(UInt8 others);
		void initOtherSeats(UInt8 others);
		void initOtherPlayers(UInt8 ohters);
		bool onTouchBegan(Touch *touch, Event *unused_event);
		void onTouchEnded(Touch *touch, Event *unused_event);
		void onPokerStart(UInt32 mBaseChip, UInt8 bBlindPos, UInt8 sBlindPos);
		void dealingCard();
		void initCardBacks();
		void initCardBacksPos();
	private:
		Sprite *_backGroud;
		std::vector<VBasePlayer*> _votherSeats;
		std::vector<VOtherPlayer*> _votherPlayers;
		std::vector<Point> _votherPoints;
		std::vector<Sprite*> _cardBacks;
	private:
		UInt32 mBaseChip;
		UInt8 mBigBlindPos;
		UInt8 mSmallBlindPos;
		UInt8 mGameFlag;
	};
}
#endif // !_TABLE_H_
