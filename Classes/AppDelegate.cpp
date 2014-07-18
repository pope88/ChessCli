#include "Config.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "TcpNetwork/TcpNet.h"
#include "View/Layer/GameLayer.h"
#include "View/Table/Table.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {

	//design 

	auto designSize = Size(640, 960);


    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
    //	glview->setFrameZoomFactor(0.5);
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::FIXED_HEIGHT);

	glview->setFrameSize(640, 800);

    auto wisize = director->getWinSize();


	director->setContentScaleFactor(1136/designSize.height);


	// create a scene. it's an autorelease object
	auto scene = View::Table::creatScene();

    // run
    director->runWithScene(scene);

	TcpNetWork::_tcpnet.connect("127.0.0.1", 7771, 50);

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
