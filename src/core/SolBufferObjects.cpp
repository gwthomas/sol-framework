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

#include "SolBufferObjects.h"
#include "SolTexture.h"

namespace sol
{
    
    VBO* gCurrentArrayBuffer = nullptr;
    VBO* gCurrentElementArrayBuffer = nullptr;
    Renderbuffer* gCurrentRenderbuffer = nullptr;
    Framebuffer* gCurrentFramebuffer = nullptr;
    
    Renderbuffer& getCurrentRenderbuffer() { return *gCurrentRenderbuffer; }
    Framebuffer& getCurrentFramebuffer() { return *gCurrentFramebuffer; }
    
    VBO::VBO(unsigned int target) :
        _target(target)
    {
        assert(target == GL_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER);
        glGenBuffers(1, &_handle);
    }
    
    void VBO::data(size_t size, const void* data, unsigned int usage)
    {
        bind();
        glBufferData(_target, size, data, usage);
    }
        
    void VBO::subdata(int offset, size_t size, const void* data)
    {
        bind();
        glBufferSubData(_target, offset, size, data);
    }
    
    void VBO::bind()
    {
        if (_target == GL_ARRAY_BUFFER)
        {
            if (gCurrentArrayBuffer != this)
            {
                glBindBuffer(GL_ARRAY_BUFFER, _handle);
                gCurrentArrayBuffer = this;
            }
        }
        else
        {
            if (gCurrentElementArrayBuffer != this)
            {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _handle);
                gCurrentElementArrayBuffer = this;
            }
        }
    }
    
    void VBO::unbind(unsigned int target)
    {
        if (target == GL_ARRAY_BUFFER && gCurrentArrayBuffer)
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            gCurrentArrayBuffer = nullptr;
        }
        else if (target == GL_ELEMENT_ARRAY_BUFFER && gCurrentElementArrayBuffer)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            gCurrentElementArrayBuffer = nullptr;
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    void Renderbuffer::storage(unsigned int format, Vec2i size)
    {
        bind();
        glRenderbufferStorage(GL_RENDERBUFFER, format, size.x, size.y);
    }
    
    void Renderbuffer::bind()
    {
        if (gCurrentRenderbuffer != this)
        {
            glBindRenderbuffer(GL_RENDERBUFFER, _handle);
            gCurrentRenderbuffer = this;
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    bool Framebuffer::isComplete()
    {
        bind();
        return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    }
    
    void Framebuffer::clear()
    {
        bind();
        glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
        glClear((_color ? GL_COLOR_BUFFER_BIT : 0) | (_depth ? GL_DEPTH_BUFFER_BIT : 0));
    }
    
    void Framebuffer::attachColorBuffer(const Renderbuffer& rb)
    {
        bind();
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rb.getHandle());
        _color = true;
    }
    
    void Framebuffer::attachDepthBuffer(const Renderbuffer& rb)
    {
        bind();
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rb.getHandle());
        _depth = true;
    }
    
    void Framebuffer::attachColorBuffer(const Texture& tex, int level)
    {
        bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex.getHandle(), level);
        _color = true;
    }
    
    void Framebuffer::attachDepthBuffer(const Texture& tex, int level)
    {
        bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex.getHandle(), level);
        _depth = true;
    }
    
    void Framebuffer::bind()
    {
        if (gCurrentFramebuffer != this)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, _handle);
            gCurrentFramebuffer = this;
        }
    }
    
}