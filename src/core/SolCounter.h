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

#ifndef SOL_COUNTER_H
#define SOL_COUNTER_H

#include "SolSceneNode.h"

namespace sol
{
    
    template<class T>
    class Counter : public SceneNode
    {
    public:
        typedef std::function<bool (T)> Test;
        typedef std::function<void ()> Callback;
        
        Test test;
        Callback onTestSuccess;
        Callback onReset;
        
        Counter(T min, T max, T increment = 1, bool reset = true);
        
        T getCount() const { return _count; }
        void reset() { _count = _min; }
        
        void update() override;
        
    private:
        T _min;
        T _max;
        T _count;
        T _increment;
        bool _reset;
    };
    
    template<class T>
    Counter<T>::Counter(T min, T max, T increment, bool reset) :
        _min(min),
        _max(max),
        _increment(increment),
        _reset(reset)
    {
        assert(max > 0);
        _count = min;
    }
    
    template<class T>
    void Counter<T>::update()
    {
        _count += _increment;
        
        if (test && test(_count))
        {
            if (onTestSuccess) onTestSuccess();
        }
        
        if (_count >= _max && _reset)
        {
            if (onReset) onReset();
            reset();
        }
    }
    
}

#endif