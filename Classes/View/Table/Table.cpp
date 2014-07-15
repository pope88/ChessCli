#include "Config.h"
#include "Table.h"

namespace View
{
	Table::Table()
	{
	}

	Scene* Table::creatScene()
	{
		auto scene = Scene::create();
		auto layer = Table::create();
		scene->addChild(layer);
		//layer->createCards();
		return scene;
	}

	void Table::onEnter()
	{
		_backGroud = Sprite::create(spTableBackGroud);
		this->addChild(_backGroud);
	}
}