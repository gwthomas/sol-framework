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

#include "SolInputManager.h"
#include "SolScene.h"
#include "SolTouchable.h"

namespace sol
{
    
    void Touchable::onAdd(Scene& scene)
    {
        scene.getInputManager().addTouchable(*this);
        SceneNode::onAdd(scene);
    }
    
    void Touchable::onRemove()
    {
        _scene->getInputManager().removeTouchable(*this);
        SceneNode::onRemove();
    }
    
    bool Touchable::canHandleTouchEvent(const Touch& touch, TouchEvent event)
    {
        return enabled && ((event == TouchDown && _touchID == -1) || touch.id == _touchID);
    }
    
    bool Touchable::handleTouchEvent(const Touch& touch, TouchEvent event)
    {
        AABBf bounds = getBounds();
        bool containsPrev = bounds.containsPoint(touch.prev);
        bool containsLoc = bounds.containsPoint(touch.loc);
        
        switch (event)
        {
            case TouchDown:
                if (containsLoc)
                {
                    _touchID = touch.id;
                    if (onPress) onPress(touch);
                    break;
                }
                else return false;

            case TouchMoved:
                if (containsLoc && containsPrev) { if (onMoveInside) onMoveInside(touch); }
                else if (!containsLoc && !containsPrev) { if (onMoveOutside) onMoveOutside(touch); }
                else if (containsLoc && !containsPrev) { if (onEnter) onEnter(touch); }
                else { if (onExit) onExit(touch); }
                break;
                
            case TouchUp:
                if (containsLoc) { if (onRelease) onRelease(touch); }
                else { if (onCancel) onCancel(touch); }
                
                _touchID = -1;
        }
        
        return true;
    }
    
}