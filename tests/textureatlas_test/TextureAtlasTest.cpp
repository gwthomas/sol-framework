#include "SolSprite.h"
#if SOL_USE_XML
#   include "TextureAtlasTest.h"

using namespace sol;

TextureAtlasTest::TextureAtlasTest() :
    batch("SolSprites.xml", true),
    dude(batch.create()),
    sun(batch.create())
{    
    batch.useBufferObjects();
    add(batch);
    
    dude.textureAtlasRegion("Dude.png");
    add(dude);
    
    sun.textureAtlasRegion("Sun.png");
    sun.setPosition(Vec2f(100.0, 50.0));
    add(sun);
}

void TextureAtlasTest::update()
{
    batch.rotate(1.0);
    Scene::update();
}

bool TextureAtlasTest::onTouchEvent(const Touch& touch, TouchEvent event)
{
    if (event == TouchDown || event == TouchMoved) batch.setPosition(touch.loc);

    return true;
}

#endif