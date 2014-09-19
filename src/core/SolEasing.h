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

#ifndef SOL_EASING_H
#define SOL_EASING_H

#include <cmath>
#include <functional>

// Adapted from Robert Penner's easing functions

namespace sol
{
    
    template<typename T>
    struct Easing
    {
        typedef std::function<T (T, T, float, float)> Function;
    };
    
    template<typename T>
    T linearTween(T initial, T change, float time, float duration)
    {
        float tmp = time/duration;
        return initial+change*tmp;
    }
    
    template<typename T>
    T easeInQuad(T initial, T change, float time, float duration)
    {
        float tmp = time/duration;
        return initial+change*tmp*tmp;
    }
    
    template<typename T>
    T easeOutQuad(T initial, T change, float time, float duration)
    {
        float tmp = time/duration;
        return initial+(-change)*tmp*(tmp-2.0f);
    }
    
    template<typename T>
    T easeInOutQuad(T initial, T change, float time, float duration)
    {
        float tmp = (time/duration)*2.0f;
        if (tmp < 1.0f) return initial+(change*0.5f)*tmp*tmp;
        tmp -= 1.0f;
        return initial+(-change*0.5f)*(tmp*(tmp-2.0f)-1.0f);
    }
    
    template<typename T>
    T easeInCubic(T initial, T change, float time, float duration)
    {
        float tmp = time/duration;
        return initial+change*tmp*tmp*tmp;
    }
    
    template<typename T>
    T easeOutCubic(T initial, T change, float time, float duration)
    {
        float tmp = time/duration;
        tmp -= 1.0f;
        return initial+change*(tmp*tmp*tmp+1.0f);
    }
    
    template<typename T>
    T easeInOutCubic(T initial, T change, float time, float duration)
    {
        float tmp = (time/duration)*2.0f;
        if (tmp < 1.0f) return initial+(change*0.5f)*tmp*tmp*tmp;
        tmp -= 2.0f;
        return initial+(change*0.5f)*(tmp*tmp*tmp+2.0f);
    }
    
    template<typename T>
    T easeInQuart(T initial, T change, float time, float duration)
    {
        float tmp = time/duration;
        return initial+change*tmp*tmp*tmp*tmp;
    }
    
    template<typename T>
    T easeOutQuart(T initial, T change, float time, float duration)
    {
        float tmp = time/duration;
        tmp -= 1.0f;
        return initial+(-change)*(tmp*tmp*tmp*tmp-1.0f);
    }
    
    template<typename T>
    T easeInOutQuart(T initial, T change, float time, float duration)
    {
        float tmp = (time/duration)*2.0f;
        if (tmp < 1.0f) return initial+(change*0.5f)*tmp*tmp*tmp*tmp;
        tmp -= 2.0f;
        return initial+(-change*0.5f)*(tmp*tmp*tmp*tmp-2.0f);
    }
    
    template<typename T>
    T easeInQuint(T initial, T change, float time, float duration)
    {
        float tmp = time/duration;
        return initial+change*tmp*tmp*tmp*tmp*tmp;
    }
    
    template<typename T>
    T easeOutQuint(T initial, T change, float time, float duration)
    {
        float tmp = time/duration;
        tmp -= 1.0f;
        return initial+change*(tmp*tmp*tmp*tmp*tmp+1.0f);
    }
    
    template<typename T>
    T easeInOutQuint(T initial, T change, float time, float duration)
    {
        float tmp = (time/duration)*2.0f;
        if (tmp < 1.0f) return initial+(change*0.5)*tmp*tmp*tmp*tmp*tmp;
        tmp -= 2.0f;
        return initial+(change*0.5f)*(tmp*tmp*tmp*tmp*tmp+2.0f);
    }
    
    template<typename T>
    T easeInSine(T initial, T change, float time, float duration)
    {
        float tmp = time/duration;
        return initial+change*(-std::cos(tmp*M_PI_2)+1.0f);
    }
    
    template<typename T>
    T easeOutSine(T initial, T change, float time, float duration)
    {
        float tmp = time/duration;
        return initial+change*std::sin(tmp*M_PI_2);
    }
    
    template<typename T>
    T easeInOutSine(T initial, T change, float time, float duration)
    {
        float tmp = time/duration;
        return initial+(-change*0.5f)*(std::cos(tmp*M_PI)-1.0f);
    }
    
    template<typename T>
    T easeInExp(T initial, T change, float time, float duration)
    {
        float tmp = time/duration;
        return initial+change*std::exp(10.0f*(tmp-1.0f));
    }
    
    template<typename T>
    T easeOutExp(T initial, T change, float time, float duration)
    {
        float tmp = time/duration;
        return initial+change*(-std::exp(-10.0f*tmp)+1.0f);
    }
    
    template<typename T>
    T easeInOutExp(T initial, T change, float time, float duration)
    {
        float tmp = (time/duration)*2.0f;
        if (tmp < 1.0f) return initial+(change*0.5f)*std::exp(10.0f*(tmp-1.0f));
        tmp -= 1.0f;
        return initial+(change*0.5f)*(-std::exp(-10.0f*tmp)+2.0f);
    }
    
    template<typename T>
    T easeInCirc(T initial, T change, float time, float duration)
    {
        float tmp = time/duration;
        return initial+(-change)*(std::sqrt(1.0f-tmp*tmp)-1.0f);
    }
    
    template<typename T>
    T easeOutCirc(T initial, T change, float time, float duration)
    {
        float tmp = time/duration;
        tmp -= 1.0;
        return initial+change*std::sqrt(1.0f-tmp*tmp);
    }
    
    template<typename T>
    T easeInOutCirc(T initial, T change, float time, float duration)
    {
        float tmp = (time/duration)*2.0f;
        if (tmp < 1.0f) return initial+(-change*0.5f)*(std::sqrt(1.0f-tmp*tmp)-1.0f);
        tmp -= 2.0f;
        return initial+(change*0.5f)*(std::sqrt(1.0f-tmp*tmp)+1.0f);
    }
    
}

#endif
