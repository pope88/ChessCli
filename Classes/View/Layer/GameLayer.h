#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_
#include "cocos2d.h"
USING_NS_CC;

namespace View
{
	namespace Layer
	{
		class GameLayer : public CCLayer
		{
			enum TAG_BG
			{
				TAG_BG_NEAR_LAYER = 0,
				TAG_BG_FAR_LAYER = 1
			};
		public:
			GameLayer();
			~GameLayer();
		public:
			void initBackground();
			void update(float dt);
			void movingBackground(CCObject *pObj, float dt);
		private:
			// ±³¾°(Ô¶¾°²ã)  
			CCSprite *m_pSkySprite;  
			CCSprite *m_pSkySpriteRe;  
			float m_fSkyVelocity;  
			float m_fSkyHeight;  

			// µØÍ¼(½ü¾°²ã)  
			CCSprite *m_pTileMap;  
			CCSprite *m_pTileMapRe;  
			float m_fTileMapVelocity;  
			float m_fTileMapHeight;

		};
	}
}
#endif