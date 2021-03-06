//
//  MessageBox.h
//  TurnAndTurn
//
//  Created by MrZhou on 13-9-6.
//
//

#ifndef TurnAndTurn_MessageHandleBox_h
#define TurnAndTurn_MessageHandleBox_h

#include "cocos2d.h"

USING_NS_CC;

class MessageHandleBox;

class CC_DLL MessageBoxDelegate
{
public:
    //回调函数
    virtual void msgBoxDelegateCB(MessageHandleBox* box) = 0;
};

class MessageHandleBox : public CCLayerColor
{
public:
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    //对外接口
    static bool showMessageBox(cocos2d::CCLayer* delegateLayer, char* pTitle, char* pContent);
    
private:
    //模态对话框菜单
    CCMenu *m_pMenu;
    //记录菜单点击
    bool m_bTouchedMenu;
    //
    bool initWithTips(char* pTitle, char* pContent, CCLayer* delegateLayer);
    
    void okMenuItemCallback(CCObject* pSender);
    void cancelMenuItemCallback(CCObject* pSender);
    
    virtual void onEnter();
    virtual void onExit();
    
    //代理协议
    MessageBoxDelegate* m_pDelegate;
};

#endif
