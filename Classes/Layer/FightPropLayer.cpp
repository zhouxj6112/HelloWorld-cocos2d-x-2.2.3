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
    
    propArray = CCArray::createWithCapacity(2);
    propArray->retain();
    {
        PropItemData* itemData = new PropItemData();
        itemData->propName = "道具1";
        itemData->propIndex = 1;
        itemData->propEffect = "跳过本道题目";
        itemData->useCount = 2;
        propArray->addObject(itemData);
    }
    {
        PropItemData* itemData = new PropItemData();
        itemData->propName = "道具2";
        itemData->propIndex = 2;
        itemData->propEffect = "选取正确答案";
        itemData->useCount = 2;
        propArray->addObject(itemData);
    }
    
    PropItemData* itemData1 = (PropItemData *)propArray->objectAtIndex(0);
    CCString* str1 = CCString::createWithFormat("%s-%d个", itemData1->propName, itemData1->useCount);
    CCMenuItemFont* pMenuItem1 = CCMenuItemFont::create(str1->getCString(), this, menu_selector(FightPropLayer::menuDidSelected));
    pMenuItem1->setFontSizeObj(24);
    pMenuItem1->setColor(cocos2d::ccc3(0,255,255));
    pMenuItem1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/4, 30));
    pMenuItem1->setTag(itemData1->propIndex+1000);
    PropItemData* itemData2 = (PropItemData *)propArray->objectAtIndex(1);
    CCString* str2 = CCString::createWithFormat("%s-%d个", itemData2->propName, itemData2->useCount);
    CCMenuItemFont* pMenuItem2 = CCMenuItemFont::create(str2->getCString(), this, menu_selector(FightPropLayer::menuDidSelected));
    pMenuItem2->setFontSizeObj(24);
    pMenuItem2->setColor(cocos2d::ccc3(0,255,255));
    pMenuItem2->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/4*3, 30));
    pMenuItem2->setTag(itemData2->propIndex+1000);
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pMenuItem1, pMenuItem2, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    return true;
}

void FightPropLayer::menuDidSelected(CCObject* pSender)
{
    CCMenuItem* menuItem = (CCMenuItem *)pSender;
    if (mDelegate) {
        PropItemData* itemData = (PropItemData *)propArray->objectAtIndex(menuItem->getTag()-1001);
        if (itemData->useCount > 0) {
            mDelegate->useProp(itemData);
        }
        itemData->useCount -= 1;
        if (itemData->useCount <= 0) {
            menuItem->setEnabled(false);
        }
    }
}

void FightPropLayer::setDelegate(FightPropLayerDelegate* delegate)
{
    mDelegate = delegate;
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
