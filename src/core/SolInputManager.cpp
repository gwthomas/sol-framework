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

#include "SolTouchable.h"
#include "SolInputManager.h"
#include "SolScene.h"

namespace sol
{
    
    using std::vector;
    
    bool compareDepth(Touchable* t1, Touchable* t2)
    {
        return t1->getAbsoluteDepth() < t2->getAbsoluteDepth();
    }
    
    InputManager* InputManager::currentInstance()
    {
        Scene* activeScene = Manager::instance().getCurrentScene();
        return activeScene != nullptr ? &activeScene->getInputManager() : nullptr;
    }
    
    InputManager::InputManager()
    {
        for (bool& exists : _touchExists) exists = false;
    }
    
    const Touch* InputManager::getTouch(int index) const
    {
        return (0 <= index && index < SOL_MAX_TOUCHES && _touchExists[index]) ? &_touches[index] : nullptr;
    }
    
    void InputManager::addTouchable(Touchable& touchable)
    {
        _touchables.push_back(&touchable);
        setNeedsReorder();
    }
    
    void InputManager::removeTouchable(Touchable& touchable)
    {
        for (auto b = _touchables.begin(), e = _touchables.end(); b != e; ++b)
        {
            if (*b == &touchable)
            {
                _touchables.erase(b);
                return;
            }
        }
    }
    
    void InputManager::touchDown(unsigned int index, const Vec2f& loc)
    {
        Touch& touch = _touches[index];
        touch.id = index;
        touch.orig = touch.prev = touch.loc = loc;
        
        _touchExists[index] = true;
        _touchCount++;
        
        //if (_needsReorder)
        {
            std::sort(_touchables.begin(), _touchables.end(), &compareDepth);
            setNeedsReorder(false);
        }
                
        if (!Manager::instance().getCurrentScene()->onTouchEvent(touch, TouchDown)) return;
        
        for (Touchable* touchable : _touchables)
        {
            if (touchable->canHandleTouchEvent(touch, TouchDown) &&
                touchable->handleTouchEvent(touch, TouchDown) &&
                touchable->consumesTouches) return;
        }
    }
    
    void InputManager::touchMoved(unsigned int index, const Vec2f& loc)
    {
        Touch& touch = _touches[index];
        touch.prev = touch.loc;
        touch.loc = loc;
        
        //if (_needsReorder)
        {
            std::sort(_touchables.begin(), _touchables.end(), &compareDepth);
            setNeedsReorder(false);
        }
        
        if (!Manager::instance().getCurrentScene()->onTouchEvent(touch, TouchMoved)) return;
        
        for (Touchable* touchable : _touchables)
        {
            if (touchable->canHandleTouchEvent(touch, TouchMoved) &&
                touchable->handleTouchEvent(touch, TouchMoved) &&
                touchable->consumesTouches) return;
        }
    }
    
    void InputManager::touchUp(unsigned int index)
    {
        Touch& touch = _touches[index];
        
        //if (_needsReorder)
        {
            std::sort(_touchables.begin(), _touchables.end(), &compareDepth);
            setNeedsReorder(false);
        }
        
        if (!Manager::instance().getCurrentScene()->onTouchEvent(touch, TouchUp)) return;
        
        for (Touchable* touchable : _touchables)
        {
            if (touchable->canHandleTouchEvent(touch, TouchUp) &&
                touchable->handleTouchEvent(touch, TouchUp) &&
                touchable->consumesTouches) break;
        }
        
        _touchExists[index] = false;
        _touchCount--;
    }
    
}