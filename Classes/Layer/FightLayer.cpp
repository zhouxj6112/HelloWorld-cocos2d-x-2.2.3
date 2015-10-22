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

bool FightLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //战斗背景
    CCScale9Sprite* bgSpr = CCScale9Sprite::create("PortTown.jpg");
    bgSpr->setAnchorPoint( ccp(0.5, 0.5) );
    bgSpr->setContentSize( CCSizeMake(size.height*5/12*2, size.height*5/12) );
    this->addChild(bgSpr, -1);
//    CCScale9Sprite* leftBgSpr = CCScale9Sprite::create("PortTown.jpg");
//    leftBgSpr->setAnchorPoint( ccp(-0.5, 0.5) );
//    leftBgSpr->setContentSize( CCSizeMake(size.width, size.height*5/12) );
//    this->addChild(leftBgSpr, -1);
//    CCScale9Sprite* rightBgSpr = CCScale9Sprite::create("PortTown.jpg");
//    rightBgSpr->setAnchorPoint( ccp(1.5, 0.5) );
//    rightBgSpr->setContentSize( CCSizeMake(size.width, size.height*5/12) );
//    this->addChild(rightBgSpr, -1);
    
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
    atkNumber->setString(CCString::createWithFormat("%d", roleAttackCount)->getCString(), true);
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
            CCMoveTo* pMove = CCMoveTo::create(0.5f, _role->curPos);
            CCDelayTime* pDelay = CCDelayTime::create(1.0f);
            CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(FightLayer::actionDidFinished), NULL);
            _role->playerSpr->runAction(CCSequence::create(pMove, pDelay, pStop, NULL));
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
         float f = _boss->curPos.x-(_role->curPos.x);
        _boss->changeToStatus(STATUS_RUN, 0, -f, DIRECTION_LEFT);
        
    } else {                   //BOSS被击晕,没有反击机会
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
    atkNumber->setString(CCString::createWithFormat("%d", bossAttackCount)->getCString(), true);
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
        int damage = skill->atkDamage/skill->atkCount;
        if (role_attack_count>=5 && roleAttackCount==1) {
            _boss->changeToStatus(STATUS_BEHIT, 1, damage, DIRECTION_LEFT);
        } else {
            _boss->changeToStatus(STATUS_BEHIT, 0, damage, DIRECTION_LEFT);
        }
        if (skill->sid==8 || skill->sid==9) {
            CCLog("boss postionX:%f", _boss->getRotationX());
//            _boss->playerSpr->setPosition( ccp(_boss->playerSpr->getPositionX()+skill->moveDistance, _boss->playerSpr->getPositionY()) );
            _boss->setPosition(_boss->curPos.x+skill->moveDistance, _boss->curPos.y);

            atkNumber->setPosition( ccp(atkNumber->getPositionX()+skill->moveDistance, atkNumber->getPositionY()) );
            
            if (mDelegate != NULL) {
                mDelegate->moveVisibleWindow(this, -(skill->moveDistance));
            }
        } else if (skill->sid == 10) {
            if (mDelegate != NULL) {
                mDelegate->moveVisibleWindow(this, -(skill->moveDistance));
            }
        }
    } else if (obj->isEqual(_boss)) {
        int damage = skill->atkDamage/skill->atkCount;
        _role->changeToStatus(STATUS_BEHIT, 0, damage, DIRECTION_RIGHT);
    }
}
