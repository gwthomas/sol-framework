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

#ifndef SOL_SPRITEBATCH_H
#define SOL_SPRITEBATCH_H

#include <vector>
#include "SolRenderable.h"
#include "SolRenderComponents.h"

namespace sol
{
    
    class Sprite;
    class TextureAtlas;
    
    class SpriteBatch : public RenderObject
    {        
    public:
        SpriteBatch(const std::string& filename, bool isAtlas = false);
#if SOL_USE_XML
        SpriteBatch(TextureAtlas& atlas);
#endif
        SpriteBatch(Texture& texture);
        ~SpriteBatch();
        
#if SOL_USE_XML
        TextureAtlas* getAtlas() const { return _atlas; }
#endif
        
        Sprite& create();
        void destroy(Sprite& sprite);
        
        void useBufferObjects(bool positions = true, bool textureCoords = true, bool indices = true);
        
        void render() override;
        
    private:
        VertexPositionArray _positions;
        VertexTextureCoordArray _textureCoords;
        IndexArray _indices;
        
        std::vector<Sprite*> _sprites;
        bool _sizeChanged = false;
        
#if SOL_USE_XML
        TextureAtlas* _atlas = nullptr;
#endif
        
        void copyVertices();
    };

}

#endif