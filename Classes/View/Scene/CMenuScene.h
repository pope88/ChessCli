#ifndef _CMENUSCENE_H_
#define _CMENUSCENE_H_
#include "CBaseScene.h"

namespace View
{
	//for test SCENE_MENU
	class CMenuScene : public BaseScene
	{
	public:
		virtual void runThisScene();
		virtual void InitScene();
		void ShowOtherScene();
		void OnTextmenu_Click(Ref *pSender);

	};
}
#endif