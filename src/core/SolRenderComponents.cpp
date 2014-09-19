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

#include "SolRenderComponents.h"

namespace sol
{
    
    unsigned int gCurrentAttribs = 0;
    
    void useVertexAttribs(unsigned int attribs)
    {
        if (gCurrentAttribs != attribs)
        {
            if (testbit<PositionAttribFlag>(attribs) && !testbit<PositionAttribFlag>(gCurrentAttribs))
            {
                glEnableVertexAttribArray(kPositionAttribLocation);
            }
            else if (!testbit<PositionAttribFlag>(attribs) && testbit<PositionAttribFlag>(gCurrentAttribs))
            {
                glDisableVertexAttribArray(kPositionAttribLocation);
            }
            
            if (testbit<TextureCoordAttribFlag>(attribs) && !testbit<TextureCoordAttribFlag>(gCurrentAttribs))
            {
                glEnableVertexAttribArray(kTextureCoordAttribLocation);
            }
            else if (!testbit<TextureCoordAttribFlag>(attribs) && testbit<TextureCoordAttribFlag>(gCurrentAttribs))
            {
                glDisableVertexAttribArray(kTextureCoordAttribLocation);
            }
            
            if (testbit<ColorAttribFlag>(attribs) && !testbit<ColorAttribFlag>(gCurrentAttribs))
            {
                glEnableVertexAttribArray(kColorAttribLocation);
            }
            else if (!testbit<ColorAttribFlag>(attribs) && testbit<ColorAttribFlag>(gCurrentAttribs))
            {
                glDisableVertexAttribArray(kColorAttribLocation);
            }
            
            if (testbit<ParticleAttribsFlag>(attribs) && !testbit<ParticleAttribsFlag>(gCurrentAttribs))
            {
                glEnableVertexAttribArray(kParticleInterpolationAttribLocation);
                glEnableVertexAttribArray(kParticleStartColorAttribLocation);
                glEnableVertexAttribArray(kParticleEndColorAttribLocation);
                glEnableVertexAttribArray(kParticleStartSizeAttribLocation);
                glEnableVertexAttribArray(kParticleEndSizeAttribLocation);
            }
            else if (!testbit<ParticleAttribsFlag>(attribs) && testbit<ParticleAttribsFlag>(gCurrentAttribs))
            {
                glDisableVertexAttribArray(kParticleInterpolationAttribLocation);
                glDisableVertexAttribArray(kParticleStartColorAttribLocation);
                glDisableVertexAttribArray(kParticleEndColorAttribLocation);
                glDisableVertexAttribArray(kParticleStartSizeAttribLocation);
                glDisableVertexAttribArray(kParticleEndSizeAttribLocation);
            }
            
            gCurrentAttribs = attribs;
        }
    }
    
    void IndexArray::alloc(unsigned int count)
    {
        clear();
        _buffer.reserve(count);
        
        for (int i = 0; i < count; i++) _buffer.emplace_back(0);
    }
    
    void IndexArray::useVBO()
    {
        if (!_vbo)
        {
            _vbo = new VBO(GL_ELEMENT_ARRAY_BUFFER);
            _dirty = true;
        }
    }
    
    bool IndexArray::submit()
    {
        if (_buffer.empty() && _vbo == nullptr) return false;
        
        if (_vbo)
        {
            _vbo->bind();
            
            if (_dirty && !_buffer.empty())
            {
                _vbo->data(_buffer.size() * sizeof(unsigned short), _buffer.data(), GL_STATIC_DRAW);
            }
        }
        else VBO::unbind(GL_ELEMENT_ARRAY_BUFFER);
        
        setDirty(false);
        
        return true;
    }
    
}