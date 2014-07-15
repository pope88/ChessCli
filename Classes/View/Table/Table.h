#ifndef _TABLE_H_
#define _TABLE_H_
#include "cocos2d.h"
USING_NS_CC;
#include "View/Table/VOtherPlayer.h"
namespace View
{
	static const std::string spTableBackGroud = "flump/table_backgroud/table0.jpg";
	class Table : public Layer
	{
	public:
		CREATE_FUNC(Table);
		static Scene* creatScene();
		Table();
		void onEnter();
	private:
		Sprite *_backGroud;
		std::vector<VBasePlayer*> _votherPlayers;

	};
}
#endif // !_TABLE_H_
