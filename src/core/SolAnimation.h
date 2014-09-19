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

#ifndef SOL_ANIMATION_H
#define SOL_ANIMATION_H

#include <vector>
#include "SolAABB.h"
#include "SolImage.h"

namespace sol
{
    
    class TextureAtlas;
    
    class Animation : public Noncopyable
    {
    public:
#if SOL_USE_XML
        Animation(TextureAtlas& atlas);
#endif
        Animation(Texture& texture);
        
        Texture& getTexture() { return _texture; }
        unsigned int getFrameCount() const { return _frames.size(); }
        const AABBi& getFrame(unsigned int index) { return _frames[index]; }
        
        void addFrame(const AABBi& frame) { _frames.push_back(frame); }
#if SOL_USE_XML
        bool addNamedFrame(const std::string& name);
#endif
        
    private:
#if SOL_USE_XML
        TextureAtlas* _atlas = nullptr;
#endif
        
        Texture& _texture;
        
        std::vector<AABBi> _frames;
    };
    
}

#endif