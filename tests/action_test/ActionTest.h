#ifndef ACTIONTEST_H
#define ACTIONTEST_H

#include "SolAction.h"
#include "SolScene.h"
#include "SolSprite.h"

class ActionTest : public sol::Scene
{
public:
    ActionTest();
    
private:
    sol::Sprite spr;
    sol::Action* trans;
    sol::Action* scale;
    sol::Action* rot;
};

#endif