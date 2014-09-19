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

#ifndef SOL_INTERSECTION_H
#define SOL_INTERSECTION_H

#include "SolAABB.h"

namespace sol
{
    
    /// Determines whether a circle with the given center and radius interesects the rectangle.
    template<class T>
    bool intersects(const AABB<T>& aabb, Vec2<T> center, T radius)
    {
        return (center.x + radius > aabb.left) && (center.x - radius < aabb.right) && (center.y + radius > aabb.bottom) && (center.y - radius < aabb.top);
    }
    
    /// Determines whether two rectangles intersect.
    template<class T>
    bool intersects(const AABB<T>& aabb1, const AABB<T>& aabb2)
    {
        return aabb1.containsPoint(Vec2<T>(aabb2.left, aabb2.bottom)) || aabb1.containsPoint(Vec2<T>(aabb2.right, aabb2.bottom))
            || aabb1.containsPoint(Vec2<T>(aabb2.left, aabb2.top))    || aabb1.containsPoint(Vec2<T>(aabb2.right, aabb2.top))
            || aabb2.containsPoint(Vec2<T>(aabb1.left, aabb1.bottom)) || aabb2.containsPoint(Vec2<T>(aabb1.right, aabb1.bottom))
            || aabb2.containsPoint(Vec2<T>(aabb1.left, aabb1.top))    || aabb2.containsPoint(Vec2<T>(aabb1.right, aabb1.top));
    }
    
    template<class T>
    bool intersects(Vec2<T> center1, T radius1, Vec2<T> center2, T radius2)
    {
        return (center1 - center2).magnitude() < radius1 + radius2;
    }
    
}

#endif