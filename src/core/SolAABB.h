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

#ifndef SOL_AABB_H
#define SOL_AABB_H

#include "SolVec.h"

namespace sol
{
    
    /// Type-templated axis-aligned bounding box.
    template<class T>
    struct AABB
    {
        T left; ///< Smallest x value.
        T right; ///< Largest x value.
        T bottom; ///< Smallest y value.
        T top; ///< Largest y value.
        
        /// Constructs the rectangle with initial values.
        AABB(T left, T right, T bottom, T top);
        
        /// Constructs the rectangle from the bottom left point and size.
        AABB(const Vec2<T>& bottomLeft, const Vec2<T>& size);
        
        /// Constructs the rectangle from the center, width, and height.
        AABB(const Vec2<T>& center, T width, T height);
        
        /// Default constructor that initializes to zero.
        AABB() : AABB(0, 0, 0, 0) {}
        
        /// Width of rectangle.
        T width() const { return right - left; }
        
        /// Height of rectangle.
        T height() const { return top - bottom; }
        
        /// Determines whether values of left, right, bottom, and top are logically valid.
        bool isValid() const { return left <= right && bottom <= top; }
        
        /// Determines whether a point lies within the rectangle.
        bool containsPoint(Vec2<T> point) const;
        
        /// Multiplies all components of the rectable by a scalar.
        AABB<T> operator*(T scale) const;
        
        /// Converts rectangle to boolean value: true if it has dimensions, and those are valid; otherwise false.
        operator bool() const { return (left != 0 || right != 0 || bottom != 0 || top != 0) && isValid(); }
    };
    
    typedef AABB<int> AABBi;
    typedef AABB<float> AABBf;
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    template<class T>
    AABB<T>::AABB(T left, T right, T bottom, T top) :
        left(left),
        right(right),
        bottom(bottom),
        top(top)
    {
        assert(isValid());
    }
    
    template<class T>
    AABB<T>::AABB(const Vec2<T>& bottomLeft, const Vec2<T>& size) :
        AABB(bottomLeft.x, bottomLeft.x + size.x, bottomLeft.y, bottomLeft.y + size.y)
    {}
    
    template<class T>
    AABB<T>::AABB(const Vec2<T>& center, T width, T height)
    {
        T halfw = width * 0.5;
        T halfh = height * 0.5;
        
        left = center.x - halfw;
        right = center.x + halfw;
        bottom = center.y - halfh;
        top = center.y + halfh;
    }
    
    template<class T>
    bool AABB<T>::containsPoint(Vec2<T> point) const
    {
        return left <= point.x && point.x <= right && bottom <= point.y && point.y <= top;
    }
    
    template<class T>
    AABB<T> AABB<T>::operator*(T scale) const
    {
        return AABB<T>(left * scale, right * scale, bottom * scale, top * scale);
    }
}

#endif