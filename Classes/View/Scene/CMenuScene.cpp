#include "Config.h"
#include "CMenuScene.h"
#include "../../Game/GameManager.h"
#include "../GameResources.h"

namespace View
{
	void CMenuScene::InitScene()
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();

		Layer *testLayer = Layer::create();

		//try 九宫格
		//CCRect rect = CCRectMake(0, 0, 320, 480);
		//CCRect rectInsets = CCRectMake(1, 118, 1, 30);
		//Size winRect = CCSizeMake(visibleSize.width, visibleSize.height);
		//CCScale9Sprite *pbgSprite = CCScale9Sprite::create(s_pPathBackGround2, rect, rectInsets);
		//pbgSprite->setContentSize(winRect);
		Sprite  *pbgSprite = Sprite::create(s_pPathBackGround2);

		LabelTTF* label = LabelTTF::create("second scene", "Arial", 20);
		//#endif
		MenuItemLabel* pMenuItem = MenuItemLabel::create(label, this, menu_selector(CMenuScene::OnTextmenu_Click));

		
		CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);

		pbgSprite->setPosition(ccp(origin.x + visibleSize.width/2 , origin.y + visibleSize.height/2));
		pMenu->setPosition(ccp(origin.x + visibleSize.width/2 , origin.y + visibleSize.height/2));

		pbgSprite->setScale(2.0);
		testLayer->addChild(pbgSprite);
		testLayer->addChild(pMenu);
		this->addChild(testLayer);

		testLayer->setTouchEnabled(true);
		
	}


	void CMenuScene::runThisScene()
	{

		InitScene();

		if (!Director::getInstance()->getRunningScene())
		{
			Director::getInstance()->runWithScene(this);
		}
		else
		{
			//Director::getInstance()->replaceScene(CCTransitionSlideInR::create(1.5, this));
			Director::getInstance()->replaceScene(CCTransitionFade::create(1.5, this));
		}
	}

	void CMenuScene::OnTextmenu_Click(Object *pSender)
	{
		printf("nothing");

		_gamemanager::instance()->DisplayNowScene(SCENE_INIT);
	}

	void CMenuScene::ShowOtherScene()
	{
		_gamemanager::instance()->DisplayNowScene(SCENE_LOGIN);
	}
}
