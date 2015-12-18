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
    
    if (propArray == NULL) {
        propArray = CCArray::createWithCapacity(3);
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
//        {
//            PropItemData* itemData = new PropItemData();
//            itemData->propName = "道具3";
//            itemData->propIndex = 3;
//            itemData->propEffect = "答题延时";
//            itemData->useCount = 2;
//            propArray->addObject(itemData);
//        }
        {
            PropItemData* itemData = new PropItemData();
            itemData->propName = "道具4";
            itemData->propIndex = 4;
            itemData->propEffect = "强行攻击";
            itemData->useCount = 2;
            propArray->addObject(itemData);
        }
    }
    
    for (int i=0; i<propArray->count(); i++) {
        PropItemData* data = (PropItemData *)(propArray->objectAtIndex(i));
        CCLOG("遍历[%d]:%s %d 地址:%p", i, data->propName, data->useCount, data);
    }
    
    PropItemData* itemData1 = (PropItemData *)propArray->objectAtIndex(0);
    CCString* str1 = CCString::createWithFormat("%s(%d个)", itemData1->propName, itemData1->useCount);
    CCMenuItemFont* pMenuItem1 = CCMenuItemFont::create(str1->getCString(), this, menu_selector(FightPropLayer::menuDidSelected));
    pMenuItem1->setFontSizeObj(24);
    pMenuItem1->setColor(cocos2d::ccc3(0,255,255));
    pMenuItem1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/6, 25));
    pMenuItem1->setTag(itemData1->propIndex+1000);
    if (itemData1->useCount <= 0) {
        pMenuItem1->setEnabled(false);
    }
    PropItemData* itemData2 = (PropItemData *)propArray->objectAtIndex(1);
    CCString* str2 = CCString::createWithFormat("%s(%d个)", itemData2->propName, itemData2->useCount);
    CCMenuItemFont* pMenuItem2 = CCMenuItemFont::create(str2->getCString(), this, menu_selector(FightPropLayer::menuDidSelected));
    pMenuItem2->setFontSizeObj(24);
    pMenuItem2->setColor(cocos2d::ccc3(0,255,255));
    pMenuItem2->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/6*3, 25));
    pMenuItem2->setTag(itemData2->propIndex+1000);
    if (itemData2->useCount <= 0) {
        pMenuItem2->setEnabled(false);
    }
    PropItemData* itemData3 = (PropItemData *)propArray->objectAtIndex(2);
    CCString* str3 = CCString::createWithFormat("%s(%d个)", itemData3->propName, itemData3->useCount);
    CCMenuItemFont* pMenuItem3 = CCMenuItemFont::create(str3->getCString(), this, menu_selector(FightPropLayer::menuDidSelected));
    pMenuItem3->setFontSizeObj(24);
    pMenuItem3->setColor(cocos2d::ccc3(0,255,255));
    pMenuItem3->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/6*5, 25));
    pMenuItem3->setTag(itemData3->propIndex+1000);
    if (itemData3->useCount <= 0) {
        pMenuItem3->setEnabled(false);
    }
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pMenuItem1, pMenuItem2, pMenuItem3, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    return true;
}

void FightPropLayer::menuDidSelected(CCObject* pSender)
{
//    for (int i=0; i<propArray->count(); i++) {
//        PropItemData* data = (PropItemData *)(propArray->objectAtIndex(i));
//        CCLOG("遍历[%d]:%s %d 地址:%p", i, data->propName, data->useCount, data);
//    }
    
    CCMenuItemFont* menuItem = (CCMenuItemFont *)pSender;
    if (mDelegate) {
        PropItemData* itemData = NULL;
        for (int i=0; i<propArray->count(); i++) {
            PropItemData* pData = (PropItemData *)propArray->objectAtIndex(i);
            if (pData->propIndex == menuItem->getTag()-1000) {
                itemData = pData;
                break;
            }
        }
        if (itemData->useCount > 0) {
            bool b = mDelegate->useProp(itemData);
            if (!b) {
                return;
            }
        }
        itemData->useCount -= 1;
        menuItem->setString(CCString::createWithFormat("%s-%d个", itemData->propName, itemData->useCount)->getCString());
        menuItem->setFontSizeObj(24);
        
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
