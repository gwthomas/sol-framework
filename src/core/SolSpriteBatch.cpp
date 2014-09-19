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

#include "SolImage.h"
#include "SolProgram.h"
#include "SolSprite.h"
#include "SolSpriteBatch.h"
#include "SolTextureAtlas.h"

namespace sol
{
    
    using std::string;
    
    SpriteBatch::SpriteBatch(const string& name, bool isAtlas)
    {
        if (isAtlas)
        {
#if SOL_USE_XML
            _atlas = ResourceManager::instance().getResource<TextureAtlas>(name);
            assert(_atlas);
            _texture = &_atlas->getTexture();
#else
            assert(false && "Must have XML enabled to use atlases");
#endif
        }
        else
        {
            Image* image = ResourceManager::instance().getResource<Image>(name);
            assert(image);
            _texture = &image->getTexture();
        }
        
        program = ResourceManager::instance().getResource<Program>("default_p_tc");
        _attribs |= (PositionAttribFlag | TextureCoordAttribFlag);
    }
    
#if SOL_USE_XML
    SpriteBatch::SpriteBatch(TextureAtlas& atlas) :
        SpriteBatch(atlas.getTexture())
    {
        _atlas = &atlas;
    }
#endif
    
    SpriteBatch::SpriteBatch(Texture& texture)
    {
        _texture = &texture;
        program = ResourceManager::instance().getResource<Program>("default_p_tc");
        _attribs |= (PositionAttribFlag | TextureCoordAttribFlag);
    }
    
    SpriteBatch::~SpriteBatch()
    {
        for (Sprite* sprite : _sprites) delete sprite;
        _sprites.clear();
    }
    
    Sprite& SpriteBatch::create()
    {
        Sprite* ret = new Sprite(*this);
        ret->autorender = false;
        _sprites.push_back(ret);
        _sizeChanged = true;
        return *ret;
    }
    
    void SpriteBatch::destroy(Sprite& sprite)
    {
        for (int i = 0; i < _sprites.size(); i++)
        {
            if (_sprites[i] == &sprite)
            {
                delete _sprites[i];
                _sprites.erase(_sprites.begin() + i);
                _sizeChanged = true;
                return;
            }
        }
    }
    
    void SpriteBatch::useBufferObjects(bool positions, bool textureCoords, bool indices)
    {
        if (positions)     _positions.useVBO();        
        if (textureCoords) _textureCoords.useVBO();        
        if (indices)       _indices.useVBO();
    }
    
    void SpriteBatch::copyVertices()
    {
        bool copyAll = false;
        
        if (_sizeChanged)
        {
            unsigned int size = _sprites.size();
            _positions.alloc(size * 4);
            _textureCoords.alloc(size * 4);
            _indices.alloc(size * 6);
            _sizeChanged = false;
            copyAll = true;
        }
        
        for (int i = 0; i < _sprites.size(); i++)
        {
            Sprite* sprite = _sprites[i];
            
            if (copyAll || sprite->isDirty())
            {
                const VertexPositionArray& positions = sprite->getPositions();
                const VertexTextureCoordArray& textureCoords = sprite->getTextureCoords();
                Matrix transform = sprite->getTransform();
                
                for (int j = 0; j < 4; j++)
                {
                    _positions[i * 4 + j] = transform * positions[j];
                    _textureCoords[i * 4 + j] = textureCoords[j];
                }
                
                _indices[i * 6] = i * 4;
                _indices[i * 6 + 1] = i * 4 + 1;
                _indices[i * 6 + 2] = i * 4 + 2;
                _indices[i * 6 + 3] = i * 4 + 2;
                _indices[i * 6 + 4] = i * 4 + 1;
                _indices[i * 6 + 5] = i * 4 + 3;
                
                _positions.setDirty();
                _textureCoords.setDirty();
                sprite->setDirty(false);
            }
        }
    }
    
    void SpriteBatch::render()
    {
        copyVertices();
        prerender();
        assert(_positions.submit());
        assert(_textureCoords.submit());
        assert(_indices.submit());
        glDrawElements(GL_TRIANGLES, _indices.getCount(), GL_UNSIGNED_SHORT, _indices.getPointer());
    }
    
}