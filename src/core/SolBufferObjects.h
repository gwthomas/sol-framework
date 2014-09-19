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

#ifndef SOL_BUFFEROBJECTS_H
#define SOL_BUFFEROBJECTS_H

#include "SolGL.h"
#include "SolColor.h"
#include "SolUtil.h"
#include "SolVec.h"

namespace sol
{
    
    class Texture;
    
    class VBO : public Noncopyable
    {
    public:
        VBO(unsigned int target);
        ~VBO() { glDeleteBuffers(1, &_handle); }
        
        unsigned int getHandle() const { return _handle; }
        
        void data(size_t size, const void* data, unsigned int usage);
        void subdata(int offset, size_t size, const void* data);
        
        void bind();
        static void unbind(unsigned int target);
        
    private:
        unsigned int _target;
        unsigned int _handle;
    };
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    class Renderbuffer : public Noncopyable
    {
    public:
        Renderbuffer() { glGenRenderbuffers(1, &_handle); }
        ~Renderbuffer() { glDeleteRenderbuffers(1, &_handle); }
        
        unsigned int getHandle() const { return _handle; }
        
        void storage(unsigned int format, Vec2i size);
        
        void bind();
        
    private:
        unsigned int _handle;
    };
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    class Framebuffer : public Noncopyable
    {
    public:
        Framebuffer() { glGenFramebuffers(1, &_handle); }
        ~Framebuffer() { glDeleteFramebuffers(1, &_handle); }
        
        const Colorf& getClearColor() const { return _clearColor; }
        bool hasColorBuffer() const { return _color; }
        bool hasDepthBuffer() const { return _depth; }
        
        bool isComplete();
        
        void setClearColor(const Colorf& color) { _clearColor = color; }
        void clear();
        
        void attachColorBuffer(const Renderbuffer& rb);
        void attachDepthBuffer(const Renderbuffer& rb);
        void attachColorBuffer(const Texture& tex, int level = 0);
        void attachDepthBuffer(const Texture& tex, int level = 0);
        
        void bind();
        
    private:
        unsigned int _handle;
        
        Colorf _clearColor;
        
        bool _color = false;
        bool _depth = false;
    };
    
    Renderbuffer& getCurrentRenderbuffer();
    Framebuffer& getCurrentFramebuffer();
    
}

#endif