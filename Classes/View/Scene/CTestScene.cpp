#include "Config.h"
#include "CTestScene.h"
#include "Utils/CharacterConver.h"
#include "../../Game/GameManager.h"
#include "../GameResources.h"
//#include "../Sprite/CardBase.h"
#include "../Sprite/CCardSprite.h"
namespace View
{
	void CTestScene::InitScene()
	{
		//Size visibleSize = Director::getInstance()->getVisibleSize();
		//Point origin = Director::getInstance()->getVisibleOrigin();

		//Layer *testLayer = Layer::create();
	
		//Sprite *pbgSprite = Sprite::create("Images/BackGround/background_2.jpg");

		//LabelTTF* label = LabelTTF::create("first scene", "Arial", 20);
		////#endif
		//MenuItemLabel* pMenuItem = MenuItemLabel::create(label, this, menu_selector(CTestScene::OnTextmenu_Click));


		// CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);

		// pbgSprite->setPosition(ccp(origin.x + visibleSize.width/2 , origin.y + visibleSize.height/2));
		// pMenu->setPosition(ccp(origin.x + visibleSize.width/2 , origin.y + visibleSize.height/2));

		//testLayer->addChild(pbgSprite);
		//testLayer->addChild(pMenu);
		//testLayer->scheduleOnce(schedule_selector(CTestScene::ShowOtherScene), 10.0f);

		//this->addChild(testLayer);

		////add animation
		//SpriteFrameCache *cache = SpriteFrameCache::sharedSpriteFrameCache();
		//cache->addSpriteFramesWithFile("Images/animation/chooserole/mt/chooserole_mt_part1.plist");
		//cache->addSpriteFramesWithFile("Images/animation/chooserole/mt/chooserole_mt_part2.plist");
		////cache->addSpriteFramesWithFile("Images/animation/chooserole/mt/skill_tenarmy.plist");
		//

		//Sprite *plistSprite=Sprite::createWithSpriteFrameName("mt_0001.png");
		////Sprite *plistSprite=Sprite::createWithSpriteFrameName("tenarmy_01.png");

		//testLayer->addChild(plistSprite);
		//plistSprite->setPosition(ccp(Director::getInstance()->getWinSize().width/2,Director::getInstance()->getWinSize().height/2 + plistSprite->getContentSize().width));

		////为帧创建图片
		//Array *walkFrames = Array::createWithCapacity(11);
		//for (int i = 1; i <= 11; i++)  
		//{  
		//	SpriteFrame *frame;
		//	//if (i == 4 || i == 6 || i == 8)
		//	//{
		//	//	continue;
		//	//}
		//	if (i < 10)
		//	{
		//		frame = cache->spriteFrameByName(CCString::createWithFormat("mt_000%d.png", i)->getCString());   
		//	}
		//	else
		//	{
		//		frame = cache->spriteFrameByName(CCString::createWithFormat("mt_00%d.png", i)->getCString());  
		//	}


		//	walkFrames->addObject(frame);  
		//}  

		//// 创建动画  
		//CCAnimation *walkAnimation = CCAnimation::createWithSpriteFrames(walkFrames, 1.0f / 15.0f);  
		////CC_BREAK_IF(!walkAnimation);  
		//CCAnimate* walkAnimate = CCAnimate::create(walkAnimation);  
		////CC_BREAK_IF(!walkAnimate);  

		//// 运行动画动作  
		//plistSprite->runAction(CCRepeatForever::create(walkAnimate));  

		//testLayer->setTouchEnabled(true);

		//test
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();

		Layer *testLayer = Layer::create();
	
		Sprite *pbgSprite = Sprite::create(s_pPathBackGround3);

		LabelTTF* label = LabelTTF::create("first scene", "Arial", 20);
		//#endif
		MenuItemLabel* pMenuItem = MenuItemLabel::create(label, this, menu_selector(CTestScene::OnTextmenu_Click));


		 CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);

		 pbgSprite->setPosition(ccp(origin.x + visibleSize.width/2 , origin.y + visibleSize.height/2));
		 pMenu->setPosition(ccp(origin.x + visibleSize.width/2 , origin.y + visibleSize.height/2));

		testLayer->addChild(pbgSprite);
		testLayer->addChild(pMenu);

		this->addChild(testLayer);


 		Texture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(s_pPathDDZMainGame0);
		Sprite *pSprite;
		Sprite *pSpriteA;
		Sprite *pSpriteB;
		Sprite *pSpriteC;
		Sprite *pSpriteD;
		pSprite = Sprite::createWithTexture(pTexture, CCRect(3, 130, 123, 160));
		pSpriteA = Sprite::createWithTexture(pTexture, CCRect(0, 0, 40, 40)); 
		pSpriteB = Sprite::createWithTexture(pTexture, CCRect(0, 0, 40, 40));
		
		pSpriteC = Sprite::createWithTexture(pTexture, CCRect(274, 215, 28, 30)); 
		pSpriteD = Sprite::createWithTexture(pTexture, CCRect(274, 215, 28, 30));

		pSprite->addChild(pSpriteA);
		pSpriteA->setAnchorPoint(Point(0, 0));
		pSpriteA->setPosition(Point(0, 115));

		pSprite->addChild(pSpriteB);
		pSpriteB->setAnchorPoint(Point(0, 0));
		pSpriteB->setPosition(Point(85, 5));
		pSpriteB->setFlipY(true);

		pSprite->addChild(pSpriteC);
		pSpriteC->setAnchorPoint(Point(0, 0));
		pSpriteC->setPosition(Point(5, 85));

		pSprite->addChild(pSpriteD);
		pSpriteD->setAnchorPoint(Point(0, 0));
		pSpriteD->setPosition(Point(90, 47));
		pSpriteD->setFlipY(true);


		testLayer->addChild(pSprite);
		pSprite->setAnchorPoint(Point(0, 0));
		pSprite->setPosition(Point(origin.x + 100, origin.y+100));

		CardBase *pcard = new CardBase(15, 0);
		pcard->drawCard();
		//testLayer->addChild(pcard->getCardBackGround());
		//pcard->getCardBackGround()->setPosition(Point(origin.x + 300, origin.y+100));

		pcard->setPosition(Point(origin.x + 300, origin.y+100));
		testLayer->addChild(pcard);

		CCardSprite carda;
		carda.m_nValue = 3;
		carda.m_nColor = 1;
		carda.getCardSprite()->setAnchorPoint(Point(0, 0));
		carda.getCardSprite()->setPosition(Point(200, 200));
		testLayer->addChild(carda.getCardSprite());

		CCardSprite cardb;
		cardb.m_nValue = 3;
		cardb.m_nColor = 1;
		cardb.getCardSprite()->setAnchorPoint(Point(0, 0));
		cardb.getCardSprite()->setPosition(Point(400, 200));
		testLayer->addChild(cardb.getCardSprite());
	}

	void CTestScene::runThisScene( )
	{
		//show some effect

		InitScene();

		if (!Director::getInstance()->getRunningScene())
		{
			Director::getInstance()->runWithScene(this);
		}
		else
		{
			Director::getInstance()->replaceScene(this);
		}
	}

	void CTestScene::OnTextmenu_Click(Ref *pSender)
	{
		printf("nothing");

		_gamemanager::instance()->DisplayNowScene(SCENE_MENU);
	}

	void CTestScene::ShowOtherScene(float t)
	{
	    _gamemanager::instance()->DisplayNowScene(SCENE_MENU);
		printf("do nothing");
	}
}