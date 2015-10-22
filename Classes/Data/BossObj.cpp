//
//  BossObj.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-10-15.
//
//

#include "BossObj.h"
#include "GameSoundManager.h"

#include "cocos2d.h"
USING_NS_CC;

BossObj::BossObj(CCLayer* superLayer):PlayerObj(superLayer)
{
    //
}

bool BossObj::init()
{
    totalHealth = 1000;
    curHealth = totalHealth;
    playerSpr = cocos2d::CCSprite::create("0.png");
    playerSpr->setPosition(curPos);
    superLayer->addChild(playerSpr);
    //预加载精灵图片
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("role_boss.plist");
    CCSpriteFrame* sFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::create("40078-1.png")->getCString());
    playerSpr->setTexture(sFrame->getTexture());
    //
    healthProgressTimer->setMidpoint( ccp(0, 1) );
    
    return true;
}

void BossObj::preLoadResource()
{
}

void BossObj::stand()
{
//    CCAnimation* pAnimation = CCAnimation::create();
//    for (int i=0; i<3; i++)
//    {
//        CCSpriteFrame* pFrame = CCSpriteFrame::create("role_walk.png", CCRectMake((9+i)*24, 32*1, 24, 32));
//        pAnimation->addSpriteFrame(pFrame);
//    }
//    pAnimation->setRestoreOriginalFrame(true);
//    pAnimation->setDelayPerUnit(1.0f/6);    // 必须设置这个，要不就不会播放
//    pAnimation->setLoops(1);
//    CCAnimate* pAnimate = CCAnimate::create(pAnimation);
//    CCAction* repeatAction = CCRepeatForever::create(pAnimate);
//    playerSpr->runAction(repeatAction);
////    playerSpr->setPosition(curPos);
//    playerSpr->setScale(2.0f);
//    if (curDir == DIRECTION_RIGHT) {
//        playerSpr->setFlipX(false);
//    } else if (curDir == DIRECTION_LEFT) {
//        playerSpr->setFlipX(true);
//    }
    
    CCArray *actionArray = CCArray::createWithCapacity(4);
    int frameNum = 4;   //取几帧
    int frameStart = 1; //起始number
    //获取纹理缓存
    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    for (int i=frameStart; i<frameNum; i++) {
        CCSpriteFrame* spriteFrame = frameCache->spriteFrameByName(CCString::createWithFormat("40078-%d.png",i)->getCString());
        actionArray->addObject(spriteFrame);
    }
    CCAnimation* idleAnimation = CCAnimation::createWithSpriteFrames(actionArray, 0.2f);
    CCAnimate* pAnimate = CCAnimate::create(idleAnimation);
    playerSpr->runAction(CCRepeatForever::create(pAnimate));
//    playerSpr->setPosition(curPos);
    if (curDir == DIRECTION_RIGHT) {
        playerSpr->setFlipX(false);
    } else if (curDir == DIRECTION_LEFT) {
        playerSpr->setFlipX(true);
    }
}

void BossObj::run(int distance)
{
//    CCAnimation* pAnimation = CCAnimation::create();
//    for (int i=0; i<3; i++)
//    {
//        CCSpriteFrame* pFrame = CCSpriteFrame::create("role_walk.png", CCRectMake((9+i)*24, 32*1, 24, 32));
//        pAnimation->addSpriteFrame(pFrame);
//    }
//    pAnimation->setRestoreOriginalFrame(true);
//    pAnimation->setDelayPerUnit(0.5f/3);    // 必须设置这个，要不就不会播放
//    pAnimation->setLoops(1);
//    CCAnimate* pAnimate = CCAnimate::create(pAnimation);
//    CCAction* repeatAction = CCRepeatForever::create(pAnimate);
//    playerSpr->runAction(repeatAction);
    
    CCArray *actionArray = CCArray::createWithCapacity(8);
    int frameNum = 8;   //取几帧
    int frameStart = 1; //起始number
    //获取纹理缓存
    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    for (int i=frameStart; i<frameNum; i++) {
        CCSpriteFrame* spriteFrame = frameCache->spriteFrameByName(CCString::createWithFormat("40080-%d.png",i)->getCString());
        actionArray->addObject(spriteFrame);
    }
    CCAnimation* movingAnimation = CCAnimation::createWithSpriteFrames(actionArray, 0.1f);
    CCAnimate* pAnimate = CCAnimate::create(movingAnimation);
    playerSpr->runAction(CCRepeatForever::create(pAnimate));
    
    CCMoveBy* pMove = CCMoveBy::create(1.0f, ccp(distance, 0));
    CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::didAction), NULL);
    playerSpr->runAction(CCSequence::create(pMove, pStop, NULL));
    
    if (curDir == DIRECTION_RIGHT) {
        playerSpr->setFlipX(false);
    } else if (curDir == DIRECTION_LEFT) {
        playerSpr->setFlipX(true);
    }
}

void BossObj::attack(int sType)
{
    CCArray *actionArray = CCArray::createWithCapacity(4);
    int frameNum = 5;   //取几帧
    int frameStart = 1; //起始number
    //获取纹理缓存
    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    for (int i=frameStart; i<frameNum; i++) {
        CCSpriteFrame* spriteFrame = frameCache->spriteFrameByName(CCString::createWithFormat("40086-%d.png",i)->getCString());
        actionArray->addObject(spriteFrame);
    }
    CCAnimation* attackAnimation = CCAnimation::createWithSpriteFrames(actionArray, 0.2f);
    CCAnimate* pAnimate = CCAnimate::create(attackAnimation);
    CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::didAction), NULL);
    playerSpr->runAction(CCSequence::create(pAnimate, pStop, NULL));
    
    if (curDir == DIRECTION_RIGHT) {
        playerSpr->setFlipX(false);
    } else if (curDir == DIRECTION_LEFT) {
        playerSpr->setFlipX(true);
    }
    
    //通知被攻击者受到攻击
    CSkill* skill = new CSkill(0, 100, 1);
    CCDelayTime* pDelay = CCDelayTime::create(0.5f);
    CCAction* pAction = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::attackAction), (void*)skill);
    playerSpr->runAction(CCSequence::create(pDelay, pAction, NULL));
    
//    //播放攻击声效
//    GameSoundManager::shareManager()->playAttackEffect();
}

void BossObj::beHit(int damage)
{
    float hurt = damage;
    
    curHealth -= hurt;
    CCProgressFromTo* fromTo = CCProgressFromTo::create(0.5f, (curHealth+hurt)*1.0f/totalHealth*100, curHealth*1.0f/totalHealth*100);
    healthProgressTimer->runAction(fromTo);
    
    CCString* str = CCString::createWithFormat("-%d", (int)hurt);
    CCLabelBMFont* pLabel = CCLabelBMFont::create(str->getCString(), "fight_damage.fnt");
    pLabel->setAnchorPoint(ccp(0.5, 0.5));
    pLabel->setPosition(ccp(playerSpr->getPositionX(), playerSpr->getPositionY()+30));
    superLayer->addChild(pLabel);
    CCMoveBy* pMove = CCMoveBy::create(0.5f, ccp(0, 120));
    CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(BossObj::hurtActionDidFinished), NULL);
    pLabel->runAction(CCSequence::create(pMove, pStop, NULL));
    CCFadeOut* pFade = CCFadeOut::create(0.5f);
    pLabel->runAction(pFade);
    
    //播放受攻击动画
    CCArray *actionArray = CCArray::createWithCapacity(2);
    int frameNum = 3;   //取几帧
    int frameStart = 1; //起始number
    //获取纹理缓存
    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    for (int i=frameStart; i<frameNum; i++) {
        CCSpriteFrame* spriteFrame = frameCache->spriteFrameByName(CCString::createWithFormat("40081-%d.png",1)->getCString());
        actionArray->addObject(spriteFrame);
    }
    CCAnimation* attackAnimation = CCAnimation::createWithSpriteFrames(actionArray, 0.2f);
    CCAnimate* pAnimate = CCAnimate::create(attackAnimation);
    CCAction* pFinished = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::didAction), NULL);
    playerSpr->runAction(CCSequence::create(pAnimate, pFinished, NULL));
    //
    if (curDir == DIRECTION_RIGHT) {
        playerSpr->setFlipX(false);
    } else if (curDir == DIRECTION_LEFT) {
        playerSpr->setFlipX(true);
    }
}

void BossObj::dead()
{
    //播放受攻击动画
    CCArray *actionArray = CCArray::createWithCapacity(10);
    int frameNum = 10;  //取几帧
    int frameStart = 1; //起始number
    //获取纹理缓存
    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    for (int i=frameStart; i<frameNum; i++) {
        CCSpriteFrame* spriteFrame = frameCache->spriteFrameByName(CCString::createWithFormat("40082-%d.png",i)->getCString());
        actionArray->addObject(spriteFrame);
    }
    CCAnimation* attackAnimation = CCAnimation::createWithSpriteFrames(actionArray, 0.1f);
    CCAnimate* pAnimate = CCAnimate::create(attackAnimation);
    CCDelayTime* pDelay = CCDelayTime::create(3.0f);
    CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(BossObj::deadActionDidFinished), NULL);
    playerSpr->runAction(CCSequence::create(pAnimate, pDelay, pStop, NULL));
}

void BossObj::fightWin(int sid)
{
}

void BossObj::hurtActionDidFinished(CCObject *object, void *param)
{
    ((CCLabelAtlas *)object)->removeFromParent();
}

void BossObj::deadActionDidFinished(cocos2d::CCObject *object, void *param)
{
    playerSpr->removeFromParent();
}
