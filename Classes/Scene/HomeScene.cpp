//
//  HomeScene.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-8-18.
//
//

#include "HomeScene.h"
#include "HomeLayer.h"
#include "LevelScene.h"

CCScene* HomeScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    // 'layer' is an autorelease object
    HomeScene *layer = HomeScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

bool HomeScene::init()
{
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* bgSpr = CCSprite::create("home_bg.png");
    bgSpr->setAnchorPoint(ccp(0, 0));
    bgSpr->setPosition( ccp(0, size.height-960) );
    this->addChild(bgSpr, -1, 0);
    
    HomeLayer* layer = new HomeLayer();
    layer->initWithDelegate(this);
    this->addChild(layer);
    
    //下导航区域
    CCMenuItemImage *bu01 = CCMenuItemImage::create("zhuye.png", "zhuye.png", this, menu_selector(HomeScene::menuItemCallBack));
    bu01->setTag(1);
    bu01->setPosition(ccp(60, 0));
    CCMenuItemImage *bu02 = CCMenuItemImage::create("chengshi.png", "chengshi.png", this, menu_selector(HomeScene::menuItemCallBack));
    bu02->setTag(2);
    bu02->setPosition(ccp(165, 0));
    CCMenuItemImage *bu03 = CCMenuItemImage::create("fuben.png", "fuben.png", this, menu_selector(HomeScene::menuItemCallBack));
    bu03->setTag(3);
    bu03->setPosition(ccp(270, 0));
    CCMenuItemImage *bu04 = CCMenuItemImage::create("huodong.png", "huodong.png", this, menu_selector(HomeScene::menuItemCallBack));
    bu04->setTag(4);
    bu04->setPosition(ccp(375, 0));
    CCMenuItemImage *bu05 = CCMenuItemImage::create("beibao.png", "beibao.png", this, menu_selector(HomeScene::menuItemCallBack));
    bu05->setTag(5);
    bu05->setPosition(ccp(480, 0));
    CCMenuItemImage *bu06 = CCMenuItemImage::create("shangcheng.png", "shangcheng.png", this, menu_selector(HomeScene::menuItemCallBack));
    bu06->setTag(6);
    bu06->setPosition(ccp(585, 0));
    CCMenu* menu = CCMenu::create(bu01, bu02, bu03, bu04, bu05, bu06, NULL);
    menu->setPosition(ccp(0, 60));
    menu->setAnchorPoint(ccp(0, 0.5));
    this->addChild(menu);
    
    //系统公告
    CCLabelTTF* sysLabel = CCLabelTTF::create("系统公告板:展示系统消息", "", 24.0f);
    sysLabel->setAnchorPoint( ccp(0, 0.5f) );
    sysLabel->setPosition( ccp(size.width, size.height-25) );
    this->addChild(sysLabel, 0, 100);
    //
    CCMoveBy* pMove = CCMoveBy::create(10.0f, ccp(-size.width-sysLabel->getContentSize().width, 0));
    CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(HomeScene::actionDidFinished), NULL);
    sysLabel->runAction(CCSequence::create(pMove, pStop, NULL));
    
    sysLabel->runAction(pMove);
    
    return true;
}

void HomeScene::actionDidFinished(cocos2d::CCObject *object, void *param)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* sysLabel = (CCLabelTTF *)(this->getChildByTag(100));
    sysLabel->setPosition( ccp(size.width, size.height-25) );
    CCMoveBy* pMove = CCMoveBy::create(10.0f, ccp(-size.width-sysLabel->getContentSize().width, 0));
    CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(HomeScene::actionDidFinished), NULL);
    sysLabel->runAction(CCSequence::create(pMove, pStop, NULL));
}

void HomeScene::pressDelegateCB(HomeLayer* layer, int buttonTag)
{
    if (buttonTag == 10) {
        CCScene* pScene = LevelScene::scene();
        CCDirector::sharedDirector()->pushScene(pScene);
    } else {
        CCDirector::sharedDirector()->popScene();
    }
}

void HomeScene::menuItemCallBack(CCObject* pSender)
{
    CCMenuItemImage* item = (CCMenuItemImage *)pSender;
    switch (item->getTag()) {
        case 1:
            CCLOG("主页");
            break;
        case 2:
            CCLOG("城市");
            break;
        case 3:
            CCLOG("副本");
            break;
        case 4:
            CCLOG("活动");
            break;
        case 5:
            CCLOG("背包");
            break;
        case 6:
            CCLOG("商城");
            break;
        default:
            break;
    }
}
