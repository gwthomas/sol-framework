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

#include "SolGL.h"
#include "SolProgram.h"
#include "SolRenderComponents.h"
#include "SolResourceManager.h"
#include "SolShader.h"
#include "SolUtil.h"

namespace sol
{
    
    using std::string;
    
    Program* gCurrentProgram = nullptr;
    
    bool Program::load()
    {
        unsigned int barIndex = _filename.find_last_of('|');
        
        if (barIndex == string::npos)
        {
            _vertex = ResourceManager::instance().getResource<VertexShader>(_filename + ".vsh");
            _fragment = ResourceManager::instance().getResource<FragmentShader>(_filename + ".fsh");
        }
        else
        {
            string vertPart = _filename.substr(0, barIndex);
            string fragPart = _filename.substr(barIndex + 1);
            
            _vertex = ResourceManager::instance().getResource<VertexShader>(vertPart + ".vsh");
            _fragment = ResourceManager::instance().getResource<FragmentShader>(fragPart + ".fsh");
        }
        
        if (!_vertex || !_fragment) return false;
        
        glBindAttribLocation(_handle, kPositionAttribLocation, "aPosition");
        glBindAttribLocation(_handle, kTextureCoordAttribLocation, "aTextureCoord");
        glBindAttribLocation(_handle, kColorAttribLocation, "aColor");
        glBindAttribLocation(_handle, kParticleInterpolationAttribLocation, "aInterpolation");
        glBindAttribLocation(_handle, kParticleStartColorAttribLocation, "aStartColor");
        glBindAttribLocation(_handle, kParticleEndColorAttribLocation, "aEndColor");
        glBindAttribLocation(_handle, kParticleStartSizeAttribLocation, "aStartSize");
        glBindAttribLocation(_handle, kParticleEndSizeAttribLocation, "aEndSize");
        
        glAttachShader(_handle, _vertex->getHandle());
        glAttachShader(_handle, _fragment->getHandle());
        glLinkProgram(_handle);
        
        int status;
        glGetProgramiv(_handle, GL_LINK_STATUS, &status);
        
        if (status == GL_FALSE)
        {
            // link failed. find out what went wrong
            char message[100];
            glGetProgramInfoLog(_handle, sizeof(message), nullptr, message);
            SOL_ERROR(message);
            return false;
        }
        
        _valid = true;
        _transformUniformLocation = glGetUniformLocation(_handle, "uTransform");
        _tintUniformLocation = glGetUniformLocation(_handle, "uTint");
        
        return true;
    }
    
    int Program::getAttribLocation(const string& name)
    {
        return _valid ? glGetAttribLocation(_handle, name.c_str()) : -1;
    }
    
    int Program::getUniformLocation(const string& name)
    {
        return _valid ? glGetUniformLocation(_handle, name.c_str()) : -1;
    }
    
    void Program::use()
    {
        if (gCurrentProgram != this)
        {
            assert(isValid());
            glUseProgram(_handle);
            gCurrentProgram = this;
        }
    }
    
    void Program::setTint(const Colorf& tint)
    {
        if (gCurrentProgram == this && tint != _currentTint)
        {
            glUniform4f(_tintUniformLocation, tint.r, tint.g, tint.b, tint.a);
            _currentTint = tint;
        }
    }
    
}