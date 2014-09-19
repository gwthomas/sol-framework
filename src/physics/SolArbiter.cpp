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

#include "SolArbiter.h"

#if SOL_USE_PHYSICS

namespace sol
{
    namespace physics
    {
        
        std::pair<Shape*, Shape*> Arbiter::getShapes() const
        {
            cpShape* a, * b;
            cpArbiterGetShapes(_arbiter, &a, &b);
            return std::make_pair((Shape*)cpShapeGetUserData(a), (Shape*)cpShapeGetUserData(b));
        }
        
        std::pair<Body*, Body*> Arbiter::getBodies() const
        {
            cpBody* a, * b;
            cpArbiterGetBodies(_arbiter, &a, &b);
            return std::make_pair((Body*)cpBodyGetUserData(a), (Body*)cpBodyGetUserData(b));
        }
        
    }
}

#endif // SOL_USE_PHYSICS