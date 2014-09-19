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

#ifndef SOL_FILTER_H
#define SOL_FILTER_H

#include "SolEffect.h"
#include "SolRenderTexture.h"
#include "SolSprite.h"

namespace sol
{
    
    /// Effect that provides a filter driven by a shader.
    class Filter : public Effect
    {
    public:
        /// Constructor that takes the name of the program and the names of all the required "parameters" (uniforms).
        Filter(const std::string& program, const std::vector<std::string>& params = std::vector<std::string>());
        
        /// Sets the tint of the filter.
        void tint(const Colorf& color) { _spr.tint = color; }
    
        /// MUST be called before passing any parameters.
        void prepare();
        
        /// Passes a parameter to the shader as a uniform int.
        void param(const std::string& param, int val) { glUniform1i(_parameters[param], val); }
        
        /// Passes a parameter to the shader as a uniform float.
        void param(const std::string& param, float val) { glUniform1f(_parameters[param], val); }
        
        /// Passes a parameter to the shader as a uniform ivec2.
        void param(const std::string& param, Vec2i val) { glUniform2i(_parameters[param], val.x, val.y); }
        
        /// Passes a parameter to the shader as a uniform vec2.
        void param(const std::string& param, Vec2f val) { glUniform2f(_parameters[param], val.x, val.y); }
        
        /// Passes a parameter to the shader as a uniform vec4.
        void param(const std::string& param, const Colorf& val) { glUniform4fv(_parameters[param], 1, &val.r); }
        
        /// Calls the given render function, applying a filter to anything rendered in the function.
        void render(std::function<void ()> renderFunc) override;
        
    private:
        Program* _prog = nullptr;
        
        std::map<std::string, int> _parameters;
        
        RenderTexture _texture;
        Sprite _spr;
    };
        
}

#endif