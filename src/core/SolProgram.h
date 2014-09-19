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

#ifndef SOL_PROGRAM_H
#define SOL_PROGRAM_H

#include "SolColor.h"
#include "SolShader.h"
#include "SolResourceManager.h"

namespace sol
{
        
    class Program : public Resource
    {
        friend class ResourceManager;
        
    public:
        unsigned int getHandle() { return _handle; }
        bool isValid() { return _valid; }
        
        VertexShader& getVertexShader() { return *_vertex; }
        FragmentShader& getFragmentShader() { return *_fragment; }
        
        int getTransformUniformLocation() const { return _transformUniformLocation; }
        int getTintUniformLocation() const { return _tintUniformLocation; }
                
        // for getting a generic attribute from the program. use the predefined values whenever you can
        int getAttribLocation(const std::string& name);
        
        // for getting a generic uniform from the program. use the cached values whenever you can
        int getUniformLocation(const std::string& name);
        
        // set this program as the active one
        void use();
        
        void setTint(const Colorf& tint);
        
    private:
        unsigned int _handle = 0;
        
        bool _valid = false;
        
        VertexShader* _vertex = nullptr;
        FragmentShader* _fragment = nullptr;
                        
        int _transformUniformLocation = -1;
        int _tintUniformLocation = -1;
        Colorf _currentTint; // optimization: cache the tint and change it only when necessary (it's usually white)
        
        Program(const std::string& name) : Resource(name), _handle(glCreateProgram()) {}
        ~Program() { glDeleteProgram(_handle); }
        
        bool load() override;
    };
    
}

#endif