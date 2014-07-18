#ifndef _VISIBLERECT_H_
#define _VISIBLERECT_H_
#include "cocos2d.h"
namespace View
{
	class VisibleRect
	{
	public:
		static cocos2d::Rect getVisibleRect();

		static cocos2d::Point left();
		static cocos2d::Point right();
		static cocos2d::Point top();
		static cocos2d::Point bottom();
		static cocos2d::Point center();
		static cocos2d::Point leftTop();
		static cocos2d::Point rightTop();
		static cocos2d::Point leftBottom();
		static cocos2d::Point rightBottom();
	private:
		static void lazyInit();
		static cocos2d::Rect s_visibleRect;
	};
}

#endif // !_VISIBLERECT_H_
