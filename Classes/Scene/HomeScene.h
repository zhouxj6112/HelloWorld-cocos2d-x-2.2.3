//
//  HomeScene.h
//  HelloWorld
//
//  Created by MrZhou on 14-8-18.
//
//

#ifndef HelloWorld_HomeScene_h
#define HelloWorld_HomeScene_h

#include "cocos2d.h"
USING_NS_CC;

#include "HomeLayer.h"

class HomeScene : public cocos2d::CCLayer, public HomeLayerDelegate
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(HomeScene);
    
public:
    virtual void pressDelegateCB(HomeLayer* layer, int buttonTag);
    void menuItemCallBack(CCObject* pSender);
    void actionDidFinished(cocos2d::CCObject *object, void *param);
};

#endif
