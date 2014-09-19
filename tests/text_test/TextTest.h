#ifndef TEXTTEST_H
#define TEXTTEST_H

#include "SolFont.h"
#include "SolLabel.h"
#include "SolScene.h"

class TextTest : public sol::Scene
{
public:
    TextTest();
    ~TextTest();
    
    bool onTouchEvent(const sol::Touch& touch, sol::TouchEvent event) override;
    
    void update() override;
    
private:
    sol::Font* arial;
    sol::Font* droidSans;
    
    sol::SimpleLabel* label0;
    sol::TextArea* label1;
    
    bool expanding;
};

#endif