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

#ifndef SOL_INPUTHANDLER_H
#define SOL_INPUTHANDLER_H

#include <vector>
#include "SolConfig.h"
#include "SolTouch.h"

namespace sol
{
    
    class Touchable;
    
    class InputManager : public Noncopyable
    {        
    public:
        static InputManager* currentInstance();
        
        InputManager();
        ~InputManager() { _touchables.clear(); }
        
        const Touch* getTouch(int index) const;
        unsigned int getTouchCount() const { return _touchCount; }
#if SOL_USE_ACCELEROMETER
        const Vec3f& getTilt() const { return _tilt; }
#endif
        
        void setNeedsReorder(bool needsReorder = true) { _needsReorder = needsReorder; }
        
        void addTouchable(Touchable& touchable);
        void removeTouchable(Touchable& touchable);
        
        void touchDown(unsigned int index, const Vec2f& loc);
        void touchMoved(unsigned int index, const Vec2f& loc);
        void touchUp(unsigned int index);
        
#if SOL_USE_ACCELEROMETER
        void tilt(const Vec3f& tilt) { _tilt = tilt; }
#endif
        
    private:
        std::vector<Touchable*> _touchables;
        bool _needsReorder = false;
                              
        Touch _touches[SOL_MAX_TOUCHES];
        bool _touchExists[SOL_MAX_TOUCHES];
        unsigned int _touchCount = 0;
                
#if SOL_USE_ACCELEROMETER
        Vec3f _tilt;
#endif
    };
    
}

#endif