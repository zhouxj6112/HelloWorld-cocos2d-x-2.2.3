//
//  FightLayer.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-9-1.
//
//

#include "FightLayer.h"
#include "BattleResultLayer.h"
#include "RoleObj.h"
#include "GameSoundManager.h"
#include "AnimationManager.h"

bool FightLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //左边
    _role = new RoleObj(this);
    _role->init();
//    _role->setDelegate(this);
    _role->setPosition(150-size.width/2, -80);
    _role->changeToStatus(STATUS_STAND, 0, 0, DIRECTION_RIGHT);
    //右边
    _boss = new RoleObj(this);
    _boss->init();
//    _boss->setDelegate(this);
    _boss->setPosition(size.width/2-150, -80);
    _boss->changeToStatus(STATUS_STAND, 0, 0, DIRECTION_LEFT);
    {
        _role->healthBgSpr->setPosition( ccp(-size.width/2+90, 180) );
        _boss->healthBgSpr->setPosition( ccp(size.width/2-90, 180) );
    }
    
    atkNumber = CCLabelBMFont::create("0", "fight_damage.fnt");
    this->addChild(atkNumber);
    atkNumber->setVisible(false);
    
    return true;
}

FightLayer::FightLayer()
{
}
FightLayer::~FightLayer()
{
    delete _role;
    delete _boss;
}

void FightLayer::releaseResource()
{
    delete _role;
    delete _boss;
}

void FightLayer::setDelegate(FightLayerDelegate* delegate)
{
    mDelegate = delegate;
}

static int role_attack_count = 0;
static int boss_attack_count = 0;

void FightLayer::attackProcedure(int attack_count, int counter_attack_count)
{
    attack_count = 10;
    counter_attack_count = 5;
    
    roleAttackCount = attack_count;
    bossAttackCount = counter_attack_count;
    role_attack_count = attack_count;
    boss_attack_count = counter_attack_count;
    
    CCLOG("attackProcedure");
    
    //开始主角的攻击
    if (roleAttackCount > 0) {
        //
        _role->changeToStatus(STATUS_RUN, 0, +200);
        //
    } else {
        //
        this->attackBackProcedure(NULL, NULL);
    }
}
                            
void FightLayer::runActionDidFinished(CCObject* object, void* param)
{
    atkNumber->setVisible(true);
    atkNumber->setString(CCString::createWithFormat("%d", role_attack_count-roleAttackCount+1)->getCString(), true);
    _role->changeToStatus(STATUS_ATTACK, 0, role_attack_count-roleAttackCount);
}

void FightLayer::attackActionDidFinished(CCObject* object, void* param)
{
//    _boss->changeToStatus(STATUS_BEHIT, 100);
    
    roleAttackCount--;
    
    _role->playerSpr->stopAllActions();
    
    if (_boss->curHealth <= 0) {
        CCLOG("BOSS挂了");
        _role->changeToStatus(STATUS_WIN);
        //攻击方开始回归原位动画
        CCMoveTo* pMove = CCMoveTo::create(0.5f, _role->curPos);
        CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(FightLayer::actionDidFinished), NULL);
        _role->playerSpr->runAction(CCSequence::create(pMove, pStop, NULL));
        //
        _boss->changeToStatus(STATUS_DEATH);
        
        //同时播放KO动画
        this->playKOAnimation();
        
    } else {
        CCLOG("BOSS还没挂");
        
        if (roleAttackCount > 0) {
            //继续攻击
            CCLOG("主角还能攻击");
            this->runActionDidFinished(object, param);
        } else {
            //主角攻击完成,恢复原位
            _role->changeToStatus(STATUS_STAND);
            atkNumber->setVisible(false);
            //攻击方开始回归原位动画
            CCLog("_role curPos:%f %f", _role->curPos.x, _role->curPos.y);
            CCMoveTo* pMove = CCMoveTo::create(0.5f, _role->curPos);
            CCDelayTime* pDelay = CCDelayTime::create(1.0f);
            CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(FightLayer::actionDidFinished), NULL);
            _role->playerSpr->runAction(CCSequence::create(pMove, pDelay, pStop, NULL));
            
            this->stopFightBgAnimation();
        }
    }
}

void FightLayer::moveDidFinished(CCObject* object, void* param)
{
}

void FightLayer::actionDidFinished(CCObject* object, void* param)
{
    if (_boss->curHealth > 0) {
        CCLog("BOSS开始反攻");
        this->attackBackProcedure(object, param);
    } else {
        //通知外部,战斗结束
        this->battleResultShow(object, param);
    }
}

void FightLayer::attackBackProcedure(cocos2d::CCObject *object, void *param)
{
    CCLOG("attackBackProcedure");
    
    //开始BOSS反击
    if (bossAttackCount > 0) { //BOSS有反击的机会
        //
        _boss->changeToStatus(STATUS_RUN, 0, -200, DIRECTION_LEFT);
        
    } else {                   //BOSS没有反击机会
        if (_role->curHealth > 0) {
            _role->changeToStatus(STATUS_STAND);
        }
        if (_boss->curHealth > 0) {
            _boss->changeToStatus(STATUS_STAND, 0, 0, DIRECTION_LEFT);
        }
        
        //攻击结束
        if (mDelegate) {
            mDelegate->fightDidFinished(this);
        }
    }
}

void FightLayer::runBackActionDidFinished(cocos2d::CCObject *object, void *param)
{
    atkNumber->setVisible(true);
    atkNumber->setString(CCString::createWithFormat("%d", boss_attack_count-bossAttackCount+1)->getCString(), true);
    //
    _boss->changeToStatus(STATUS_ATTACK, 0, boss_attack_count-bossAttackCount, DIRECTION_LEFT);
}

void FightLayer::attackBackActionDidFinished(CCObject *object, void *param)
{
//    _role->changeToStatus(STATUS_BEHIT, 50);
    
    bossAttackCount--;
    
    if (_role->curHealth <= 0) {
        CCLOG("您挂了");
        _boss->changeToStatus(STATUS_STAND, 0, 0, DIRECTION_LEFT);
        //开始回归原位动画
        CCMoveTo* pMove = CCMoveTo::create(0.5f, _boss->curPos);
        CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(FightLayer::backActionDidFinished), NULL);
        _boss->playerSpr->runAction(CCSequence::create(pMove, pStop, NULL));
        //
        _role->changeToStatus(STATUS_DEATH);
    } else {
        CCLOG("您还没挂");
        if (bossAttackCount > 0) {
            //BOSS还能继续反击
            CCLOG("BOSS还能继续攻击");
            this->runBackActionDidFinished(object, param);
        } else {
            _boss->changeToStatus(STATUS_STAND, 0, 0, DIRECTION_LEFT);
            atkNumber->setVisible(false);
            
            //开始回归原位动画
            CCMoveTo* pMove = CCMoveTo::create(0.5f, _boss->curPos);
            CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(FightLayer::backActionDidFinished), NULL);
            _boss->playerSpr->runAction(CCSequence::create(pMove, pStop, NULL));
            
            _role->changeToStatus(STATUS_STAND);
        }
    }
}

void FightLayer::backActionDidFinished(CCObject *object, void *param)
{
    if (_role->curHealth > 0) {
        if (mDelegate) {
            mDelegate->fightDidFinished(this);
        }
    } else {
        //通知外部,战斗结束
        this->battleResultShow(object, param);
    }
}

void FightLayer::battleResultShow(CCObject *object, void *param)
{
    if (mDelegate) {
        if (_role->curHealth <= 0) {
            mDelegate->battleOver(this, false);
        } else if (_boss->curHealth <= 0) {
            mDelegate->battleOver(this, true);
        }
        mDelegate = NULL;
    }
}

#pragma mark -
#pragma mark IPlayerObj

void FightLayer::actionFrameDidFinished(PlayerObj* obj, PlayerStatus status)
{
    if (obj->isEqual(_role)) {
        CCLOG("role status:%d", status);
        if (status == STATUS_ATTACK) {
            this->attackActionDidFinished(obj, NULL);
        } else if (status == STATUS_RUN) {
            this->runActionDidFinished(obj, NULL);
        }
    } else if (obj->isEqual(_boss)) {
        CCLOG("boss status:%d", status);
        if (status == STATUS_ATTACK) {
            this->attackBackActionDidFinished(obj, NULL);
        } else if (status == STATUS_RUN) {
            this->runBackActionDidFinished(obj, NULL);
        }
    }
}

void FightLayer::attackCollision(PlayerObj *obj, CSkill* skill)
{
    //播放攻击音效
    GameSoundManager::shareManager()->playAttackEffect(false);
    
    if (obj->isEqual(_role)) {
        if (skill->sid==8 || skill->sid==9) {
            CCLog("boss postionX:%f", _boss->getRotationX());
            
            if (mDelegate != NULL) {
                mDelegate->moveVisibleWindow(this, -(skill->moveDistance), 0);
            }
        } else if (skill->sid == 10) {
            if (role_attack_count>=5 && roleAttackCount==1) {
                if (skill->atkCountEx == 0) {
                    if (mDelegate != NULL) {
                        mDelegate->moveVisibleWindow(this, -(skill->moveDistance), 1.2f);
                    }
                }
            }
            CCLog("skill 10: %f", skill->moveDistance);
        }
        int damage = skill->atkDamage/skill->atkCount;
        if (role_attack_count>=5 && roleAttackCount==1) {
            if (skill->atkCountEx == 0) {
                _boss->changeToStatus(STATUS_BEHIT, 1, damage, DIRECTION_LEFT);
                skill->atkCountEx += 1;
            } else {
                CCLog("_boss已经启用了被攻击的状态");
//                _boss->changeToStatus(STATUS_BEHIT, 0, damage, DIRECTION_LEFT);
//                skill->atkCountEx += 1;
            }
        } else {
            _boss->changeToStatus(STATUS_BEHIT, 0, damage, DIRECTION_LEFT);
        }
    } else if (obj->isEqual(_boss)) {
        int damage = skill->atkDamage/skill->atkCount;
        _role->changeToStatus(STATUS_BEHIT, 0, damage, DIRECTION_RIGHT);
    }
}

void FightLayer::actionWillStart(PlayerObj *obj, PlayerStatus status, int sid)
{
    CCLOG("%d", sid);
    if (status==STATUS_ATTACK && sid==10) {
        this->playFightBgAnimation();
    }
}

void FightLayer::playKOAnimation()
{
    atkNumber->setVisible(false);
    
    CCAnimation* pAnimation = AnimationManager::shareInstance()->getAnimationWithName(str_atk_ko);
    CCAnimate* pAnimate = CCAnimate::create(pAnimation);
    CCAction* pAct = CCCallFuncND::create(this, callfuncND_selector(FightLayer::koDidFinished), NULL);
    CCSprite* spr = CCSprite::create("3001.png");
    spr->setAnchorPoint( ccp(0.5f, 0.5f) );
    spr->setPosition( ccp(0, 0) );
    this->addChild(spr);
    spr->runAction(CCSequence::create(pAnimate, pAct, NULL));
    
    GameSoundManager::shareManager()->playKOEffect();
}

void FightLayer::koDidFinished(cocos2d::CCObject *object, void *param)
{
    ((CCSprite *)object)->removeFromParent();
}

void FightLayer::playFightBgAnimation()
{
    CCAnimation* pAnimation = AnimationManager::shareInstance()->getAnimationWithName(str_atk_bg);
    //
    CCSprite* spr = (CCSprite *)(this->getChildByTag(1234));
    if (spr == NULL) {
        CCSprite* spr = CCSprite::create("1001.png");
        spr->setAnchorPoint( ccp(0.5f, 0.5f) );
        spr->setPosition( ccp(0, 0) );
        spr->cocos2d::CCNode::setScale(this->getContentSize().width/spr->getContentSize().width, this->getContentSize().height/spr->getContentSize().height);
        this->addChild(spr, -1, 1234);
        
        CCAnimate* pAnimate = CCAnimate::create(pAnimation);
        CCAction* repeatAction = CCRepeatForever::create(pAnimate);
        spr->runAction(repeatAction);
        CCLOG("%p", spr);
    }
}

void FightLayer::stopFightBgAnimation()
{
    CCSprite* spr = (CCSprite *)(this->getChildByTag(1234));
    if (spr) {
        spr->stopAllActions();
        spr->removeFromParent();
        CCLOG("%p", spr);
    }
}
