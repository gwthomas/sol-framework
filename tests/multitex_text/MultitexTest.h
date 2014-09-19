#ifndef MULTITEXTEST_H
#define MULTITEXTEST_H

#include "SolScene.h"
#include "SolLabel.h"
#include "SolMultiSprite.h"
#include "SolRenderTexture.h"

class MultitexTest : public sol::Scene
{
public:
    MultitexTest();
    
    void render();
    
private:
    sol::TextArea label;
    sol::RenderTexture tex;
    sol::MultiSprite spr;
};

#endif