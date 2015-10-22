//
//  QuestionObj.h
//  HelloWorld
//
//  Created by MrZhou on 14-10-26.
//
//

#ifndef HelloWorld_QuestionObj_h
#define HelloWorld_QuestionObj_h

#include "cocos2d.h"
USING_NS_CC;

class QuestionObj : public cocos2d::CCObject
{
public:
    int questionType;                  //问题类型
    cocos2d::CCString* questionString; //问题标题
    cocos2d::CCArray*  answerArray;    //供选择的答案
    cocos2d::CCDictionary* rightAnswer;
private:
    QuestionObj();
    virtual ~QuestionObj();
public:
    QuestionObj(int qType, const char* qStr, CCArray* qAnswer);
};

#endif
