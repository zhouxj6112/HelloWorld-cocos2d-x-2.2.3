//
//  HomeLayer.h
//  HelloWorld
//
//  Created by MrZhou on 14-8-18.
//
//

#ifndef HelloWorld_HomeLayer_h
#define HelloWorld_HomeLayer_h

#include "cocos2d.h"
USING_NS_CC;

#include "cocos-ext.h"
USING_NS_CC_EXT;

class HomeLayer;

class CC_DLL HomeLayerDelegate
{
public:
    //回调函数
    virtual void pressDelegateCB(HomeLayer* layer, int buttonTag) = 0;
};

class HomeLayer : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    bool initWithDelegate(HomeLayerDelegate* delegate);
    
    virtual void touchButtonAction(CCObject *sender, CCControlEvent controlEvent);
    
    //代理协议
    HomeLayerDelegate* mDelegate;
    //
    void menuItemCallBack(CCObject* pSender);
};

#endif
