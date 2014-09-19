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

#ifndef SOL_TEXTURE_H
#define SOL_TEXTURE_H

#include "SolAABB.h"
#include "SolGL.h"

namespace sol
{
    
    class Texture : public Noncopyable
    {
        friend class Renderer;
        
    public:
        Texture() { glGenTextures(1, &_handle); }
        ~Texture() { glDeleteTextures(1, &_handle); }
        
        unsigned int getHandle() const { return _handle; }
        Vec2i getSizeInPixels() const { return _size; }
        Vec2i getSizeInPoints() const { return _retina ? _size / 2 : _size; }
        
        void getDefaultTextureCoords(Vec2f* textureCoords) const;
        void getTextureCoordsForRegion(const AABBi& region, Vec2f* textureCoords) const;
        
        bool image2D(unsigned char* data, unsigned int format, Vec2i size, bool retina);
        
        void bind(unsigned int index = 0);
        static void unbind(unsigned int index = 0);
        
    private:
        unsigned int _handle;
        
        Vec2i _size; // in pixels
        unsigned int _format;
        bool _retina;
    };
    
}

#endif