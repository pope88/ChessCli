#ifndef _GMEEMANAGER_H_
#define _GMEEMANAGER_H_
#include "../Utils/Singleton.h"
#include "../View/Scene/CBaseScene.h"
#include "../View/Scene/CTestScene.h"
#include "../View/Scene/CMenuScene.h"

using namespace Utils;
namespace View
{
	enum 
	{
		SCENE_INIT = 1,
		SCENE_LOGIN = 2,
		SCENE_MENU = 3,
	};

	class GameManager
	{
	public:
		void DisplayNowScene(int sID);
	private:
		GameManager() {}
		~GameManager() {}
	private:
		std::map<UInt8, BaseScene*> _allScenesMap;
		//BaseScene *actScene;

		DECLARE_SINGLETON_CLASS(GameManager);
	};
	typedef Singleton<GameManager> _gamemanager;
}
#endif