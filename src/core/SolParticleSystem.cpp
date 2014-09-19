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

#include "SolImage.h"
#include "SolParticleSystem.h"
#include "SolProgram.h"
#include "SolResourceManager.h"

namespace sol
{
    
    void Particle::die()
    {
        age = 0;
        lifespan = 0;
        interpolation = 0.0;
        startSize = 0.0;
        endSize = 0.0;
        position = Vec2f(1000000.0, 1000000.0);
    }

    void ParticleSystem::spawnAtOrigin(Particle& particle)
    {
        particle.position = Vec2f();
    }
    
    void ParticleSystem::spawnWithinRect(Vec2f& size, Particle& particle)
    {
        particle.position.x = randomVariancef(0.0, size.x * 0.5);
        particle.position.y = randomVariancef(0.0, size.y * 0.5);
    }
    
    void ParticleSystem::spawnOnCircle(float& radius, Particle& particle)
    {
        float angle = degreesToRadians(randomInRangef(0.0, 360.0));
        particle.position = Vec2f(radius * std::cos(angle), radius * std::sin(angle));
    }
    
    void ParticleSystem::spawnWithinCircle(float& radius, Particle& particle)
    {
        float angle = degreesToRadians(randomInRangef(0.0, 360.0));
        float actualRange = randomInRangef(0.0, radius);
        particle.position = Vec2f(actualRange * std::cos(angle), actualRange * std::sin(angle));
    }
    
    void ParticleSystem::updateLinearVelocity(Particle& particle)
    {
        particle.position += particle.velocity;
    }
    
    void ParticleSystem::updateJitter(Vec2f& maxJitter, Particle& particle)
    {
        particle.position += particle.velocity;
        particle.position += Vec2f(randomVariancef(0.0, maxJitter.x), randomVariancef(0.0, maxJitter.y));
    }
    
    void ParticleSystem::updateGravity(Vec2f& gravity, Particle& particle)
    {
        particle.velocity += gravity;
        particle.position += particle.velocity;
    }
    
    ParticleSystem::ParticleSystem(Texture& texture, unsigned int maxParticles)
    {
        program = ResourceManager::instance().getResource<Program>("particle");
        assert(program);
        
        _texture = &texture;
        _attribs = PositionAttribFlag | ParticleAttribsFlag;
        
        setMaxParticles(maxParticles);
    }
    
    ParticleSystem::ParticleSystem(const std::string& imageName, unsigned int maxParticles) :
        ParticleSystem(ResourceManager::instance().getResource<Image>(imageName)->getTexture(), maxParticles)
    {}
    
    void ParticleSystem::setMaxParticles(unsigned int maxParticles)
    {
        unsigned int prevMax = getMaxParticles();
        
        if (prevMax == maxParticles) return;
        
        _particles.reserve(maxParticles);
        
        for (int i = prevMax; i < maxParticles; i++)
        {
            _particles.emplace_back();
            _particles.back().die();
        }
    }
    
    void ParticleSystem::spawn(unsigned int count)
    {
        if (count == 0 || _livingParticleCount == getMaxParticles()) return;
        
        Vec2f absolute = getAbsolutePosition();
        unsigned int spawned = 0;
        
        for (int i = 0; i < getMaxParticles(); i++)
        {
            Particle& particle = _particles[i];
            
            if (!particle.isAlive())
            {
                float angle = degreesToRadians(randomVariancef(launchAngle, launchAngleVariance));
                particle.velocity = Vec2f(std::cos(angle), std::sin(angle)) * randomVariancef(particleVelocity, particleVelocityVariance);
                particle.age = 0;
                particle.lifespan = randomVariancei(particleLifespan, particleLifespanVariance);
                particle.startColor = Colorc(randomVariancei(startParticleColor.r, startParticleColorVariance.r),
                                             randomVariancei(startParticleColor.g, startParticleColorVariance.g),
                                             randomVariancei(startParticleColor.b, startParticleColorVariance.b),
                                             randomVariancei(startParticleColor.a, startParticleColorVariance.a));
                particle.endColor = Colorc(randomVariancei(endParticleColor.r, endParticleColorVariance.r),
                                           randomVariancei(endParticleColor.g, endParticleColorVariance.g),
                                           randomVariancei(endParticleColor.b, endParticleColorVariance.b),
                                           randomVariancei(endParticleColor.a, endParticleColorVariance.a));
                particle.startSize = randomVariancef(startParticleSize, startParticleSizeVariance);
                particle.endSize = randomVariancef(endParticleSize, endParticleSizeVariance);
                
                if (Manager::instance().isRetinaDisplay())
                {
                    particle.startSize *= 2.0;
                    particle.endSize *= 2.0;
                }
                
                spawnFunc(particle);
                particle.position += absolute;
                
                _livingParticleCount++;
                spawned++;
                
                if (spawned == count) break;
            }
        }
    }
    
    void ParticleSystem::update()
    {
        spawn(std::max(randomVariancei(spawnsPerFrame, spawnsPerFrameVariance), 0));
                
        for (int i = 0; i < getMaxParticles(); i++)
        {
            Particle& particle = _particles[i];
            
            if (particle.isAlive())
            {
                if (particle.age == particle.lifespan)
                {
                    particle.die();
                    _livingParticleCount--;
                }
                else
                {
                    particle.age++;
                    particle.interpolation = float(particle.age) / float(particle.lifespan);
                    particle.velocity *= particleVelocityDamping;
                    updateFunc(particle);
                }
            }
        }
    }
    
    void ParticleSystem::render()
    {
        _texture->bind();
        program->use();
        program->setTint(tint);
        useVertexAttribs(_attribs);
        
        // additive blending to get that nice shine effect
        if (blendAdditive) glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        
        Matrix transform = Manager::instance().getWorldTransform(); // particle systems don't act according to normal SceneNode transformations
        glUniformMatrix3fv(program->getTransformUniformLocation(), 1, GL_FALSE, &transform[0]);
        
        VBO::unbind(GL_ELEMENT_ARRAY_BUFFER);
        glVertexAttribPointer(kPositionAttribLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), &_particles[0].position);
        glVertexAttribPointer(kParticleInterpolationAttribLocation, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), &_particles[0].interpolation);
        glVertexAttribPointer(kParticleStartColorAttribLocation, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Particle), &_particles[0].startColor);
        glVertexAttribPointer(kParticleEndColorAttribLocation, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Particle), &_particles[0].endColor);
        glVertexAttribPointer(kParticleStartSizeAttribLocation, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), &_particles[0].startSize);
        glVertexAttribPointer(kParticleEndSizeAttribLocation, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), &_particles[0].endSize);
        
        glDrawArrays(GL_POINTS, 0, getMaxParticles());
        
        // put blending back to normal
        if (blendAdditive) glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

}