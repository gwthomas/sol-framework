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

#ifndef SOL_BLUR_H
#define SOL_BLUR_H

#include "SolEffect.h"
#include "SolRenderTexture.h"

namespace sol
{
    
    class Sprite;
    
    /// Effect that provides simple Gaussian blur.
    class Blur : public Effect
    {
    public:
        Blur();
        ~Blur();
        
        /// Calls the given render function, applying a Gaussian blur to anything rendered in the function.
        void render(std::function<void ()> renderFunc) override;
            
    private:
        RenderTexture _texture[2];
        Sprite* _blur[2];
    };

}

#endif