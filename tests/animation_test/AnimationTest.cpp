#include "AnimationTest.h"
#if SOL_USE_XML

#   include "SolTextureAtlas.h"

using namespace sol;

AnimationTest::AnimationTest() :
    atlas(*ResourceManager::instance().getResource<TextureAtlas>("SolSprites.xml")),
    anim(atlas),
    spr1(atlas.getTexture()),
    spr2(atlas.getTexture())
{
    anim.addNamedFrame("Dude.png");
    anim.addNamedFrame("Sun.png");
    anim.addNamedFrame("Particle.png");
    anim.addNamedFrame("LeftButton.png");
    anim.addNamedFrame("RightButton.png");
    anim.addNamedFrame("UpButton.png");
    anim.addNamedFrame("DownButton.png");
    
    spr1.setTimePerFrame(1.0);
    spr1.enqueueAnimation(anim, -1); // negative parameter makes it loop forever
    spr1.setPosition(Vec2f(-50.0, 50.0));
    add(spr1);
    
    spr2.setTimePerFrame(0.5);
    spr2.setDefaultFrame(atlas.getRegionNamed("Dude.png"));
    spr2.setPosition(Vec2f(50.0, -50.0));
    add(spr2);
}

AnimationTest::~AnimationTest()
{
    ResourceManager::instance().destroyAllResourceManager();
}

bool AnimationTest::onTouchEvent(const Touch& touch, TouchEvent event)
{
    switch (event)
    {
        case TouchDown:
            spr1.playing = false;
            
            if (!spr2.hasCurrentAnimation())
            {
                spr2.enqueueAnimation(anim, 1);
            }
            break;
            
        case TouchUp:
            spr1.playing = true;
            
        default:
            break;
    }
    
    return true;
}

#endif