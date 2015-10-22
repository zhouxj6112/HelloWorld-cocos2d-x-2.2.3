//
//  GameMissionScene.h
//  HelloWorld
//
//  Created by MrZhou on 14-7-23.
//
//

#ifndef HelloWorld_LevelScene_h
#define HelloWorld_LevelScene_h

#include "cocos2d.h"
#include "HttpRequestManager.h"
#include "CCGameScrollView.h"
#include "JobHuntingScene.h"
#include "RoleObj.h"

class LevelScene : public cocos2d::CCLayer, public IHttpResponseData, public CCCGameScrollViewDelegate
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(LevelScene);
    
    CCCGameScrollView* mScrollView;
    RoleObj* _player;
    
public:
    virtual bool handleResponseData(const char* tag, rapidjson::Value& resValue);
    
    void login();
    
    //以下五个方法必须继承
    //滚动触发
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView *view);
    //缩放触发
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView *view);
    //初始化每个单独页面,pPage为这个页面的容器,nPage是这个页面的ID
    virtual bool scrollViewInitPage(cocos2d::CCNode *pScroll, cocos2d::CCNode *pPage, int nPage);
    //点击某个页面处理
    virtual void scrollViewClick(const cocos2d::CCPoint &oOffset, const cocos2d::CCPoint &oPoint , cocos2d::CCNode *pPage, int nPage);
    //每一次滑动后结束的回调,可以在这里处理一些事情
    virtual void scrollViewScrollEnd(cocos2d::CCNode *pPage, int nPage);
    
private:
    virtual void onEnter();
    virtual void onExit();
    int displayMissionLv;
};

#endif
