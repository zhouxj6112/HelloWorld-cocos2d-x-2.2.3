//
//  WebSocketManager.h
//  HelloWorld
//
//  Created by MrZhou on 14-7-8.
//
//

#ifndef HelloWorld_WebSocketManager_h
#define HelloWorld_WebSocketManager_h

#include "cocos2d.h"

#include "network/WebSocket.h"

//消息头定义
struct NetMessageHead
{
    unsigned long uMessageSize;   //消息总长度=(消息头长度+消息体长度)
    unsigned long bMainID;        //处理主类型
    unsigned long bAssistantID;   //辅助处理类型
    unsigned long bHandleCode;    //处理代码 (消息处理的优先级)
    unsigned long bReserve;       //保留字段
};

class WebSocketManager;

class CC_DLL IWebSocket : public cocos2d::CCObject
{
public:
    //网络读取消息
    virtual bool OnSocketReadEvent(NetMessageHead* pNetHead, void* pNetData, unsigned int uDataSize, WebSocketManager* pClientSocket) = 0;
    //网络连接消息
    virtual bool OnSocketConnectEvent(unsigned int uErrorCode, WebSocketManager* pClientSocket) = 0;
    //网络关闭消息
    virtual bool OnSocketCloseEvent() = 0;
};

class WebSocketManager : public cocos2d::CCObject, cocos2d::extension::WebSocket::Delegate
{
private:
    WebSocketManager();
    virtual ~WebSocketManager();
    
public:
    static WebSocketManager* shareManager();
    //添加代理
    void addDelegate(IWebSocket *pIService);
    //移除代理
    void removeDelegate(IWebSocket *pIService);
    //
    bool sendMessage();
private:
    virtual void onOpen(cocos2d::extension::WebSocket* ws);
    virtual void onMessage(cocos2d::extension::WebSocket* ws, const cocos2d::extension::WebSocket::Data& data);
    virtual void onClose(cocos2d::extension::WebSocket* ws);
    virtual void onError(cocos2d::extension::WebSocket* ws, const cocos2d::extension::WebSocket::ErrorCode& error);
    //
    cocos2d::CCArray* m_delegates;
    //
    cocos2d::extension::WebSocket* webSocket;
};

#endif
