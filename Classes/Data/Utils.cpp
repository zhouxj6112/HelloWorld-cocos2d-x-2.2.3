//
//  Util.cpp
//  HelloWorld
//
//  Created by MrZhou on 14-10-26.
//
//

#include "Utils.h"

USING_NS_CC;

int GBKToUTF8(std::string & gbkStr, const char* toCode, const char* fromCode)
{
    iconv_t iconvH;
    iconvH = iconv_open(fromCode, toCode);
    
    if (iconvH == 0)
    {
        return -1;
    }
    const char* strChar = gbkStr.c_str();
    const char** pin = &strChar;
    size_t strLength = gbkStr.length();
    char* outbuf = (char *)malloc(strLength*4);
    
    char* pBuff = outbuf;
    
    memset(outbuf, 0, strLength*4);
    size_t outLength = strLength*4;
    if (-1 == ::iconv(iconvH, (char**)pin, &strLength, &outbuf, &outLength))
    {
        iconv_close(iconvH);
        return -1;
    }
    
    gbkStr = pBuff;
    iconv_close(iconvH);
    
    return 0;
}

CCSprite *createGraySprite(const char* imageName)
{
    // create CCSprite
    CCSprite* sprite = CCSprite::create(imageName);
    
    unsigned int width = sprite->getTexture()->getPixelsWide();
    unsigned int height = sprite->getTexture()->getPixelsHigh();
    
    // create CCRenderTexture base on the CCSprite
    CCRenderTexture* r = CCRenderTexture::create(width, height);
    r->beginWithClear(1, 1, 1, 0);
    sprite->setPosition(ccp(width / 2.0, height/ 2.0)); // Node: set position here!
    sprite->visit();
    r->end();
    
    // create a new CCImage
    CCImage* image = r->newCCImage();
    
    width = image->getWidth();
    height= image->getHeight();
    
    // this data is the texture data in memery
    unsigned char* data = image->getData();
    
    typedef enum {
        RED = 0,
        GREEN = 1,
        BLUE = 2,
        ALPHA = 3
    } PIXELS;
    
    // convert unsigned char*(1 Byte) to uint_32_t(4 Bytes)
    uint32_t *pixels = (uint32_t *)data;
    
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            uint8_t *rgbaPixel = (uint8_t *) &pixels[y * width + x];
            
            // convert to grayscale using recommended method: http://en.wikipedia.org/wiki/Grayscale#Converting_color_to_grayscale
            uint32_t gray = 0.3 * rgbaPixel[RED] + 0.59 * rgbaPixel[GREEN] + 0.11 * rgbaPixel[BLUE];
            
            // set the pixels to gray
            rgbaPixel[RED] = gray;
            rgbaPixel[GREEN] = gray;
            rgbaPixel[BLUE] = gray;
        }
    }
    
    // create a new CCTexture2D based on the CCImage data modified above
    CCTexture2D* texture = new CCTexture2D();
    texture->initWithImage(image);
    
    // create a new CCSprite to return
    CCSprite* s = CCSprite::create();
    s->initWithTexture(texture);
    
    // release other resources
    r->release();
    image->release();
    sprite->release();
    
    return s;
}
