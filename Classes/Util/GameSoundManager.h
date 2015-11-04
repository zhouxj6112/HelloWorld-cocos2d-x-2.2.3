//
//  SoundManager.h
//  HelloWorld
//
//  Created by MrZhou on 14-7-30.
//
//  游戏声音加载播放类

#ifndef HelloWorld_GameSoundManager_h
#define HelloWorld_GameSoundManager_h

class GameSoundManager
{
public:
    static GameSoundManager* shareManager();
    void preLoad();
    void playFightBackgroundMusic();
    void playAttackEffect(bool isHeavy);
    void playKOEffect();
    void playReadyEffect();
    void playGoEffect();
    void playWinEffect();
    void playReadyGoEffect();
private:
    GameSoundManager();
    virtual ~GameSoundManager();
};

#endif
