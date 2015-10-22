//
//  HttpRequestManager.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-7-23.
//
//

#include "HttpRequestManager.h"

#include "cocos-ext.h"
USING_NS_CC_EXT;


HttpRequestManager::HttpRequestManager()
{
}

HttpRequestManager::~HttpRequestManager()
{
}

HttpRequestManager* HttpRequestManager::shareManager()
{
    HttpRequestManager* request = new HttpRequestManager();
    return request;
}

void HttpRequestManager::requestServer(const char* url, CCDictionary* paramDict, IHttpResponseData* responseDelegate, bool bShowLoading)
{
    mDelegate = responseDelegate;
    
    //发出网络请求
    CCHttpClient* httpClient = CCHttpClient::getInstance();
    CCHttpRequest* httpReq = new CCHttpRequest();
    httpReq->setRequestType(CCHttpRequest::kHttpGet);
    httpReq->setUrl(url);
    httpReq->setTag(url);
    httpReq->setResponseCallback(this, callfuncND_selector(HttpRequestManager::httpRequestDidFinished));
    httpClient->send(httpReq);
    httpReq->release();
}

void HttpRequestManager::httpRequestDidFinished(CCNode* node, CCObject* obj)
{
    CCHttpResponse* response = (CCHttpResponse *)obj;
    const char* tag = response->getHttpRequest()->getTag();
    
    if (!response->isSucceed())
    {
        CCLOG("http[%s] Receive Error! %s\n", tag, response->getErrorBuffer());
        return ;
    }
    
    std::vector<char>* data = response->getResponseData();
    int data_length = data->size();
    std::string res;
    for (int i=0; i<data_length; ++i)
    {
        res += (*data)[i];
    }
    res += '\0';
    CCLOG("%s", res.c_str());
    
    rapidjson::Document doc;
    doc.Parse<kParseDefaultFlags>(res.c_str());
    rapidjson::Value& resValue = doc["data"];
    
    if (mDelegate)
    {
        mDelegate->handleResponseData(tag, resValue);
    }
}
