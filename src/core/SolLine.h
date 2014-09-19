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

#ifndef SOL_LINE_H
#define SOL_LINE_H

#include "SolRenderComponents.h"
#include "SolRenderObject.h"

namespace sol
{
    
    class Line : public RenderObject
    {
    public:
        Line();
        
        const Vec2f& getStart() const { return _positions[0]; }
        const Vec2f& getEnd() const { return _positions[1]; }
        float getWidth() const { return _width; }
        
        void setStart(const Vec2f& start) { _positions[0] = start; }
        void setEnd(const Vec2f& end) { _positions[1] = end; }
        void setWidth(float width) { _width = width; }
        
        void render() override;
        
    private:
        VertexPositionArray _positions;
        float _width;
    };
    
}

#endif