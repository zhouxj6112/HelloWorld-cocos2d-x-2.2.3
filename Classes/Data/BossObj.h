//
//  BossObj.h
//  HelloWorld
//
//  Created by MrZhou on 14-10-15.
//
//

#ifndef HelloWorld_BossObj_h
#define HelloWorld_BossObj_h

#include "PlayerObj.h"

class BossObj : public PlayerObj
{
public:
    BossObj(CCLayer* superLayer);
    virtual bool init();
public:
    virtual void stand();
    virtual void run(int distance);
    virtual void attack(int sType);
    virtual void beHit(int damage);
    virtual void dead();
    virtual void fightWin(int sid);
private:
    void hurtActionDidFinished(CCObject* object, void* param);
    void deadActionDidFinished(CCObject* object, void* param);
};

#endif
