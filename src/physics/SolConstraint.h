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

#ifndef SOL_PHYSICS_CONSTRAINT_H
#define SOL_PHYSICS_CONSTRAINT_H

#include "SolConfig.h"
#if SOL_USE_PHYSICS

#   include "SolBody.h"
#   include "SolVec.h"

namespace sol
{
    namespace physics
    {
        
        class Body;
        
        class Constraint : public SceneNode
        {
        public:
            ~Constraint() { cpConstraintFree(_constraint); }
            
            Body& getA() const { return _a; }
            Body& getB() const { return _b; }
            
            float getMaxForce() const { return cpConstraintGetMaxForce(_constraint); }
            float getErrorBias() const { return cpConstraintGetErrorBias(_constraint); }
            float getMaxBias() const { return cpConstraintGetMaxBias(_constraint); }
            float getImpulse() const { return cpConstraintGetImpulse(_constraint); }

            void setMaxForce(float maxForce) { cpConstraintSetMaxForce(_constraint, maxForce); }
            void setErrorBias(float errorBias) { cpConstraintSetErrorBias(_constraint, errorBias); }
            void setMaxBias(float maxBias) { cpConstraintSetMaxBias(_constraint, maxBias); }
            
            operator cpConstraint* () const { return _constraint; }
            
        protected:
            cpConstraint* _constraint = nullptr;
            
            Body& _a;
            Body& _b;
            
            Constraint(Body& a, Body& b);
            
            void onAdd(Scene& scene) override;
            void onRemove() override;
        };
        
        class PinJoint : public Constraint
        {
        public:
            PinJoint(Body& a, Body& b, const Vec2f& anchr1, const Vec2f& anchr2);
            
            Vec2f getAnchr1() const { return Vec2f(cpPinJointGetAnchr1(_constraint)); }
            Vec2f getAnchr2() const { return Vec2f(cpPinJointGetAnchr2(_constraint)); }
            float getDist() const { return cpPinJointGetDist(_constraint); }
            
            void setAnchr1(const Vec2f& anchr1) { cpPinJointSetAnchr1(_constraint, anchr1); }
            void setAnchr2(const Vec2f& anchr2) { cpPinJointSetAnchr2(_constraint, anchr2); }
            void setDist(float dist) { cpPinJointSetDist(_constraint, dist); }
        };
        
        class SlideJoint : public Constraint
        {
        public:
            SlideJoint(Body& a, Body& b, const Vec2f& anchr1, const Vec2f& anchr2, float min, float max);
            
            Vec2f getAnchr1() const { return Vec2f(cpSlideJointGetAnchr1(_constraint)); }
            Vec2f getAnchr2() const { return Vec2f(cpSlideJointGetAnchr2(_constraint)); }
            float getMin() const { return cpSlideJointGetMin(_constraint); }
            float getMax() const { return cpSlideJointGetMax(_constraint); }
            
            void setAnchr1(const Vec2f& anchr1) { cpSlideJointSetAnchr1(_constraint, anchr1); }
            void setAnchr2(const Vec2f& anchr2) { cpSlideJointSetAnchr2(_constraint, anchr2); }
            void setMin(float min) { cpSlideJointSetMin(_constraint, min); }
            void setMax(float max) { cpSlideJointSetMax(_constraint, max); }
        };
        
        class PivotJoint : public Constraint
        {
        public:
            PivotJoint(Body& a, Body& b, const Vec2f& pivot);
            PivotJoint(Body& a, Body& b, const Vec2f& anchr1, const Vec2f& anchr2);
            
            Vec2f getAnchr1() const { return Vec2f(cpPivotJointGetAnchr1(_constraint)); }
            Vec2f getAnchr2() const { return Vec2f(cpPivotJointGetAnchr2(_constraint)); }
            
            void setAnchr1(const Vec2f& anchr1) { cpPivotJointSetAnchr1(_constraint, anchr1); }
            void setAnchr2(const Vec2f& anchr2) { cpPivotJointSetAnchr2(_constraint, anchr2); }
        };
        
        class GrooveJoint : public Constraint
        {
        public:
            GrooveJoint(Body& a, Body& b, const Vec2f& groove_a, const Vec2f& groove_b, const Vec2f& anchr2);
            
            Vec2f getGrooveA() const { return Vec2f(cpGrooveJointGetGrooveA(_constraint)); }
            Vec2f getGrooveB() const { return Vec2f(cpGrooveJointGetGrooveB(_constraint)); }
            Vec2f getAnchr2() const { return Vec2f(cpGrooveJointGetAnchr2(_constraint)); }
            
            void setGrooveA(const Vec2f& grooveA) { cpGrooveJointSetGrooveA(_constraint, grooveA); }
            void setGrooveB(const Vec2f& grooveB) { cpGrooveJointSetGrooveB(_constraint, grooveB); }
            void setAnchr2(const Vec2f& anchr2) { cpGrooveJointSetAnchr2(_constraint, anchr2); }
        };
        
        class DampedSpring : public Constraint
        {
        public:
            DampedSpring(Body& a, Body& b, const Vec2f& anchr1, const Vec2f& anchr2, float restLength, float stiffness, float damping);
            
            Vec2f getAnchr1() const { return Vec2f(cpDampedSpringGetAnchr1(_constraint)); }
            Vec2f getAnchr2() const { return Vec2f(cpDampedSpringGetAnchr2(_constraint)); }
            float getRestLength() const { return cpDampedSpringGetRestLength(_constraint); }
            float getStiffness() const { return cpDampedSpringGetStiffness(_constraint); }
            float getDamping() const { return cpDampedSpringGetDamping(_constraint); }
            
            void setAnchr1(const Vec2f& anchr1) { cpDampedSpringSetAnchr1(_constraint, anchr1); }
            void setAnchr2(const Vec2f& anchr2) { cpDampedSpringSetAnchr2(_constraint, anchr2); }
            void setRestLength(float restLength) { cpDampedSpringSetRestLength(_constraint, restLength); }
            void setStiffness(float stiffness) { cpDampedSpringSetStiffness(_constraint, stiffness); }
            void setDamping(float damping) { cpDampedSpringSetDamping(_constraint, damping); }
        };
        
        class DampedRotarySpring : public Constraint
        {
        public:
            DampedRotarySpring(Body& a, Body& b, float restAngle, float stiffness, float damping);
            
            float getRestAngle() const { return cpDampedRotarySpringGetRestAngle(_constraint); }
            float getStiffness() const { return cpDampedRotarySpringGetStiffness(_constraint); }
            float getDamping() const { return cpDampedRotarySpringGetDamping(_constraint); }
            
            void setRestAngle(float restAngle) { cpDampedRotarySpringSetRestAngle(_constraint, restAngle); }
            void setStiffness(float stiffness) { cpDampedRotarySpringSetStiffness(_constraint, stiffness); }
            void setDamping(float damping) { cpDampedRotarySpringSetDamping(_constraint, damping); }
        };
        
        class RotaryLimitJoint : public Constraint
        {
        public:
            RotaryLimitJoint(Body& a, Body& b, float min, float max);
            
            float getMin() const { return cpRotaryLimitJointGetMin(_constraint); }
            float getMax() const { return cpRotaryLimitJointGetMax(_constraint); }
            
            void setMin(float min) { cpRotaryLimitJointSetMin(_constraint, min); }
            void setMax(float max) { cpRotaryLimitJointSetMax(_constraint, max); }
        };
        
        class RatchetJoint : public Constraint
        {
        public:
            RatchetJoint(Body& a, Body& b, float phase, float ratchet);
            
            float getAngle() const { return cpRatchetJointGetAngle(_constraint); }
            float getPhase() const { return cpRatchetJointGetPhase(_constraint); }
            float getRatchet() const { return cpRatchetJointGetRatchet(_constraint); }
            
            void setAngle(float angle) { cpRatchetJointSetAngle(_constraint, angle); }
            void setPhase(float phase) { cpRatchetJointSetPhase(_constraint, phase); }
            void setRatchet(float ratchet) { cpRatchetJointSetRatchet(_constraint, ratchet); }
        };
        
        class GearJoint : public Constraint
        {
        public:
            GearJoint(Body& a, Body& b, float phase, float ratio);
            
            float getPhase() const { return cpGearJointGetPhase(_constraint); }
            float getRatio() const { return cpGearJointGetRatio(_constraint); }
            
            void setPhase(float phase) { cpGearJointSetPhase(_constraint, phase); }
            void setRatio(float ratio) { cpGearJointSetRatio(_constraint, ratio); }
        };
        
        class SimpleMotor : public Constraint
        {
        public:
            SimpleMotor(Body& a, Body& b, float rate);
            
            float getRate() const { return cpSimpleMotorGetRate(_constraint); }
            
            void setRate(float rate) { cpSimpleMotorSetRate(_constraint, rate); }
        };
        
    }
}

#endif // SOL_USE_PHYSICS

#endif