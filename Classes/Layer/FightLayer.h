//
//  FightLayer.h
//  HelloWorld
//
//  Created by MrZhou on 14-9-1.
//
//

#ifndef HelloWorld_FightLayer_h
#define HelloWorld_FightLayer_h

#include "cocos2d.h"
USING_NS_CC;

#include "RoleObj.h"
#include "BossObj.h"

class FightLayer;

class CC_DLL FightLayerDelegate
{
public:
    //回调函数
    virtual void fightDidFinished(FightLayer* layer) = 0;
    virtual void battleOver(FightLayer* layer, bool isWin) = 0;
    virtual void moveVisibleWindow(FightLayer* layer, float deltaX, float time) = 0;
};

class FightLayer : public CCLayer, public IPlayerObj
{
public:
    PlayerObj* _role;
    PlayerObj* _boss;
    void releaseResource();
    //
private:
    FightLayerDelegate* mDelegate;
    FightLayer();
    virtual ~FightLayer();
    
public:
    CREATE_FUNC(FightLayer);
    virtual bool init();
    void setDelegate(FightLayerDelegate* delegate);
    
    //role开始攻击过程
    void attackProcedure(int attack_count, int counter_attack_count);
    void runActionDidFinished(CCObject* object, void* param);
    void attackActionDidFinished(CCObject* object, void* param);
    void actionDidFinished(CCObject* object, void* param);
    void moveDidFinished(CCObject* object, void* param);
    //boss反击过程
    void attackBackProcedure(CCObject* object, void* param);
    void runBackActionDidFinished(CCObject* object, void* param);
    void attackBackActionDidFinished(CCObject* object, void* param);
    void backActionDidFinished(CCObject* object, void* param);
    
    void battleResultShow(CCObject* object, void* param);
    //IPlayerObj
    virtual void actionFrameDidFinished(PlayerObj* obj, PlayerStatus status);
    virtual void attackCollision(PlayerObj* obj, CSkill* skill);
    virtual void actionWillStart(PlayerObj* obj, PlayerStatus status, int sid);
private:
    //攻击剩余次数
    int roleAttackCount;
    int bossAttackCount;
    //剩余攻击次数展示图层
    CCLabelBMFont* atkNumber;
    
    void playKOAnimation();
    void playFightBgAnimation();
    void stopFightBgAnimation();
    
    void koDidFinished(CCObject* object, void* param);
};

#endif
