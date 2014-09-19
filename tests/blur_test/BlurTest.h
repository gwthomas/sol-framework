#ifndef BLURTEST_H
#define BLURTEST_H

#include "SolBlur.h"
#include "SolScene.h"
#include "SolSprite.h"

class BlurTest : public sol::Scene
{
public:
    BlurTest();
    
    void render() override;
    
private:
    sol::Sprite spr0;
    sol::Sprite spr1;
    sol::Blur blur;
};

#endif