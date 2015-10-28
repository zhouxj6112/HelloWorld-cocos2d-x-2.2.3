//
//  AnimationManager.h
//  HelloWorld
//
//  Created by MrZhou on 15-10-28.
//
//

#ifndef __HelloWorld__AnimationManager__
#define __HelloWorld__AnimationManager__

#include "cocos2d.h"

#define str_hero_idle "hero_idle"
#define str_hero_run  "hero_run"
#define str_atk_ko    "atk_ko"
#define str_atk_bg    "atk_bg"

class AnimationManager : public cocos2d::CCObject
{
public:
    static AnimationManager* shareInstance();
public:
    void preLoadAnimations();
    cocos2d::CCAnimation* getAnimationWithName(const char* animationName);
};

#endif /* defined(__HelloWorld__AnimationManager__) */
