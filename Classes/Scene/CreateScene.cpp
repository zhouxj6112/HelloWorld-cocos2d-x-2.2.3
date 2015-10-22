//
//  CreateScene.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-10-31.
//
//

#include "CreateScene.h"
#include "CreateRoleLayer.h"
#include "HomeScene.h"

USING_NS_CC;

CCScene* CreateScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    // 'layer' is an autorelease object
    CreateScene *layer = CreateScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

bool CreateScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* bgSpr = CCSprite::create("launch.jpg");
    bgSpr->setAnchorPoint(ccp(0, 0));
    float winw = size.width; //获取屏幕宽度
    float winh = size.height;//获取屏幕高度
    float spx = bgSpr->getTextureRect().getMaxX();
    float spy = bgSpr->getTextureRect().getMaxY();
    //设置精灵宽度缩放比例
    bgSpr->setScaleX(winw/spx);
    bgSpr->setScaleY(winh/spy);
    this->addChild(bgSpr, -1);
    
    CreateRoleLayer* layer = CreateRoleLayer::create();
    layer->setDelegate(this);
    layer->setAnchorPoint(ccp(0, 0));
    this->addChild(layer);
    
    return true;
}

void CreateScene::createDidFinished(CreateRoleLayer* pLayer)
{
    CCScene* pScene = HomeScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}
