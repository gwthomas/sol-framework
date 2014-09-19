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

#include "SolAABB.h"
#include "SolImage.h"
#include "SolProgram.h"
#include "SolResourceManager.h"
#include "SolSprite.h"
#include "SolSpriteBatch.h"
#include "SolTextureAtlas.h"
#include "SolUtil.h"

namespace sol
{
    
    using std::string;
    
    Sprite::Sprite(Texture& texture) :
        Sprite()
    {        
        setTexture(&texture);
        defaultRegion();
    }
    
    Sprite::Sprite(const string& imageName) :
        Sprite(ResourceManager::instance().getResource<Image>(imageName)->getTexture())
    {}
    
    Sprite::Sprite(SpriteBatch& batch)
    {
        setTexture(batch.getTexture());
        _textureCoords.alloc(4);
        defaultRegion();
        
        _batch = &batch;
        _batched = true;
    }
    
    Sprite::Sprite()
    {
        program = ResourceManager::instance().getResource<Program>("default_p_tc");
        _attribs |= TextureCoordAttribFlag;
        _textureCoords.alloc(4);
    }
    
    void Sprite::defaultRegion()
    {
        _texture->getDefaultTextureCoords(_textureCoords.getData());
        setSize(Vec2f(_texture->getSizeInPoints().x, _texture->getSizeInPoints().y));
        
        if (_batched) setDirty();
    }
    
    void Sprite::textureRegion(const AABBi& region)
    {
        _texture->getTextureCoordsForRegion(region, _textureCoords.getData());
        setSize(Vec2f(region.width(), region.height()));
        
        if (_batched) setDirty();
    }

#if SOL_USE_XML
    void Sprite::textureAtlasRegion(const string& name)
    {
        assert(_batch); // the sprite must have been created from a batch
        TextureAtlas* atlas = _batch->getAtlas();
        assert(atlas); //  the batch must have a texture atlas of course
        textureRegion(atlas->getRegionNamed(name));
    }
#endif
    
    void Sprite::useBufferObjects(bool positions, bool textureCoords, bool indices)
    {
        if (positions)     _positions.useVBO();
        if (textureCoords) _textureCoords.useVBO();
        if (indices)       _indices.useVBO();
    }
    
    void Sprite::render()
    {
        if (!_batched && _texture)
        {
            assert(_textureCoords.submit());
            Quad::render();
        }
    }
    
}