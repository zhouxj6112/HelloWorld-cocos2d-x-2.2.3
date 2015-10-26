//
//  PlayerObj.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-10-14.
//
//

#include "PlayerObj.h"

USING_NS_CC;

PlayerObj::PlayerObj()
{
}
PlayerObj::PlayerObj(CCLayer* superLayer)
{
    playerSpr = NULL;
    this->superLayer = superLayer;
    
    healthBgSpr = CCSprite::create("bg_bar_health.png");
    healthBgSpr->setAnchorPoint( ccp(0.5, 0.5) );
    healthBgSpr->setPosition( ccp(0, 0) );
    superLayer->addChild(healthBgSpr);
    //
    healthProgressTimer = CCProgressTimer::create(CCSprite::create("bar_health.png"));
    healthProgressTimer->setType(kCCProgressTimerTypeBar);
    healthProgressTimer->setPercentage(100);
    healthProgressTimer->setMidpoint(ccp(1, 0));
    healthProgressTimer->setBarChangeRate(ccp(1, 0));
    healthProgressTimer->setAnchorPoint(ccp(0, 0));
    healthProgressTimer->setPosition(ccp(5, 5));
    healthBgSpr->addChild(healthProgressTimer);
    
    mDelegate = dynamic_cast<IPlayerObj *>(superLayer);
}
PlayerObj::~PlayerObj()
{
    playerSpr->stopAllActions();
    
    mDelegate = NULL;
}

bool PlayerObj::init()
{
    this->preLoadResource();
    
    return true;
}

void PlayerObj::setDelegate(IPlayerObj* delegate)
{
    mDelegate = delegate;
}

void PlayerObj::changeToStatus(PlayerStatus status, int sid, int sType, PlayerDirection dir)
{
    if (playerSpr!=NULL && playerSpr->numberOfRunningActions()>0) {
        playerSpr->stopAllActions();
    }
    curDir = dir;
    if (status == STATUS_STAND) {
        this->stand(sid);
    } else if (status == STATUS_RUN) {
        this->run(sid, sType);    //sType移动距离
    } else if (status == STATUS_ATTACK) {
        this->attack(sid, sType); //sType攻击技能类别
    } else if (status == STATUS_BEHIT) {
        this->beHit(sid, sType);  //sType受攻击的伤害值
    } else if (status == STATUS_DEATH) {
        this->dead(sid);
    } else if (status == STATUS_WIN) {
        this->fightWin(sid);
    }
    curStatus = status;
}

void PlayerObj::setPosition(float x, float y)
{
    curPos = ccp(x, y);
//    if (healthBgSpr) {
//        healthBgSpr->setPosition( ccp(x, y-100) );
//    }
    if (playerSpr) {
        playerSpr->setPosition( ccp(x, y) );
    }
}

void PlayerObj::didAction(cocos2d::CCObject *object, void *param)
{
    if (mDelegate != NULL) {
        mDelegate->actionFrameDidFinished(this, curStatus);
    }
}

void PlayerObj::attackAction(cocos2d::CCObject* object, void* param)
{
    if (mDelegate != NULL) {
        CSkill* skill = (CSkill *)param;
        mDelegate->attackCollision(this, skill);
        
        //播放攻击特效
        CCSprite* texiao = CCSprite::create("dianguanghuoshi@2x.png");
        if (this->curDir == DIRECTION_LEFT) {
            texiao->setPosition( ccp(playerSpr->getPositionX()-100-skill->moveDistance, playerSpr->getPositionY()+50) );
        } else {
            texiao->setPosition( ccp(playerSpr->getPositionX()+100+skill->moveDistance, playerSpr->getPositionY()+50) );
        }
        texiao->setScale(0.2f);
        texiao->setAnchorPoint( ccp(0.5f, 0.5f) );
        superLayer->addChild(texiao);
        CCScaleTo* pScaleBy = CCScaleTo::create(0.3f, 0.6f);
        CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(PlayerObj::boomActionDidFinished), NULL);
        texiao->runAction(CCSequence::create(pScaleBy, pStop, NULL));
    }
}

void PlayerObj::boomActionDidFinished(cocos2d::CCObject *object, void *param)
{
    ((CCSprite *)object)->removeFromParent();
}
