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

#include "SolSpace.h"
#if SOL_USE_PHYSICS

#   include "SolArbiter.h"
#   include "SolScene.h"

namespace sol
{
    namespace physics
    {
        
        Space* Space::currentInstance()
        {
            Scene* currentScene = Manager::instance().getCurrentScene();
            return currentScene != nullptr ? currentScene->getSpace() : nullptr;
        }
        
        Space::Space() :
            _space(&_theSpace)
        {
            cpSpaceInit(_space);
            cpSpaceSetUserData(_space, this);
            cpSpaceSetDefaultCollisionHandler(_space, beginFunc, preSolveFunc, postSolveFunc, separateFunc, 0);
        }
        
        int Space::beginFunc(cpArbiter* arb, cpSpace* space, void* data)
        {
            const std::function<bool (const Arbiter&)>& func = currentInstance()->onCollisionBegin;
            if (func) return func(Arbiter(arb)) ? cpTrue : cpFalse;
            else return cpTrue;
        }
        
        int Space::preSolveFunc(cpArbiter* arb, cpSpace* space, void* data)
        {
            const std::function<bool (const Arbiter&)>& func = currentInstance()->onCollisionPreSolve;
            if (func) return func(Arbiter(arb)) ? cpTrue : cpFalse;
            else return cpTrue;
        }
        
        void Space::postSolveFunc(cpArbiter* arb, cpSpace* space, void* data)
        {
            const std::function<void (const Arbiter&)>& func = currentInstance()->onCollisionPostSolve;
            if (func) func(Arbiter(arb));
        }
        
        void Space::separateFunc(cpArbiter* arb, cpSpace* space, void* data)
        {
            const std::function<void (const Arbiter&)>& func = currentInstance()->onCollisionSeparate;
            if (func) func(Arbiter(arb));
        }
        
    }
}

#endif // SOL_USE_PHYSICS