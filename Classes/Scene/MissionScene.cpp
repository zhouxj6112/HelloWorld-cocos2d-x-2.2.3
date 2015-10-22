//
//  JobMissionScene.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-8-4.
//
//

#include "MissionScene.h"
#include "FightScene.h"
#include "Global.h"
#include "Utils.h"

CCScene* MissionScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    // 'layer' is an autorelease object
    MissionScene *layer = MissionScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MissionScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            CCString* str = CCString::createWithFormat("公司(%d)", i*3+j+1);
            CCLabelTTF* pLabel = CCLabelTTF::create(str->getCString(), "Arial", 24);
            CCControlButton* button = CCControlButton::create(pLabel, CCScale9Sprite::create("button_answer.png", CCRectMake(0, 0, 126, 70)));
            button->addTargetWithActionForControlEvents(this, cccontrol_selector(MissionScene::touchDownAction), CCControlEventTouchUpInside);
            button->setTag(i*3+j+100);
            button->setAnchorPoint(ccp(0.5f, 0.5f));
            button->setPosition(ccp(120+j*200, size.height/2+200-i*200));
            button->setPreferredSize(CCSize(180, 120));
            this->addChild(button, 1);
            button->setEnabled(false);
            CCSprite* sprite = createGraySprite("button_answer.png");
            CCSpriteFrame* sprFrame = CCSpriteFrame::createWithTexture(sprite->getTexture(), CCRectMake(0, 0, 126, 70));
            button->setBackgroundSpriteFrameForState(sprFrame, CCControlStateDisabled);
            
            if (i*3+j < Global::shareInstance()->smallMissionGate) {
                CCParticleSun* par = CCParticleSun::createWithTotalParticles(30);
                par->setTexture( CCTextureCache::sharedTextureCache()->addImage("fire.png") );
                par->setAnchorPoint( ccp(0.5f, 0.5f) );
                par->setPosition( ccp(90, 60) );
                button->addChild(par, 1, 123);
                //
                button->setEnabled(true);
            } else if (i*3+j == Global::shareInstance()->smallMissionGate) {
                button->setEnabled(true);
            } else {
                //
            }
        }
    }
    
    CCMenuItemImage* closeItem = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(MissionScene::menuItemCallBack));
    closeItem->setPosition(ccp(size.width-40, size.height-40));
    CCMenu* menu = CCMenu::create(closeItem, NULL);
    menu->setPosition(ccp(0, 0));
    this->addChild(menu);
    
    return true;
}

void MissionScene::menuItemCallBack(cocos2d::CCObject *pSender)
{
    CCDirector::sharedDirector()->popScene();
}

void MissionScene::touchDownAction(cocos2d::CCObject *sender, CCControlEvent controlEvent)
{
    CCScene* pScene = FightScene::scene();
    CCDirector::sharedDirector()->pushScene(pScene);
}

void MissionScene::onEnter()
{
    CCLayer::onEnter();
    
    for (int i=0; i<Global::shareInstance()->smallMissionGate+1; i++) {
        CCControlButton* button = (CCControlButton *)(this->getChildByTag(i+100));
        if (button == NULL) { continue; }
        if (i < Global::shareInstance()->smallMissionGate) {
            CCParticleSun* par = (CCParticleSun *)(button->getChildByTag(123));
            if (par == NULL) {
                par = CCParticleSun::createWithTotalParticles(30);
                par->setTexture( CCTextureCache::sharedTextureCache()->addImage("fire.png") );
                par->setAnchorPoint( ccp(0.5f, 0.5f) );
                par->setPosition( ccp(button->getContentSize().width/2, button->getContentSize().height/2) );
                button->addChild(par);
            }
        }
        button->setEnabled(true);
    }
    //
    if (Global::shareInstance()->smallMissionGate >= 9) {
        CCLOG("小关卡都完成了,需要更新大关卡");
        Global::shareInstance()->missionGate += 1;
        Global::shareInstance()->smallMissionGate = 0;
        
        CCDelayTime* pTime = CCDelayTime::create(3.0f);
        CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(MissionScene::actionDidFinished), NULL);
        this->runAction(CCSequence::create(pTime, pStop, NULL));
        
        CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(false);
    }
}

void MissionScene::onExit()
{
    CCLayer::onExit();
}

void MissionScene::actionDidFinished(CCObject *object, void *param)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(true);
    CCDirector::sharedDirector()->popScene();
}
