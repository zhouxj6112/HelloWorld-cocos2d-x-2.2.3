//
//  QuestionLayer.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-6-30.
//
//

#include "QuestionLayer.h"
#include "Utils.h"
#include "GameSoundManager.h"
#include "LoadingScene.h"

USING_NS_CC;

static int number_in_group = 5;

QuestionLayer::QuestionLayer()
{
    queType = SingleQuestion;
}
QuestionLayer::QuestionLayer(QuestionType qType)
{
    this->queType = qType;
}
QuestionLayer::~QuestionLayer()
{
    this->unschedule(schedule_selector(QuestionLayer::timerCB));
}

QuestionLayer* QuestionLayer::create(QuestionType qType)
{
    QuestionLayer *pRet = new QuestionLayer(qType);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool QuestionLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    timerTotal = 10;
    rightAnswer = errorAnswer = 0;
    rightLimit = 0;
    serialNo = 0;
    CCLOG("queType:%d", queType);
    
    if (is_realy_fight == false) {
        number_in_group = 1;
    } else {
        number_in_group = 5;
    }
    
    CCSize size = this->getContentSize();
    
    //开始显示题型
    const char* str = NULL;
    if (queType == SingleQuestion) {
        str = "单选题";
        timerTotal = 15;
    } else if (queType == JudgeQuestion) {
        str = "判断题";
        timerTotal = 12;
    } else {
        str = "多选题";
        timerTotal = 30;
    }
    CCLabelTTF* ttf = CCLabelTTF::create(str, "STHeitiK-Medium", 36);
    ttf->setAnchorPoint(ccp(0.5f, 0.5f));
    ttf->setPosition(ccp(0, 120));
    this->addChild(ttf, 0, 1234);
    CCScaleTo* scaleTo = CCScaleTo::create(1.0f, 2.0f);
    CCAction* pAction = CCCallFuncND::create(this, callfuncND_selector(QuestionLayer::start), NULL);
    ttf->runAction(CCSequence::create(scaleTo, pAction, NULL));
    
//    GameSoundManager::shareManager()->playReadyGoEffect();
    
    isAnswerFinished = false;
    
    return true;
}

void QuestionLayer::start(cocos2d::CCObject *object, void *param)
{
    ((CCLayer *)object)->removeFromParent();
    
    this->startAnswer();
    
//    //播放背景
//    GameSoundManager::shareManager()->playFightBackgroundMusic();
}

void QuestionLayer::startAnswer()
{
    timerCount = timerTotal;
    
    CCSize size = this->getContentSize();
    CCLOG("%f %f", size.width, size.height);
    
    CCSprite* labelBg = CCSprite::create("bg_question.png");
    labelBg->setAnchorPoint(ccp(0.5, 0.5));
    labelBg->setPosition(ccp(0, size.height/2-100));
    this->addChild(labelBg, 0);
    
    const char* filePath = NULL;
    if (queType == SingleQuestion) {
        filePath = CCFileUtils::sharedFileUtils()->fullPathForFilename("question_4.plist").c_str();
    } else if (queType == JudgeQuestion) {
        filePath = CCFileUtils::sharedFileUtils()->fullPathForFilename("question_2.plist").c_str();
    } else {
        filePath = CCFileUtils::sharedFileUtils()->fullPathForFilename("question_3.plist").c_str();
    }
    CCArray* plistArray = CCArray::createWithContentsOfFile(filePath);
    CCDictionary* dic = (CCDictionary*)plistArray->objectAtIndex(serialNo);
    CCString* qType = (CCString *)(dic->objectForKey("type")); //Number类型
    CCString* pStr = (CCString *)(dic->objectForKey("question"));
    CCLOG("%d %s", qType->intValue(), pStr->getCString());
    CCArray* ans = (CCArray *)(dic->objectForKey("answer"));
    
    questionObj = new QuestionObj(qType->intValue(), pStr->getCString(), ans);
    CCLOG("读取题目信息完成");
    
    questionString = questionObj->questionString;
    displayLen = 0;
    //题目
    CCLabelTTF* pLabel = CCLabelTTF::create(questionStr.c_str(), "Arial", 24, CCSize(size.width-20, 90), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    pLabel->setAnchorPoint(ccp(1, 0));
    pLabel->setPosition(ccp(-size.width/2+15, size.height/2-130));
    pLabel->setAnchorPoint(ccp(0, 0));
    this->addChild(pLabel, 1, 11);
    
    const char* typeStr = "单选题";
    if (questionObj->questionType == 1) {
        typeStr = "单选题";
        timerTotal = 15;
    } else if (questionObj->questionType == 2) {
        typeStr = "判断题";
        timerTotal = 12;
    } else {
        typeStr = "多选题";
        timerTotal = 30;
    }
    CCString* title = CCString::createWithFormat("题型:%s", typeStr);
    CCLabelTTF* label = CCLabelTTF::create(title->getCString(), "Arial", 24);
    label->setAnchorPoint(ccp(0, 1));
    label->setPosition(ccp(140, size.height/2-135));
    this->addChild(label, 1, 12);
    
//    CCSprite* timerBg = CCSprite::create("money_bg.png");
//    timerBg->setPosition(ccp(0, size.height/2-200));
//    this->addChild(timerBg);
    progressTimer = CCProgressTimer::create(CCSprite::create("money_bg.png"));
    progressTimer->setType(kCCProgressTimerTypeBar);
    progressTimer->setMidpoint(ccp(0, 0));
    progressTimer->setBarChangeRate(ccp(1, 0));
    progressTimer->setAnchorPoint(ccp(0.5, 0.5));
    progressTimer->setPosition(ccp(0, size.height/2-200));
    progressTimer->setPercentage(100);
    this->addChild(progressTimer, 2);
    timerLabel_ = CCLabelTTF::create(CCString::createWithFormat("%d", timerCount)->getCString(), "Arial", 24);
    timerLabel_->setAnchorPoint(ccp(1, 0));
    timerLabel_->setPosition(ccp(0, 0));
    progressTimer->addChild(timerLabel_);
    warnTipSpr = CCSprite::create("arrow000.png");
    warnTipSpr->setPosition( ccp(progressTimer->getContentSize().width/3*2, 0) );
    warnTipSpr->setAnchorPoint( ccp(0.5, 0) );
    progressTimer->addChild(warnTipSpr);
    
    //显示宫格答案
    this->displaySubViews();
    
    this->schedule(schedule_selector(QuestionLayer::displayActionTimerCB), 0.05f);
    
    isAnswerFinished = false;
    //
    serialNo++;
    if (serialNo > plistArray->count()-1) {
        serialNo = 0;
    }
    
    propLayer_ = FightPropLayer::create();
    propLayer_->setDelegate(this);
    propLayer_->setAnchorPoint( ccp(0.5, 0.5) );
    propLayer_->setPosition( ccp(-size.width/2, -320) );
    this->addChild(propLayer_, 100, 100);
}

void QuestionLayer::timerCB()
{
    timerCount--;
    timerLabel_->setString(CCString::createWithFormat("%d", timerCount)->getCString());
    CCProgressFromTo* fromTo = CCProgressFromTo::create(1.0f, (timerCount+1)*1.0f/timerTotal*100, (timerCount)*1.0f/timerTotal*100);
    progressTimer->runAction(fromTo);
//    CCLOG("timerCB:%d", timerCount);
    if (timerCount <= 0)
    {
        errorAnswer++;
        this->noticeDelegate(nil, NULL);
    }
}

void QuestionLayer::displayActionTimerCB()
{
//    CCLOG("displayActionTimerCB");
    CCLabelTTF* title = (CCLabelTTF *)(this->getChildByTag(11));
    if (title) {
        if (displayLen >= questionString->length()) {
            this->unschedule(schedule_selector(QuestionLayer::displayActionTimerCB));
            title->setString(questionString->getCString()); //修补偶尔不显示bug
            //开启答题倒计时功能
            this->schedule(schedule_selector(QuestionLayer::timerCB), 1);
            return;
        }
        const char* s = questionString->m_sString.substr(displayLen, displayLen+1).c_str();
        if (s[0]>=0 && s[0]<=127) {
            displayLen += 1;
        } else {
            displayLen += 3;
        }
        const char* cstr = questionString->m_sString.substr(0, displayLen).c_str();
        if (cstr != NULL) {
            CCLOG("%s", cstr);
            title->setString(cstr);
        } else {
            CCLOG("error:发生了bug");
        }
    }
}

void QuestionLayer::setDelegate(QuestionLayerDelegate* delegate)
{
    mDelegate = delegate;
}

void QuestionLayer::touchDownAction(CCObject *sender, CCControlEvent controlEvent)
{
    CCLOG("QuestionLayer::touchDownAction");
    
    if (isAnswerFinished) {
        return;
    }
    this->unschedule(schedule_selector(QuestionLayer::timerCB));
    
    CCControlButton* button = (CCControlButton *)sender;
    CCLOG("%d", button->getTag());
    button->setEnabled(false);
    
    bool bFind = false;
    CCDictionary* results = questionObj->rightAnswer;
    for (int i=0; i<results->allKeys()->count(); i++) {
        CCString* key = (CCString *)(results->allKeys()->objectAtIndex(i));
        if (key->intValue() == button->getTag()) {
            results->setObject(CCString::createWithFormat("%d", 1), key->getCString());
            bFind = true;
            break;
        }
    }
    
    if (bFind) {
        //统计已经回答正确答案的数量
        int rCount = 0;
        for (int i=0; i<results->allKeys()->count(); i++) {
            CCString* key = (CCString *)(results->allKeys()->objectAtIndex(i));
            CCString* value = (CCString *)(results->objectForKey(key->getCString()));
            if (value->intValue() == 1) {
                rCount++;
            }
        }
        CCLOG("rCount:%d", rCount);
        
        if (rCount == results->allKeys()->count()) {
            //回答完成所有正确答案
            for (int i=0; i<results->allKeys()->count(); i++) {
                CCString* key = (CCString *)(results->allKeys()->objectAtIndex(i));
                CCControlButton* btn = (CCControlButton *)(this->getChildByTag(key->intValue()));
                CCSprite* spr = CCSprite::create("star000.png");
                spr->setAnchorPoint(ccp(0.5f, 0.5f));
                spr->setPosition(ccp(button->getContentSize().width/2, button->getContentSize().height/2));
                btn->addChild(spr);
                CCBlink* blink = CCBlink::create(1.0f, 3);
                if (i < results->allKeys()->count()-1) {
                    spr->runAction(blink);
                } else {
                    CCAction* pAction = CCCallFuncND::create(this, callfuncND_selector(QuestionLayer::noticeDelegate), NULL);
                    spr->runAction(CCSequence::create(blink, pAction, NULL));
                }
            }
            
            rightAnswer++;
            if (timerCount >= timerTotal*2/3) {
                rightLimit += 1;
                //播放快速答题音效
                GameSoundManager::shareManager()->playAnswerCool();
            } else {
                //播放普通答题正确音效
                GameSoundManager::shareManager()->playAnswerRight();
            }
            
            isAnswerFinished = true;
            
        } else {
            CCLOG("正确答案没选完");
        }
    } else {
        //回答错误
        CCSprite* spr = CCSprite::create("arrow000.png");
        spr->setAnchorPoint(ccp(0.5f, 0.5f));
        spr->setPosition(ccp(button->getContentSize().width/2, button->getContentSize().height/2));
        button->addChild(spr);
        CCFadeIn* fadeIn = CCFadeIn::create(1.0f);
        CCAction* pAction = CCCallFuncND::create(this, callfuncND_selector(QuestionLayer::noticeDelegate), NULL);
        spr->runAction(CCSequence::create(fadeIn, pAction, NULL));
        
        errorAnswer++;
        isAnswerFinished = true;
        
        //播放错误音效
        GameSoundManager::shareManager()->playAnswerError();
    }
}

void QuestionLayer::resetNextQuestion()
{
    this->removeAllChildren();
    if (questionObj) {
        questionObj->release();
    }
    this->startAnswer();
}

void QuestionLayer::noticeDelegate(cocos2d::CCObject *object, void *param)
{
    this->unschedule(schedule_selector(QuestionLayer::timerCB));
    
//    GameSoundManager::shareManager()->stopPlayBackgroundMusic();
    
    if ((rightAnswer+errorAnswer) >= number_in_group) { //每回答5道题,结算一次
        if (mDelegate) {
            mDelegate->answerDelegateCB(this, rightAnswer+rightLimit, errorAnswer);
        }
        //显示结算界面
        this->removeAllChildren();
        CCString* str = CCString::createWithFormat("结算结果\n答对:%d 答错:%d\n速答%d题", rightAnswer, errorAnswer, rightLimit);
        CCLabelTTF* label = CCLabelTTF::create(str->getCString(), "STHeitiK-Medium", 36);
        this->addChild(label);
    } else {
        //
        this->resetNextQuestion();
    }
}

void QuestionLayer::displaySubViews()
{
    CCLOG("%f %f %f %f", this->getPositionX(), this->getPositionY(), this->getContentSize().width, this->getContentSize().height);
    
    CCArray* answer = questionObj->answerArray;
    
    int columns = 0;
    int rows = 0;
    float spaceX = 0;
    if (answer->count() <= 2) {
        //判断题2X1个
        columns = 2;
        rows = 1;
        spaceX = 80;
    } else if (answer->count() <= 3) {
        //3选1
        columns = 1;
        rows = 3;
        spaceX = 50;
    } else if (answer->count() <= 4) {
        //最多2x2个答案选项的
        columns = 2;
        rows = (answer->count()*1.0f/columns)>(answer->count()/columns)?(answer->count()/columns+1):(answer->count()/columns);
        spaceX = 60;
    } else if (answer->count() <= 9) {
        //最多3x3个答案选项
        columns = 3;
        rows = (answer->count()*1.0f/columns)>(answer->count()/columns)?(answer->count()/columns+1):(answer->count()/columns);
        spaceX = 40;
    } else if (answer->count() <= 16) {
        //最多4x4个答案选项
        columns = 4;
        rows = (answer->count()*1.0f/columns)>(answer->count()/columns)?(answer->count()/columns+1):(answer->count()/columns);
        spaceX = 20;
    }
    float spaceY = spaceX;
    
    //题目标题栏高度
    float topHeight = 220;
    CCLOG("%f %f", this->getContentSize().width, this->getContentSize().height);
    //
    float totalWidth = this->getContentSize().width;
    float cellWidth = (totalWidth-spaceX*(columns+1))/columns;
    float totalHeight = this->getContentSize().height-topHeight; //要减去答题头部区域
    float cellHeight = (totalHeight-spaceY*(rows+1))/rows;
    CCLOG("[%d %d]:%f %f", columns, rows, cellWidth, cellHeight);
    while (cellHeight > cellWidth) {
        spaceY += 10;
        cellHeight = (totalHeight-spaceY*(rows+1))/rows;
    }
    for (int i=0; i<answer->count(); i++) {
        //
        CCString* ans = (CCString *)(answer->objectAtIndex(i));
        CCLabelTTF* pLabel = CCLabelTTF::create(ans->getCString(), "Arial", 24, CCSizeMake(cellWidth, cellHeight), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
        CCControlButton* button = CCControlButton::create(pLabel, CCScale9Sprite::create("button_answer.png", CCRectMake(0, 0, 126, 70)));
        button->addTargetWithActionForControlEvents(this, cccontrol_selector(QuestionLayer::touchDownAction), CCControlEventTouchUpInside);
        button->setTag(i+1);
        button->setAnchorPoint(ccp(0.5f, 0.5f));
//        button->setPosition( ccp(-totalWidth/2+spaceX+(cellWidth+spaceX)*(i%columns)+cellWidth/2, -topHeight/2-totalHeight/2+spaceY+(cellHeight+spaceY)*(i/columns)+cellHeight/2) );
        button->setPosition( ccp(-totalWidth/2+spaceX+(cellWidth+spaceX)*(i%columns)+cellWidth/2, (totalHeight-topHeight)/2-spaceY-(cellHeight+spaceY)*(i/columns)-cellHeight/2) );
        CCLOG("button坐标:%f %f", button->getPositionX(), button->getPositionY());
        button->setPreferredSize(CCSize(cellWidth, cellHeight));
        this->addChild(button, 1);
    }
}

void QuestionLayer::onEnter()
{
    CCLayer::onEnter();
}
void QuestionLayer::onExit()
{
    CCLayer::onExit();
}

void QuestionLayer::useProp(int propIndex)
{
    if (propIndex == 0) {
        this->resetNextQuestion();
    } else if (propIndex == 1) {
        //
    } else {
        //
    }
}
