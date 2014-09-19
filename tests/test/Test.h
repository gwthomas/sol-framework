#ifndef TEST_H
#define TEST_H

#include "SolCircle.h"
#include "SolGradient.h"
#include "SolLabel.h"
#include "SolParticleSystem.h"
#include "SolScene.h"
#include "SolSprite.h"
#include "SolSpriteBatch.h"

class Test : public sol::Scene
{
public:
    Test();
    ~Test();
    
    void update() override;
    
private:                
    sol::Gradient gradient;
    
    sol::SpriteBatch dudeBatch;
    
    sol::Sprite& dude;
    sol::Sprite& otherDude;
        
    sol::SimpleLabel label;
    bool spreading;
    
    sol::Circle circle;
    
    float spawnRadius = 50.0;
    sol::Vec2f gravity;
    sol::ParticleSystem emitter;
};

#endif