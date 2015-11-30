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

class CC_DLL FightPropLayerDelegate
{
public:
    //回调函数
    virtual void useProp(int propIndex) = 0;
};

class FightPropLayer : public CCLayer
{
public:
    CREATE_FUNC(FightPropLayer);
    virtual bool init();
    void setDelegate(FightPropLayerDelegate* delegate);
    CCArray* propArray;
private:
    FightPropLayerDelegate* mDelegate;
    void menuDidSelected(CCObject* pSender);
};

struct PropItemData
{
    char* propName;
    int propIndex;
    char* propEffect;
};

#endif
