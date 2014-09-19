/*
 *
 * Copyright (c) 2012 Garrett Thomas
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin o this software must not be misrepresented; you must not claim that you wrote the original software.
 *    I you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */

#ifndef SOL_PHYSICS_SPACE_H
#define SOL_PHYSICS_SPACE_H

#include "SolConfig.h"
#if SOL_USE_PHYSICS

#   include "SolBody.h"
#   include "SolConstraint.h"
#   include "SolShape.h"
#   include "SolVec.h"

namespace sol
{
    namespace physics
    {
        
        class Arbiter;
        
        /// The world in which all physics objects reside and interact.
        class Space : public Noncopyable
        {
            friend class Body;
            friend class Constraint;
            friend class Shape;
            
        public:
            /// Function called when collision begins.
            /// Should return true if the collision should take place as normal, or false if the collision should be ignored.
            std::function<bool (const Arbiter&)> onCollisionBegin = [](const Arbiter&) { return true; };
            
            /// Function called when collision is about to be solved.
            /// Should return true if the collision should take place as normal, or false if the collision should be ignored.
            std::function<bool (const Arbiter&)> onCollisionPreSolve = [](const Arbiter&) { return true; };
            
            /// Function called when collision has been solved.
            std::function<void (const Arbiter&)> onCollisionPostSolve = [](const Arbiter&) {};
            
            /// Function called when collision has separated.
            std::function<void (const Arbiter&)> onCollisionSeparate = [](const Arbiter&) {};
            
            Space();
            ~Space() { cpSpaceDestroy(_space); }
            
            int getIterations() { return cpSpaceGetIterations(_space); }
            Vec2f getGravity() { return Vec2f(cpSpaceGetGravity(_space)); }
            float getDamping() { return cpSpaceGetDamping(_space); }
            float getIdleSpeedThreshold() { return cpSpaceGetIdleSpeedThreshold(_space); }
            float getSleepTimeThreshold() { return cpSpaceGetSleepTimeThreshold(_space); }
            float getCollisionSlop() { return cpSpaceGetCollisionSlop(_space); }
            float getCollisionBias() { return cpSpaceGetCollisionBias(_space); }
            float getCurrentTimeStep() { return cpSpaceGetCurrentTimeStep(_space); }
            
            void setIterations(int iterations) { cpSpaceSetIterations(_space, iterations); }
            void setGravity(const Vec2f& gravity) { cpSpaceSetGravity(_space, gravity); }
            void setDamping(float damping) { cpSpaceSetDamping(_space, damping); }
            void setIdleSpeedThreshold(float idleSpeedThreshold) { cpSpaceSetIdleSpeedThreshold(_space, idleSpeedThreshold); }
            void setSleepTimeThreshold(float sleepTimeThreshold) { cpSpaceSetSleepTimeThreshold(_space, sleepTimeThreshold); }
            void setCollisionSlop(float collisionSlop) { cpSpaceSetCollisionSlop(_space, collisionSlop); }
            void setCollisionBias(float collisionBias) { cpSpaceSetCollisionBias(_space, collisionBias); }
            
            void reindexStatic() { cpSpaceReindexStatic(_space); }
            
            void step(float dt) { cpSpaceStep(_space, dt); }
            
            void useSpatialHash(float dim, int count) { cpSpaceUseSpatialHash(_space, dim, count); }
            
            bool containsBody(Body& body) { return cpSpaceContainsBody(_space, body); }
            bool containsConstraint(Constraint& constraint) { return cpSpaceContainsConstraint(_space, constraint); }
            bool containsShape(Shape& shape) { return cpSpaceContainsShape(_space, shape); }
            
            void reindexShape(Shape& shape) { cpSpaceReindexShape(_space, shape); }
            void reindexShapesForBody(Body& body) { cpSpaceReindexShapesForBody(_space, body); }
                        
        private:
            cpSpace _theSpace;
            cpSpace* _space;
            
            static Space* currentInstance();
            
            void addBody(Body& body) { cpSpaceAddBody(_space, body); }
            void addConstraint(Constraint& constraint) { cpSpaceAddConstraint(_space, constraint); }
            void addShape(Shape& shape) { cpSpaceAddShape(_space, shape); }
            
            void removeBody(Body& body) { cpSpaceRemoveBody(_space, body); }
            void removeConstraint(Constraint& constraint) { cpSpaceRemoveConstraint(_space, constraint); }
            void removeShape(Shape& shape) { cpSpaceRemoveShape(_space, shape); }
                        
            static int beginFunc(cpArbiter *arb, cpSpace *space, void *data);
            static int preSolveFunc(cpArbiter *arb, cpSpace *space, void *data);
            static void postSolveFunc(cpArbiter *arb, cpSpace *space, void *data);
            static void separateFunc(cpArbiter *arb, cpSpace *space, void *data);
        };
        
    }
}

#endif // SOL_USE_PHYSICS

#endif