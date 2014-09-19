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
#include "SolScene.h"
#include "SolSceneNode.h"

namespace sol
{
    
    using std::vector;
    
    SceneNode::~SceneNode()
    {
        clearChildren();
    }
    
    SceneNode* SceneNode::getChildByName(const std::string& name)
    {
        for (SceneNode* node : _children)
        {
            if (node->getName() == name) return node;
        }
        
        return nullptr;
    }
    
    void SceneNode::setPosition(const Vec2f& position)
    {
        _position = position;
        setNeedsTransform();
    }
    
    void SceneNode::setScale(const Vec2f& scale)
    {
        _scale = scale;
        setNeedsTransform();
    }
    
    void SceneNode::setRotation(float rotation)
    {
        _rotation = rotation;
        setNeedsTransform();
    }
    
    void SceneNode::setDepth(float depth)
    {
        _depth = depth;
        _dirtyDepth = true;
    }
    
    bool SceneNode::hasDirtyDepth(bool recursive) const
    {
        if (_dirtyDepth) return true;
        if (!recursive) return false; // don't care about children
        
        for (int i = 0; i < _children.size(); i++)
        {
            if (_children[i]->hasDirtyDepth()) return true;
        }
        
        return false;
    }
    
    void SceneNode::clearChildren()
    {
        if (_ownsChildren)
        {
            for (SceneNode* child : _children) delete child;
        }
        
        _children.clear();
    }
    
    void SceneNode::addChild(SceneNode& node)
    {
        if (!_fertile || node.hasParent()) return;
        
        _children.push_back(&node);
        node.setParent(this);
        
        if (hasScene()) node.onAdd(*_scene);
    }
    
    void SceneNode::removeChild(SceneNode& node)
    {
        if (node.getParent() != this) return;
        
        for (int i = 0; i < _children.size(); i++)
        {
            if (_children[i] == &node)
            {
                _children.erase(_children.begin() + i);
                
                if (hasScene()) node.onRemove();
                node.setParent(nullptr);
                
                return;
            }
        }
    }
    
    void SceneNode::removeChildByName(const std::string& name)
    {
        for (int i = 0; i < _children.size(); i++)
        {
            if (_children[i]->getName() == name)
            {
                SceneNode* node = _children[i];
                _children.erase(_children.begin() + i);
                
                if (hasScene()) node->onRemove();
                node->setParent(nullptr);
                
                return;
            }
        }
    }
    
    void SceneNode::onAdd(Scene& scene)
    {
        _scene = &scene;
        for (SceneNode* child : _children) child->onAdd(scene);
    }
    
    void SceneNode::onRemove()
    {
        _scene = nullptr;
        for (SceneNode* child : _children) child->onRemove();
    }
    
    void SceneNode::updateAll()
    {
        _dirtyDepth = false; // clear this flag
        update();        
        updateTransform();
        for (SceneNode* child : _children) child->updateAll();
    }
    
    void SceneNode::updateTransform()
    {
        _dirtyTransform = false;
        
        if (_needsTransform) // something about this node changed. recalculate local matrix
        {
            _localTransform.transform(_position, _scale, _rotation);
            _needsTransform = false;
            _dirtyTransform = true;
        }
        
        if (_parent)
        {
            if (_parent->hasDirtyTransform())
            {
                _combinedTransform = _parent->getTransform() * _localTransform;
                _dirtyTransform = true; // in case only the parent was dirty
            }
            else if (_dirtyTransform)
            {
                _combinedTransform = _parent->getTransform() * _localTransform;
            }
        }
    }
        
}