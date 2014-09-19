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

#include "SolQuad.h"

namespace sol
{
    
    Quad::Quad()
    {
        _attribs |= PositionAttribFlag;
        _positions.alloc(4);
        _indices.alloc(6);
        
        _indices[0] = 0;
        _indices[1] = 1;
        _indices[2] = 2;
        _indices[3] = 2;
        _indices[4] = 1;
        _indices[5] = 3;
    }
    
    void Quad::setSize(const Vec2f& size)
    {
        _size = size;
        calcVertices();
    }
    
    void Quad::calcVertices()
    {
        float halfw = _size.x * 0.5, halfh = _size.y * 0.5;
        
        _positions[0] = Vec2f(-halfw, halfh);
        _positions[1] = Vec2f(halfw, halfh);
        _positions[2] = Vec2f(-halfw, -halfh);
        _positions[3] = Vec2f(halfw, -halfh);
    }
    
    void Quad::update()
    {
        if (_dirtyTransform && _batched) setDirty();
    }
    
    void Quad::render()
    {
        if (!_batched)
        {
            prerender();
            _positions.submit();
            _indices.submit();
            glDrawElements(GL_TRIANGLES, _indices.getCount(), GL_UNSIGNED_SHORT, _indices.getPointer());
        }
    }
    
}