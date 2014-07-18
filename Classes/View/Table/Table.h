#ifndef _TABLE_H_
#define _TABLE_H_
#include "cocos2d.h"
USING_NS_CC;
#include "View/Table/VOtherPlayer.h"
namespace View
{
	static const std::string spTableBackGroud = "flump/table_backgroud/table0.jpg";
	static const std::string spStest = "CloseNormal.png";
    static const UInt8 OTHER = 6;

	class Table : public Layer
	{
	public:
		Table();
		CREATE_FUNC(Table);
		static Scene* creatScene();
		virtual void onEnter();
		bool init();
		void initOhterPos(UInt8 others);
		void initOhterPlayers(UInt8 others);
		bool onTouchBegan(Touch *touch, Event *unused_event);
		void onTouchEnded(Touch *touch, Event *unused_event);
	private:
		Sprite *_backGroud;
		std::vector<VBasePlayer*> _votherSeats;
		std::vector<Point> _votherPoints;
	};
}
#endif // !_TABLE_H_
