#include "Config.h"
#include "GameManager.h"

namespace View
{
	void GameManager::DisplayNowScene(int sID)
	{
		CBaseScene *actScene = NULL;
		bool bFirstScene = false;
		do 
		{
			//auto it = _allScenesMap.find(sID);
			//if (it != _allScenesMap.end())
			//{
			//	actScene = _allScenesMap[sID];
			//	break;
			//}
			switch (sID)
			{
			case SCENE_INIT:
				bFirstScene = true;
				actScene = new CTestScene();// CBaseScene::create();
				break;
			case SCENE_LOGIN:
				actScene = new CTestScene();
				break;
			case SCENE_MENU:
				actScene = new CMenuScene();
				break;
			default:
				break;

			}
			//_allScenesMap[sID] = actScene;
		} while (0);

		if (actScene != NULL)
		{
			actScene->runThisScene();
			actScene->release();  //ªÿ ’
		}
	}
}