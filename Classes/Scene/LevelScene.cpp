//
//  GameMissionScene.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-7-23.
//
//

#include "LevelScene.h"
#include "MissionScene.h"
#include "Global.h"
#include "Utils.h"

USING_NS_CC;

CCScene* LevelScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    // 'layer' is an autorelease object
    LevelScene *layer = LevelScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LevelScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    displayMissionLv = Global::shareInstance()->missionGate;
    
    mScrollView = CCCGameScrollView::create();
    mScrollView->setDirection(kCCScrollViewDirectionHorizontal);
    mScrollView->createContainer(this, 5, CCSizeMake(CCDirector::sharedDirector()->getVisibleSize().width*0.85f, CCDirector::sharedDirector()->getVisibleSize().height));
    mScrollView->setPosition(ccp(0, 0));
    mScrollView->setViewSize(CCDirector::sharedDirector()->getVisibleSize());
    this->addChild(mScrollView);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    //行走主角
    _player = new RoleObj(this);
    _player->init();
//    _role->setDelegate(this);
    _player->setPosition(size.width/2, 240);
    _player->changeToStatus(STATUS_STAND);
    //不显示血条
    _player->hiddenHealthBar();
    
    return true;
}

void LevelScene::login()
{
    CCDictionary* param = CCDictionary::create();
    param->setObject(CCString::create("1"), "pageNo");
    param->setObject(CCString::create("20"), "pageSize");
    HttpRequestManager::shareManager()->requestServer("http://uphone.3g.tianya.cn/v/proxy/travel/note.getHotNotes/?", param, this, false);
}

bool LevelScene::handleResponseData(const char* tag, rapidjson::Value& resValue)
{
    rapidjson::Value& list = resValue["list"];
    if (list.IsArray())
    {
        for (int i=0; i<list.Size(); i++) {
            rapidjson::Value& obj = list[i];
            CCLOG("%s:%s", obj["travelId"].GetString(), obj["travelName"].GetString());
        }
    }
        
    return true;
}

void LevelScene::scrollViewDidScroll(cocos2d::extension::CCScrollView *view)
{
    static CCPoint ptPre = CCPointZero;
    CCPoint pt = view->getContentOffset();
    CCLOG("%f %f", pt.x, pt.y);
    if (pt.x < ptPre.x) {
        CCLOG("向右");
        if (_player->curDir==DIRECTION_RIGHT && _player->curStatus==STATUS_RUN) {
            //继续
        } else {
            //切换到向右跑动动画
            _player->changeToStatus(STATUS_RUN, 0, 0, DIRECTION_RIGHT);
        }
    } else if (pt.x > ptPre.x) {
        CCLOG("向左");
        if (_player->curDir==DIRECTION_LEFT && _player->curStatus==STATUS_RUN) {
            //继续
        } else {
            //切换到向左跑动动画
            _player->changeToStatus(STATUS_RUN, 0, 0, DIRECTION_LEFT);
        }
    }
    ptPre = pt;
}
void LevelScene::scrollViewDidZoom(cocos2d::extension::CCScrollView *view)
{

}
bool LevelScene::scrollViewInitPage(cocos2d::CCNode *pScroll, cocos2d::CCNode *pPage, int nPage)
{
    CCString* str = CCString::createWithFormat("%03d.png", nPage+1);
    CCSprite *sprite = CCSprite::create(str->getCString());
    if (nPage < Global::shareInstance()->missionGate) {
        //星级标示
        CCSprite* star = CCSprite::create("star000.png");
        star->setAnchorPoint(ccp(0.5f, 0.5f));
        star->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height/2));
        sprite->addChild(star, 0, 100);
    } else if (nPage == Global::shareInstance()->missionGate) {
        //
        CCSprite* star = CCSprite::create("start_n.png");
        star->setAnchorPoint(ccp(0.5f, 0.5f));
        star->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height/2));
        sprite->addChild(star, 0, 101);
    } else {
        //黑白效果
        sprite = createGraySprite(str->getCString());
    }
    pPage->addChild(sprite, 1, 30);
    return true;
}
void LevelScene::scrollViewClick(const cocos2d::CCPoint &oOffset, const cocos2d::CCPoint &oPoint, cocos2d::CCNode *pPage, int nPage)
{
    if (nPage <= Global::shareInstance()->missionGate) {
        CCScene* pScene = MissionScene::scene();
        CCDirector::sharedDirector()->pushScene(pScene);
    }
}
void LevelScene::scrollViewScrollEnd(cocos2d::CCNode *pPage, int nPage)
{
    CCLOG("Current Page = %d", nPage);
    if (_player->curDir == DIRECTION_LEFT) {
        //向左站立动画
        _player->changeToStatus(STATUS_STAND, 0, DIRECTION_LEFT);
    } else if (_player->curDir== DIRECTION_RIGHT) {
        //向右站立动画
        _player->changeToStatus(STATUS_STAND, 0, DIRECTION_RIGHT);
    }
}

void LevelScene::onEnter()
{
    CCLayer::onEnter();
    
    if (displayMissionLv < Global::shareInstance()->missionGate) {
        mScrollView->scrollToPage(Global::shareInstance()->missionGate);
        //
        for (int i=0; i<Global::shareInstance()->missionGate+1; i++) {
            //
            CCNode* pNode = mScrollView->getPage(i);
            CCSprite* spr = (CCSprite *)pNode->getChildByTag(30);
            if (spr) {
                CCString* str = CCString::createWithFormat("%03d.png", i+1);
                spr->setTexture(CCSprite::create(str->getCString())->getTexture());
            }
            if (i < Global::shareInstance()->missionGate) {
                CCSprite* star = (CCSprite *)(this->getChildByTag(100));
                if (star == NULL) {
                    star = CCSprite::create("star000.png");
                    star->setAnchorPoint(ccp(0.5f, 0.5f));
                    star->setPosition(ccp(spr->getContentSize().width/2, spr->getContentSize().height/2));
                    spr->addChild(star, 0, 100);
                }
            } else {
                CCSprite* star = (CCSprite *)(this->getChildByTag(100));
                if (star == NULL) {
                    star = CCSprite::create("start_n.png");
                    star->setAnchorPoint(ccp(0.5f, 0.5f));
                    star->setPosition(ccp(spr->getContentSize().width/2, spr->getContentSize().height/2));
                    spr->addChild(star, 0, 101);
                }
            }
        }
    }
    displayMissionLv = Global::shareInstance()->missionGate;
}

void LevelScene::onExit()
{
    CCLayer::onExit();
}
