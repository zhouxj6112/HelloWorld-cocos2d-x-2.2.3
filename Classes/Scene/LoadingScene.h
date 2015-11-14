//
//  LoadingScene.h
//  HelloWorld
//
//  Created by MrZhou on 15-10-22.
//
//

#ifndef __HelloWorld__LoadingScene__
#define __HelloWorld__LoadingScene__

#include "cocos2d.h"
USING_NS_CC;

extern bool is_realy_fight;

class LoadingScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(LoadingScene);
    
    void didAction(cocos2d::CCObject* object, void* param);
};

#endif /* defined(__HelloWorld__LoadingScene__) */
