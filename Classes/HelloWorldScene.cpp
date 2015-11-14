#include "HelloWorldScene.h"
#include "JobHuntingScene.h"
#include "LevelScene.h"
#include "HomeScene.h"
#include "CreateScene.h"
#include "FightScene.h"
#include "LoadingScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCLog("屏幕尺寸:%f %f %f %f", origin.x, origin.y, visibleSize.width, visibleSize.height);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    CCMenuItemFont* pMenuItem1 = CCMenuItemFont::create("创建流程", this, menu_selector(HelloWorld::menuPopScene));
    pMenuItem1->setFontSizeObj(30);
    pMenuItem1->setColor(cocos2d::ccc3(0,255,255));
    pMenuItem1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/5*4));
    CCMenuItemFont* pMenuItem2 = CCMenuItemFont::create("主界面测试", this, menu_selector(HelloWorld::menuTestLayer));
    pMenuItem2->setFontSizeObj(30);
    pMenuItem2->setColor(cocos2d::ccc3(0,255,255));
    pMenuItem2->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/5*3));
    CCMenuItemFont* pMenuItem3 = CCMenuItemFont::create("城市选择", this, menu_selector(HelloWorld::menuGameLayer));
    pMenuItem3->setFontSizeObj(30);
    pMenuItem3->setColor(cocos2d::ccc3(0,255,255));
    pMenuItem3->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/5*2));
    CCMenuItemFont* pMenuItem4 = CCMenuItemFont::create("战斗逻辑(10连击)", this, menu_selector(HelloWorld::menuFightAllLayer));
    pMenuItem4->setFontSizeObj(30);
    pMenuItem4->setColor(cocos2d::ccc3(0,255,255));
    pMenuItem4->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/5*1+20));
    CCMenuItemFont* pMenuItem5 = CCMenuItemFont::create("战斗逻辑(普通击)", this, menu_selector(HelloWorld::menuFightLayer));
    pMenuItem5->setFontSizeObj(30);
    pMenuItem5->setColor(cocos2d::ccc3(0,255,255));
    pMenuItem5->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/5*1-30));
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, pMenuItem1, pMenuItem2, pMenuItem3, pMenuItem4, pMenuItem5, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("测试界面", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void HelloWorld::menuPopScene(cocos2d::CCObject *pSender)
{
    CCScene* pScene = CreateScene::scene();
    CCDirector::sharedDirector()->pushScene(pScene);
}

void HelloWorld::menuTestLayer(CCObject* pSender)
{
    CCScene* pScene = HomeScene::scene();
    CCDirector::sharedDirector()->pushScene(pScene);
}

void HelloWorld::menuGameLayer(CCObject* pSender)
{
    CCScene* pScene = LevelScene::scene();
    CCDirector::sharedDirector()->pushScene(pScene);
}

void HelloWorld::menuFightLayer(CCObject* pSender)
{
    is_realy_fight = true;
    
    CCScene* pScene = LoadingScene::scene();
    CCDirector::sharedDirector()->pushScene(pScene);
}
void HelloWorld::menuFightAllLayer(CCObject* pSender)
{
    is_realy_fight = false;
    
    CCScene* pScene = LoadingScene::scene();
    CCDirector::sharedDirector()->pushScene(pScene);
}
