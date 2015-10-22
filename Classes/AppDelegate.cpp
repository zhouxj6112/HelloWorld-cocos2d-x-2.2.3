#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "WebSocketManager.h"
#include "NetworkProtocol.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
//    // turn on display FPS
//    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);
    
//    WebSocketManager::shareManager()->addDelegate(this);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

bool AppDelegate::OnSocketReadEvent(NetMessageHead* pNetHead, void* pNetData, unsigned int uDataSize, WebSocketManager* pClientSocket)
{
    struct LoginRequestData* request = (LoginRequestData *)pNetData;
    if (request->loginType == 3) {
        CCLOG("+++++++++++++++++++++");
    }
    
    pClientSocket->sendMessage();
    return true;
}

bool AppDelegate::OnSocketConnectEvent(unsigned int uErrorCode, WebSocketManager *pClientSocket)
{
    return true;
}

bool AppDelegate::OnSocketCloseEvent()
{
    return true;
}
