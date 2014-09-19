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

#ifndef SOL_FONT_H
#define SOL_FONT_H

#include "SolAABB.h"
#include "SolResourceManager.h"
#include "stb_truetype.h"

namespace sol
{
    
    class BitmapChar;
    class Texture;
    
    class Font : public Resource
    {
        friend class ResourceManager;
        
    public:                
        Texture& getTexture() const { return *_texture; }
        unsigned int getSize() const { return _size; }
        float getVerticalOffset() const { return _verticalOffset; }
        float getCharWidth(int c) const;
        
        void vertexDataForCharacter(int c, const Vec2f& penPos, Vec2f* positions, Vec2f* textureCoords);

    private:   
        unsigned int _size; // in pixels
        float _verticalOffset;
        
        Texture* _texture = nullptr; // a bitmap containing all the characters
        
        stbtt_bakedchar _characters[SOL_FONT_LAST_CHAR - SOL_FONT_FIRST_CHAR];
        
        // called by friend ResourceManager
        Font(const std::string& filename);
        ~Font();
        
        bool load() override;
        
        void determineVerticalOffset();
    };
        
}

#endif