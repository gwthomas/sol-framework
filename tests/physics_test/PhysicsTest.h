#ifndef PHYSICSTEST_H
#define PHYSICSTEST_H

#include "SolConfig.h"
#if SOL_USE_PHYSICS

#include "SolParticleSystem.h"
#include "SolArbiter.h"
#include "SolBody.h"
#include "SolConstraint.h"
#include "SolPhysicsScene.h"
#include "SolShape.h"
#include "SolScene.h"
#include "SolSprite.h"

class PhysicsTest : public sol::physics::PhysicsScene
{
public:
    PhysicsTest();
    ~PhysicsTest();
    
    void update() override;
    
    bool onTouchEvent(const sol::Touch& touch, sol::TouchEvent event) override;
        
private:    
    sol::Sprite dudeSprite;
    bool rotating;
    
    sol::ParticleSystem emitter;
    
    sol::physics::Body emitterBody;
    sol::physics::Body dudeBody;
    
    sol::physics::CircleShape emitterShape;
    sol::physics::CircleShape dudeShape;
    
    sol::physics::SlideJoint constraint;
};

#endif // SOL_USE_PHYSICS

#endif