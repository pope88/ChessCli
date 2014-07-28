#ifndef _BUTTON_H_
#define _BUTTON_H_
#include "cocos2d.h"
USING_NS_CC;
class Button : public Node
{
public:
	static Button* createWithSprite(const char* *filePath)
	{
		auto b = new Button();
		if (b && !b->initSpriteButton(filePath))
		{
			delete b;
			b = nullptr;
		}
		b->autorelease();
		return b;
	}
	static Button *createWithText(const char *text)
	{
		auto b = new Button();
		if (b && !b->initTextButton(text))
		{
			delete b;
			b = nullptr;
		}
		b->autorelease();
		return b;
	}

	virtual ~Button(){}
	//init();
	void onTriggered(const std::function<void(void)> &onTriggered)
	{
		_onTriggered = onTriggered;
	}
private:
		Button():_child(nullptr)
		{
			auto listener = EventListenerTouchOneByOne::create();
			listener->setSwallowTouches(true);
			listener->onTouchBegan = CC_CALLBACK_2(Button::onTouchBegan, this);
			listener->onTouchEnded = CC_CALLBACK_2(Button::onTouchEnded, this);
			listener->onTouchCancelled = CC_CALLBACK_2(Button::onTouchCancelled, this);

			_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		}

		bool initSpriteButton(const char *filePath)
		{
			_child = Label::createWithTTF(TEXT, "fonts/arial.ttf", 16);
			addChild(_child);
			return true;
		}

		bool touchHits(Touch *touch)
		{
			const Rect area(0, 0, _child->getContentSize().width, _child->getContentSize().height);
			return area.containsPoint(_child->convertToNodeSpace(touch->getLocation()));
		}

		bool onTouchBegan(Touch  *touch, Event  *event)
		{
			CC_UNUSED_PARAM(event);
			const bool hits = touchHits(touch);
			if (hits)
				scaleButtonTo(0.9f);
			return hits;
		}

		void onTouchEnded(Touch  *touch, Event  *event)
		{
			CC_UNUSED_PARAM(event);
			const bool hits = touchHits(touch);
			if (hits && _onTriggered)
				_onTriggered();
			scaleButtonTo(1);
		}

		void onTouchCancelled(Touch  *touch, Event  *event)
		{
			CC_UNUSED_PARAM(event);
			scaleButtonTo(1);
		}

		void scaleButtonTo(float scale)
		{
			auto action = ScaleTo::create(0.1f, scale);
			action->setTag(900);
			stopActionByTag(900);
			runAction(action);
		}
private:
	Node *_child;
	std::function<void(void)> _onTriggered;
};
#endif