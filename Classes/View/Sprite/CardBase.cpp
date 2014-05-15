#include "Config.h"
#include "CardBase.h"
#include "../GameResources.h"

CardBase::CardBase(UInt8 cValue, UInt8 color):CCNode(), cardValue(cValue), cardColor(color)
{
	drawCard();
}
CardBase::~CardBase()
{
	clearCard();
}
void CardBase::drawCard()
{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(s_pPlistDDZMainGame0);
	backGround = CCSprite::createWithSpriteFrameName(s_pNameCardBackGround);
	this->addChild(backGround);
	//backGround->autorelease();

	//cache->addSpriteFramesWithFile("Images/animation/chooserole/mt/chooserole_mt_part1.plist");
	//backGround=CCSprite::createWithSpriteFrameName("mt_0001.png");
	//this->addChild(backGround);	

	shadow = CCSprite::createWithSpriteFrameName(s_pNameCardShadow);

}

void CardBase::clearCard()
{
	this->removeChild(backGround, true);
}

void CardBase::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
	CCNode::onEnter();
}

void CardBase::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);  
	CCNode::onExit();  
}


bool CardBase::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	glLineWidth(16);
	ccDrawColor4B(255,0,0,255);
	CCPoint vertices[] = { ccp(0, 0), ccp(50, 50), ccp(100, 50), ccp(100, 100) };
	ccDrawPoly(vertices, 4, true);

	//glLineWidth(16);
	//ccDrawColor4B(0, 255, 0, 255);
	//ccDrawCircle( VisibleRect::center(), 100, 0, 10, false);
	CCSize s = this->backGround->getContentSize();

	CCDrawNode *draw = CCDrawNode::create();
	addChild(draw, 10);

	// Draw polygons
	CCPoint points[] = { CCPoint(s.height/4,0), CCPoint(s.width,s.height/5), CCPoint(s.width/3*2,s.height) };
	draw->drawPolygon(points, sizeof(points)/sizeof(points[0]), ccc4f(1,0,0,0.5), 0, ccc4f(0,0,0,0));

	// Draw segment
	//draw->drawSegment(ccp(20,s.height), ccp(20,s.height/2), 10, ccc4f(0, 1, 0, 0.5));

	//draw->drawSegment(ccp(10,s.height/2), ccp(s.width/2, s.height/2), 40, ccc4f(1, 0, 1, 0.5));

//	this->addChild(shadow);
//	addChild(shadow);

	CCLog("ccTouchBegan");
	return true;
}
void CardBase::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLog("ccTouchMoved");
}
void CardBase::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	ccColor3B b;
	b.r = 255;
	b.g = 255;
	b.b = 255;
	backGround->setColor(b);
	CCLog("ccTouchEnded");
	removeChild(shadow,false);
}