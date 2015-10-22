//
//  WebSocketManager.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-7-8.
//
//

#include "WebSocketManager.h"
#include "NetworkProtocol.h"

WebSocketManager* WebSocketManager::shareManager()
{
    static WebSocketManager* manager = NULL;
    if (manager == NULL) {
        manager = new WebSocketManager();
    }
    return manager;
}

WebSocketManager::WebSocketManager()
{
    m_delegates = cocos2d::CCArray::createWithCapacity(1);
    m_delegates->retain();
    cocos2d::extension::WebSocket* socket = new cocos2d::extension::WebSocket();
    socket->init(*this, "ws://echo.websocket.org");
}

WebSocketManager::~WebSocketManager()
{
}

void WebSocketManager::addDelegate(IWebSocket *pIService)
{
    m_delegates->addObject(pIService);
}

void WebSocketManager::removeDelegate(IWebSocket *pIService)
{
    m_delegates->removeObject(pIService);
}

bool WebSocketManager::sendMessage()
{
    LoginRequestData request;
    request.loginType = 3;
    webSocket->send((unsigned char*)&request, sizeof(request));
    return true;
}

void WebSocketManager::onOpen(cocos2d::extension::WebSocket* ws)
{
    CCLOG("websocket onOpen:%p", ws);
    webSocket = ws;
    char buf[] = "Hello WebSocket,中文!~~~";
    ws->send((unsigned char*)buf, sizeof(buf));
}

void WebSocketManager::onMessage(cocos2d::extension::WebSocket* ws, const cocos2d::extension::WebSocket::Data& data)
{
    CCLOG("%d:%s", data.len, data.bytes);
    for (int i=0; i<m_delegates->count(); i++) {
        IWebSocket* pWebSocket = (IWebSocket *)m_delegates->objectAtIndex(i);
        if (pWebSocket->OnSocketReadEvent(NULL, data.bytes, data.len, this)) {
            CCLOG("有类[%p]处理了", pWebSocket);
            break;
        }
    }
}

void WebSocketManager::onClose(cocos2d::extension::WebSocket* ws)
{
    
}

void WebSocketManager::onError(cocos2d::extension::WebSocket* ws, const cocos2d::extension::WebSocket::ErrorCode& error)
{
    
}
