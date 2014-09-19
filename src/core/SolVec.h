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

#ifndef SOL_VEC_H
#define SOL_VEC_H

#include <cmath>
#include "SolUtil.h"
#if SOL_USE_PHYSICS
#include "chipmunk.h"
#endif

namespace sol
{
    
    template<class T>
    struct Vec2
    {
        T x = 0;
        T y = 0;
        
        Vec2(T x, T y) : x(x), y(y) {}
        Vec2() = default;
        
#if SOL_USE_PHYSICS
        Vec2(const cpVect& vec) : Vec2(vec.x, vec.y) {}
        
        operator cpVect() const { return cpv(x, y); }
#endif
        
        void normalize() { float m = magnitude(); x /= m; y /= m; }
        Vec2<T> normalized() const { float m = magnitude(); return Vec2<T>(x / m, y / m); }
        
        Vec2<T> flipflop() const { return Vec2<T>(y, x); }
        Vec2<T> abs() const { return Vec2<T>(std::abs(x), std::abs(y)); }
        float magnitude() const { return std::sqrt(magnitudeSquared()); }
        T magnitudeSquared() const { return x * x + y * y; }
        
        float dot(const Vec2<T>& vec) const { return x * vec.x + y * vec.y; }
        
        float angle() const;
        float angle(const Vec2<T>& vec) const { return acosf(dot(vec) / magnitude() / vec.magnitude()); }
        
        Vec2<T> midpoint(const Vec2<T>& vec) const { return Vec2<T>((x + vec.x) / T(2), (y + vec.y) / T(2)); }
        
        Vec2<T> operator-() const { return Vec2<T>(-x, -y); }
        
        Vec2<T> operator+(const Vec2<T>& vec) const { return Vec2<T>(x + vec.x, y + vec.y); }
        Vec2<T> operator-(const Vec2<T>& vec) const { return Vec2<T>(x - vec.x, y - vec.y); }
        Vec2<T> operator*(T scale) const { return Vec2<T>(x * scale, y * scale); }
        Vec2<T> operator/(T scale) const { return Vec2<T>(x / scale, y / scale); }
        
        void operator+=(const Vec2<T>& vec) { x += vec.x; y += vec.y; }
        void operator-=(const Vec2<T>& vec) { x -= vec.x; y -= vec.y; }
        void operator*=(T scale) { x *= scale; y *= scale; }
        void operator/=(T scale) { x /= scale; y /= scale; }
        
        bool operator==(const Vec2<T>& vec) const { return x == vec.x && y == vec.y; }
        bool operator!=(const Vec2<T>& vec) const { return x != vec.x || y != vec.y; }
        
        operator bool() const { return x != 0 || y != 0; }
        
        template<class U>
        Vec2<U> cast() const { return Vec2<U>(x, y); }
        
        friend std::ostream& operator<<(std::ostream& os, const Vec2<T>& vec)
        {
            os << "(" << vec.x << ", " << vec.y << ")";
            return os;
        }
    };
        
    template<class T>
    float Vec2<T>::angle() const
    {
        if (x == 0.0)
        {
            if (y == 0.0) return 0.0;
            else if (y > 0.0) return M_PI_2;
            else return 3.0 * M_PI_2;
        }
        else if (x > 0.0)
        {
            if (y == 0.0) return 0.0;
            else if (y > 0.0) return atanf(y / x);
            else return 2.0 * M_PI + atanf(y / x);
        }
        else
        {
            if (y == 0.0) return M_PI;
            else return M_PI + atanf(y / x);
        }
    }
    
    typedef Vec2<float> Vec2f;
    typedef Vec2<int> Vec2i;
        
    inline Vec2f unitVec2f(float theta)
    {
        float rad = degreesToRadians(theta);
        return Vec2f(std::cos(rad), std::sin(rad));
    }
        
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    template<class T>
    struct Vec3
    {
        T x = 0;
        T y = 0;
        T z = 0;
        
        Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
        Vec3(const Vec2<T>& vec, T z) : Vec3(vec.x, vec.y, x) {}
        Vec3() = default;
        
        Vec2<T> to2D() const { return Vec2<T>(x, y); }
                
        void normalize()
        {
            float m = magnitude();
            x /= m;
            y /= m;
            z /= m;
        }
        
        Vec3<T> normalized() const
        {
            float m = magnitude();
            return Vec3<T>(x / m, y / m, z / m);
        }
        
        float magnitude() const { return std::sqrt(magnitudeSquared()); }
        float magnitudeSquared() const { return x * x + y * y + z * z; }
        
        float dotProduct(const Vec3<T>& vec) const { return x * vec.x + y * vec.y + z * vec.z; }
        
        Vec3<T> crossProduct(const Vec3<T>& vec) const
        {
            return Vec3<T>((y * vec.z) - (z * vec.y), (z * vec.x) - (x * vec.z), (x * vec.y) - (y * vec.x));
        }
        
        Vec3<T> midpoint(const Vec3<T>& vec) const { return Vec3<T>((x + vec.x) * 0.5, (y + vec.y) * 0.5, (z + vec.z) * 0.5); }
        
        Vec3<T> operator+(const Vec3<T>& vec) const { return Vec3<T>(x + vec.x, y + vec.y, z + vec.z); }
        Vec3<T> operator-(const Vec3<T>& vec) const { return Vec3<T>(x - vec.x, y - vec.y, z - vec.z); }
        Vec3<T> operator*(T scale) const { return Vec3<T>(x * scale, y * scale, z * scale); }
        Vec3<T> operator/(T scale) const { return Vec3<T>(x / scale, y / scale, z / scale); }
        
        void operator+=(const Vec3<T>& vec) { x += vec.x; y += vec.y; z += vec.z; }
        void operator-=(const Vec3<T>& vec) { x -= vec.x; y -= vec.y; z -= vec.z; }
        void operator*=(T scale) { x *= scale; y *= scale; z *= scale; }
        void operator/=(T scale) { x /= scale; y /= scale; z /= scale; }
        
        bool operator==(const Vec3<T>& vec) const { return x == vec.x && y == vec.y && z == vec.z; }
        bool operator!=(const Vec3<T>& vec) const { return x != vec.x || y != vec.y || z != vec.z; }
        
        operator bool() const { return x != 0 || y != 0 || z != 0; }
        
        template<class U>
        Vec3<U> cast() const { return Vec3<U>(x, y, z); }
        
        friend std::ostream& operator<<(std::ostream& os, const Vec3<T>& vec)
        {
            os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
            return os;
        }
    };
    
    typedef Vec3<float> Vec3f;
    typedef Vec3<int> Vec3i;
    
}


#endif