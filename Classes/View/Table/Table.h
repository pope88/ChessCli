#ifndef _TABLE_H_
#define _TABLE_H_
#include "cocos2d.h"
#include "View/Table/VOtherPlayer.h"
#include "ui/CocosGUI.h"
#include "../../Packet/Builder.h"
#include "../PreConfig.h"

USING_NS_CC;
using namespace ui;
namespace View
{
	static const std::string spTableBackGroud = "flump/table_backgroud/table0.jpg";
	static const std::string spStest = "CloseNormal.png";
	static const std::string spCardBacks[3] = { "flump/table/cardback0.png", "flump/table/cardback1.png", "flump/table/cardback2.png" };
	static const std::string spBoss = "flump/table/boss.png";

	static const std::string spCheck = "flump/table/btn/check_btn.png";
	static const std::string spRaise = "flump/table/btn/raise_btn.png";
	static const std::string spFold = "flump/table/btn/fold_btn.png";
	static const std::string spCall = "flump/table/btn/call_btn.png";

    static const UInt8 OTHER = 6;
	static const float DEALINGTIME = 0.5;
	static const UInt8 MAXPLAYER = 7;

	enum GameFlag
	{
		GAMEBEGIN = 1,
		GAMEING = 2,
		GAMEEND = 3,
	};

	enum DZPKOP
	{
		GIVEUP =     (1 << 0),
		CALL =       (1 << 1),
		CHECK =      (1 << 2),
		ADDCHIPS =   (1 << 3),
		SMALLBLIND = (1 << 4),
		BIGBLIND =   (1 << 5),
	};

	struct PlayerInfo
	{
		UInt8 chairid;
		std::string nickname;
		UInt32 allchips;
	};

	struct BaseTableInfo
	{
		UInt32 allchips;
		UInt8 bigblind;
		UInt8 smallblind;
	};

	class Table : public Layer
	{
	public:
		Table();
		~Table();
		//CREATE_FUNC(Table);
		static Scene* creatScene();
		virtual void onEnter();
		bool init();
		void reInit();
		void newRound();
		void initOtherPos(UInt8 others = OTHER);
		void initBossPos();
		void initCardsPos();
		void initCommonCardPos();
		inline Point& getBossPos(UInt8 pos) { if(pos < MAXPLAYER) return _bossPos[pos]; }
		void initOtherSeats(UInt8 others);
		void initOtherPlayers(UInt8 ohters);
		void initMySelf();
		bool onTouchBegan(Touch *touch, Event *unused_event);
		void onTouchEnded(Touch *touch, Event *unused_event);
		void onTouchCheckEnd(Ref* sender, Button::TouchEventType event);
		void onTouchBetEnd(Ref* sender, Button::TouchEventType event);
		void onTouchFoldEnd(Ref* sender, Button::TouchEventType event);
		void onTouchCallEnd(Ref* sender, Button::TouchEventType event);
		void onCommonCards(UInt8 stage, const std::vector<CCard> &cards);
		void askMyOperate(UInt8 opcode, UInt32 chips);
		void onMyOperate(UInt8 opcode, UInt32 chips);
		void onPlayerOperateAck(UInt8 opcode, UInt32 chips);

		void onPokerStart(UInt32 mBaseChip, UInt8 bBlindPos, UInt8 sBlindPos);
		void onPokerEnd();
		void dealingCard();
		void renderCardByPos(UInt8 pos, const std::vector<CCard> &cards);
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
		int S2CPos(char cChair);
		int C2SPos(char cChiar);
		void onOhterPlayerEnter(const PlayerInfo &pi);
		void onOtherPlayerLeave(UInt8 charid);
		void onPlayerEnter(const std::vector<PlayerInfo> &pInfos);
		void clearCommonCards();
		void showOperateButton(bool bshow);
		inline UInt8 getOnwerChairId() { return  onwerCharid; }
		inline void setOnwerChairId(UInt8 c) { onwerCharid = c; }
		//inline VBasePlayer* getPMy() { return _pMy; }
	private:

		LS_PROPERTY_RETAIN(Sprite*, backGroud, backGroud);
		LS_PROPERTY_RETAIN(Sprite*, bossSprite, bossSprite);
		LS_PROPERTY_RETAIN(VPlayer*, pMy, pMy);
	    LS_PROPERTY_RETAIN(VBaseSeat*, pMySeat, pMySeat);
		LS_PROPERTY_RETAIN(Label*, baseChipLabel, baseChipLabel);
		LS_PROPERTY_RETAIN(Label*, allChipLabel, allChipLabel);
		
		LS_PROPERTY_RETAIN(Button*, foldButton, foldButton);
		LS_PROPERTY_RETAIN(Button*, callButton, callButton);

		LS_PROPERTY_RETAIN(Button*, checkButton, checkButton);
		LS_PROPERTY_RETAIN(Button*, betButton, betButton);

		std::vector<VBaseSeat*> _votherSeats;
		std::vector<VOtherPlayer*> _votherPlayers;
		std::vector<Point> _votherPoints;
		std::vector<Sprite*> _cardBacks;
		std::vector<Point> _initCardBackPos;
		std::vector<Point> _endCardBackPos;
		std::vector<Point> _cardsPos;
		std::vector<Point> _bossPos;
		std::vector<CCardSprite*> _commonCards;
		std::vector<Point> _commonCardPos;
	private:
		UInt32 mBaseChip;
		UInt8 mBankerPos;
		UInt8 mBigBlindPos;
		UInt8 mSmallBlindPos;
		UInt8 mGameFlag;
		UInt8 onwerCharid; //chair server id
	private:
		UInt32 mCallChips;
	};
	extern Table _table;
}
#endif // !_TABLE_H_
