//
//  Util.h
//  HelloWorld
//
//  Created by MrZhou on 14-10-26.
//
//

#ifndef HelloWorld_Utils_h
#define HelloWorld_Utils_h

#include <iconv.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma comment(lib, "libiconv.lib")
#endif

#include "cocos2d.h"

int GBKToUTF8(std::string & gbkStr, const char* toCode, const char* fromCode);

cocos2d::CCSprite *createGraySprite(const char* imageName);

#endif
