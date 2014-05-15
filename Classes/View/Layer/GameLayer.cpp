#include "Config.h"
#include "GameLayer.h"
namespace View
{
namespace Layer
{
GameLayer::GameLayer()
{
	initBackground();
}

GameLayer::~GameLayer()
{

}

void GameLayer::initBackground()
{
	// Sky  
	m_pSkySprite = CCSprite::create("farm.jpg");  
	m_pSkySpriteRe = CCSprite::create("farm.jpg");  
	m_pSkySprite->setAnchorPoint(CCPointZero);  
	m_pSkySpriteRe->setAnchorPoint(CCPointZero);  
	this->addChild(m_pSkySprite, -10, TAG_BG_NEAR_LAYER);  
	this->addChild(m_pSkySpriteRe, -10, TAG_BG_NEAR_LAYER);  

	// Map  
	m_pTileMap = CCSprite::create("land.png");  
	m_pTileMapRe = CCSprite::create("land.png");  
	m_pTileMap->setAnchorPoint(CCPointZero);  
	m_pTileMapRe->setAnchorPoint(CCPointZero);      
	this->addChild(m_pTileMap, -9, TAG_BG_FAR_LAYER);  
	this->addChild(m_pTileMapRe, -9, TAG_BG_FAR_LAYER);  

	// 设置高度  
	m_fSkyHeight = m_pSkySprite->getContentSize().height;  
	m_fTileMapHeight =m_pTileMap->getContentSize().height;//m_pTileMap->getMapSize().height * m_pTileMap->getTileSize().height;  

	// 设置副本背景位置  
	m_pSkySpriteRe->setPosition(ccp(0, m_fSkyHeight));  
	m_pTileMapRe->setPosition(ccp(0, m_fTileMapHeight));  

	// 设置移动速度  
	m_fSkyVelocity = -16;  
	m_fTileMapVelocity = -60;  
	//    m_fSkyVelocity = -160;  
	//    m_fTileMapVelocity = -600;  
}

void GameLayer::update(float dt)
{
	CCArray *bgSprites = this->getChildren();  
	CCObject *obj = NULL;  

	CCARRAY_FOREACH(bgSprites, obj)  
	{  
		movingBackground(obj, dt);  
	}  
}

void GameLayer::movingBackground(CCObject *pObj, float dt)
{
	CCNode *bgNode = (CCNode*) pObj;  
	int tag = bgNode->getTag();  

	if (tag == TAG_BG_NEAR_LAYER)
	{  
		// 远景层  
		bgNode->setPositionY(bgNode->getPositionY() + m_fSkyVelocity * dt);  
		if (bgNode->getPositionY() < -m_fSkyHeight)
		{  
			bgNode->setPositionY(bgNode->getPositionY() + m_fSkyHeight * 2 - 2);  
		}  
	}  
	else if (tag == TAG_BG_FAR_LAYER)
	{  
		// 近景层  
		bgNode->setPositionY(bgNode->getPositionY() + m_fTileMapVelocity * dt);  
		if (bgNode->getPositionY() < -m_fTileMapHeight)
		{  
			bgNode->setPositionY(bgNode->getPositionY() + m_fTileMapHeight * 2 - 2);  
		}  
	}  
}

}

}