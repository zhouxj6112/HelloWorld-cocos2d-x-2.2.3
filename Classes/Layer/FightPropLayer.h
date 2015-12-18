//
//  FightPropLayer.hpp
//  HelloWorld
//
//  Created by MrZhou on 15/11/27.
//
//

#ifndef __HelloWorld__FightPropLayer__
#define __HelloWorld__FightPropLayer__

#include "cocos2d.h"
USING_NS_CC;

class FightPropLayer;

static CCArray* propArray = NULL;

class PropItemData : public CCObject
{
public:
    char* propName;
    int propIndex;
    char* propEffect;
    int useCount;
};

class CC_DLL FightPropLayerDelegate
{
public:
    //回调函数
    virtual bool useProp(PropItemData* itemData) = 0;
};

class FightPropLayer : public CCLayer
{
public:
    CREATE_FUNC(FightPropLayer);
    virtual bool init();
    void setDelegate(FightPropLayerDelegate* delegate);
private:
    FightPropLayerDelegate* mDelegate;
    void menuDidSelected(CCObject* pSender);
};

#endif
