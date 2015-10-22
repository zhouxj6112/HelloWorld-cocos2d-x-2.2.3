//
//  MessageBox.cpp
//  TurnAndTurn
//
//  Created by MrZhou on 13-9-6.
//
//

#include "MessageHandleBox.h"

USING_NS_CC;

bool MessageHandleBox::initWithTips(char* pTitle, char* pContent, CCLayer* delegateLayer)
{
    // super init first
	if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 128)))
	{
		return false;
	}
    
    //转换赋值
    m_pDelegate = dynamic_cast<MessageBoxDelegate*>(delegateLayer);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF *label = CCLabelTTF::create(pContent, "", 64);
    label->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 50));
    this->addChild(label);
    
    CCMenuItemFont *okMenuItem = CCMenuItemFont::create("确定", this, menu_selector(MessageHandleBox::okMenuItemCallback));
    okMenuItem->setColor(ccc3(255,0,0));
    okMenuItem->setFontSizeObj(32);
    okMenuItem->setPosition(ccp(winSize.width / 2 - 100, winSize.height / 2 - 50));
    
    CCMenuItemFont *cancelMenuItem = CCMenuItemFont::create("取消", this, menu_selector(MessageHandleBox::cancelMenuItemCallback));
    cancelMenuItem->setColor(ccc3(255,0,0));
    cancelMenuItem->setFontSizeObj(32);
    cancelMenuItem->setPosition(ccp(winSize.width / 2 + 100, winSize.height / 2 - 50));
    
    m_pMenu = CCMenu::create(okMenuItem, cancelMenuItem, NULL);
    m_pMenu->setPosition(CCPointZero);
    this->addChild(m_pMenu);
    
    //移进动画
    this->setPosition(ccp(0, winSize.height));
    CCMoveTo* pMove = CCMoveTo::create(0.5f, ccp(0, 0 ));
    this->runAction(pMove);
    
    return true;
}

void MessageHandleBox::onEnter()
{
    CCLayerColor::onEnter();
    //
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

void MessageHandleBox::onExit()
{
    CCLayerColor::onExit();
    //
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool MessageHandleBox::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
    
    return true;
}
void MessageHandleBox::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchMoved(pTouch, pEvent);
    }
}
void MessageHandleBox::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}
void MessageHandleBox::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchCancelled(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

bool MessageHandleBox::showMessageBox(cocos2d::CCLayer* delegateLayer, char* pTitle, char* pContent)
{
    MessageHandleBox* box = new MessageHandleBox();
    if (box && box->initWithTips(pTitle, pContent, delegateLayer)) {
        delegateLayer->addChild(box);
        box->autorelease();
        return true;
    }
    return false;
}

void MessageHandleBox::okMenuItemCallback(cocos2d::CCObject *pSender)
{
    if (m_pDelegate) {
        m_pDelegate->msgBoxDelegateCB(this);
    }
    this->removeFromParentAndCleanup(true);
}

void MessageHandleBox::cancelMenuItemCallback(cocos2d::CCObject *pSender)
{
    this->removeFromParentAndCleanup(true);
}
