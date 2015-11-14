//
//  GameSoundManager.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-7-30.
//
//

#include "GameSoundManager.h"
#include "SimpleAudioEngine.h"

static GameSoundManager* manager;

GameSoundManager* GameSoundManager::shareManager()
{
    if (manager == NULL) {
        manager = new GameSoundManager();
    }
    return manager;
}

GameSoundManager::GameSoundManager()
{
}
GameSoundManager::~GameSoundManager()
{
}

void GameSoundManager::preLoad()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("拳皇背景.mp3");
}

void GameSoundManager::playFightBackgroundMusic()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("拳皇背景.mp3", true);
}

void GameSoundManager::stopPlayBackgroundMusic()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
}

void GameSoundManager::playAttackEffect(bool isHeavy)
{
    if (!isHeavy) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("普通攻击.mp3");
    } else {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("重击.mp3");
    }
}

void GameSoundManager::playKOEffect()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("KO.mp3");
}

void GameSoundManager::playReadyEffect()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Ready.mp3");
}

void GameSoundManager::playGoEffect()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("GO.mp3");
}

void GameSoundManager::playWinEffect()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("欢呼.mp3");
}

void GameSoundManager::playReadyGoEffect()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ready_go.mp3");
}

void GameSoundManager::playAnswerRight()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("正确回答.mp3");
}
void GameSoundManager::playAnswerError()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("回答错误.mp3");
}
void GameSoundManager::playAnswerCool()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("cool.mp3");
}
