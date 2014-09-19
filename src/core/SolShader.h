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

#ifndef SOL_SHADER_H
#define SOL_SHADER_H

#include "SolFileBuffer.h"
#include "SolGL.h"
#include "SolManager.h"
#include "SolResourceManager.h"

namespace sol
{
    
    template<unsigned int T>
    class Shader : public Resource
    {
        friend class ResourceManager;
        
    public:
        unsigned int getHandle() const { return _handle; }
        
    private:
        unsigned int _handle = 0;
        
        Shader(const std::string& filename);
        ~Shader() { glDeleteShader(_handle); }
        
        bool load() override;
    };
    
    typedef Shader<GL_VERTEX_SHADER> VertexShader;
    typedef Shader<GL_FRAGMENT_SHADER> FragmentShader;
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
        
    template<unsigned int T>
    Shader<T>::Shader(const std::string& filename) :
        Resource(filename)
    {
        assert(T == GL_VERTEX_SHADER || T == GL_FRAGMENT_SHADER);
        _handle = glCreateShader(T);
    }
    
    template<unsigned int T>
    bool Shader<T>::load()
    {
        FileBuffer<char> f;
        
        if (!f.openText(Manager::instance().getResourcePath() + _filename, "r"))
        {
            return false;
        }
        
        const char* source = f.getData();
        int len = -1;
        glShaderSource(_handle, 1, &source, &len);
        glCompileShader(_handle);
        
        int status;
        glGetShaderiv(_handle, GL_COMPILE_STATUS, &status);
            
        if (status == GL_FALSE)
        {
            // compile failed. find out what went wrong
            char message[100];
            glGetShaderInfoLog(_handle, sizeof(message), nullptr, message);
            SOL_ERROR(message);
            return false;
        }
            
        return true;
    }
    
}

#endif