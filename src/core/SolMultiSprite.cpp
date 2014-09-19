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

#include "SolMultiSprite.h"
#include "SolProgram.h"
#include "SolTexture.h"

namespace sol
{
    
    void MultiSprite::setMultiTexture(Texture* texture)
    {
        _multiTexture = texture;
        
        if (texture && program)
        {
            int multiLoc = program->getUniformLocation("sMultiTexture");
            
            if (multiLoc != -1)
            {
                program->use();
                glUniform1i(multiLoc, 1);
            }
        }
    }
    
    void MultiSprite::render()
    {
        if (_multiTexture) _multiTexture->bind(1);
        else Texture::unbind(1);
        
        Sprite::render();
    }
    
}