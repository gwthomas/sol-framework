#include "Test.h"
#include "SolAudio.h"
#include "SolFont.h"
#include "SolNative.h"
#include "SolRenderable.h"
#include "SolResourceManager.h"
#include "SolSprite.h"

using namespace sol;

Test::Test() :
    dudeBatch("Dude.png"),
    dude(dudeBatch.create()),
    otherDude(dudeBatch.create()),
    label("arial-rounded.ttf@50"),
    emitter("Particle.png", 3000),
    circle(50.0)
{
    native::getDefaultFramebuffer().setClearColor(blackColorf());
    
    gradient.setDepth(10);
    gradient.setSize(Manager::instance().getScreenSizePoints().cast<float>());
    gradient.setColor(0, redColorc());
    gradient.setColor(1, greenColorc());
    gradient.setColor(2, blueColorc());
    gradient.setColor(3, whiteColorc());
    add(gradient);
        
    dude.setScale(Vec2f(3.0, 0.5));
    dude.setPosition(Vec2f(-70.0, 120.0));
    add(dude);
    
    otherDude.setPosition(Vec2f(50.0, -100.0));
    add(otherDude);
    
    dudeBatch.setDepth(2);
    add(dudeBatch);
    
    label.setDepth(3);
    label.setAlignment(Label::AlignCenter);
    label.setPosition(Vec2f(-50.0, 50.0));
    label.setText("Hello!");
    label.setPadding(3.0);
    add(label);
    
    dudeBatch.useBufferObjects(true, true, true);
    label.useBufferObjects(false, true, true);
    
    spreading = true;
    
    emitter.spawnFunc = std::bind(&ParticleSystem::spawnOnCircle, std::ref(spawnRadius), std::placeholders::_1);
    emitter.updateFunc = std::bind(&ParticleSystem::updateGravity, std::ref(gravity), std::placeholders::_1);
    emitter.setDepth(7);
    emitter.blendAdditive = false;
    emitter.particleLifespan = 75;
    emitter.particleLifespanVariance = 25;
    emitter.startParticleColorVariance = Colorc(10, 10, 10, 50);
    emitter.endParticleColor = Colorc(0, 0, 0, 0);
    emitter.startParticleSize = 50.0;
    emitter.endParticleSize = 30.0;
    add(emitter);
    
    circle.setPosition(100.0, 50.0);
    circle.fill = greyColorf(0.8);
    circle.edge = blueColorf();
    circle.edgeWidth = 5.0;
    add(circle);
}

Test::~Test()
{    
    ResourceManager::instance().destroyAllResourceManager();
}

void Test::update()
{
    dude.rotate(2.0);
    otherDude.rotate(-1.0);
    
#if SOL_USE_ACCELEROMETER
    const Vec3f& tilt = getInputManager().getTilt();
    gravity = tilt.to2D();
#endif
    
    for (int i = 0; i < SOL_MAX_TOUCHES; i++)
    {
        const Touch* touch = getInputManager().getTouch(i);
        
        if (touch)
        {            
            if (i == 0) emitter.startParticleColor = Colorc(240, 10, 10, 200);
            else if (i == 1) emitter.startParticleColor = Colorc(10, 240, 10, 200);
            else if (i == 2) emitter.startParticleColor = Colorc(10, 10, 240, 200);
            else if (i == 3) emitter.startParticleColor = Colorc(240, 120, 10, 200);
            else if (i == 4) emitter.startParticleColor = Colorc(240, 10, 240, 200);
            else emitter.startParticleColor = Colorc(randomVariancei(128, 100), randomVariancei(128, 100), randomVariancei(128, 100), 200);
            
            emitter.setPosition(touch->loc);
            emitter.spawn(5);
        }
    }
    
    if (spreading)
    {
        if (label.getPadding() > 20.0) spreading = false;
        else label.setPadding(label.getPadding() + 0.5);
    }
    else
    {
        if (label.getPadding() < 2.0) spreading = true;
        else label.setPadding(label.getPadding() - 0.5);
    }
    
    Scene::update();
}