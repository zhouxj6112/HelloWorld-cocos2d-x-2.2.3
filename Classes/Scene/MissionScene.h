//
//  JobMissionScene.h
//  HelloWorld
//
//  Created by MrZhou on 14-8-4.
//
//

#ifndef HelloWorld_MissionScene_h
#define HelloWorld_MissionScene_h

#include "cocos2d.h"
USING_NS_CC;

#include "cocos-ext.h"
USING_NS_CC_EXT;

class MissionScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(MissionScene);
    
    virtual void touchDownAction(CCObject *sender, CCControlEvent controlEvent);
    
    void actionDidFinished(CCObject* object, void* param);
    
    void menuItemCallBack(CCObject* pSender);
    
private:
    virtual void onEnter();
    virtual void onExit();
};

#endif
