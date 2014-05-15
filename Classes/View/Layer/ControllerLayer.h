#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include "cocos2d.h"
USING_NS_CC;

class ControllerLayer :public CCLayer
{
public:
	ControllerLayer();
	~ControllerLayer() {}
private:
	CCPoint m_tBeginPos;
	CCMenu* m_pItemMenu;

};

#endif