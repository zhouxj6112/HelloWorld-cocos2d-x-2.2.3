//
//  FightScene.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-9-1.
//
//

#include "FightScene.h"
#include "GameSoundManager.h"
#include "Global.h"

USING_NS_CC;

CCScene* FightScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    // 'layer' is an autorelease object
    FightScene *layer = FightScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

bool FightScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    //预加载
    GameSoundManager::shareManager()->preLoad();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    float width = size.width;
    float height = size.height*5/12;
    
    fightBgLayer_ = FightBgLayer::create();
    fightBgLayer_->setAnchorPoint( ccp(0.5, 0.5) );
    fightBgLayer_->setPosition( ccp(width/2, size.height-height/2) );
    fightBgLayer_->setContentSize( CCSizeMake(width, height));
    this->addChild(fightBgLayer_);
    
    fightLayer_ = FightLayer::create();
    fightLayer_->setDelegate(this);
    fightLayer_->setAnchorPoint( ccp(0.5, 0.5) );
    fightLayer_->setPosition( ccp(width/2, size.height-height/2) );
    fightLayer_->setContentSize( CCSizeMake(width, height));
    this->addChild(fightLayer_);
    
    width = width;
    height = size.height-height;
    
    questionlayer_ = QuestionLayer::create(SingleQuestion);
    questionlayer_->setAnchorPoint( ccp(0.5, 0.5) );
    questionlayer_->setPosition( ccp(width/2, height/2) );
    questionlayer_->setContentSize( CCSizeMake(width, height) );
    questionlayer_->setDelegate(this);
    this->addChild(questionlayer_);
    answerCount = 0;
    
    GameSoundManager::shareManager()->playReadyGoEffect();
    
//    /*测试*/
//    CCLabelTTF* pLabel1 = CCLabelTTF::create("", "Arial", 24);
//    CCControlButton* button1 = CCControlButton::create(pLabel1, CCScale9Sprite::create("left.png"));
//    button1->addTargetWithActionForControlEvents(this, cccontrol_selector(FightScene::test1Callback), CCControlEventTouchUpInside);
//    button1->setPosition(ccp(48, size.height-48));
//    button1->setPreferredSize(CCSizeMake(96, 96));
//    this->addChild(button1, 10, 1000);
//    CCLabelTTF* pLabel2 = CCLabelTTF::create("", "Arial", 24);
//    CCControlButton* button2 = CCControlButton::create(pLabel2, CCScale9Sprite::create("right.png"));
//    button2->addTargetWithActionForControlEvents(this, cccontrol_selector(FightScene::test2Callback), CCControlEventTouchUpInside);
//    button2->setPosition(ccp(size.width-48, size.height-48));
//    button2->setPreferredSize(CCSizeMake(96, 96));
//    this->addChild(button2, 10, 2000);
    
    return true;
}

void FightScene::preLoadResource()
{

}

static float speed = 1.0f;
void FightScene::test1Callback(CCObject* object, void* param)
{
    speed -= 0.2f; if (speed < 0.2) speed = 0.2f;
    CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
    pScheduler->setTimeScale(speed); //实现减速效果
}
void FightScene::test2Callback(CCObject* object, void* param)
{
    speed += 0.2f; if (speed > 3.0) speed = 3.0f;
    CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
    pScheduler->setTimeScale(speed); //实现加速效果
}

void FightScene::onEnter()
{
    CCLayer::onEnter();
    
//    /*测试动画帧代码*/
//    speed = 0.5f;
//    CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
//    pScheduler->setTimeScale(speed);
    
    GameSoundManager::shareManager()->playFightBackgroundMusic();
}
void FightScene::onExit()
{
    speed = 1.0f;
    CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
    pScheduler->setTimeScale(speed);
    
    GameSoundManager::shareManager()->stopPlayBackgroundMusic();
    
    CCLayer::onExit();
}

#pragma mark -
#pragma mark QuestionLayerDelegate

void FightScene::answerDelegateCB(QuestionLayer* box, int rightCount, int errorCount)
{
    fightLayer_->attackProcedure(rightCount, errorCount);
}

void FightScene::moveVisibleWindow(FightLayer *layer, float deltaX, float time)
{
    if (deltaX != 0) {
        fightBgLayer_->moveBgLayer(deltaX, time);
    }
}

void FightScene::fightDidFinished(FightLayer* layer)
{
    answerCount++;
    
    //开启下一轮题目
    questionlayer_->removeFromParentAndCleanup(true);
    questionlayer_ = NULL;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    float width = size.width;
    float height = size.height-size.height*5/12;
    
    if (answerCount%2 == 1) {
        questionlayer_ = QuestionLayer::create(JudgeQuestion);
        questionlayer_->setAnchorPoint( ccp(0.5, 0.5) );
        questionlayer_->setPosition( ccp(width/2, height/2) );
        questionlayer_->setContentSize( CCSizeMake(width, height) );
        questionlayer_->setDelegate(this);
        this->addChild(questionlayer_);
    } else {
        questionlayer_ = QuestionLayer::create(SingleQuestion);
        questionlayer_->setAnchorPoint( ccp(0.5, 0.5) );
        questionlayer_->setPosition( ccp(width/2, height/2) );
        questionlayer_->setContentSize( CCSizeMake(width, height) );
        questionlayer_->setDelegate(this);
        this->addChild(questionlayer_);
    }
}

void FightScene::battleOver(FightLayer* layer, bool isWin)
{
    CCSize size = questionlayer_->getContentSize();
    questionlayer_->removeFromParentAndCleanup(true);
    questionlayer_ = NULL;
    
    CCLabelTTF *label = CCLabelTTF::create("", "", 32);
    if (isWin) {
        label->setString("您赢了,战斗将继续");
    } else {
        label->setString("您输了,将结束战斗");
    }
    label->setPosition(ccp(size.width/2, size.height/2-30));
    this->addChild(label);
    CCScaleBy* pScale = CCScaleBy::create(2.0f, 2.0f);
    CCDelayTime* pDelay = CCDelayTime::create(2.0f);
    CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(FightScene::fightOverCallback), (void *)&isWin);
    label->runAction(CCSequence::create(pScale, pDelay, pStop, NULL));
    _isWin = isWin;
    
    if (isWin) {
        GameSoundManager::shareManager()->playWinEffect();
    }
}

void FightScene::fightOverCallback(CCObject *object, void *param)
{
    bool isWin = &param;
    if (_isWin) {
        Global::shareInstance()->smallMissionGate += 1;
        Global::shareInstance()->userExp += 100;
    }
    //退出战斗
    CCDirector::sharedDirector()->popScene();
    CCDirector::sharedDirector()->purgeCachedData();
}
