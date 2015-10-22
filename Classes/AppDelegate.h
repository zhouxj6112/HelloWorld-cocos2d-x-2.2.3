#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"
#include "WebSocketManager.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class  AppDelegate : private cocos2d::CCApplication, public IWebSocket
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
    
public:
    //网络读取消息
    virtual bool OnSocketReadEvent(NetMessageHead* pNetHead, void* pNetData, unsigned int uDataSize, WebSocketManager* pClientSocket);
    //网络连接消息
    virtual bool OnSocketConnectEvent(unsigned int uErrorCode, WebSocketManager* pClientSocket);
    //网络关闭消息
    virtual bool OnSocketCloseEvent();
};

#endif // _APP_DELEGATE_H_

