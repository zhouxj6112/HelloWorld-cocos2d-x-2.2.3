//
//  QuestionObj.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-10-26.
//
//

#include "QuestionObj.h"

QuestionObj::QuestionObj()
{
}

QuestionObj::~QuestionObj()
{
    questionString->release();
    answerArray->release();
    rightAnswer->release();
}

QuestionObj::QuestionObj(int qType, const char* qStr, CCArray* qAnswer)
{
    questionType = qType;
    questionString = CCString::create(qStr);
    questionString->retain();
    answerArray = CCArray::createWithCapacity(4);
    answerArray->retain();
    rightAnswer = CCDictionary::create();
    rightAnswer->retain();
    for (int i=0; i<qAnswer->count(); i++) {
        CCDictionary* dic = (CCDictionary *)(qAnswer->objectAtIndex(i));
        answerArray->addObject(dic->objectForKey("content"));
        CCString* bString = (CCString *)(dic->objectForKey("right"));
        if (bString->boolValue()) {
            rightAnswer->setObject(CCString::create("0"), CCString::createWithFormat("%d", i+1)->getCString()); //正确答案
        }
    }
}