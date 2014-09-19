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

#ifndef SOL_PHYSICS_BODY_H
#define SOL_PHYSICS_BODY_H

#include "SolConfig.h"
#if SOL_USE_PHYSICS

#   include "SolSceneNode.h"

namespace sol
{
    namespace physics
    {
        
        class Body : public SceneNode
        {
        public:
            Body(float m, float i);
            Body();
            ~Body() { cpBodyDestroy(_body); }
            
            bool isStatic() const { return _static; }
            
            float getAngle() const { return cpBodyGetAngle(_body); }
            float getAngVel() const { return cpBodyGetAngVel(_body); }
            float getAngVelLimit() const { return cpBodyGetAngVelLimit(_body); }
            Vec2f getForce() const { return Vec2f(cpBodyGetForce(_body)); }
            float getMass() const { return cpBodyGetMass(_body); }
            float getMoment() const { return cpBodyGetMoment(_body); }
            Vec2f getPos() const { return Vec2f(cpBodyGetPos(_body)); }
            Vec2f getRot() const { return Vec2f(cpBodyGetRot(_body)); }
            float getTorque() const { return cpBodyGetTorque(_body); }
            Vec2f getVel() const { return Vec2f(cpBodyGetVel(_body)); }
            float getVelLimit() const { return cpBodyGetVelLimit(_body); }
            
            void setPosition(const Vec2f& position) override { setPos(position); }
            void setRotation(float rotation) override { setAngle(rotation); }
            void setAngle(float angle) { cpBodySetAngle(_body, angle); }
            void setAngVel(float angVel) { cpBodySetAngVel(_body, angVel); }
            void setAngVelLimit(float angVelLimit) { cpBodySetAngVelLimit(_body, angVelLimit); }
            void setForce(const Vec2f& force) { cpBodySetForce(_body, force); }
            void setMass(float mass) { cpBodySetMass(_body, mass); }
            void setMoment(float moment) { cpBodySetMoment(_body, moment); }
            void setPos(const Vec2f& pos) { cpBodySetPos(_body, pos); }
            void setTorque(float torque) { cpBodySetTorque(_body, torque); }
            void setVel(const Vec2f& vel) { cpBodySetVel(_body, vel); }
            void setVelLimit(float velLimit) { cpBodySetVelLimit(_body, velLimit); }
            bool isSleeping() { return bool(cpBodyIsSleeping(_body)); }
            bool isRogue() { return bool(cpBodyIsRogue(_body)); }
            
            void resetForces() { cpBodyResetForces(_body); }
            void applyForce(const Vec2f& f, const Vec2f& r) { cpBodyApplyForce(_body, f, r); }
            void applyImpulse(const Vec2f& j, const Vec2f& r) { cpBodyApplyImpulse(_body, j, r); }
            
            void update() override;
            
            operator cpBody*() const { return _body; }
            
        private:
            cpBody _theBody;
            cpBody* _body;
            
            bool _static;
            
            void onAdd(Scene& scene) override;
            void onRemove() override;
        };
        
    }
}

#endif // SOL_USE_PHYSICS

#endif