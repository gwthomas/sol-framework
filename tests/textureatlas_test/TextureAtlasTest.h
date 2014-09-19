#ifndef TEXTUREATLASTEST_H
#define TEXTUREATLASTEST_H

#include "SolScene.h"
#include "SolSpriteBatch.h"

#if SOL_USE_XML

class TextureAtlasTest : public sol::Scene
{
public:
    TextureAtlasTest();
        
    bool onTouchEvent(const sol::Touch& touch, sol::TouchEvent event) override;
    
    void update() override;
    
private:
    sol::SpriteBatch batch;
        
    sol::Sprite& dude;
    sol::Sprite& sun;
};

#endif // SOL_USE_XML

#endif