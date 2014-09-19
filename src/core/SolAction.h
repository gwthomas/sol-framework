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

#ifndef SOL_ACTION_H
#define SOL_ACTION_H

#include "SolEasing.h"
#include "SolQuad.h"

namespace sol
{

    class Action
    {
    public:
        std::function<void (float t)> onUpdate;
        std::function<void ()> onEnd;
        
        Action(float duration);
        virtual ~Action();
        
        bool isDone() const { return _done; }
        
        void kill() { _done = true; }
        
        void update();
        
    private:
        float _duration;
        float _time;
        bool _done;
    };
    
    Action* createTranslateTo(float duration, SceneNode* node, Vec2f dest, Easing<Vec2f>::Function easing);
    Action* createTranslateBy(float duration, SceneNode* node, Vec2f delta, Easing<Vec2f>::Function easing);
    Action* createScaleTo(float duration, SceneNode* node, Vec2f dest, Easing<Vec2f>::Function easing);
    Action* createScaleBy(float duration, SceneNode* node, Vec2f delta, Easing<Vec2f>::Function easing);
    Action* createRotateTo(float duration, SceneNode* node, float dest, Easing<float>::Function easing);
    Action* createRotateBy(float duration, SceneNode* node, float delta, Easing<float>::Function easing);
    
    Action* createFadeTo(float duration, RenderObject* rend, float dest, Easing<float>::Function easing);
    Action* createFadeBy(float duration, RenderObject* rend, float delta, Easing<float>::Function easing);
    
    Action* createSizeTo(float duration, Quad* quad, Vec2f dest, Easing<Vec2f>::Function easing);
    Action* createSizeBy(float duration, Quad* quad, Vec2f delta, Easing<Vec2f>::Function easing);
    
    Action* createDelayedAction(float duration, Action* action);
    
}

#endif