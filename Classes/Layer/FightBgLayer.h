//
//  FightBgLayer.h
//  HelloWorld
//
//  Created by MrZhou on 15-10-26.
//
//

#ifndef __HelloWorld__FightBgLayer__
#define __HelloWorld__FightBgLayer__

#include "cocos2d.h"
USING_NS_CC;

class FightBgLayer : public CCLayer {
    
public:
    CREATE_FUNC(FightBgLayer);
    virtual bool init();
public:
    void moveBgLayer(float deltaX, float moveTime);
};

#endif /* defined(__HelloWorld__FightBgLayer__) */
