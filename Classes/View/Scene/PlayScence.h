#ifndef _PLAYSCENCE_H_
#define _PLAYSCENCE_H_
#include "cocos2d.h"
#include "CBaseScene.h"

USING_NS_CC;
using namespace std;

namespace View
{
	class PlayScence : public CBaseScene
	{
	public:
		virtual void runThisScene();
		virtual void InitScene();
		void ShowOtherScene();
	};
}
#endif