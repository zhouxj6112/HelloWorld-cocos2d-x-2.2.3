//
//  AnimationManager.cpp
//  HelloWorld
//
//  Created by MrZhou on 15-10-28.
//
//

#include "AnimationManager.h"

USING_NS_CC;

static AnimationManager* manager;

AnimationManager* AnimationManager::shareInstance()
{
    if (manager == NULL) {
        manager = new AnimationManager();
    }
    return manager;
}

void AnimationManager::preLoadAnimations()
{
    CCAnimation* pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_idle");
    if (pAnimation == NULL) {
        pAnimation = CCAnimation::create();
        for (int i=0; i<4; i++)
        {
            CCString* pFileName = CCString::createWithFormat("idle/o%04d.png", i);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
        }
        pAnimation->setRestoreOriginalFrame(true);
        pAnimation->setDelayPerUnit(0.2f);    // 必须设置这个，要不就不会播放
        pAnimation->setLoops(1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_idle");
    }
    pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_run");
    if (pAnimation == NULL) {
        pAnimation = CCAnimation::create();
        for (int i=0; i<4; i++)
        {
            CCString* pFileName = CCString::createWithFormat("run/m%04d.png", i);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
        }
        pAnimation->setRestoreOriginalFrame(true);
        pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
        pAnimation->setLoops(1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_run");
    }
    pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_a");
    if (pAnimation == NULL) {
        int iKeyFrame = 4;
        pAnimation = CCAnimation::create();
        for (int i=1; i<=4; i++)
        {
            CCString* pFileName = CCString::createWithFormat("skill/a%04d.png", i);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
            if (i == iKeyFrame) {
                for (int k=0; k<2; k++) {
                    pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                }
            }
        }
        pAnimation->setRestoreOriginalFrame(true);
        pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
        pAnimation->setLoops(1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_a");
    }
    pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_b");
    if (pAnimation == NULL) {
        int iKeyFrame = 2;
        pAnimation = CCAnimation::create();
        for (int i=1; i<=4; i++)
        {
            CCString* pFileName = CCString::createWithFormat("skill/b%04d.png", i);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
            if (i == iKeyFrame) {
                for (int k=0; k<2; k++) {
                    pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                }
            }
        }
        pAnimation->setRestoreOriginalFrame(true);
        pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
        pAnimation->setLoops(1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_b");
    }
    pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_c");
    if (pAnimation == NULL) {
        int iKeyFrame = 3;
        pAnimation = CCAnimation::create();
        for (int i=1; i<=4; i++)
        {
            CCString* pFileName = CCString::createWithFormat("skill/c%04d.png", i);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
            if (i == iKeyFrame) {
                for (int k=0; k<2; k++) {
                    pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                }
            }
        }
        pAnimation->setRestoreOriginalFrame(true);
        pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
        pAnimation->setLoops(1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_c");
    }
    pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_d");
    if (pAnimation == NULL) {
        int iKeyFrame = 4;
        pAnimation = CCAnimation::create();
        for (int i=1; i<=4; i++)
        {
            CCString* pFileName = CCString::createWithFormat("skill/d%04d.png", i);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
            if (i == iKeyFrame) {
                for (int k=0; k<2; k++) {
                    pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                }
            }
        }
        pAnimation->setRestoreOriginalFrame(true);
        pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
        pAnimation->setLoops(1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_d");
    }
    pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_e");
    if (pAnimation == NULL) {
        int iKeyFrame = 3;
        pAnimation = CCAnimation::create();
        for (int i=1; i<=4; i++)
        {
            CCString* pFileName = CCString::createWithFormat("skill/e%04d.png", i);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
            if (i == iKeyFrame) {
                for (int k=0; k<2; k++) {
                    pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                }
            }
        }
        pAnimation->setRestoreOriginalFrame(true);
        pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
        pAnimation->setLoops(1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_e");
    }
    pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_f");
    if (pAnimation == NULL) {
        int iKeyFrame = 3;
        pAnimation = CCAnimation::create();
        for (int i=1; i<=4; i++)
        {
            CCString* pFileName = CCString::createWithFormat("skill/f%04d.png", i);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
            if (i == iKeyFrame) {
                for (int k=0; k<2; k++) {
                    pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                }
            }
        }
        pAnimation->setRestoreOriginalFrame(true);
        pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
        pAnimation->setLoops(1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_f");
    }
    pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_g");
    if (pAnimation == NULL) {
        int iKeyFrame = 2;
        pAnimation = CCAnimation::create();
        for (int i=1; i<=4; i++)
        {
            CCString* pFileName = CCString::createWithFormat("skill/g%04d.png", i);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
            if (i == iKeyFrame) {
                for (int k=0; k<2; k++) {
                    pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                }
            }
        }
        pAnimation->setRestoreOriginalFrame(true);
        pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
        pAnimation->setLoops(1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_g");
    }
    pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_h");
    if (pAnimation == NULL) {
        int iKeyFrame = 3;
        pAnimation = CCAnimation::create();
        for (int i=1; i<=4; i++)
        {
            CCString* pFileName = CCString::createWithFormat("skill/h%04d.png", i);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
            if (i == iKeyFrame) {
                for (int k=0; k<2; k++) {
                    pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                }
            }
        }
        pAnimation->setRestoreOriginalFrame(true);
        pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
        pAnimation->setLoops(1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_h");
    }
    pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_i");
    if (pAnimation == NULL) {
        int iKeyFrame = 4;
        pAnimation = CCAnimation::create();
        for (int i=1; i<=4; i++)
        {
            CCString* pFileName = CCString::createWithFormat("skill/i%04d.png", i);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
            if (i == iKeyFrame) {
                for (int k=0; k<2; k++) {
                    pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                }
            }
        }
        pAnimation->setRestoreOriginalFrame(true);
        pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
        pAnimation->setLoops(1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_i");
    }
    pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_atk_j");
    if (pAnimation == NULL) {
        int iKeyFrame1 = 2;
        int iKeyFrame2 = 5;
        pAnimation = CCAnimation::create();
        for (int i=1; i<=8; i++)
        {
            CCString* pFileName = CCString::createWithFormat("skill/j%04d.png", i);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
            if (i==iKeyFrame1 || i==iKeyFrame2) {
                for (int k=0; k<2; k++) {
                    pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
                }
            }
        }
        pAnimation->setRestoreOriginalFrame(true);
        pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
        pAnimation->setLoops(1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_atk_j");
    }
    pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_behit_0");
    if (pAnimation == NULL) {
        pAnimation = CCAnimation::create();
        for (int i=1; i<=3; i++)
        {
            CCString* pFileName = CCString::createWithFormat("behit/n%04d.png", i);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
        }
        pAnimation->setRestoreOriginalFrame(true);
        pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
        pAnimation->setLoops(1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_behit_0");
    }
    pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("hero_behit_1");
    if (pAnimation == NULL) {
        pAnimation = CCAnimation::create();
        for (int i=1; i<=5; i++)
        {
            CCString* pFileName = CCString::createWithFormat("behit/n%04d.png", 1);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
        } //补偿动画
        for (int i=0; i<=6; i++)
        {
            CCString* pFileName = CCString::createWithFormat("behit/r%04d.png", i);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
        }
        pAnimation->setRestoreOriginalFrame(true);
        pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
        pAnimation->setLoops(1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "hero_behit_1");
    }
    
    pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("atk_bg");
    if (pAnimation == NULL) {
        pAnimation = CCAnimation::create();
        for (int i=1; i<=3; i++)
        {
            CCString* pFileName = CCString::createWithFormat("1%03d.png", i);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
        }
        pAnimation->setRestoreOriginalFrame(true);
        pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
        pAnimation->setLoops(1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "atk_bg");
    }
    pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("atk_ko");
    if (pAnimation == NULL) {
        pAnimation = CCAnimation::create();
        for (int i=1; i<30; i++)
        {
            CCString* pFileName = CCString::createWithFormat("3%03d.png", i);
            pAnimation->addSpriteFrameWithFileName(pFileName->getCString());
        }
        pAnimation->setRestoreOriginalFrame(true);
        pAnimation->setDelayPerUnit(0.1f);    // 必须设置这个，要不就不会播放
        pAnimation->setLoops(1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, "atk_ko");
    }
}

CCAnimation* AnimationManager::getAnimationWithName(const char* animationName)
{
    return CCAnimationCache::sharedAnimationCache()->animationByName(animationName);
}
