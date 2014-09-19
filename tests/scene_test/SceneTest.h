#ifndef SCENETEST_H
#define SCENETEST_H

#include "SolLabel.h"
#include "SolScene.h"

class Scene1 : public sol::Scene
{
public:
    Scene1();
    
    bool onTouchEvent(const sol::Touch& touch, sol::TouchEvent event) override;
    
private:
    sol::SimpleLabel label;
};

class Scene2 : public sol::Scene
{
public:
    Scene2();
    
    bool onTouchEvent(const sol::Touch& touch, sol::TouchEvent event) override;
    
private:
    sol::SimpleLabel label;
};

#endif