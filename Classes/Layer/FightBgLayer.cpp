//
//  FightBgLayer.cpp
//  HelloWorld
//
//  Created by MrZhou on 15-10-26.
//
//

#include "FightBgLayer.h"

#include "cocos-ext.h"
USING_NS_CC_EXT;

bool FightBgLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //战斗背景
    CCScale9Sprite* bgSpr = CCScale9Sprite::create("PortTown.jpg");
    bgSpr->setAnchorPoint( ccp(0.5, 0.5) );
    bgSpr->setPosition( ccp (0, 0) );
    bgSpr->setContentSize( CCSizeMake(size.height*5/12*2, size.height*5/12) );
    this->addChild(bgSpr, -1);
    CCScale9Sprite* leftBgSpr = CCScale9Sprite::create("PortTown.jpg");
    leftBgSpr->setAnchorPoint( ccp(0.5, 0.5) );
    leftBgSpr->setPosition( ccp(-size.height*5/12*2, 0) );
    leftBgSpr->setContentSize( CCSizeMake(size.height*5/12*2, size.height*5/12) );
    this->addChild(leftBgSpr, -1);
    CCScale9Sprite* rightBgSpr = CCScale9Sprite::create("PortTown.jpg");
    rightBgSpr->setAnchorPoint( ccp(0.5, 0.5) );
    rightBgSpr->setPosition( ccp(size.height*5/12*2, 0) );
    rightBgSpr->setContentSize( CCSizeMake(size.height*5/12*2, size.height*5/12) );
    this->addChild(rightBgSpr, -1);
    
    return true;
}

void FightBgLayer::moveBgLayer(float deltaX, float moveTime)
{
    CCMoveBy* pMove = CCMoveBy::create(moveTime, ccp(deltaX, 0) );
    this->runAction(pMove);
}
