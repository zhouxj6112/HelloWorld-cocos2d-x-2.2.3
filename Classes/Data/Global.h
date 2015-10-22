//
//  Global.h
//  HelloWorld
//
//  Created by MrZhou on 15-1-2.
//
//

#ifndef HelloWorld_Global_h
#define HelloWorld_Global_h

#include "cocos2d.h"

class Global : public cocos2d::CCObject
{
private:
    Global();
    virtual ~Global();
public:
    static Global* shareInstance();
    const char* userName;
    int gender;
    int userLevel;
    int userExp;
    //
    int missionGate;
    int smallMissionGate;
};

#endif
