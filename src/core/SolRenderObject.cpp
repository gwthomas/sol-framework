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

#include "SolProgram.h"
#include "SolRenderObject.h"
#include "SolRenderComponents.h"
#include "SolScene.h"
#include "SolTexture.h"

namespace sol
{
    
    void RenderObject::setTexture(Texture* texture)
    {
        _texture = texture;
        
        if (texture && program)
        {
            int texLoc = program->getUniformLocation("sTexture");
            
            if (texLoc != -1)
            {
                program->use();
                glUniform1i(texLoc, 0);
            }
        }
    }
    
    void RenderObject::prerender()
    {
        assert(program);
        
        if (_texture) _texture->bind();
        else Texture::unbind();
        
        program->use();
        program->setTint(tint);
        useVertexAttribs(_attribs);
        
        Matrix transform = Manager::instance().getWorldTransform() * _combinedTransform;
        glUniformMatrix3fv(program->getTransformUniformLocation(), 1, GL_FALSE, &transform[0]);
    }
    
}