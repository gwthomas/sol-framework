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

#include "SolCanvas.h"
#include "SolImage.h"
#include "SolProgram.h"

namespace sol
{
    
    Canvas::Canvas(const Vec2i& dimensions, float pixelSize) :
        _dimensions(dimensions),
        _pixelSize(pixelSize)
    {
        int pixelCount = dimensions.x * dimensions.y;
        
        program = ResourceManager::instance().getResource<Program>("default_p_c");
        _attribs = PositionAttribFlag | ColorAttribFlag;
        _positions.alloc(4 * pixelCount);
        _colors.alloc(4 * pixelCount);
        _indices.alloc(6 * pixelCount);
        _pixels = new Colorc[pixelCount];
        calcVertices();
        clear(blackColorc());
    }
    
    Canvas::~Canvas()
    {
        SOL_SAFE_DELETE_ARRAY(_pixels);
    }
    
    void Canvas::clear(const Colorc& color)
    {
        for (int i = 0; i < _dimensions.x * _dimensions.y; i++)
        {
            _pixels[i] = color;
        }
        
        _dirty = true;
    }
    
    void Canvas::blit(const Image& img, const Vec2i& loc)
    {
        const Colorc* imgPixels = img.getPixels();
        Vec2i imgSize = img.getSize();
        
        for (int offy = 0; offy < imgSize.y; offy++)
        {
            for (int offx = 0; offx < imgSize.x; offx++)
            {
                int x = loc.x + offx;
                int y = loc.y + offy;
                
                if (0 <= x && x < _dimensions.x && 0 <= y && y < _dimensions.y)
                {
                    Colorc pixel = imgPixels[offy * imgSize.x + offx];
                    
                    if (pixel.a > 0)
                    {
                        pixel.a = 255; // all or nothing
                        _pixels[y * _dimensions.x + x] = pixel;
                    }
                }
            }
        }
        
        _dirty = true;
    }
    
    void Canvas::update()
    {
        if (_dirty)
        {
            updateColors();
            _dirty = false;
        }
    }
    
    void Canvas::render()
    {
        prerender();
        _positions.submit();
        _colors.submit();
        _indices.submit();
        glDrawElements(GL_TRIANGLES, _indices.getCount(), GL_UNSIGNED_SHORT, _indices.getPointer());
    }
    
    void Canvas::calcVertices()
    {
        Vec2f sizeInScreenPoints = _dimensions.cast<float>() * _pixelSize;
        Vec2f lowerLeft = sizeInScreenPoints * -0.5f;
        
        for (int y = 0; y < _dimensions.y; y++)
        {
            for (int x = 0; x < _dimensions.x; x++)
            {
                int index = y * _dimensions.x + x;
                
                _positions[index * 4] = lowerLeft + Vec2f(x, y + 1) * _pixelSize;
                _positions[index * 4 + 1] = lowerLeft + Vec2f(x + 1, y + 1) * _pixelSize;
                _positions[index * 4 + 2] = lowerLeft + Vec2f(x, y) * _pixelSize;
                _positions[index * 4 + 3] = lowerLeft + Vec2f(x + 1, y) * _pixelSize;
                
                _indices[index * 6] = index * 4;
                _indices[index * 6 + 1] = index * 4 + 1;
                _indices[index * 6 + 2] = index * 4 + 2;
                _indices[index * 6 + 3] = index * 4 + 2;
                _indices[index * 6 + 4] = index * 4 + 1;
                _indices[index * 6 + 5] = index * 4 + 3;
            }
        }
    }
    
    void Canvas::updateColors()
    {
        for (int y = 0; y < _dimensions.y; y++)
        {
            for (int x = 0; x < _dimensions.x; x++)
            {
                int index = y * _dimensions.x + x;
                
                _colors[index * 4] =
                _colors[index * 4 + 1] =
                _colors[index * 4 + 2] =
                _colors[index * 4 + 3] = _pixels[index];
            }
        }
    }
    
}