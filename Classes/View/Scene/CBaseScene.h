#ifndef _CBASESCENE_H_
#define _CBASESCENE_H_
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

namespace View
{
	class CBaseScene : public CCScene
	{
	public:
		CBaseScene(bool bPortrait = false);
	public:
		virtual void  InitScene() {}
		virtual void onEnter();
		virtual void runThisScene() {}

	};
}

#endif