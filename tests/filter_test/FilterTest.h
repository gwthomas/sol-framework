#ifndef INVERTTEST_H
#define INVERTTEST_H

#include "SolFilter.h"
#include "SolScene.h"
#include "SolSprite.h"

class FilterTest : public sol::Scene
{
public:
    FilterTest();
    
    void render() override;

private:
    sol::Sprite spr;
    sol::Filter filter;
};

#endif