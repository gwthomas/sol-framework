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

#ifndef SOL_QUAD_H
#define SOL_QUAD_H

#include "SolAABB.h"
#include "SolRenderComponents.h"
#include "SolRenderObject.h"

namespace sol
{
    
    class Quad : public RenderObject
    {
    public:
        Quad();
        virtual ~Quad() = default;
        
        const Vec2f& getSize() const { return _size; }
        AABBf getBounds() { return AABBf(SceneNode::getAbsolutePosition(), _size.x*_scale.x, _size.y*_scale.y); }
        bool isDirty() const { return _dirty; }
        
        virtual void setSize(const Vec2f& size);
        void setSize(float width, float height) { setSize(Vec2f(width, height)); }
        void setDirty(bool dirty = true) { _dirty = dirty; }
        
        void update() override;
        virtual void render() override;
        
    protected:
        Vec2f _size;
        
        VertexPositionArray _positions;
        IndexArray _indices;
                
        // internal use
        void calcVertices();
        
        bool _batched = false;
        bool _dirty = false;
                
        const VertexPositionArray& getPositions() const { return _positions; }
    };

}

#endif