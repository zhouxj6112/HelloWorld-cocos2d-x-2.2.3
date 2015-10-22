//
//  CreateScene.h
//  HelloWorld
//
//  Created by MrZhou on 14-10-31.
//
//

#ifndef HelloWorld_CreateScene_h
#define HelloWorld_CreateScene_h

#include "cocos2d.h"
#include "CreateRoleLayer.h"

#include "cocos-ext.h"
USING_NS_CC_EXT;

class CreateScene : public cocos2d::CCLayer, public CreateRoleDelegate
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(CreateScene);
    //
    virtual void createDidFinished(CreateRoleLayer* pLayer);
};

#endif
