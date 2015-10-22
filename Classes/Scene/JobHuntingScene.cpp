//
//  JobHuntingScene.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-6-25.
//
//

#include "JobHuntingScene.h"
#include "PlayerObj.h"

USING_NS_CC;

CCScene* JobHunting::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    JobHunting *layer = JobHunting::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool JobHunting::init()
{
    //////////////////////////////
    // 1. super init first
    if (!CCLayer::init()) {
        return false;
    }
    
    this->setTouchEnabled(true);
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
    PIX_PTM_RATIO = 64;
    
    m_mapSpr = CCSprite::create();
    m_mapSpr->setAnchorPoint(ccp(0.5f, 0.5f));
    m_mapSpr->setPosition(ccp(0, 0));
    this->addChild(m_mapSpr, 0);
    
    CCMenuItemFont* pMenuItem1 = CCMenuItemFont::create("掷骰子", this, menu_selector(JobHunting::randomStep));
    pMenuItem1->setFontSizeObj(30);
    pMenuItem1->setColor(cocos2d::ccc3(0,255,255));
    pMenuItem1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width-60, CCDirector::sharedDirector()->getWinSize().height-60));
    pMenuItem1->setTag(1);
    CCMenuItemFont* pMenuItem2 = CCMenuItemFont::create("返回", this, menu_selector(JobHunting::exitScene));
    pMenuItem2->setFontSizeObj(30);
    pMenuItem2->setColor(cocos2d::ccc3(0,255,255));
    pMenuItem2->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width-60, 60));
    // create menu, it's an autorelease object
    mMenu = CCMenu::create(pMenuItem1, pMenuItem2, NULL);
    mMenu->setPosition(CCPointZero);
    this->addChild(mMenu, 1, 100);
    
    this->readMapFile();
    
    m_role = new Player();
    CCSprite* spr = CCSprite::create("star000.png");
    spr->setAnchorPoint(ccp(0.5f, 0.5f));
    m_mapSpr->addChild(spr, 1);
    m_role->sprite = spr;
    m_role->status = 0;
    m_role->direction = DIRECTION_RIGHT;
    
    mapItem* pItem = mapItemArray[0][0];
    spr->setPosition(pItem->sprite->getPosition());
    CCScaleBy* scaleBy = CCScaleBy::create(0.5f, 0.8);
    CCAction* repeatAction = CCRepeatForever::create(CCSequence::create(scaleBy, scaleBy->reverse(), NULL));
    repeatAction->setTag(0);
    spr->runAction(repeatAction);
    
    if (mPathArray == NULL) {
        mPathArray = CCArray::createWithCapacity(10);
        mPathArray->retain();
    }
    mPathArray->addObject(pItem);
    
    return true;
}

void JobHunting::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    if (pTouches->count() >= 2) {
        CCSetIterator iter = pTouches->begin();
        CCPoint mPoint1 = ((CCTouch*)(*iter))->getLocation();
        mPoint1 = CCDirector::sharedDirector()->convertToGL(mPoint1);
        iter ++;
        CCPoint mPoint2 = ((CCTouch*)(*iter))->getLocation();
        mPoint2 = CCDirector::sharedDirector()->convertToGL(mPoint2);
        
        distance = sqrt((mPoint1.x - mPoint2.x) * (mPoint1.x - mPoint2.x) + (mPoint1.y - mPoint2.y) * (mPoint1.y - mPoint2.y));
        
        deltax = (mPoint1.x + mPoint2.x)/2 - m_mapSpr->getPositionX();
        deltay = (mPoint1.y + mPoint2.y)/2 - m_mapSpr->getPositionY();
    }
}

void JobHunting::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    if (pTouches->count() == 1) {
        CCSetIterator iter=pTouches->begin();
        CCTouch* pTouch = (CCTouch*)(*iter);
        CCPoint pt = pTouch->getLocation()-pTouch->getPreviousLocation();
        m_mapSpr->setPosition(m_mapSpr->getPosition()+pt);
    } else if (pTouches->count() >= 2) {
        CCSetIterator iter = pTouches->begin();
        CCPoint mPoint1 = ((CCTouch*)(*iter))->getLocation();
        mPoint1 = CCDirector::sharedDirector()->convertToGL(mPoint1);
        iter ++;
        CCPoint mPoint2 = ((CCTouch*)(*iter))->getLocation();
        mPoint2 = CCDirector::sharedDirector()->convertToGL(mPoint2);
        
        float mdistance = sqrt((mPoint1.x - mPoint2.x) * (mPoint1.x - mPoint2.x) + (mPoint1.y - mPoint2.y) * (mPoint1.y - mPoint2.y));
        
        mscale = mdistance / distance * mscale;
        
        distance = mdistance;
        
        m_mapSpr->setScale(mscale);
        CCLOG("%f", mscale);
        
        float x = (mPoint1.x + mPoint2.x)/2 - deltax;
        float y = (mPoint1.y + mPoint2.y)/2 - deltax;
        m_mapSpr->setPosition(ccp(x,y));
        deltax = (mPoint1.x + mPoint2.x)/2 - m_mapSpr->getPositionX();
        deltay = (mPoint1.y + mPoint2.y)/2 - m_mapSpr->getPositionY();
    }
}

void JobHunting::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    
}

void JobHunting::exitScene(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
}

void JobHunting::randomStep(CCObject* pSender)
{
    if (m_role->status == 1) {
        return;
    }
    
    CCSprite* spr = m_role->sprite;
    spr->stopAllActions();
    spr->setScale(1.0f);
    
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    CCLOG("%d", mPathArray->count());
    mapItem* preItem = NULL;
    mapItem* roleItem = NULL;
    if (mPathArray->count() > 0) {
        roleItem = (mapItem *)(mPathArray->lastObject());
        roleItem->retain();
    }
    if (mPathArray->count() > 1) {
        preItem = (mapItem *)(mPathArray->objectAtIndex(mPathArray->count()-2));
        preItem->retain();
        CCLOG("%p", preItem);
    }
    mPathArray->removeAllObjects();
    mPathArray->addObject(roleItem);
    CCLOG("%d, %p, %p", mPathArray->count(), preItem, roleItem);
    
    int step = arc4random()%10+1;
    CCLOG("随机数:%d", step);
    CCMenuItemFont* pFont = (CCMenuItemFont *)(mMenu->getChildByTag(1));
    pFont->setString(CCString::createWithFormat("骰子:%d点", step)->getCString());
    //计算
    this->searchRoadPath(roleItem, step, preItem);
    
    CCArray* array = CCArray::createWithCapacity(mPathArray->count()+1);
    for (int i=0; i<mPathArray->count(); i++) {
//        mapItem* pItem = (mapItem *)(mPathArray->objectAtIndex(i));
        //CCLOG("坐标:%d-%d", pItem->i, pItem->j);
        
        mapItem* pCurItem = NULL;
        if (i == 0) {
            pCurItem = roleItem;
        } else {
            pCurItem = (mapItem *)(mPathArray->objectAtIndex(i-1));
        }
        mapItem* pNext = (mapItem *)(mPathArray->objectAtIndex(i));
        
        if (pNext->i == pCurItem->i) {
            if (pNext->j > pCurItem->j) {
                //向右
                CCAnimation* pAnimation = CCAnimation::create();
                for (int i=0; i<3; i++)
                {
                    CCSpriteFrame* pFrame = CCSpriteFrame::create("role_walk.png", CCRectMake((9+i)*24, 32*1, 24, 32));
                    pAnimation->addSpriteFrame(pFrame);
                }
                pAnimation->setRestoreOriginalFrame(true);
                pAnimation->setDelayPerUnit(0.5f/3);    // 必须设置这个，要不就不会播放
                pAnimation->setLoops(1);
                CCAnimate* pAnimate = CCAnimate::create(pAnimation);
                //
                CCMoveTo* pMove = CCMoveTo::create(0.5f, pNext->sprite->getPosition());
                //一起执行的动画
                CCSpawn* pSpawn = CCSpawn::create(pAnimate, pMove, NULL);
                array->addObject(pSpawn);
            } else if (pNext->j < pCurItem->j) {
                //向左
                CCAnimation* pAnimation = CCAnimation::create();
                for (int i=0; i<3; i++)
                {
                    CCSpriteFrame* pFrame = CCSpriteFrame::create("role_walk.png", CCRectMake((9+i)*24, 32*3, 24, 32));
                    pAnimation->addSpriteFrame(pFrame);
                }
                pAnimation->setRestoreOriginalFrame(true);
                pAnimation->setDelayPerUnit(0.5f/3);    // 必须设置这个，要不就不会播放
                pAnimation->setLoops(1);
                CCAnimate* pAnimate = CCAnimate::create(pAnimation);
                //
                CCMoveTo* pMove = CCMoveTo::create(0.5f, pNext->sprite->getPosition());
                //一起执行的动画
                CCSpawn* pSpawn = CCSpawn::create(pAnimate, pMove, NULL);
                array->addObject(pSpawn);
            }
        } else {
            if (pNext->i > pCurItem->i) {
                //向下
                CCAnimation* pAnimation = CCAnimation::create();
                for (int i=0; i<3; i++)
                {
                    CCSpriteFrame* pFrame = CCSpriteFrame::create("role_walk.png", CCRectMake((9+i)*24, 32*2, 24, 32));
                    pAnimation->addSpriteFrame(pFrame);
                }
                pAnimation->setRestoreOriginalFrame(true);
                pAnimation->setDelayPerUnit(0.5f/3);    // 必须设置这个，要不就不会播放
                pAnimation->setLoops(1);
                CCAnimate* pAnimate = CCAnimate::create(pAnimation);
                //
                CCMoveTo* pMove = CCMoveTo::create(0.5f, pNext->sprite->getPosition());
                //一起执行的动画
                CCSpawn* pSpawn = CCSpawn::create(pAnimate, pMove, NULL);
                array->addObject(pSpawn);
            } else if (pNext->i < pCurItem->i) {
                //向上
                CCAnimation* pAnimation = CCAnimation::create();
                for (int i=0; i<3; i++)
                {
                    CCSpriteFrame* pFrame = CCSpriteFrame::create("role_walk.png", CCRectMake((9+i)*24, 32*0, 24, 32));
                    pAnimation->addSpriteFrame(pFrame);
                }
                pAnimation->setRestoreOriginalFrame(true);
                pAnimation->setDelayPerUnit(0.5f/3);    // 必须设置这个，要不就不会播放
                pAnimation->setLoops(1);
                CCAnimate* pAnimate = CCAnimate::create(pAnimation);
                //
                CCMoveTo* pMove = CCMoveTo::create(0.5f, pNext->sprite->getPosition());
                //一起执行的动画
                CCSpawn* pSpawn = CCSpawn::create(pAnimate, pMove, NULL);
                array->addObject(pSpawn);
            }
        }
    }
    CCAction* moveStopCallFunc = CCCallFuncND::create(this, callfuncND_selector(JobHunting::moveStop), NULL);
    array->addObject(moveStopCallFunc);
    CCSequence* sequence = CCSequence::create(array);
    spr->runAction(sequence);
    m_role->status = 1;
}

void JobHunting::moveStop(CCObject* object, void* param)
{
    CCSprite* spr = m_role->sprite;
    CCScaleBy* scaleBy = CCScaleBy::create(0.5f, 0.8);
    CCAction* pRepeatAction = CCRepeatForever::create(CCSequence::create(scaleBy, scaleBy->reverse(), NULL));
    pRepeatAction->setTag(0);
    spr->runAction(pRepeatAction);
    m_role->status = 0;
    CCMenuItemFont* pFont = (CCMenuItemFont *)(mMenu->getChildByTag(1));
    pFont->setString("掷骰子");
}

void JobHunting::searchRoadPath(mapItem* pItem, int moveCount, mapItem* preItem)
{
    CCLOG("节点:%p:%d %d", pItem, pItem->i, pItem->j);
    if (pItem==NULL || moveCount<=0) {
        return ;
    }
    CCLOG("前一个节点:%p", preItem);
    
    mapItem* pNext = NULL;
    //向右
    mapItem* pRight = NULL;
    if (pItem->j+1 < 10) {
        pRight = mapItemArray[pItem->i][pItem->j+1];
    }
    if (pRight!=NULL && pRight->type!='0' && pRight!=preItem) {
        pNext = pRight;
    } else {
        //向下
        mapItem* pDown = NULL;
        if (pItem->i+1 < 10) {
            pDown = mapItemArray[pItem->i+1][pItem->j];
        }
        if (pDown!=NULL && pDown->type!='0' && pDown!=preItem) {
            pNext = pDown;
        } else {
            //向左
            mapItem* pLeft = NULL;
            if (pItem->j-1 >= 0) {
                pLeft = mapItemArray[pItem->i][pItem->j-1];
            }
            if (pLeft!=NULL && pLeft->type!='0' && pLeft!=preItem) {
                pNext = pLeft;
            } else {
                //向上
                mapItem* pUp = NULL;
                if (pItem->i-1 >= 0) {
                    pUp = mapItemArray[pItem->i-1][pItem->j];
                }
                if (pUp!=NULL && pUp->type!='0' && pUp!=preItem) {
                    pNext = pUp;
                }
            }
        }
    }
    if (pNext != NULL) {
        mPathArray->addObject(pNext);
        searchRoadPath(pNext, moveCount-1, pItem);
    } else {
        CCLOG("找不到下一步");
    }
}

void JobHunting::readMapFile()
{
    //分配内存
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            mapItem* pItem = new mapItem();
            pItem->i = i;
            pItem->j = j;
            mapItemArray[i][j] = pItem;
            CCLOG("节点:%p:%d %d", pItem, pItem->i, pItem->j);
        }
    }
    
    unsigned long size;
    unsigned char* pFileContent = cocos2d::CCFileUtils::sharedFileUtils()->getFileData("map1-3.txt", "r", &size);
    if (pFileContent) {
        CCLOG("file content:\n%s", pFileContent);
        int k = 0;
        for (int i=0; i<size; i++) {
            char c = pFileContent[i];
            if (c == '{') {
                mapItem* item = mapItemArray[k/10][k%10];
                item->type = pFileContent[i+1];
                switch (pFileContent[i+3]) {
                    case '0':
                        item->status = 0;
                        break;
                    case '1':
                        item->status = 1;
                        break;
                    case '2':
                        item->status = 2;
                        break;
                    default:
                        break;
                }
                if (pFileContent[i+5] == '0') {
                    item->containStar = false;
                } else {
                    item->containStar = true;
                }
                item->sprite = NULL;
                k++;
            }
        }
    }
    
    CCLOG("<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    for (int i=0; i<10; i++) {
        CCLOG("%c %c %c %c %c %c %c %c %c %c", mapItemArray[i][0]->type, mapItemArray[i][1]->type, mapItemArray[i][2]->type, mapItemArray[i][3]->type, mapItemArray[i][4]->type, mapItemArray[i][5]->type, mapItemArray[i][6]->type, mapItemArray[i][7]->type, mapItemArray[i][8]->type, mapItemArray[i][9]->type);
    }
    CCLOG(">>>>>>>>>>>>>>>>>>>>>>>>>>>");
    
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            //先填充底层背景
            mapItem* pItem = mapItemArray[i][j];
            addGameSpriteWithCoords(ccp((j+0.5)*PIX_PTM_RATIO, (9-i+0.5)*PIX_PTM_RATIO), pItem);
        }
    }
}

void JobHunting::addGameSpriteWithCoords(cocos2d::CCPoint p, mapItem* pItem)
{
    if (pItem->type == '1' || pItem->type=='2' || pItem->type=='3' || pItem->type=='4') {
        CCSprite *sprite = CCSprite::create("bkg_title.png");
        sprite->setPosition(ccp(p.x, p.y));
        sprite->setAnchorPoint(ccp(0.5f, 0.5f));
        sprite->setScale(PIX_PTM_RATIO/64);
        m_mapSpr->addChild(sprite, 0, 1);
        pItem->sprite = sprite; //赋值指针
    }
}
