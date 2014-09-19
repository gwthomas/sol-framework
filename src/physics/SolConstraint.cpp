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

#include "SolConstraint.h"
#if SOL_USE_PHYSICS

#   include "SolScene.h"
#   include "SolSpace.h"

namespace sol
{
    namespace physics
    {
        
        Constraint::Constraint(Body& a, Body& b) :
            _a(a),
            _b(b)
        {}
        
        void Constraint::onAdd(Scene& scene)
        {
            scene.getSpace()->addConstraint(*this);
            SceneNode::onAdd(scene);
        }
        
        void Constraint::onRemove()
        {
            _scene->getSpace()->removeConstraint(*this);
            SceneNode::onRemove();
        }
        
        PinJoint::PinJoint(Body& a, Body& b, const Vec2f& anchr1, const Vec2f& anchr2) :
            Constraint(a, b)
        {
            _constraint = cpPinJointNew(a, b, anchr1, anchr2);
            cpConstraintSetUserData(_constraint, this);
        }
        
        SlideJoint::SlideJoint(Body& a, Body& b, const Vec2f& anchr1, const Vec2f& anchr2, float min, float max) :
            Constraint(a, b)
        {
            _constraint = cpSlideJointNew(a, b, anchr1, anchr2, min, max);
            cpConstraintSetUserData(_constraint, this);
        }
        
        PivotJoint::PivotJoint(Body& a, Body& b, const Vec2f& pivot) :
            Constraint(a, b)
        {
            _constraint = cpPivotJointNew(a, b, pivot);
            cpConstraintSetUserData(_constraint, this);
        }
        
        PivotJoint::PivotJoint(Body& a, Body& b, const Vec2f& anchr1, const Vec2f& anchr2) :
            Constraint(a, b)
        {
            _constraint = cpPivotJointNew2(a, b, anchr1, anchr2);
            cpConstraintSetUserData(_constraint, this);
        }
        
        GrooveJoint::GrooveJoint(Body& a, Body& b, const Vec2f& groove_a, const Vec2f& groove_b, const Vec2f& anchr2) :
            Constraint(a, b)
        {
            _constraint = cpGrooveJointNew(a, b, groove_a, groove_b, anchr2);
            cpConstraintSetUserData(_constraint, this);
        }
        
        DampedSpring::DampedSpring(Body& a, Body& b, const Vec2f& anchr1, const Vec2f& anchr2, float restLength, float stiffness, float damping) :
            Constraint(a, b)
        {
            _constraint = cpDampedSpringNew(a, b, anchr1, anchr2, restLength, stiffness, damping);
            cpConstraintSetUserData(_constraint, this);
        }
        
        DampedRotarySpring::DampedRotarySpring(Body& a, Body& b, float restAngle, float stiffness, float damping) :
            Constraint(a, b)
        {
            _constraint = cpDampedRotarySpringNew(a, b, restAngle, stiffness, damping);
            cpConstraintSetUserData(_constraint, this);
        }
        
        RotaryLimitJoint::RotaryLimitJoint(Body& a, Body& b, float min, float max) :
            Constraint(a, b)
        {
            _constraint = cpRotaryLimitJointNew(a, b, min, max);
            cpConstraintSetUserData(_constraint, this);
        }
        
        RatchetJoint::RatchetJoint(Body& a, Body& b, float phase, float ratchet) :
            Constraint(a, b)
        {
            _constraint = cpRatchetJointNew(a, b, phase, ratchet);
            cpConstraintSetUserData(_constraint, this);
        }
        
        GearJoint::GearJoint(Body& a, Body& b, float phase, float ratio) :
            Constraint(a, b)
        {
            _constraint = cpGearJointNew(a, b, phase, ratio);
            cpConstraintSetUserData(_constraint, this);
        }
        
        SimpleMotor::SimpleMotor(Body& a, Body& b, float rate) :
            Constraint(a, b)
        {
            _constraint = cpSimpleMotorNew(a, b, rate);
            cpConstraintSetUserData(_constraint, this);
        }
        
    }
}

#endif // SOL_USE_PHYSICS