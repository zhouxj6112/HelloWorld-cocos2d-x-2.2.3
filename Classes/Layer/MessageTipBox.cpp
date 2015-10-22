//
//  MessageTipBox.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-7-17.
//
//

#include "MessageTipBox.h"

USING_NS_CC;

bool MessageTipBox::initWithTips(char* pTitle, char* pContent, CCLayer* delegateLayer)
{
    // super init first
	if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))
	{
		return false;
	}
    
    //转换赋值
    m_pDelegate = dynamic_cast<MessageBoxDelegate*>(delegateLayer);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF *label = CCLabelTTF::create(pContent, "", 64);
    label->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 50));
    this->addChild(label);
    
    CCMenuItemFont *okMenuItem = CCMenuItemFont::create("确定", this, menu_selector(MessageTipBox::okMenuItemCallback));
    okMenuItem->setColor(ccc3(255,0,0));
    okMenuItem->setFontSizeObj(32);
    okMenuItem->setPosition(ccp(winSize.width / 2 - 30, winSize.height / 2 - 50));
    
    m_pMenu = CCMenu::create(okMenuItem, NULL);
    m_pMenu->setPosition(CCPointZero);
    this->addChild(m_pMenu);
    
    //移进动画
    this->setPosition(ccp(0, winSize.height));
    CCMoveTo* pMove = CCMoveTo::create(0.5f, ccp(0, 0));
    CCDelayTime* pDelay = CCDelayTime::create(10.0f);
    CCMoveTo* pRemove = CCMoveTo::create(0.5f, ccp(0, winSize.height));
    CCAction* removeCallFunc = CCCallFuncND::create(this, callfuncND_selector(MessageTipBox::showAnimateDidFinished), NULL);
    this->runAction(CCSequence::create(pMove, pDelay, pRemove, removeCallFunc, NULL));
    
    return true;
}

void MessageTipBox::showAnimateDidFinished(CCObject* object, void* param)
{
    if (m_pDelegate) {
        m_pDelegate->msgBoxDelegateCB(this);
    }
    this->removeFromParentAndCleanup(true);
}

void MessageTipBox::onEnter()
{
    CCLayerColor::onEnter();
    //
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

void MessageTipBox::onExit()
{
    CCLayerColor::onExit();
    //
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool MessageTipBox::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
    
    return true;
}
void MessageTipBox::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchMoved(pTouch, pEvent);
    }
}
void MessageTipBox::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}
void MessageTipBox::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchCancelled(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

bool MessageTipBox::showMessageBox(cocos2d::CCLayer* delegateLayer, char* pTitle, char* pContent)
{
    MessageTipBox* box = new MessageTipBox();
    if (box && box->initWithTips(pTitle, pContent, delegateLayer)) {
        delegateLayer->addChild(box);
        box->autorelease();
        return true;
    }
    return false;
}

void MessageTipBox::okMenuItemCallback(cocos2d::CCObject *pSender)
{
    this->stopAllActions();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCMoveTo* pMove = CCMoveTo::create(0.5f, ccp(0, winSize.height));
    CCAction* removeCallFunc = CCCallFuncND::create(this, callfuncND_selector(MessageTipBox::showAnimateDidFinished), NULL);
    this->runAction(CCSequence::create(pMove, removeCallFunc));
}
