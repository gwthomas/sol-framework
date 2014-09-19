#include "PhysicsTest.h"
#if SOL_USE_PHYSICS

#   include "SolParticleSystem.h"
#   include "SolArbiter.h"
#   include "SolConstraint.h"
#   include "SolNative.h"
#   include "SolSpace.h"
#   include "SolResourceManager.h"
#   include "SolSprite.h"

using namespace sol;

PhysicsTest::PhysicsTest() :
    dudeSprite("Dude.png"),
    emitter("Particle.png"),
    emitterBody(1.0, 1.0),
    dudeBody(),
    emitterShape(emitterBody, 10.0, Vec2f()),
    dudeShape(dudeBody, dudeSprite.getSize().x * 0.5, Vec2f()),
    constraint(emitterBody, dudeBody, Vec2f(), Vec2f(), 0.0, Manager::instance().getScreenSizePoints().y / 3.0)
{
    native::getDefaultFramebuffer().setClearColor(blackColorf());
    
    dudeSprite.setDepth(2);
    rotating = false;
    
    dudeShape.setFriction(0.5);
    dudeShape.setElasticity(0.75);
    dudeBody.addChild(dudeSprite);
    dudeBody.addChild(dudeShape);
    add(dudeBody);
    
    emitter.spawnsPerFrame = 5;
    emitter.spawnsPerFrameVariance = 2;
    emitter.particleLifespan = 40;
    emitter.particleLifespanVariance = 20;
    emitter.startParticleColor = Colorc(240, 50, 10, 100);
    emitter.startParticleColorVariance = Colorc(10, 30, 10, 10);
    emitter.endParticleColor = greyColorc(0);
    emitter.startParticleSize = 50.0;
    emitter.endParticleSize = 100.0;
    emitter.launchAngle = 90.0;
    emitter.launchAngleVariance = 25.0;
    emitter.particleVelocity = 5.0;
    emitter.particleVelocityVariance = 1.0;
    emitter.particleVelocityDamping = 0.98;
    emitter.setDepth(1);
    
    emitterBody.setPosition(Vec2f(50.0, 50.0));
    emitterShape.setFriction(0.5);
    emitterShape.setElasticity(0.75);
    emitterBody.addChild(emitter);
    emitterBody.addChild(emitterShape);
    add(emitterBody);
        
    add(constraint);
    
    _space.setGravity(Vec2f(0.0, -500.0f));
    _space.onCollisionBegin = [this](const physics::Arbiter&) { rotating = true; return true; };
}

PhysicsTest::~PhysicsTest()
{
    ResourceManager::instance().destroyAllResourceManager();
}

void PhysicsTest::update()
{
    PhysicsScene::update();
    
    Vec2f tilt = getInputManager().getTilt().to2D();
    
    if (tilt)
    {
        _space.setGravity(tilt * 500.0f);
    }
    
    if (rotating)
    {
        dudeSprite.rotate(3.0);
        
        if (dudeSprite.getRotation() > 360.0)
        {
            dudeSprite.setRotation(0.0);
            rotating = false;
        }
    }
}

bool PhysicsTest::onTouchEvent(const Touch& touch, TouchEvent event)
{
    emitterBody.setPosition(touch.loc);
    
    return true;
}

#endif