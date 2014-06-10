#ifndef _TPLAYER_H_
#define _TPLAYER_H_

namespace Game
{
	class Player
	{
	public:
		Player();
		virtual ~Player();
		virtual void updateHandCards() {}
		virtual void updatePutCards() {}
		virtual void init() {}
		virtual void reInit() {}
		virtual void addCard(int nCard, int x, int y);
		virtual void playAni(int nAni);
		virtual void drawPlayerInfo();
	public:
		void setUserData();
		void getUserData();
		void getPlayCards();
		void loadAvatar(int nID);
		void setLeftTime();
		void initHandCards();
		void setHandCards();
		void setPutCards();
		void setPutCardsType();
		void clearPutCards();
		void showTips();
		void addChat();
		void changeSortType();
		void playSound();
		void playPutSound();
		void playShowCardAni();
	protected:

	};

	class LeftTplayer : public Player
	{

	};

	class TopTplayer : public Player
	{

	};

	class RightTplayer : public Player
	{

	};

	class SelfTplayer : public Player
	{
	public:
		SelfTplayer();
		~SelfTplayer();

	};

}

#endif