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

#ifndef SOL_SCENE_H
#define SOL_SCENE_H

#include "SolAdManager.h"
#include "SolColor.h"
#include "SolManager.h"
#include "SolSceneNode.h"
#include "SolVec.h"

namespace sol
{
        
#if SOL_USE_PHYSICS
    namespace physics
    {
        class Space;
        class Body;
        class Constraint;
        class Shape;
    }
#endif
    
    class Scene : public Noncopyable
    {
        friend class InputManager;
#if SOL_USE_PHYSICS
        friend class physics::Space;
        friend class physics::Body;
        friend class physics::Constraint;
        friend class physics::Shape;
#endif
        
    public:
        Scene() { _root.onAdd(*this); }
        virtual ~Scene() = default;
        
        InputManager& getInputManager() { return _inputManager; }
        Renderer& getRenderer() { return _renderer; }
#if SOL_USE_PHYSICS
        virtual physics::Space* getSpace() { return nullptr; }
#endif
        
        void add(SceneNode& node) { _root.addChild(node); }
        void remove(SceneNode& node) { _root.removeChild(node); }
        void removeByName(const std::string& name) { _root.removeChildByName(name); }
        
        virtual void update();
        virtual void render();
        virtual void onPause() {}
        virtual void onResume() {}
        virtual bool onTouchEvent(const Touch& touch, TouchEvent event) { return true; }
#if SOL_USE_ADS
        virtual void onAdEvent(AdEvent event);
#endif
        
    protected:
        Colorf _clearColor;
        
        const InputManager& getInputManager() const { return _inputManager; }
        const Renderer& getRenderer() const { return _renderer; }
        
    private:
        InputManager _inputManager;
        Renderer _renderer;
        SceneNode _root;
    };
    
}

#endif