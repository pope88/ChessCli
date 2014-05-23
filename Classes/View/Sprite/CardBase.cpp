#include "Config.h"
#include "CardBase.h"
#include "../GameResources.h"

CardBase::CardBase(UInt8 cValue, UInt8 color):Node(), cardValue(cValue), cardColor(color)
{
	drawCard();
}
CardBase::~CardBase()
{
	clearCard();
}

void CardBase::drawCard()
{
	backGround = Sprite::createWithSpriteFrameName(s_pNameCardBackGround);
	this->addChild(backGround);
}

void CardBase::clearCard()
{
	this->removeChild(backGround, true);
}

void CardBase::onEnter()
{
	//Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
	//Node::onEnter();
}

void CardBase::onExit()
{
/*	Director::getInstance()->getTouchDispatcher()->removeDelegate(this);  
	Node::onExit(); */ 
}


bool CardBase::ccTouchBegan(Touch* touch, Event* event)
{
	glLineWidth(16);
	ccDrawColor4B(255,0,0,255);
	Point vertices[] = { Point(0, 0), Point(50, 50), Point(100, 50), Point(100, 100) };
	ccDrawPoly(vertices, 4, true);

	//glLineWidth(16);
	//ccDrawColor4B(0, 255, 0, 255);
	//ccDrawCircle( VisibleRect::center(), 100, 0, 10, false);

	Size s = backGround->getContentSize();

	DrawNode *draw = DrawNode::create();
	addChild(draw, 10);

	// Draw polygons
	Point points[] = { Point(s.height/4,0), Point(s.width,s.height/5), Point(s.width/3*2,s.height) };
	draw->drawPolygon(points, sizeof(points)/sizeof(points[0]), Color4F(1,0,0,0.5), 0, Color4F(0,0,0,0));

	// Draw segment
	//draw->drawSegment(ccp(20,s.height), ccp(20,s.height/2), 10, ccc4f(0, 1, 0, 0.5));

	//draw->drawSegment(ccp(10,s.height/2), ccp(s.width/2, s.height/2), 40, ccc4f(1, 0, 1, 0.5));

//	this->addChild(shadow);
//	addChild(shadow);

	CCLog("ccTouchBegan");
	return true;
}
void CardBase::ccTouchMoved(Touch *pTouch, Event *pEvent)
{
	CCLog("ccTouchMoved");
}
void CardBase::ccTouchEnded(Touch *pTouch, Event *pEvent)
{
	Color3B b;
	b.r = 255;
	b.g = 255;
	b.b = 255;

	backGround->setColor(b);
	CCLog("ccTouchEnded");
}