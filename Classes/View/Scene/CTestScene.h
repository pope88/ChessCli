#ifndef _CTESTSCENE_H_
#define _CTESTSCENE_H_
#include "cocos2d.h"
#include "../Classes/Utils/Singleton.h"
#include "CBaseScene.h"
USING_NS_CC;
namespace View
{
	//for test initSecen
	class CTestScene : public BaseScene
	{
	public:
		virtual void runThisScene();
		void InitScene();
		void OnTextmenu_Click(Ref *pSender);
		void ShowOtherScene(float t = 0.0);
	};
}
#endif