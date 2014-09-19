#ifndef TOUCHTEST_H
#define TOUCHTEST_H

#include "SolGradient.h"
#include "SolScene.h"
#include "SolTouchable.h"

class TouchTest : public sol::Scene
{
public:
    TouchTest();
    
    void press() { SOL_PRINT("press"); gradient.setColor(sol::redColorc()); }
    void release() { SOL_PRINT("release"); gradient.setColor(sol::blueColorc()); }
    void cancel() { SOL_PRINT("cancel"); gradient.setColor(sol::blueColorc()); }
    void enter() { SOL_PRINT("enter"); }
    void exit() { SOL_PRINT("exit"); }
    void update() override;
    
private:
    sol::Touchable touchable;
    sol::Gradient gradient;
};

#endif