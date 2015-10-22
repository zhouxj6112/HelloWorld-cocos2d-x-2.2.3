//
//  HomeLayer.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-8-18.
//
//

#include "HomeLayer.h"
#include "Global.h"

bool HomeLayer::init()
{
    // 1. super init first
    if (!CCLayer::init())
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* titleSpr = CCSprite::create("title_bg.png");
    titleSpr->setPosition( ccp(10, size.height-140) );
    titleSpr->setAnchorPoint(ccp(0, 0.5f));
    this->addChild(titleSpr);
    
    CCSprite* player = NULL;
    if (Global::shareInstance()->gender == 0) {
        player = CCSprite::create("player_female.png");
    } else {
        player = CCSprite::create("player_male.png");
    }
    player->setPosition(ccp(75, 80));
    player->setAnchorPoint(ccp(0.5f, 0.5f));
    titleSpr->addChild(player);
    
    CCLabelTTF* nameLabel = CCLabelTTF::create(Global::shareInstance()->userName, "STHeitiK-Medium", 30);
    nameLabel->setPosition( ccp(220, 120) );
    nameLabel->setAnchorPoint(ccp(0.5f, 0.5f));
    nameLabel->setFontFillColor(ccc3(0, 0, 0));
    nameLabel->enableShadow(CCSizeMake(1, 1), 0.5f, 0.5f);
    titleSpr->addChild(nameLabel);
    //游戏币
    CCSprite* moneyBg = CCSprite::create("money_bg.png");
    moneyBg->setPosition(ccp(500, 120));
    titleSpr->addChild(moneyBg);
    CCSprite* money = CCSprite::create("money_icon.png");
    money->setPosition(ccp(415, 120));
    titleSpr->addChild(money);
    CCSprite* moneyProp = CCSprite::create("money_prop.png");
    moneyProp->setPosition(ccp(595, 120));
    titleSpr->addChild(moneyProp);
    CCLabelTTF* incomeLabel = CCLabelTTF::create("700", "STHeitiK-Medium", 30);
    incomeLabel->setPosition( ccp(500, 120) );
    incomeLabel->setAnchorPoint(ccp(0.5f, 0.5f));
    incomeLabel->setFontFillColor(ccc3(255, 255, 255));
    incomeLabel->enableShadow(CCSizeMake(1, 1), 0.5f, 0.5f);
    titleSpr->addChild(incomeLabel);
    //经验等级
    CCSprite* levelBg = CCSprite::create("bar_bg.png");
    levelBg->setPosition(ccp(350, 56));
    titleSpr->addChild(levelBg);
    CCLabelTTF* levelLabel = CCLabelTTF::create("1级", "STHeitiK-Medium", 30);
    levelLabel->setPosition( ccp(195, 60) );
    levelLabel->setAnchorPoint(ccp(0.5f, 0.5f));
    levelLabel->setFontFillColor(ccc3(0, 0, 0));
    levelLabel->enableShadow(CCSizeMake(1, 1), 0.5f, 0.5f);
    titleSpr->addChild(levelLabel);
    CCLabelTTF* level = CCLabelTTF::create("0/10", "STHeitiK-Medium", 30);
    level->setPosition( ccp(350, 60) );
    level->setAnchorPoint(ccp(0.5f, 0.5f));
    level->setFontFillColor(ccc3(0, 0, 0));
    level->enableShadow(CCSizeMake(1, 1), 0.5f, 0.5f);
    titleSpr->addChild(level);
    
    //三个按钮
    CCLabelTTF* pLabel = CCLabelTTF::create("", "Arial", 24);
    CCControlButton* button = CCControlButton::create(pLabel, CCScale9Sprite::create("to_city.png"));
    button->addTargetWithActionForControlEvents(this, cccontrol_selector(HomeLayer::touchButtonAction), CCControlEventTouchUpInside);
    button->setPosition(ccp(size.width/2, size.height/2+150));
    button->setPreferredSize(CCSizeMake(338, 142));
    this->addChild(button, 1, 10);
    pLabel = CCLabelTTF::create("", "Arial", 24);
    CCControlButton* button2 = CCControlButton::create(pLabel, CCScale9Sprite::create("to_copy.png"));
    button2->addTargetWithActionForControlEvents(this, cccontrol_selector(HomeLayer::touchButtonAction), CCControlEventTouchUpInside);
    button2->setPosition(ccp(size.width/2, size.height/2));
    button2->setPreferredSize(CCSizeMake(338, 123));
    this->addChild(button2, 1, 11);
    pLabel = CCLabelTTF::create("", "Arial", 24);
    CCControlButton* button3 = CCControlButton::create(pLabel, CCScale9Sprite::create("to_activity.png"));
    button3->addTargetWithActionForControlEvents(this, cccontrol_selector(HomeLayer::touchButtonAction), CCControlEventTouchUpInside);
    button3->setPosition(ccp(size.width/2, size.height/2-150));
    button3->setPreferredSize(CCSizeMake(338, 129));
    this->addChild(button3, 1, 12);
    
    //下导航区域
    CCMenuItemImage *bu01 = CCMenuItemImage::create("friends.png", "friends.png", this, menu_selector(HomeLayer::menuItemCallBack));
    bu01->setTag(1);
    bu01->setPosition(ccp(100, 0));
    CCMenuItemImage *bu02 = CCMenuItemImage::create("talk.png", "talk.png", this, menu_selector(HomeLayer::menuItemCallBack));
    bu02->setTag(2);
    bu02->setPosition(ccp(210, 0));
    CCMenuItemImage *bu03 = CCMenuItemImage::create("message.png", "message.png", this, menu_selector(HomeLayer::menuItemCallBack));
    bu03->setTag(3);
    bu03->setPosition(ccp(320, 0));
    CCMenuItemImage *bu04 = CCMenuItemImage::create("equip.png", "equip.png", this, menu_selector(HomeLayer::menuItemCallBack));
    bu04->setTag(4);
    bu04->setPosition(ccp(430, 0));
    CCMenuItemImage *bu05 = CCMenuItemImage::create("manager.png", "manager.png", this, menu_selector(HomeLayer::menuItemCallBack));
    bu05->setTag(5);
    bu05->setPosition(ccp(540, 0));
    CCMenu* menu = CCMenu::create(bu01, bu02, bu03, bu04, bu05, NULL);
    menu->setPosition(ccp(0, 180));
    menu->setAnchorPoint(ccp(0, 0.5));
    this->addChild(menu);
    
    return true;
}

bool HomeLayer::initWithDelegate(HomeLayerDelegate* delegate)
{
    mDelegate = delegate;
    return this->init();
}

void HomeLayer::touchButtonAction(cocos2d::CCObject *sender, CCControlEvent controlEvent)
{
    if (mDelegate) {
        mDelegate->pressDelegateCB(this, ((CCControlButton *)sender)->getTag());
    }
}

void HomeLayer::menuItemCallBack(CCObject* pSender)
{
    CCMenuItemImage* item = (CCMenuItemImage *)pSender;
    switch (item->getTag()) {
        case 1:
            CCLOG("好友");
            break;
        case 2:
            CCLOG("聊天");
            break;
        case 3:
            CCLOG("消息");
            break;
        case 4:
            CCLOG("装备");
            break;
        case 5:
            CCLOG("角色");
            break;
    }
    if (mDelegate) {
        mDelegate->pressDelegateCB(this, ((CCMenuItemImage *)pSender)->getTag());
    }
}
