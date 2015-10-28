//
//  RoleObj.h
//  HelloWorld
//
//  Created by MrZhou on 14-10-15.
//
//

#ifndef HelloWorld_RoleObj_h
#define HelloWorld_RoleObj_h

#include "PlayerObj.h"

class RoleObj : public PlayerObj
{
public:
    RoleObj(CCLayer* superLayer);
    virtual bool init();
public:
    virtual void stand(int sid);
    virtual void run(int sid, int distance);
    virtual void attack(int sid, int sType);
    virtual void beHit(int sid, int damage);
    virtual void dead(int sid);
    virtual void fightWin(int sid);
private:
    void hurtActionDidFinished(CCObject* object, void* param);
    void deadActionDidFinished(CCObject* object, void* param);
    //
    void behitDidFinished(CCObject* object, void* param);
public:
    void hiddenHealthBar();
};

#endif
