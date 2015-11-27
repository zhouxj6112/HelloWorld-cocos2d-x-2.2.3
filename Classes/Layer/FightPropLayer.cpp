//
//  FightPropLayer.cpp
//  HelloWorld
//
//  Created by MrZhou on 15/11/27.
//
//

#include "FightPropLayer.h"

#include "cocos-ext.h"
USING_NS_CC_EXT;

bool FightPropLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    return true;
}

//道具有以下几个
//1.更换题目：使用后可以立即更换一条题目。（并且答题时间恢复初始）
//2.正确答案：使用后可以自动选定一道正确答案。
//3.答题延时：使用后道题时间恢复初始。
//4.强行攻击：使用后在没有回答完5道题流程时候，直接攻击对手。
//攻击逻辑是，玩家在使用道具前答对了多少题，就攻击多少下。
//如果是第一道题时候，则不可以使用强攻。
//如果是第二道题时候使用，则攻击一下。
//5.绝地反击：正在被对手攻击时候，使用道具可以出招反击对手。逻辑是点击反击道具角色使用飞脚将
//敌人踢飞。（就使用十连击最后的两招飞腿）刚好破坏了对手的进攻回合。为自己获得下一次
//攻击机会。