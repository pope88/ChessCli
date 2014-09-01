#ifndef _TABLE_H_
#define _TABLE_H_
#include "cocos2d.h"
#include "View/Table/VOtherPlayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
namespace View
{
	static const std::string spTableBackGroud = "flump/table_backgroud/table0.jpg";
	static const std::string spStest = "CloseNormal.png";
	static const std::string spCardBacks[3] = { "flump/table/cardback0.png", "flump/table/cardback1.png", "flump/table/cardback2.png" };

    static const UInt8 OTHER = 6;
	static const float DEALINGTIME = 0.5;
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
		void reInit();
		void initOtherPos(UInt8 others);
		void initOtherSeats(UInt8 others);
		void initOtherPlayers(UInt8 ohters);
		bool onTouchBegan(Touch *touch, Event *unused_event);
		void onTouchEnded(Touch *touch, Event *unused_event);
		void onPokerStart(UInt32 mBaseChip, UInt8 bBlindPos, UInt8 sBlindPos);
		void onPokerEnd();
		void dealingCard();
		void initCardBacks(UInt8 others);
		void initCardBacksPos();
		void initAni();
		void initUI();
		void initPos();
		void update(float fDelta);
		void addPlayer();
		void getPlayer();
		void setLeftTime(int nChair, int nPeriod);
		void playSound(int mSound);
		void clearAllButton();
		inline int S2CPos(char cChair);
		inline int C2SPos(char cChiar);
	private:
		Sprite *_backGroud;
		std::vector<VBasePlayer*> _votherSeats;
		std::vector<VOtherPlayer*> _votherPlayers;
		std::vector<Point> _votherPoints;
		std::vector<Sprite*> _cardBacks;
		std::vector<Point> _initCardBackPos;
		std::vector<Point> _endCardBackPos;
	private:
		Button *_checkButton;
		Button *_foldButton;
	private:
		UInt32 mBaseChip;
		UInt8 mBigBlindPos;
		UInt8 mSmallBlindPos;
		UInt8 mGameFlag;
	};
}
#endif // !_TABLE_H_