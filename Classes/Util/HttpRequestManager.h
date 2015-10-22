//
//  HttpRequestManager.h
//  HelloWorld
//
//  Created by MrZhou on 14-7-23.
//
//

#ifndef HelloWorld_HttpRequestManager_h
#define HelloWorld_HttpRequestManager_h

#include "cocos2d.h"
using namespace cocos2d;

#include "cocos-ext.h"
using namespace rapidjson;

class CC_DLL IHttpResponseData
{
public:
    virtual bool handleResponseData(const char* tag, rapidjson::Value& resValue) = 0;
};

class HttpRequestManager : public cocos2d::CCObject
{
private:
    HttpRequestManager();
    ~HttpRequestManager();
    void httpRequestDidFinished(cocos2d::CCNode* node, cocos2d::CCObject* obj);
public:
    static HttpRequestManager* shareManager();
    IHttpResponseData* mDelegate;
    void requestServer(const char* url, CCDictionary* paramDict, IHttpResponseData* responseDelegate, bool bShowLoading);
};

#endif
