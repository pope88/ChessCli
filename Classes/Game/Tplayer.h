#ifndef _TPLAYER_H_
#define _TPLAYER_H_
class Tplayer
{
public:
	Tplayer();
	virtual ~Tplayer();
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


class LeftTplayer : public Tplayer
{

};

class TopTplayer : public Tplayer
{

};

class RightTplayer : public Tplayer
{

};

class SelfTplayer : public Tplayer
{
public:
	SelfTplayer();
	~SelfTplayer();

};

#endif