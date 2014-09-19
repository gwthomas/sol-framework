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

#include "SolGradient.h"
#include "SolGradientBatch.h"
#include "SolProgram.h"
#include "SolResourceManager.h"

namespace sol
{
    
    using std::string;
    
    GradientBatch::GradientBatch()
    {
        program = ResourceManager::instance().getResource<Program>("default_p_c");
        _attribs |= (PositionAttribFlag | ColorAttribFlag);
    }
    
    GradientBatch::~GradientBatch()
    {
        for (Gradient* gradient : _gradients) delete gradient;
        _gradients.clear();
    }
    
    Gradient& GradientBatch::create()
    {
        Gradient* ret = new Gradient(*this);
        ret->autorender = false;
        _gradients.push_back(ret);
        _sizeChanged = true;
        return *ret;
    }
    
    void GradientBatch::destroy(Gradient& gradient)
    {
        for (int i = 0; i < _gradients.size(); i++)
        {
            if (_gradients[i] == &gradient)
            {
                delete _gradients[i];
                _gradients.erase(_gradients.begin() + i);
                _sizeChanged = true;
                return;
            }
        }
    }
    
    void GradientBatch::useBufferObjects(bool positions, bool colors, bool indices)
    {
        if (positions) _positions.useVBO();
        if (colors)    _colors.useVBO();
        if (indices)   _indices.useVBO();
    }
    
    void GradientBatch::copyVertices()
    {
        bool copyAll = false;
        
        if (_sizeChanged)
        {
            unsigned int size = _gradients.size();
            _positions.alloc(size * 4);
            _colors.alloc(size * 4);
            _indices.alloc(size * 6);
            _sizeChanged = false;
            copyAll = true;
        }
        
        for (int i = 0; i < _gradients.size(); i++)
        {
            Gradient* gradient = _gradients[i];
            
            if (copyAll || gradient->isDirty())
            {
                const VertexPositionArray& positions = gradient->getPositions();
                const VertexColorArray& colors = gradient->getColors();
                Matrix transform = gradient->getTransform();
                
                for (int j = 0; j < 4; j++)
                {
                    _positions[i * 4 + j] = transform * positions[j];
                    _colors[i * 4 + j] = colors[j];
                }
                
                _indices[i * 6] = i * 4;
                _indices[i * 6 + 1] = i * 4 + 1;
                _indices[i * 6 + 2] = i * 4 + 2;
                _indices[i * 6 + 3] = i * 4 + 2;
                _indices[i * 6 + 4] = i * 4 + 1;
                _indices[i * 6 + 5] = i * 4 + 3;
                
                _positions.setDirty();
                _colors.setDirty();
                gradient->setDirty(false);
            }
        }
    }
    
    void GradientBatch::render()
    {        
        copyVertices();
        prerender();
        _positions.submit();
        _colors.submit();
        _indices.submit();
        glDrawElements(GL_TRIANGLES, _indices.getCount(), GL_UNSIGNED_SHORT, _indices.getPointer());
    }
    
}