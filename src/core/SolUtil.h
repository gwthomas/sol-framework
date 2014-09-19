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

#ifndef SOL_UTIL_H
#define SOL_UTIL_H

#include <cassert>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include "SolConfig.h"

#define SOL_PRINT(x) ::std::cout << x << "\n"
#define SOL_ERROR(x) SOL_PRINT("ERROR: " << x)

#define SOL_SAFE_DELETE(x) if (x) { delete (x); (x) = nullptr; }
#define SOL_SAFE_DELETE_ARRAY(x) if (x) { delete [] (x); (x) = nullptr; }

namespace sol
{
    
    class Noncopyable
    {
    protected:
        Noncopyable() = default;
        virtual ~Noncopyable() = default;
        
    private:
        Noncopyable(const Noncopyable&);
        Noncopyable& operator=(const Noncopyable&);
    };
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    inline float degreesToRadians(float theta)
    {
        return theta * 0.0174532925;
    }
    
    inline float radiansToDegrees(float theta)
    {
        return theta * 57.2957795;
    }
        
    inline float randomInRangef(float min, float max)
    {
        assert(max >= min);
        static const float k = 1000000.0;
        return min == max ? min : min + ((float)(arc4random() % ((int)(k * (max - min))))) / k;
    }
    
    inline int randomInRangei(int min, int max)
    {
        assert(max >= min);
        return min == max ? min : min + (arc4random() % (max - min));
    }
    
    inline float randomVariancef(float mid, float variance)
    {
        return randomInRangef(mid - variance, mid + variance);
    }
    
    inline int randomVariancei(int mid, int variance)
    {
        return randomInRangei(mid - variance, mid + variance);
    }
    
    inline bool maybe(float p)
    {
        assert(0.0 <= p && p <= 100.0);
        return randomInRangef(0.0, 100.0) <= p;
    }
    
    inline unsigned int nextPower2(unsigned int n)
    {
        unsigned int ret = 1;
        while (ret < n) ret <<= 1;
        return ret;
    }
    
    inline int wrap(int index, int count)
    {
        if (index < 0) return count + index;
        if (index >= count) return index - count;
        return index;
    }
    
    template<class T>
    inline T min(T a, T b)
    {
        return a > b ? b : a;
    }
    
    template<class T>
    inline T max(T a, T b)
    {
        return a > b ? a : b;
    }
    
    template<class T>
    inline T clamp(T val, T min, T max)
    {
        return val < min ? min : (val > max ? max : val);
    }
    
    template<class T>
    inline std::string tostring(const T& t)
    {
        std::stringstream ss;
        ss << t;
        return ss.str();
    }
    
    template<unsigned int bit>
    inline bool testbit(unsigned int bitfield)
    {
        return bool(bitfield & bit);
    }
    
}
    
#endif