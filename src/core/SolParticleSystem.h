/*
 *
 * Copyright (c) 2012 Garrett Thomas
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
 *    If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */

#ifndef SOL_PARTICLESYSTEM_H
#define SOL_PARTICLESYSTEM_H

#include "SolRenderComponents.h"
#include "SolRenderObject.h"

namespace sol
{
    
    struct Particle
    {
        Vec2f position;
        Vec2f velocity;
        
        unsigned int age = 0;
        unsigned int lifespan = 0;
        
        float interpolation = 0.0; // age / lifespan as float. used to calculate color and point size in shaders
        
        Colorc startColor;
        Colorc endColor;
        
        float startSize = 1.0;
        float endSize = 0.0;
        
        bool isAlive() { return lifespan > 0; }
        void die();
    };
    
    class ParticleSystem : public RenderObject
    {
    public:
        typedef std::function<void (Particle&)> ParticleFunc;
        ParticleFunc spawnFunc = spawnAtOrigin;
        ParticleFunc updateFunc = updateLinearVelocity;
        
        static void spawnAtOrigin(Particle& particle);
        static void spawnWithinRect(Vec2f& size, Particle& particle);
        static void spawnOnCircle(float& radius, Particle& particle);
        static void spawnWithinCircle(float& radius, Particle& particle);
        
        static void updateLinearVelocity(Particle& particle);
        static void updateJitter(Vec2f& maxJitter, Particle& particle);
        static void updateGravity(Vec2f& gravity, Particle& particle);
        
        float particleVelocity = 1.0;
        float particleVelocityVariance = 0.1;
        float particleVelocityDamping = 1.0;
        
        Colorc startParticleColor = whiteColorc();
        Colorc startParticleColorVariance;
        
        Colorc endParticleColor = whiteColorc(0);
        Colorc endParticleColorVariance;
        
        float startParticleSize = 10.0;
        float startParticleSizeVariance = 1.0;
        
        float endParticleSize = 5.0;
        float endParticleSizeVariance = 1.0;
                
        unsigned int particleLifespan = 100;
        unsigned int particleLifespanVariance = 10;
        
        float launchAngle = 0.0;
        float launchAngleVariance = 180.0;
        
        unsigned int spawnsPerFrame = 0;
        unsigned int spawnsPerFrameVariance = 0;
        
        bool blendAdditive = true;
        
        ParticleSystem(Texture& texture, unsigned int maxParticles = 100);
        ParticleSystem(const std::string& imageName, unsigned int maxParticles = 100);
        
        unsigned int getMaxParticles() const { return _particles.size(); }
        unsigned int getLivingParticleCount() const { return _livingParticleCount; }
        
        void setMaxParticles(unsigned int maxParticles);
        
        void spawn(unsigned int count);
        
        void update() override;
        void render() override;
        
    private:        
        std::vector<Particle> _particles;
        
        unsigned int _livingParticleCount = 0;
    };
        
}

#endif