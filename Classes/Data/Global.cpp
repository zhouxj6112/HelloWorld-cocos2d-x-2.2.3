//
//  Global.cpp
//  HelloWorld
//
//  Created by MrZhou on 15-1-2.
//
//

#include "Global.h"
#include "cocos2d.h"
USING_NS_CC;

static Global* global;

Global::Global()
{
    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
    userName = userDefault->getStringForKey("user_name", "玩家昵称").c_str();
    userLevel = userDefault->getIntegerForKey("user_level", 1);
    userExp = userDefault->getIntegerForKey("user_level", 0);
    gender = userDefault->getIntegerForKey("user_level", 0);
    //
    missionGate = userDefault->getIntegerForKey("mission_gate", 0);
    smallMissionGate = userDefault->getIntegerForKey("small_mission_gate", 8);
}
Global::~Global()
{
}

Global* Global::shareInstance()
{
    if (global == NULL) {
        global = new Global();
    }
    return global;
}
