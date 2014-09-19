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

#include "SolAction.h"
#include "SolActionManager.h"
#include "SolScenenode.h"

namespace sol
{
    
    Action::Action(float duration) :
        _duration(duration),
        _time(0.0),
        _done(false)
    {
        onUpdate = [](float) {};
        onEnd = []() {};
    }
    
    Action::~Action()
    {
        onUpdate = [](float) {};
        onEnd = []() {};
    }
    
    void Action::update()
    {
        if (_time >= _duration && _duration >= 0.0)
        {
            _time = _duration;
            _done = true;
        }

        onUpdate(_time);
        if (_done) onEnd();
        
        _time += Manager::instance().dt();
    }
    
    Action* createTranslateTo(float duration, SceneNode* node, Vec2f dest, Easing<Vec2f>::Function easing)
    {
        return createTranslateBy(duration,node,dest-node->getPosition(),easing);
    }
    
    Action* createTranslateBy(float duration, SceneNode* node, Vec2f delta, Easing<Vec2f>::Function easing)
    {
        Action* ret = new Action(duration);
        Vec2f pos = node->getPosition();
        ret->onUpdate = [=](float t)
        {
            node->setPosition(easing(pos,delta,t,duration));
        };
        return ret;
    }
    
    Action* createScaleTo(float duration, SceneNode* node, Vec2f dest, Easing<Vec2f>::Function easing)
    {
        return createScaleBy(duration,node,dest-node->getScale(),easing);
    }
    
    Action* createScaleBy(float duration, SceneNode* node, Vec2f delta, Easing<Vec2f>::Function easing)
    {
        Action* ret = new Action(duration);
        Vec2f scale = node->getScale();
        ret->onUpdate = [=](float t)
        {
            node->setScale(easing(scale,delta,t,duration));
        };
        return ret;
    }
    
    Action* createRotateTo(float duration, SceneNode* node, float dest, Easing<float>::Function easing)
    {
        return createRotateBy(duration,node,dest-node->getPosition(),easing);
    }
    
    Action* createRotateBy(float duration, SceneNode* node, float delta, Easing<float>::Function easing)
    {
        Action* ret = new Action(duration);
        float rot = node->getRotation();
        ret->onUpdate = [=](float t)
        {
            node->setRotation(easing(rot,delta,t,duration));
        };
        return ret;
    }
    
    Action* createFadeTo(float duration, RenderObject* rend, float dest, Easing<float>::Function easing)
    {
        return createFadeBy(duration,rend,dest-rend->getAlpha(),easing);
    }
    
    Action* createFadeBy(float duration, RenderObject* rend, float delta, Easing<float>::Function easing)
    {
        Action* ret = new Action(duration);
        float alpha = rend->getAlpha();
        ret->onUpdate = [=](float t)
        {
            rend->setAlpha(easing(alpha,delta,t,duration));
        };
        return ret;
    }
    
    Action* createSizeTo(float duration, Quad* quad, Vec2f dest, Easing<Vec2f>::Function easing)
    {
        return createSizeBy(duration,quad,dest-quad->getSize(),easing);
    }
    
    Action* createSizeBy(float duration, Quad* quad, Vec2f delta, Easing<Vec2f>::Function easing)
    {
        Action* ret = new Action(duration);
        Vec2f size = quad->getSize();
        ret->onUpdate = [=](float t)
        {
            quad->setSize(easing(size,delta,t,duration));
        };
        return ret;
    }

    Action* createDelayedAction(float duration, Action* action)
    {
        Action* ret = new Action(duration);
        ret->onEnd = [=]()
        {
            ActionManager::instance().runAction(action);
        };
        return ret;
    }

    
}