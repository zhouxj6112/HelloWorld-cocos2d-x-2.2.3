//
//  PlayerObj.h
//  HelloWorld
//
//  Created by MrZhou on 14-10-14.
//
//

#ifndef HelloWorld_PlayerObj_h
#define HelloWorld_PlayerObj_h

#include "cocos2d.h"
USING_NS_CC;

//攻击技能
class CSkill
{
public:
    int sid;
    const char* sName;
    int atkCount;  //攻击次数
    int atkDamage; //总伤害值
    float moveDistance; //技能攻击前进距离
    int atkCountEx;//已经攻击的次数
    //实例化
    CSkill(int sid, int damage, int count, float distance=0)
    {
        this->sid = sid;
        atkCount = count;
        atkDamage = damage;
        moveDistance = distance;
        atkCountEx = 0;
    }
};

typedef enum _PlayerStatus {
    STATUS_STAND = 0,  //站立
    STATUS_RUN = 1,    //跑动
    STATUS_ATTACK = 2, //攻击
    STATUS_BEHIT = 3,  //被攻击
    STATUS_WIN = 4,    //胜利
    STATUS_DEATH = 5   //死亡
} PlayerStatus;

typedef enum {
    DIRECTION_RIGHT = 1,
    DIRECTION_DOWN  = 2,
    DIRECTION_LEFT  = 3,
    DIRECTION_UP    = 4
} PlayerDirection;

class PlayerObj;

class CC_DLL IPlayerObj
{
public:
    virtual void actionFrameDidFinished(PlayerObj* obj, PlayerStatus status) = 0;
    virtual void attackCollision(PlayerObj* obj, CSkill* skill) = 0;
};

#define animation_delay_perUnit 0.05f

class PlayerObj : public cocos2d::CCNode
{
public:
    CCLayer* superLayer;
    cocos2d::CCSprite* playerSpr; //角色动画
    char* playerName;
    int totalHealth;              //总血量
    int curHealth;                //当前血量
    PlayerStatus curStatus;       //当前状态
    PlayerDirection curDir;       //角色朝向
    CCPoint curPos;
    cocos2d::CCSprite* healthBgSpr;
    cocos2d::CCProgressTimer* healthProgressTimer;
    //
    IPlayerObj* mDelegate;
    void setDelegate(IPlayerObj* delegate);
public:
    PlayerObj();
    PlayerObj(CCLayer* superLayer);
    virtual ~PlayerObj();
    //
    virtual bool init();
    virtual void preLoadResource() {};
    //改变角色状态
    void changeToStatus(PlayerStatus status, int sid=0, int sType=0, PlayerDirection dir=DIRECTION_RIGHT);
    //
    void setPosition(float x, float y);
public:
    virtual void stand(int sid = 0) {};
    virtual void run(int sid, int distance) {};
    virtual void attack(int sid, int sType) {};
    virtual void beHit(int sid, int damage) {};
    virtual void dead(int sid = 0) {};
    virtual void fightWin(int sid = 0) {};
    //
    void didAction(cocos2d::CCObject* object, void* param);
    void attackAction(cocos2d::CCObject* object, void* param);
private:
    void boomActionDidFinished(cocos2d::CCObject* object, void* param);
};

#endif
