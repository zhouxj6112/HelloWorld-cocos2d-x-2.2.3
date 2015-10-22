//
//  CreateRoleLayer.h
//  HelloWorld
//
//  Created by MrZhou on 14-11-1.
//
//

#ifndef HelloWorld_CreateRoleLayer_h
#define HelloWorld_CreateRoleLayer_h

#include "cocos2d.h"

#include "cocos-ext.h"
USING_NS_CC_EXT;

class CreateRoleLayer;

class CC_DLL CreateRoleDelegate
{
public:
    //回调函数
    virtual void createDidFinished(CreateRoleLayer* layer) = 0;
};

class CreateRoleLayer : public cocos2d::CCLayer, public cocos2d::extension::CCEditBoxDelegate
{
public:
    CreateRoleLayer();
    ~CreateRoleLayer();
    virtual bool init();
    CREATE_FUNC(CreateRoleLayer);
    //
    void setDelegate(CreateRoleDelegate* delegate);
private:
    CreateRoleDelegate* mDelegate;
    bool bNext;
private:
    void closeButtonAction(cocos2d::CCObject* sender, CCControlEvent controlEvent);
    void touchButtonAction(cocos2d::CCObject *sender, CCControlEvent controlEvent);
    void rollDiceDidFinished(cocos2d::CCObject* sender, void* param);
    void confirmActon(cocos2d::CCObject *sender, CCControlEvent controlEvent);
    void randomUserName(cocos2d::CCObject *sender, CCControlEvent controlEvent);
public:
    virtual void editBoxEditingDidBegin(CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(CCEditBox* editBox);
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(CCEditBox* editBox);
};

#endif
