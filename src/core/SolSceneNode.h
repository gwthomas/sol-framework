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

#ifndef SOL_SCENENODE_H
#define SOL_SCENENODE_H

#include <queue>
#include <vector>
#include "SolManager.h"

namespace sol
{
    class Action;
    class Scene;
    
    class SceneNode : public Noncopyable
    {
        friend class Scene;
        friend class SceneNode;
        
    public:
        SceneNode() = default;
        virtual ~SceneNode();
        
        const std::string& getName() const { return _name; }
        Scene* getScene() { return _scene; }
        SceneNode* getParent() { return _parent; }
        const std::vector<SceneNode*>& getChildren() const { return _children; }
        SceneNode* getChildByName(const std::string& name);
        const Vec2f& getPosition() const { return _position; }
        const Vec2f& getScale() const { return _scale; }
        float getRotation() const { return _rotation; }
        float getDepth() const { return _depth; }
        
        bool hasScene() const { return _scene != nullptr; }
        bool hasParent() const { return _parent != nullptr; }
        bool hasDirtyDepth(bool recursive = true) const;
        bool hasDirtyTransform() const { return _dirtyTransform; }
        
        Vec2f getAbsolutePosition() const { return hasParent() ? _position + _parent->getAbsolutePosition() : _position; }
        float getAbsoluteDepth() const { return hasParent() ? _depth + _parent->getAbsoluteDepth() : _depth; }
        const Matrix& getTransform() const { return _parent ? _combinedTransform : _localTransform; }
        
        void setName(const std::string& name) { _name = name; }
        void setOwnsChildren(bool ownsChildren = true) { _ownsChildren = ownsChildren; }
        virtual void setPosition(const Vec2f& position);
        void setPosition(float x, float y) { setPosition(Vec2f(x, y)); }
        virtual void setScale(const Vec2f& scale);
        void setScale(float x, float y) { setScale(Vec2f(x, y)); }
        virtual void setRotation(float rotation);
        void setDepth(float depth);
        
        void translate(const Vec2f& delta) { setPosition(_position + delta); }
        void translate(float dx, float dy) { translate(Vec2f(dx, dy)); }
        void scale(const Vec2f& delta) { setScale(Vec2f(_scale.x * delta.x, _scale.y * delta.y)); }
        void scale(float dx, float dy) { scale(Vec2f(dx, dy)); }
        void rotate(float delta) { setRotation(_rotation + delta); }
        
        void clearChildren();
        void addChild(SceneNode& node);
        void removeChild(SceneNode& node);
        void removeChildByName(const std::string& name);
                
        virtual void update() {}
        void updateAll();
                
    protected:
        Scene* _scene = nullptr;
        
        SceneNode* _parent = nullptr;
        std::vector<SceneNode*> _children;
        
        bool _fertile = true;       // true if the node can have children
        bool _ownsChildren = false; // true if the node's dtor should delete any children it has
        
        Vec2f _position;
        Vec2f _scale = Vec2f(1.0, 1.0);
        float _rotation = 0.0;
        float _depth = 0.0;
        bool _dirtyDepth = false;
        
        Matrix _localTransform;
        Matrix _combinedTransform;
        
        bool _needsTransform = false;
        bool _dirtyTransform = false;
        
        // called by friends Scene, SceneNode
        void setParent(SceneNode* parent) { _parent = parent; }
        void setNeedsTransform(bool needsIt = true) { _needsTransform = needsIt; }
        
        // internal use
        void updateTransform();
        
        virtual void onAdd(Scene& scene);
        virtual void onRemove();
        
    private:
        std::string _name;
    };
    
}

#endif