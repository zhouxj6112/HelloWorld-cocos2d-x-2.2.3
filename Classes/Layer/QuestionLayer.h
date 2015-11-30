//
//  QuestionLayer.h
//  HelloWorld
//
//  Created by MrZhou on 14-6-30.
//
//

#ifndef HelloWorld_QuestionLayer_h
#define HelloWorld_QuestionLayer_h

#include "cocos2d.h"
#include "QuestionObj.h"
#include "FightPropLayer.h"

#include "cocos-ext.h"
USING_NS_CC_EXT;

typedef enum _QuestionType {
    SingleQuestion = 1,
    JudgeQuestion  = 2,
    MultiQuestion  = 3
} QuestionType;

class QuestionLayer;

class CC_DLL QuestionLayerDelegate
{
public:
    //回调函数 (isRight:是否正确)
    virtual void answerDelegateCB(QuestionLayer* box, int rightCount, int errorCount) = 0;
};

class QuestionLayer : public cocos2d::CCLayer, public FightPropLayerDelegate
{
public:
    QuestionLayer();
    QuestionLayer(QuestionType qType);
    virtual ~QuestionLayer();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // implement the "static node()" method manually
    CREATE_FUNC(QuestionLayer);
    static QuestionLayer* create(QuestionType qType);
    virtual void onEnter();
    virtual void onExit();
    
    void setDelegate(QuestionLayerDelegate* delegate);
    //代理协议
    QuestionLayerDelegate* mDelegate;
    //
    void touchDownAction(CCObject *sender, CCControlEvent controlEvent);

    virtual void useProp(PropItemData* itemData);
private:
    QuestionType queType;
    int serialNo; //题目序号
    int timerCount;
    cocos2d::CCProgressTimer* progressTimer;
    cocos2d::CCLabelTTF* timerLabel_;
    int timerTotal;
    cocos2d::CCString* questionString;
    std::string questionStr;
    int displayLen;
    //
    QuestionObj* questionObj;
    cocos2d::CCSprite* warnTipSpr;
    
public:
    bool isAnswerFinished;
    int rightAnswer;
    int errorAnswer;
    int rightLimit;   //在很短的时间内,做出回答,并且答对奖励攻击一次
    long startTime;
    
public:
    void timerCB();
    void displayActionTimerCB();
    void resetNextQuestion();
    void start(CCObject* object, void* param);
    void startAnswer();
    void noticeDelegate(CCObject* object, void* param);
    //
    void displaySubViews();
    
    FightPropLayer* propLayer_;
    void simulateAnswerRight();
    void resetTimer();
};

#endif
