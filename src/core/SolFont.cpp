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

#include "SolFont.h"
#include "SolFileBuffer.h"
#include "SolGL.h"
#include "SolManager.h"
#include "SolNative.h"
#include "SolTexture.h"

namespace sol
{
    
    using std::string;
    
    Font::Font(const string& filename) :
        Resource(filename)
    {}
    
    Font::~Font()
    {
        SOL_SAFE_DELETE(_texture);
    }
    
    float Font::getCharWidth(int c) const
    {
        float width = _characters[c - SOL_FONT_FIRST_CHAR].xadvance;
        return Manager::instance().isRetinaDisplay() ? width * 0.5 : width;
    }
    
    void Font::vertexDataForCharacter(int c, const Vec2f& penPos, Vec2f* positions, Vec2f* textureCoords)
    {
        bool retina = Manager::instance().isRetinaDisplay();
        stbtt_aligned_quad quad;
        stbtt_bakedchar& baked = _characters[c - SOL_FONT_FIRST_CHAR];
        Vec2f off(baked.xoff, baked.yoff);
        if (retina) off *= 0.5f;
        Vec2f bottomLeft(penPos.x + off.x, penPos.y - off.y);

        quad.x0 = bottomLeft.x;
        quad.y0 = bottomLeft.y;
        quad.x1 = bottomLeft.x + (retina ? (baked.x1 - baked.x0) * 0.5 : (baked.x1 - baked.x0));
        quad.y1 = bottomLeft.y + (retina ? (baked.y0 - baked.y1) * 0.5 : (baked.y0 - baked.y1));
        
        quad.s0 = baked.x0 / (float)_texture->getSizeInPixels().x;
        quad.t0 = baked.y0 / (float)_texture->getSizeInPixels().x;
        quad.s1 = baked.x1 / (float)_texture->getSizeInPixels().y;
        quad.t1 = baked.y1 / (float)_texture->getSizeInPixels().y;
        
        positions[0] = Vec2f(quad.x1, quad.y0);
        positions[1] = Vec2f(quad.x0, quad.y0);
        positions[2] = Vec2f(quad.x1, quad.y1);
        positions[3] = Vec2f(quad.x0, quad.y1);
        
        textureCoords[0] = Vec2f(quad.s1, quad.t0);
        textureCoords[1] = Vec2f(quad.s0, quad.t0);
        textureCoords[2] = Vec2f(quad.s1, quad.t1);
        textureCoords[3] = Vec2f(quad.s0, quad.t1);
    }
    
    bool Font::load()
    {
        FileBuffer<unsigned char> f;
        
        size_t atIndex = _filename.find_last_of('@');
        if (atIndex == string::npos) return false;
        string filePart = _filename.substr(0, atIndex);
        string sizePart = _filename.substr(atIndex + 1);
        _size = atoi(sizePart.c_str());
        
        if (!f.open(Manager::instance().getResourcePath() + filePart, "rb"))
        {
            SOL_PRINT("Failed to load font " << _filename);
            return false;
        }
        
        bool retina = Manager::instance().isRetinaDisplay();
        unsigned int width = retina ? SOL_FONT_TEXTURE_WIDTH * 2 : SOL_FONT_TEXTURE_WIDTH;
        unsigned int height = retina ? SOL_FONT_TEXTURE_HEIGHT * 2 : SOL_FONT_TEXTURE_HEIGHT;
        
        unsigned char* pixels = new unsigned char[width * height];
        unsigned char* gldata = new unsigned char[2 * width * height];
        
        stbtt_BakeFontBitmap(f.getData(), 0, retina ? _size * 2.0 : _size, pixels, width, height, SOL_FONT_FIRST_CHAR, SOL_FONT_LAST_CHAR - SOL_FONT_FIRST_CHAR, _characters);
        
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int index = 2 * (y * width + x);
                
                gldata[index] = 255;
                gldata[index + 1] = pixels[y * width + x];
            }
        }
        
        _texture = new Texture();
        _texture->image2D(gldata, GL_LUMINANCE_ALPHA, Vec2i(width, height), retina);
        
        delete [] pixels;
        delete [] gldata;
        
        determineVerticalOffset();
        
        return true;
    }
    
    void Font::determineVerticalOffset()
    {
        Vec2f pos[4], tex[4];
        vertexDataForCharacter('a', Vec2f(), pos, tex);
        _verticalOffset = -std::abs(pos[0].y-pos[3].y)*0.5;
    }
    
}