#ifndef _BaseScene_H_
#define _BaseScene_H_
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

namespace View
{
	class BaseScene : public Scene
	{
	public:
		BaseScene(bool bPortrait = false);
	public:
		virtual void  InitScene() {}
		virtual void onEnter();
		virtual void runThisScene() {}

	};
}

#endif