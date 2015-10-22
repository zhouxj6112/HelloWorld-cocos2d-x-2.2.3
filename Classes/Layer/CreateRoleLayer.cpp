//
//  CreateRoleLayer.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-11-1.
//
//

#include "CreateRoleLayer.h"
#include "Global.h"

USING_NS_CC;

CreateRoleLayer::CreateRoleLayer()
{
    bNext = true;
}

CreateRoleLayer::~CreateRoleLayer()
{
}

bool CreateRoleLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* bgSpr = CCSprite::create("bg_create.png");
    bgSpr->setAnchorPoint(ccp(0.5f, 0.5f));
    bgSpr->setPosition( ccp(size.width/2, size.height/2) );
    this->addChild(bgSpr, 0, 0);
    
    CCSprite* maleSpr = CCSprite::create("icon_male.png");
    maleSpr->setPosition(ccp(size.width/2-150, 630));
    this->addChild(maleSpr);
    CCLabelTTF* pLabel = CCLabelTTF::create("", "Arial", 24);
    CCControlButton* maleButton = CCControlButton::create(pLabel, CCScale9Sprite::create("role_male.png"));
    maleButton->setPosition(ccp(size.width/2-150, 450));
    maleButton->setPreferredSize(CCSizeMake(276, 276));
    maleButton->addTargetWithActionForControlEvents(this, cccontrol_selector(CreateRoleLayer::touchButtonAction), CCControlEventTouchUpInside);
    this->addChild(maleButton, 1, 11);
    
    CCSprite* femaleSpr = CCSprite::create("icon_female.png");
    femaleSpr->setPosition(ccp(size.width/2+150, 630));
    this->addChild(femaleSpr);
    CCLabelTTF* pLabel2 = CCLabelTTF::create("", "Arial", 24);
    CCControlButton* femaleButton = CCControlButton::create(pLabel2, CCScale9Sprite::create("role_female.png"));
    femaleButton->setPosition(ccp(size.width/2+150, 450));
    femaleButton->setPreferredSize(CCSizeMake(276, 276));
    femaleButton->addTargetWithActionForControlEvents(this, cccontrol_selector(CreateRoleLayer::touchButtonAction), CCControlEventTouchUpInside);
    this->addChild(femaleButton, 1, 12);
    
    CCLabelTTF* pLabel0 = CCLabelTTF::create("", "Arial", 24);
    CCControlButton* nextButton = CCControlButton::create(pLabel0, CCScale9Sprite::create("xiayibu.png"));
    nextButton->setPosition(ccp(size.width/2, 175));
    nextButton->setPreferredSize(CCSizeMake(237, 114));
    nextButton->addTargetWithActionForControlEvents(this, cccontrol_selector(CreateRoleLayer::confirmActon), CCControlEventTouchUpInside);
    this->addChild(nextButton);
    
    CCLabelTTF* pLabel3 = CCLabelTTF::create("", "Arial", 24);
    CCControlButton* closeButton = CCControlButton::create(pLabel3, CCScale9Sprite::create("close_button.png"));
    closeButton->setPosition(ccp(590, 870));
    closeButton->setPreferredSize(CCSizeMake(105, 105));
    closeButton->addTargetWithActionForControlEvents(this, cccontrol_selector(CreateRoleLayer::closeButtonAction), CCControlEventTouchUpInside);
    this->addChild(closeButton);
    
    return true;
}

void CreateRoleLayer::touchButtonAction(cocos2d::CCObject *sender, CCControlEvent controlEvent)
{
    CCNode* node = (CCNode *)sender;
//    CCControlButton* male = (CCControlButton *)(this->getChildByTag(11));
//    CCControlButton* female = (CCControlButton *)(this->getChildByTag(12));
    if (node->getTag() == 11) {
        Global::shareInstance()->gender = 1;
//        male->getBackgroundSprite()->setScale(1.2f);
//        female->getBackgroundSprite()->setScale(1.0f);
    } else if (node->getTag() == 12) {
        Global::shareInstance()->gender = 0;
//        male->getBackgroundSprite()->setScale(1.0f);
//        female->getBackgroundSprite()->setScale(1.2f);
    }
}

void CreateRoleLayer::confirmActon(cocos2d::CCObject *sender, CCControlEvent controlEvent)
{
    if (bNext) {
        if (Global::shareInstance()->gender == 0) {
            CCControlButton* button = (CCControlButton *)(this->getChildByTag(11));
            button->removeFromParent();
            CCControlButton* leftButton = (CCControlButton *)(this->getChildByTag(12));
            leftButton->setPosition( ccp(this->getContentSize().width/2, leftButton->getPositionY()) );
        } else {
            CCControlButton* button = (CCControlButton *)(this->getChildByTag(12));
            button->removeFromParent();
            CCControlButton* leftButton = (CCControlButton *)(this->getChildByTag(11));
            leftButton->setPosition( ccp(this->getContentSize().width/2, leftButton->getPositionY()) );
        }
        CCControlButton* button = (CCControlButton *)sender;
        button->setBackgroundSpriteForState(CCScale9Sprite::create("queren.png"), CCControlStateNormal);
        //
        CCEditBox* editBox = CCEditBox::create(CCSizeMake(298, 64), CCScale9Sprite::create("edit_name.png"));
        editBox->setPosition(ccp(300, 275));
        editBox->setDelegate(this);
        this->addChild(editBox, 10, 10);
        //筛子
        CCLabelTTF* label = CCLabelTTF::create("", "", 24);
        CCControlButton* diceButton = CCControlButton::create(label, CCScale9Sprite::create("dice_1.png"));
        diceButton->setPosition(ccp(530, 275));
        diceButton->setPreferredSize(CCSizeMake(96, 99));
        diceButton->addTargetWithActionForControlEvents(this,  cccontrol_selector(CreateRoleLayer::randomUserName), CCControlEventTouchUpInside);
        this->addChild(diceButton, 10, 30);
        
        bNext = false;
    } else {
        CCEditBox* box = (CCEditBox *)(this->getChildByTag(10));
        Global::shareInstance()->userName = box->getText();
        if (mDelegate) {
            mDelegate->createDidFinished(this);
        }
    }
}

void CreateRoleLayer::setDelegate(CreateRoleDelegate *delegate)
{
    mDelegate = delegate;
}

void CreateRoleLayer::editBoxEditingDidBegin(CCEditBox* editBox)
{
}

void CreateRoleLayer::editBoxEditingDidEnd(CCEditBox* editBox)
{
    CCLOG("editBoxEditingDidEnd");
}

void CreateRoleLayer::editBoxTextChanged(CCEditBox* editBox, const std::string& text)
{
    
}

void CreateRoleLayer::editBoxReturn(CCEditBox* editBox)
{
    
}

void CreateRoleLayer::closeButtonAction(cocos2d::CCObject *sender, CCControlEvent controlEvent)
{
    CCDirector::sharedDirector()->popScene();
}

static unsigned int uLoop = 1;

void CreateRoleLayer::randomUserName(cocos2d::CCObject *sender, CCControlEvent controlEvent)
{
    CCLOG("randomUserName");
    CCControlButton* button = (CCControlButton *)sender;
    button->setVisible(false);
    
    uLoop = CCRANDOM_0_1()*5+1; //1-6
    
    CCAnimation* pAnimation = CCAnimation::create();
    for (int i=1; i<=6; i++)
    {
        CCString* pFileName = CCString::createWithFormat("dice_%d.png", i);
        pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
    }
    pAnimation->setRestoreOriginalFrame(true);
    pAnimation->setDelayPerUnit(1.0f/6);    // 必须设置这个，要不就不会播放
    pAnimation->setLoops(uLoop);
    CCAnimate* pAnimate = CCAnimate::create(pAnimation);
    CCAction* pStop = CCCallFuncND::create(this, callfuncND_selector(CreateRoleLayer::rollDiceDidFinished), NULL);
    CCSprite* diceSpr = CCSprite::create("dice_1.png");
    diceSpr->runAction(CCSequence::create(pAnimate, pStop, NULL));
    this->addChild(diceSpr, 11, 111);
    diceSpr->setPosition(button->getPosition());
    
    CCEditBox* box = (CCEditBox *)(this->getChildByTag(10));
    box->setEnabled(false);
}

void CreateRoleLayer::rollDiceDidFinished(cocos2d::CCObject *sender, void *param)
{
    CCSprite* spr = (CCSprite *)sender;
    spr->removeFromParent();
    
    CCControlButton* button = (CCControlButton *)(this->getChildByTag(30));
    button->setVisible(true);
    CCString* imageName  = CCString::createWithFormat("dice_%d.png", uLoop);
    button->setBackgroundSpriteForState(CCScale9Sprite::create(imageName->getCString()), CCControlStateNormal);
    CCEditBox* box = (CCEditBox *)(this->getChildByTag(10));
    if (uLoop == 1) {
        box->setText("角色1");
    } else if (uLoop == 2) {
        box->setText("角色2");
    } else if (uLoop == 3) {
        box->setText("角色3");
    } else if (uLoop == 4) {
        box->setText("角色4");
    } else if (uLoop == 5) {
        box->setText("角色5");
    } else {
        box->setText("角色6");
    }
    box->setEnabled(true);
}
