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

#ifndef SOL_EFFECT_H
#define SOL_EFFECT_H

#include "SolUtil.h"

namespace sol
{
    
    class Renderer;
    
    /// Base class for effects.
    struct Effect : public Noncopyable
    {
        virtual ~Effect() = default;
        
        /// Calls the given render function, applying an effect to anything rendered in the function.
        virtual void render(std::function<void ()> renderFunc) = 0;
    };
        
}

#endif