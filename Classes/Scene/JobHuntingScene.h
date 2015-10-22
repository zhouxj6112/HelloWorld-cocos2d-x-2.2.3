//
//  JobHuntingScene.h
//  HelloWorld
//
//  Created by MrZhou on 14-6-25.
//
//

#ifndef HelloWorld_JobHuntingScene_h
#define HelloWorld_JobHuntingScene_h

#include "cocos2d.h"

//地图上的一个元素
struct mapItem : public cocos2d::CCObject
{
    int i; //行
    int j; //列
    unsigned char type;     //包含的元素类型 0空 1 2 3墙体 A移动箱子 C目的地
    unsigned int status;    //砖块的状态 0等待被销毁 1还能撞击一次 2还能撞击2次才会被装破 3......
    cocos2d::CCSprite* sprite;
    bool containStar;       //是否包含星星
public:
    mapItem() {type='0'; status=0; sprite=NULL;}
    ~mapItem() {};
};

//typedef enum {
//    DIRECTION_RIGHT = 1,
//    DIRECTION_DOWN  = 2,
//    DIRECTION_LEFT  = 3,
//    DIRECTION_UP    = 4
//} HWPlayerDirection;

class Player : public cocos2d::CCObject
{
public:
    cocos2d::CCSprite* sprite;
    int status;      //角色状态 (站立|运动)
    int direction;   //朝向
};

class JobHunting : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(JobHunting);
    
    void randomStep(CCObject* pSender);
    void exitScene(CCObject* pSender);
    //递归寻路算法
    void searchRoadPath(mapItem* pItem, int moveCount, mapItem* preItem);
    
    cocos2d::CCMenu* mMenu;
    
private:
    cocos2d::CCSprite* m_mapSpr;
    float deltax;
    float deltay;
    float distance;
    float mscale;
    
    float PIX_PTM_RATIO;
    
    void readMapFile();
    void addGameSpriteWithCoords(cocos2d::CCPoint p, mapItem* pItem);
    mapItem* mapItemArray[10][10];   //地图数组
    
    Player* m_role;
    
    cocos2d::CCArray* mPathArray;
    
    void moveStop(CCObject* object, void* param);
};

#endif
