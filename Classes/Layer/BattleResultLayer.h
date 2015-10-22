//
//  BattleResultLayer.h
//  HelloWorld
//
//  Created by MrZhou on 14-12-11.
//
//

#ifndef HelloWorld_BattleResultLayer_h
#define HelloWorld_BattleResultLayer_h

#include "cocos2d.h"
USING_NS_CC;

#include "cocos-ext.h"
USING_NS_CC_EXT;

class BattleResultLayer;

class CC_DLL BattleResultLayerDelegate
{
public:
    //回调函数
    virtual void animationDidFinished(BattleResultLayer* layer) = 0;
};

class BattleResultLayer : public cocos2d::CCLayer
{
public:
    BattleResultLayer();
    ~BattleResultLayer();
    virtual bool init();
private:
    BattleResultLayerDelegate* mDelegate;
    void runActionDidFinished(CCObject* object, void* param);
};

#endif
