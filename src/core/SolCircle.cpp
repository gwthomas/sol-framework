/*
 *
 * Copyright (c) 2012 Garrett Thomas
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the use o this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin o this software must not be misrepresented; you must not claim that you wrote the original software.
 *    I you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */

#include "SolCircle.h"
#include "SolNative.h"
#include "SolProgram.h"

namespace sol
{
    
    Circle::Circle(float radius)
    {
        program = ResourceManager::instance().getResource<Program>("default_p|circle");
        _centerUniformLocation = program->getUniformLocation("uCenter");
        _radiusUniformLocation = program->getUniformLocation("uRadius");
        _edgeWidthUniformLocation = program->getUniformLocation("uEdgeWidth");
        _fillColorUniformLocation = program->getUniformLocation("uFillColor");
        _edgeColorUniformLocation = program->getUniformLocation("uEdgeColor");
        assert(_centerUniformLocation != -1);
        assert(_radiusUniformLocation != -1);
        assert(_edgeWidthUniformLocation != -1);
        assert(_fillColorUniformLocation != -1);
        assert(_edgeColorUniformLocation != -1);
        
        _attribs = PositionAttribFlag;
        _positions.alloc(4);
        setRadius(radius);
    }
    
    void Circle::update()
    {
        if (_needsCalc)
        {
            _positions[0] = Vec2f(-_radius, _radius);
            _positions[1] = Vec2f(_radius, _radius);
            _positions[2] = Vec2f(-_radius, -_radius);
            _positions[3] = Vec2f(_radius, -_radius);
            
            _needsCalc = false;
        }
    }
    
    void Circle::render()
    {
        bool retina = Manager::instance().isRetinaDisplay();
        Vec2f absolute = getAbsolutePosition();
        absolute = native::worldToGLPixels(absolute);
        
        prerender();
        assert(_positions.submit());
        
        glUniform2f(_centerUniformLocation, absolute.x, absolute.y);
        glUniform1f(_radiusUniformLocation, retina ? _radius * 2.0 : _radius);
        glUniform1f(_edgeWidthUniformLocation, retina ? edgeWidth * 2.0 : edgeWidth);
        glUniform4f(_fillColorUniformLocation, fill.r, fill.g, fill.b, fill.a);
        glUniform4f(_edgeColorUniformLocation, edge.r, edge.g, edge.b, edge.a);
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, _positions.getCount());
    }
    
}