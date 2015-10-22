//
//  BattleResultLayer.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-12-11.
//
//

#include "BattleResultLayer.h"

BattleResultLayer::BattleResultLayer()
{
}

BattleResultLayer::~BattleResultLayer()
{
}

bool BattleResultLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    CCLabelTTF* pLabel = CCLabelTTF::create("你赢了", "Arial", 24);
    pLabel->setPosition(ccp(100, 100));
    this->addChild(pLabel, 1);
    CCMoveTo* moveTo = CCMoveTo::create(1.0f, ccp(300, 300));
    CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(BattleResultLayer::runActionDidFinished), NULL);
    pLabel->runAction(CCSequence::create(moveTo, pStop, NULL));
    
    return true;
}

void BattleResultLayer::runActionDidFinished(cocos2d::CCObject *object, void *param)
{
    if (mDelegate) {
        mDelegate->animationDidFinished(this);
    }
}
