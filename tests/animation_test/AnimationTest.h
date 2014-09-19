#ifndef ANIMATIONTEST_H
#define ANIMATIONTEST_H

#include "SolAnimatedSprite.h"
#include "SolAnimation.h"
#include "SolScene.h"

#if SOL_USE_XML

class AnimationTest : public sol::Scene
{
public:
    AnimationTest();
    ~AnimationTest();
    
    bool onTouchEvent(const sol::Touch& touch, sol::TouchEvent event) override;
    
private:
    sol::TextureAtlas& atlas;
    
    sol::Animation anim;
    
    sol::AnimatedSprite spr1, spr2;
};

#endif // SOL_USE_XML

#endif