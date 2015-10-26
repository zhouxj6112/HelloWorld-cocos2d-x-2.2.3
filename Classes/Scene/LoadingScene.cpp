//
//  LoadingScene.cpp
//  HelloWorld
//
//  Created by MrZhou on 15-10-22.
//
//

#include "LoadingScene.h"
#include "FightScene.h"

USING_NS_CC;

CCScene* LoadingScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    // 'layer' is an autorelease object
    LoadingScene *layer = LoadingScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

bool LoadingScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    CCLabelTTF* pLabel = CCLabelTTF::create("资源加载中,请等待...", "Arial", 32);
    pLabel->setPosition( ccp(this->getContentSize().width/2, this->getContentSize().height/2) );
    this->addChild(pLabel);
    
    CCDelayTime* pDelay = CCDelayTime::create(0.1f);
    CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(LoadingScene::didAction), NULL);
    this->runAction(CCSequence::create(pDelay, pStop, NULL));
    
    return true;
}

void LoadingScene::didAction(cocos2d::CCObject* object, void* param)
{
    CCScene* pScene = FightScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}
