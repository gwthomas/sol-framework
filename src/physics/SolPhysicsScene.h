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

#ifndef SOL_PHYSICS_PHYSICSSCENE_H
#define SOL_PHYSICS_PHYSICSSCENE_H

#include "SolConfig.h"
#if SOL_USE_PHYSICS

#   include "SolArbiter.h"
#   include "SolScene.h"
#   include "SolSpace.h"

namespace sol
{
    namespace physics
    {
        
        /// Specialized scene that already includes the physics world.
        /// Subclass this class to create scenes that require physics.
        class PhysicsScene : public Scene
        {
        public:
            /// Steps the physics world before updating the scene as normal.
            virtual void update() override { _space.step(Manager::instance().dt()); Scene::update(); }
            
        protected:
            Space _space;
            
            Space* getSpace() override { return &_space; }
        };
        
    }
}

#endif // SOL_USE_PHYSICS

#endif