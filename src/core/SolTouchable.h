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

#ifndef SOL_TOUCHABLE_H
#define SOL_TOUCHABLE_H

#include "SolAABB.h"
#include "SolInputManager.h"
#include "SolSceneNode.h"

namespace sol
{
    
    class Touchable : public SceneNode
    {
        friend class InputManager;
        
    public:
        typedef std::function<void (const Touch&)> Callback;
        
        Callback onPress;
        Callback onMoveInside;
        Callback onMoveOutside;
        Callback onRelease;
        Callback onCancel;
        Callback onEnter;
        Callback onExit;
        
        bool enabled = true;
        bool consumesTouches = true;
        
        virtual ~Touchable() = default;
        
        AABBf getBounds() const { return AABBf(getAbsolutePosition(), _size.x, _size.y); }
        const Vec2f& getSize() const { return _size; }
        int getTouchID() const { return _touchID; }
        
        bool isDown() const { return _touchID != -1; }
        
        bool canHandleTouchEvent(const Touch& touch, TouchEvent event);
        
        void setSize(const Vec2f& size) { _size = size; }
        void setSize(float width, float height) { setSize(Vec2f(width, height)); }
                
    protected:        
        Vec2f _size;
        
        int _touchID = -1;
                
        void onAdd(Scene& scene) override;
        void onRemove() override;
        
        // called by friend InputManager
        virtual bool handleTouchEvent(const Touch& touch, TouchEvent event);
                
    private:
        // cannot scale or rotate a touchable since they use AABBs
        void setScale(const Vec2f&) override { assert(false); }
        void setRotation(float) override { assert(false); }
    };
        
}

#endif