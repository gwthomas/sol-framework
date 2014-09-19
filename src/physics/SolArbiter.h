/*
 *
 * Copyright (c) 2012 Garrett Thomas
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the use o this software.
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

#ifndef SOL_PHYSICS_ARBITER_H
#define SOL_PHYSICS_ARBITER_H

#include "SolConfig.h"
#if SOL_USE_PHYSICS

#   include <utility>
#   include "chipmunk.h"
#   include "SolVec.h"

namespace sol
{
    namespace physics
    {
        
        class Shape;
        class Body;
        
        class Arbiter
        {
            friend class Space;
            
        public:
            float getElasticity() const { return cpArbiterGetElasticity(_arbiter); }
            float getFriction() const { return cpArbiterGetFriction(_arbiter); }
            Vec2f getSurfaceVelocity() const { return Vec2f(cpArbiterGetSurfaceVelocity(_arbiter)); }
            
            bool isFirstContact() const { return cpArbiterIsFirstContact(_arbiter); }
            
            std::pair<Shape*, Shape*> getShapes() const;
            std::pair<Body*, Body*> getBodies() const;
            
        private:
            const cpArbiter* _arbiter;
            
            Arbiter(const cpArbiter* arb) : _arbiter(arb) {}
        };
        
    }
}

#endif // SOL_USE_PHYSICS

#endif