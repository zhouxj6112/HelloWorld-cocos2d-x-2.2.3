//
//  RequestUrl.h
//  HelloWorld
//
//  Created by MrZhou on 14-7-23.
//
//

#ifndef HelloWorld_RequestUrl_h
#define HelloWorld_RequestUrl_h

#include "cocos2d.h"

class CC_DLL RequestDelegate
{
public:
    virtual bool handleNetworkData(const char* tag, tinyxml2::XMLNode* xmlData) = 0;
};

class HttpRequestManager : public cocos2d:CCObject
{
private:
    HttpRequestManager();
    ~HttpRequestManager();
public:
    static HttpRequestManager* shareManager();
};

#endif
