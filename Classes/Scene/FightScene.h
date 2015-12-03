//
//  FightScene.h
//  HelloWorld
//
//  Created by MrZhou on 14-9-1.
//
//

#ifndef HelloWorld_FightScene_h
#define HelloWorld_FightScene_h

#include "cocos2d.h"
USING_NS_CC;

#include "FightLayer.h"
#include "QuestionLayer.h"
#include "FightBgLayer.h"

class FightScene : public cocos2d::CCLayer, public QuestionLayerDelegate, public FightLayerDelegate
{
private:
    FightBgLayer* fightBgLayer_;
    FightLayer* fightLayer_;
    QuestionLayer* questionlayer_;
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(FightScene);
    virtual void onEnter();
    virtual void onExit();
    
    void preLoadResource();
    
    //回调函数
    virtual void answerDelegateCB(QuestionLayer* box, int rightCount, int errorCount);
    
    void fightOverCallback(CCObject* object, void* param);
    void test1Callback(CCObject* object, void* param);
    void test2Callback(CCObject* object, void* param);
    //
    virtual void fightDidFinished(FightLayer* layer);
    virtual void battleOver(FightLayer* layer, bool isWin);
    virtual void moveVisibleWindow(FightLayer* layer, float deltaX, float time);
private:
    int rightCount_;
    int errorCount_;
    bool _isWin;
    int answerCount; //回答次数
    
    cocos2d::CCArray* historySingleQuestiones;
    cocos2d::CCArray* historyJudgeQuestiones;
};

#endif
