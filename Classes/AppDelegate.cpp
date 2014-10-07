#include "Config.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
//#include "TcpNetwork/TcpNet.h"
#include "View/Layer/GameLayer.h"
#include "View/Table/Table.h"
#include "View/Login//LoginBar.h"
#include "View/Hall/Hall.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	auto designSize = Size(640, 960);

	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if(!glview) {
		glview = GLView::createWithRect("My Game", Rect(0, 0, 640, 960));
		director->setOpenGLView(glview);
		glview->setFrameSize(640, 960);
		glview->setFrameZoomFactor(0.8);
	}

	director->setOpenGLView(glview);
	// turn on display FPS
	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::FIXED_WIDTH);


	auto wisize = director->getWinSize();

	director->setContentScaleFactor(1136/designSize.height);

	// create a scene. it's an autorelease object
	//auto scene = View::Hall::createScene();
	//auto scene = View::GameLayer::creatScene();
	// run

	auto scene = View::LoginBar::createScene();
	//View::_table.init();
	//auto scene = View::Table::creatScene();

	//std::vector<View::PlayerInfo> pInfo;
	//View::PlayerInfo pi;
	//pi.chairid = 0;
	//pi.allchips = 1000;
	//pi.nickname = "xiaocelao";
	//for (int i = 0; i < 3; ++i)
	//{
	//	pInfo.push_back(pi);
	//}
	//View::_table.onPlayerEnter(pInfo);

	Director::getInstance()->runWithScene(scene); 

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
