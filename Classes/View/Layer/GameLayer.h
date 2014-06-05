#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_
#include "cocos2d.h"
#include "../Sprite/CardBase.h"

namespace View
{
	class GameLayer : public Layer
	{
		enum TAG_BG
		{
			TAG_BG_NEAR_LAYER = 0,
			TAG_BG_FAR_LAYER = 1
		};
	public:
	    CREATE_FUNC(GameLayer);
		static Scene* creatScene();
	public :
		void createCards();
		void clearCards();
	public:
		virtual void onEnter();
		bool init();
		bool onTouchBegan(Touch* touch, Event  *event);
		void onTouchEnded(Touch* touch, Event  *event);
		void forTest();
		void onButtonClick1(Ref* pSender);
		void onButtonClick2(Ref* pSender);
		void onButtonClick3(Ref* pSender);
	private:
		Sprite *spBackGround;
		std::vector<CardBase*> cardsList;
	};
}
#endif