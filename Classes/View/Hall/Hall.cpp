#include "Hall.h"

namespace View
{
	Hall::Hall()
	{

	}

	Scene* Hall::createScene()
	{
		auto scene = Scene::create();
		auto layer = Hall::create();
		scene->addChild(layer);
		return scene;
	}

	bool Hall::init()
	{
		if (!Layer::init())
		{
			return false;
		}

		_hbackGround = Sprite::create();
		this->addChild(_hbackGround);
		return true;
	}
}