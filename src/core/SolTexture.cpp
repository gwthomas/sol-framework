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

#include "SolConfig.h"
#include "SolRenderer.h"
#include "SolTexture.h"

namespace sol
{
    
    unsigned int gActiveTexture = 0;
    Texture* gCurrentTexture[SOL_MAX_TEXTURE_UNITS] = { nullptr };
    
    void Texture::getDefaultTextureCoords(Vec2f* textureCoords) const
    {
        getTextureCoordsForRegion(AABBi(Vec2i(), getSizeInPoints()), textureCoords);
    }
    
    void Texture::getTextureCoordsForRegion(const AABBi& region, Vec2f* textureCoords) const
    {
        // if the image is retina, the coords in pixels are double the coords in points
        AABBi bounds = _retina ? region * 2 : region;
        float left = float(bounds.left) / _size.x;
        float right = float(bounds.right) / _size.x;
        float bottom = float(bounds.bottom) / _size.y;
        float top = float(bounds.top) / _size.y;
        
        textureCoords[0] = Vec2f(left, top);
        textureCoords[1] = Vec2f(right, top);
        textureCoords[2] = Vec2f(left, bottom);
        textureCoords[3] = Vec2f(right, bottom);
    }
    
    bool Texture::image2D(unsigned char* data, unsigned int format, Vec2i size, bool retina)
    {
        bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, format, size.x, size.y, 0, format, GL_UNSIGNED_BYTE, data);
        
        _format = format;
        _size = size;
        _retina = retina;
        
        return true;
    }
    
#define TEX_CASE(n) case n: glActiveTexture(GL_TEXTURE##n); break;
    
    void Texture::bind(unsigned int index)
    {        
        if (gCurrentTexture[index] != this)
        {
            if (gActiveTexture != index)
            {
                switch (index)
                {
                    TEX_CASE(0);
                    TEX_CASE(1);
                    TEX_CASE(2);
                    TEX_CASE(3);
                    TEX_CASE(4);
                    TEX_CASE(5);
                    TEX_CASE(6);
                    TEX_CASE(7);
                        
                    default:
                        SOL_ERROR("Invalid texture index!");
                        return;
                }
                
                gActiveTexture = index;
            }
            
            glBindTexture(GL_TEXTURE_2D, _handle);
            gCurrentTexture[index] = this;
        }
    }
    
    void Texture::unbind(unsigned int index)
    {
        if (gCurrentTexture[index] != nullptr)
        {
            if (gActiveTexture != index)
            {
                switch (index)
                {
                    TEX_CASE(0);
                    TEX_CASE(1);
                    TEX_CASE(2);
                    TEX_CASE(3);
                    TEX_CASE(4);
                    TEX_CASE(5);
                    TEX_CASE(6);
                    TEX_CASE(7);
                        
                    default:
                        SOL_ERROR("Invalid texture index!");
                        return;
                }
                
                gActiveTexture = index;
            }
            
            glBindTexture(GL_TEXTURE_2D, 0);
            gCurrentTexture[index] = nullptr;
        }
    }
    
}