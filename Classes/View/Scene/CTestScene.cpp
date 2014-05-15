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
		//CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		//CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		//CCLayer *testLayer = CCLayer::create();
	
		//CCSprite *pbgSprite = CCSprite::create("Images/BackGround/background_2.jpg");

		//CCLabelTTF* label = CCLabelTTF::create("first scene", "Arial", 20);
		////#endif
		//CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(CTestScene::OnTextmenu_Click));


		// CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);

		// pbgSprite->setPosition(ccp(origin.x + visibleSize.width/2 , origin.y + visibleSize.height/2));
		// pMenu->setPosition(ccp(origin.x + visibleSize.width/2 , origin.y + visibleSize.height/2));

		//testLayer->addChild(pbgSprite);
		//testLayer->addChild(pMenu);
		//testLayer->scheduleOnce(schedule_selector(CTestScene::ShowOtherScene), 10.0f);

		//this->addChild(testLayer);

		////add animation
		//CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
		//cache->addSpriteFramesWithFile("Images/animation/chooserole/mt/chooserole_mt_part1.plist");
		//cache->addSpriteFramesWithFile("Images/animation/chooserole/mt/chooserole_mt_part2.plist");
		////cache->addSpriteFramesWithFile("Images/animation/chooserole/mt/skill_tenarmy.plist");
		//

		//CCSprite *plistSprite=CCSprite::createWithSpriteFrameName("mt_0001.png");
		////CCSprite *plistSprite=CCSprite::createWithSpriteFrameName("tenarmy_01.png");

		//testLayer->addChild(plistSprite);
		//plistSprite->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height/2 + plistSprite->getContentSize().width));

		////为帧创建图片
		//CCArray *walkFrames = CCArray::createWithCapacity(11);
		//for (int i = 1; i <= 11; i++)  
		//{  
		//	CCSpriteFrame *frame;
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
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		CCLayer *testLayer = CCLayer::create();
	
		CCSprite *pbgSprite = CCSprite::create(s_pPathBackGround3);

		CCLabelTTF* label = CCLabelTTF::create("first scene", "Arial", 20);
		//#endif
		CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(CTestScene::OnTextmenu_Click));


		 CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);

		 pbgSprite->setPosition(ccp(origin.x + visibleSize.width/2 , origin.y + visibleSize.height/2));
		 pMenu->setPosition(ccp(origin.x + visibleSize.width/2 , origin.y + visibleSize.height/2));

		testLayer->addChild(pbgSprite);
		testLayer->addChild(pMenu);

		this->addChild(testLayer);


 		CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(s_pPathDDZMainGame0);
		CCSprite *pSprite;
		CCSprite *pSpriteA;
		CCSprite *pSpriteB;
		CCSprite *pSpriteC;
		CCSprite *pSpriteD;
		pSprite = CCSprite::createWithTexture(pTexture, CCRect(3, 130, 123, 160));
		pSpriteA = CCSprite::createWithTexture(pTexture, CCRect(0, 0, 40, 40)); 
		pSpriteB = CCSprite::createWithTexture(pTexture, CCRect(0, 0, 40, 40));
		
		pSpriteC = CCSprite::createWithTexture(pTexture, CCRect(274, 215, 28, 30)); 
		pSpriteD = CCSprite::createWithTexture(pTexture, CCRect(274, 215, 28, 30));

		pSprite->addChild(pSpriteA);
		pSpriteA->setAnchorPoint(CCPoint(0, 0));
		pSpriteA->setPosition(CCPoint(0, 115));

		pSprite->addChild(pSpriteB);
		pSpriteB->setAnchorPoint(CCPoint(0, 0));
		pSpriteB->setPosition(CCPoint(85, 5));
		pSpriteB->setFlipY(true);

		pSprite->addChild(pSpriteC);
		pSpriteC->setAnchorPoint(CCPoint(0, 0));
		pSpriteC->setPosition(CCPoint(5, 85));

		pSprite->addChild(pSpriteD);
		pSpriteD->setAnchorPoint(CCPoint(0, 0));
		pSpriteD->setPosition(CCPoint(90, 47));
		pSpriteD->setFlipY(true);


		testLayer->addChild(pSprite);
		pSprite->setAnchorPoint(CCPoint(0, 0));
		pSprite->setPosition(CCPoint(origin.x + 100, origin.y+100));

		CardBase *pcard = new CardBase(15, 0);
		pcard->drawCard();
		//testLayer->addChild(pcard->getCardBackGround());
		//pcard->getCardBackGround()->setPosition(CCPoint(origin.x + 300, origin.y+100));

		pcard->setPosition(CCPoint(origin.x + 300, origin.y+100));
		testLayer->addChild(pcard);

		CCardSprite carda;
		carda.m_nValue = 3;
		carda.m_nColor = 1;
		carda.getCardSprite()->setAnchorPoint(CCPoint(0, 0));
		carda.getCardSprite()->setPosition(CCPoint(200, 200));
		testLayer->addChild(carda.getCardSprite());

		CCardSprite cardb;
		cardb.m_nValue = 3;
		cardb.m_nColor = 1;
		cardb.getCardSprite()->setAnchorPoint(CCPoint(0, 0));
		cardb.getCardSprite()->setPosition(CCPoint(400, 200));
		testLayer->addChild(cardb.getCardSprite());
	}

	void CTestScene::runThisScene( )
	{
		//show some effect

		InitScene();

		if (!CCDirector::sharedDirector()->getRunningScene())
		{
			CCDirector::sharedDirector()->runWithScene(this);
		}
		else
		{
			CCDirector::sharedDirector()->replaceScene(this);
		}
	}

	void CTestScene::OnTextmenu_Click(CCObject *pSender)
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