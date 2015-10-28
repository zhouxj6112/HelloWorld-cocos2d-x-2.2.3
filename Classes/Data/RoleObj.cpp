//
//  RoleObj.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-10-15.
//
//

#include "RoleObj.h"
#include "GameSoundManager.h"
#include "Utils.h"
#include "AnimationManager.h"

#include "cocos2d.h"
USING_NS_CC;

RoleObj::RoleObj(CCLayer* superLayer):PlayerObj(superLayer)
{
}

bool RoleObj::init()
{
    totalHealth = 1500;
    curHealth = totalHealth;
    playerSpr = cocos2d::CCSprite::create("idle/o0000.png");
    playerSpr->setFlipX(true);
    playerSpr->setPosition(curPos);
    superLayer->addChild(playerSpr);
    
    return PlayerObj::init();
}

void RoleObj::stand(int sid)
{
    CCAnimation* pAnimation = AnimationManager::shareInstance()->getAnimationWithName(str_hero_idle);
    CCAnimate* pAnimate = CCAnimate::create(pAnimation);
    CCAction* repeatAction = CCRepeatForever::create(pAnimate);
    playerSpr->runAction(repeatAction);
    //
    if (curDir == DIRECTION_RIGHT) {
        playerSpr->setFlipX(false);
    } else if (curDir == DIRECTION_LEFT) {
        playerSpr->setFlipX(true);
    }
}

void RoleObj::run(int sid, int distance)
{
    CCAnimation* pAnimation = AnimationManager::shareInstance()->getAnimationWithName(str_hero_run);
    CCAnimate* pAnimate = CCAnimate::create(pAnimation);
    CCAction* repeatAction = CCRepeatForever::create(pAnimate);
    playerSpr->runAction(repeatAction);
    
    CCMoveBy* pMove = CCMoveBy::create(0.6f, ccp(distance, 0));
    CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::didAction), NULL);
    playerSpr->runAction(CCSequence::create(pMove, pStop, NULL));
    
    //
    if (curDir == DIRECTION_RIGHT) {
        playerSpr->setFlipX(false);
    } else if (curDir == DIRECTION_LEFT) {
        playerSpr->setFlipX(true);
    }
}

void RoleObj::attack(int sid, int sType)
{
    //开始攻击动画,区分不同技能
    if (sType == 0) {    //攻击技能1
        
        int iKeyFrame = 4;
        
        CCAnimation* pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_a");
        if (pAnimation == NULL) {
            pAnimation = CCAnimation::create();
            for (int i=1; i<=4; i++)
            {
                CCString* pFileName = CCString::createWithFormat("skill/a%04d.png", i);
                pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                if (i == iKeyFrame) {
                    for (int k=0; k<2; k++) {
                        pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                    }
                }
            }
            pAnimation->setRestoreOriginalFrame(true);
            pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
            pAnimation->setLoops(1);
            CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_a");
        }
        CCAnimate* pAnimate = CCAnimate::create(pAnimation);
        CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::didAction), NULL);
        playerSpr->runAction(CCSequence::create(pAnimate, pStop, NULL));
        
        //通知被攻击者受到攻击
        CCDelayTime* pDelay = CCDelayTime::create(0.1f*iKeyFrame);
        CSkill* skill = new CSkill(sType+1, 80, 1);
        CCAction* pAction = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::attackAction), (void *)skill);
        playerSpr->runAction(CCSequence::create(pDelay, pAction, NULL));
        
    }
    else if (sType == 1)  //攻击技能2
    {
        int iKeyFrame = 2;
        
        CCAnimation* pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_b");
        if (pAnimation == NULL) {
            pAnimation = CCAnimation::create();
            for (int i=1; i<=4; i++)
            {
                CCString* pFileName = CCString::createWithFormat("skill/b%04d.png", i);
                pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                if (i == iKeyFrame) {
                    for (int k=0; k<2; k++) {
                        pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                    }
                }
            }
            pAnimation->setRestoreOriginalFrame(true);
            pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
            pAnimation->setLoops(1);
            CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_b");
        }
        CCAnimate* pAnimate = CCAnimate::create(pAnimation);
        CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::didAction), NULL);
        playerSpr->runAction(CCSequence::create(pAnimate, pStop, NULL));
        
        //通知被攻击者受到攻击
        CSkill* skill = new CSkill(sType+1, 90, 1);
        CCDelayTime* pDelay1 = CCDelayTime::create(0.1f*iKeyFrame);
        CCAction* pAction = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::attackAction), (void *)skill);
        playerSpr->runAction(CCSequence::create(pDelay1, pAction, NULL));
        
    }
    else if (sType == 2)  //攻击技能3
    {
        int iKeyFrame = 3;
        
        CCAnimation* pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_c");
        if (pAnimation == NULL) {
            pAnimation = CCAnimation::create();
            for (int i=1; i<=4; i++)
            {
                CCString* pFileName = CCString::createWithFormat("skill/c%04d.png", i);
                pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                if (i == iKeyFrame) {
                    for (int k=0; k<2; k++) {
                        pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                    }
                }
            }
            pAnimation->setRestoreOriginalFrame(true);
            pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
            pAnimation->setLoops(1);
            CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_c");
        }
        CCAnimate* pAnimate = CCAnimate::create(pAnimation);
        CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::didAction), NULL);
        playerSpr->runAction(CCSequence::create(pAnimate, pStop, NULL));
        
        //通知被攻击者受到攻击
        CSkill* skill = new CSkill(sType+1, 100, 1);
        CCDelayTime* pDelay1 = CCDelayTime::create(0.1f*iKeyFrame);
        CCAction* pAction = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::attackAction), (void *)skill);
        playerSpr->runAction(CCSequence::create(pDelay1, pAction, NULL));
        
    }
    else if (sType == 3)  //攻击技能4
    {
        int iKeyFrame = 4;
        
        CCAnimation* pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_d");
        if (pAnimation == NULL) {
            pAnimation = CCAnimation::create();
            for (int i=1; i<=4; i++)
            {
                CCString* pFileName = CCString::createWithFormat("skill/d%04d.png", i);
                pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                if (i == iKeyFrame) {
                    for (int k=0; k<2; k++) {
                        pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                    }
                }
            }
            pAnimation->setRestoreOriginalFrame(true);
            pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
            pAnimation->setLoops(1);
            CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_d");
        }
        CCAnimate* pAnimate = CCAnimate::create(pAnimation);
        CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::didAction), NULL);
        playerSpr->runAction(CCSequence::create(pAnimate, pStop, NULL));
        
        //通知被攻击者受到攻击
        CSkill* skill = new CSkill(sType+1, 110, 1);
        CCDelayTime* pDelay1 = CCDelayTime::create(0.1f*iKeyFrame);
        CCAction* pAction = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::attackAction), (void *)skill);
        playerSpr->runAction(CCSequence::create(pDelay1, pAction, NULL));
        
    }
    else if (sType == 4)  //攻击技能5
    {
        int iKeyFrame = 3;
        
        CCAnimation* pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_e");
        if (pAnimation == NULL) {
            pAnimation = CCAnimation::create();
            for (int i=1; i<=4; i++)
            {
                CCString* pFileName = CCString::createWithFormat("skill/e%04d.png", i);
                pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                if (i == iKeyFrame) {
                    for (int k=0; k<2; k++) {
                        pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                    }
                }
            }
            pAnimation->setRestoreOriginalFrame(true);
            pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
            pAnimation->setLoops(1);
            CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_e");
        }
        CCAnimate* pAnimate = CCAnimate::create(pAnimation);
        CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::didAction), NULL);
        playerSpr->runAction(CCSequence::create(pAnimate, pStop, NULL));
        
        //通知被攻击者受到攻击
        CCDelayTime* pDelay1 = CCDelayTime::create(0.1f*iKeyFrame);
        CSkill* skill = new CSkill(sType+1, 120, 1);
        CCAction* pAction = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::attackAction), (void *)skill);
        playerSpr->runAction(CCSequence::create(pDelay1, pAction, NULL));
    }
    else if (sType == 5)  //攻击技能6
    {
        int iKeyFrame = 3;
        
        CCAnimation* pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_f");
        if (pAnimation == NULL) {
            pAnimation = CCAnimation::create();
            for (int i=1; i<=4; i++)
            {
                CCString* pFileName = CCString::createWithFormat("skill/f%04d.png", i);
                pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                if (i == iKeyFrame) {
                    for (int k=0; k<2; k++) {
                        pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                    }
                }
            }
            pAnimation->setRestoreOriginalFrame(true);
            pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
            pAnimation->setLoops(1);
            CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_f");
        }
        CCAnimate* pAnimate = CCAnimate::create(pAnimation);
        CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::didAction), NULL);
        playerSpr->runAction(CCSequence::create(pAnimate, pStop, NULL));
        
        //通知被攻击者受到攻击
        CCDelayTime* pDelay1 = CCDelayTime::create(0.1f*iKeyFrame);
        CSkill* skill = new CSkill(sType+1, 130, 1);
        CCAction* pAction = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::attackAction), (void *)skill);
        playerSpr->runAction(CCSequence::create(pDelay1, pAction, NULL));
    }
    else if (sType == 6)  //攻击技能7
    {
        int iKeyFrame = 2;
        
        CCAnimation* pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_g");
        if (pAnimation == NULL) {
            pAnimation = CCAnimation::create();
            for (int i=1; i<=4; i++)
            {
                CCString* pFileName = CCString::createWithFormat("skill/g%04d.png", i);
                pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                if (i == iKeyFrame) {
                    for (int k=0; k<2; k++) {
                        pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                    }
                }
            }
            pAnimation->setRestoreOriginalFrame(true);
            pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
            pAnimation->setLoops(1);
            CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_g");
        }
        CCAnimate* pAnimate = CCAnimate::create(pAnimation);
        CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::didAction), NULL);
        playerSpr->runAction(CCSequence::create(pAnimate, pStop, NULL));
        
        //通知被攻击者受到攻击
        CCDelayTime* pDelay1 = CCDelayTime::create(0.1f*iKeyFrame);
        CSkill* skill = new CSkill(sType+1, 140, 1);
        CCAction* pAction = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::attackAction), (void *)skill);
        playerSpr->runAction(CCSequence::create(pDelay1, pAction, NULL));
    }
    else if (sType == 7)  //攻击技能8
    {
        CCLog("postionX:%f", playerSpr->getPositionX());
        
        int iKeyFrame = 3;
        
        CCAnimation* pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_h");
        if (pAnimation == NULL) {
            pAnimation = CCAnimation::create();
            for (int i=1; i<=4; i++)
            {
                CCString* pFileName = CCString::createWithFormat("skill/h%04d.png", i);
                pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                if (i == iKeyFrame) {
                    for (int k=0; k<2; k++) {
                        pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                    }
                }
            }
            pAnimation->setRestoreOriginalFrame(true);
            pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
            pAnimation->setLoops(1);
            CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_h");
        }
        CCAnimate* pAnimate = CCAnimate::create(pAnimation);
        CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::didAction), NULL);
        playerSpr->runAction(CCSequence::create(pAnimate, pStop, NULL));
        
        //通知被攻击者受到攻击
        CCDelayTime* pDelay1 = CCDelayTime::create(0.1f*iKeyFrame);
        CSkill* skill = new CSkill(sType+1, 150, 1, 80);
        CCAction* pAction = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::attackAction), (void *)skill);
        playerSpr->runAction(CCSequence::create(pDelay1, pAction, NULL));
    }
    else if (sType == 8)  //攻击技能9
    {
        CCLog("postionX:%f", playerSpr->getPositionX());
//        playerSpr->setPosition( ccp(playerSpr->getPositionX()+80, playerSpr->getPositionY()) );
//        curPos.x += 80;
        
        int iKeyFrame = 4;
        
        CCAnimation* pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_i");
        if (pAnimation == NULL) {
            pAnimation = CCAnimation::create();
            for (int i=1; i<=4; i++)
            {
                CCString* pFileName = CCString::createWithFormat("skill/i%04d.png", i);
                pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                if (i == iKeyFrame) {
                    for (int k=0; k<2; k++) {
                        pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                    }
                }
            }
            pAnimation->setRestoreOriginalFrame(true);
            pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
            pAnimation->setLoops(1);
            CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_i");
        }
        CCAnimate* pAnimate = CCAnimate::create(pAnimation);
        CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::didAction), NULL);
        playerSpr->runAction(CCSequence::create(pAnimate, pStop, NULL));
        
        //通知被攻击者受到攻击
        CCDelayTime* pDelay1 = CCDelayTime::create(0.1f*iKeyFrame);
        CSkill* skill = new CSkill(sType+1, 160, 1, 80);
        CCAction* pAction = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::attackAction), (void *)skill);
        playerSpr->runAction(CCSequence::create(pDelay1, pAction, NULL));
    }
    else if (sType == 9) //攻击技能10
    {
        CCLog("postionX:%f", playerSpr->getPositionX());
//        playerSpr->setPosition( ccp(playerSpr->getPositionX()+160, playerSpr->getPositionY()) );
//        curPos.x += 160;
        
        int iKeyFrame1 = 2;
        int iKeyFrame2 = 5;
        
        CCAnimation* pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_j");
        if (pAnimation == NULL) {
            pAnimation = CCAnimation::create();
            for (int i=1; i<=8; i++)
            {
                CCString* pFileName = CCString::createWithFormat("skill/j%04d.png", i);
                pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                if (i==iKeyFrame1 || i==iKeyFrame2) {
                    for (int k=0; k<2; k++) {
                        pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                    }
                }
            }
            pAnimation->setRestoreOriginalFrame(true);
            pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
            pAnimation->setLoops(1);
            CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_j");
        }
        CCAnimate* pAnimate = CCAnimate::create(pAnimation);
        CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::didAction), NULL);
        playerSpr->runAction(CCSequence::create(pAnimate, pStop, NULL));
        
        //抛物线攻击轨迹
        {
            CCJumpBy* jumpBy = CCJumpBy::create(0.1f*pAnimation->getFrames()->count(), ccp(0, 0), 40, 1);
            playerSpr->runAction(jumpBy);
        }
        
        //通知被攻击者受到攻击
        CSkill* skill = new CSkill(sType+1, 200, 2, 80);
        CCDelayTime* pDelay1 = CCDelayTime::create(0.1f*iKeyFrame1);
        CCAction* pAction1 = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::attackAction), (void *)skill);
        CCDelayTime* pDelay2 = CCDelayTime::create(0.1f*iKeyFrame2+0.1f*2);
        CCAction* pAction2 = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::attackAction), (void *)skill);
        playerSpr->runAction(CCSequence::create(pDelay1, pAction1, pDelay2, pAction2, NULL));
    }
}

void RoleObj::beHit(int sid, int damage)
{
    float hurt = damage;
    
    curHealth -= hurt;
    if (curDir == DIRECTION_LEFT) {
        healthProgressTimer->setMidpoint( ccp(1, 1) );
    } else {
        healthProgressTimer->setMidpoint( ccp(0, 1) );
    }
    //减血动画
    CCProgressFromTo* fromTo = CCProgressFromTo::create(0.5f, (curHealth+hurt)*1.0f/totalHealth*100, curHealth*1.0f/totalHealth*100);
    healthProgressTimer->runAction(fromTo);
    
    CCString* str = CCString::createWithFormat("-%d", (int)hurt);
    CCLabelBMFont* pLabel = CCLabelBMFont::create(str->getCString(), "fight_damage.fnt");
    pLabel->setAnchorPoint(ccp(0.5, 0.5));
    pLabel->setPosition(ccp(playerSpr->getPositionX(), playerSpr->getPositionY()+30));
    superLayer->addChild(pLabel);
    CCMoveBy* pMove = CCMoveBy::create(0.5f, ccp(0, 120));
    CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(RoleObj::hurtActionDidFinished), NULL);
    pLabel->runAction(CCSequence::create(pMove, pStop, NULL));
    CCFadeOut* pFade = CCFadeOut::create(0.5f);
    pLabel->runAction(pFade);
    
    if (sid == 0) {
        //受普通攻击动画
        CCAnimation* pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_behit_0");
        if (pAnimation == NULL) {
            pAnimation = CCAnimation::create();
            for (int i=1; i<=3; i++)
            {
                CCString* pFileName = CCString::createWithFormat("behit/n%04d.png", i);
                pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
            }
            pAnimation->setRestoreOriginalFrame(true);
            pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
            pAnimation->setLoops(1);
            CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_behit_0");
        }
        CCAnimate* pAnimate = CCAnimate::create(pAnimation);
        CCAction* pAct = CCCallFuncND::create(this, callfuncND_selector(RoleObj::didAction), NULL);
        playerSpr->runAction(CCSequence::create(pAnimate, pAct, NULL));
        
    } else {
        //受重击动画
        CCAnimation* pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_behit_1");
        if (pAnimation == NULL) {
            pAnimation = CCAnimation::create();
            for (int i=1; i<=5; i++)
            {
                CCString* pFileName = CCString::createWithFormat("behit/n%04d.png", 1);
                pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
            } //补偿动画
            for (int i=0; i<=6; i++)
            {
                CCString* pFileName = CCString::createWithFormat("behit/r%04d.png", i);
                pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
            }
            pAnimation->setRestoreOriginalFrame(true);
            pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
            pAnimation->setLoops(1);
            CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_behit_1");
        }
        CCAnimate* pAnimate = CCAnimate::create(pAnimation);
        CCAction* pAct = CCCallFuncND::create(this, callfuncND_selector(RoleObj::behitDidFinished), NULL);
        playerSpr->runAction(CCSequence::create(pAnimate, pAct, NULL));
        
        {
            CCJumpBy* jumpBy = CCJumpBy::create(0.1f*pAnimation->getFrames()->count(), ccp(0, 0), 60, 1);
            playerSpr->runAction(jumpBy);
        }
    }
}

void RoleObj::behitDidFinished(cocos2d::CCObject *object, void *param)
{
    CCAnimation* pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_behit_wait");
    if (pAnimation == NULL) {
        pAnimation = CCAnimation::create();
        for (int i=2; i<=8; i++)
        {
            CCString* pFileName = CCString::createWithFormat("dead/s%04d.png", 4);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
        }
        pAnimation->setRestoreOriginalFrame(true);
        pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
        pAnimation->setLoops(1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_behit_wait");
    }
    CCAnimate* pAnimate = CCAnimate::create(pAnimation);
    CCAction* pAct = CCCallFuncND::create(this, callfuncND_selector(RoleObj::didAction), NULL);
    playerSpr->runAction(CCSequence::create(pAnimate, pAct, NULL));
}

void RoleObj::dead(int sid)
{
    CCAnimation* pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_dead");
    if (pAnimation == NULL) {
        pAnimation = CCAnimation::create();
        for (int i=0; i<5; i++)
        {
            CCString* pFileName = CCString::createWithFormat("dead/s%04d.png", i);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
        }
        pAnimation->setRestoreOriginalFrame(true);
        pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
        pAnimation->setLoops(1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_dead");
    }
    CCAnimate* pAnimate = CCAnimate::create(pAnimation);
    CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(RoleObj::deadActionDidFinished), NULL);
    playerSpr->runAction(CCSequence::create(pAnimate, pStop, NULL));
}

void RoleObj::fightWin(int sid)
{
    CCAnimation* pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_win");
    if (pAnimation == NULL) {
        pAnimation = CCAnimation::create();
        for (int i=1; i<=3; i++)
        {
            CCString* pFileName = CCString::createWithFormat("win/1%04d.png", i);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
        }
        pAnimation->setRestoreOriginalFrame(true);
        pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
        pAnimation->setLoops(1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_win");
    }
    CCAnimate* pAnimate = CCAnimate::create(pAnimation);
    CCAction* repeatAction = CCRepeatForever::create(pAnimate);
    playerSpr->runAction(repeatAction);
}

void RoleObj::hurtActionDidFinished(CCObject *object, void *param)
{
    ((CCLabelTTF *)object)->removeFromParent();
//    if (mDelegate) {
//        mDelegate->actionFrameDidFinished(this, STATUS_BEHIT);
//    }
}

void RoleObj::deadActionDidFinished(cocos2d::CCObject *object, void *param)
{
    playerSpr->setTexture(CCSpriteFrame::create("dead/s0002.png", CCRectMake(0, 0, 700, 700))->getTexture());
//    playerSpr->removeFromParent();
}

void RoleObj::hiddenHealthBar()
{
    healthBgSpr->setVisible(false);
    healthProgressTimer->setVisible(false);
}
