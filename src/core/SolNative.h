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

/// \namespace sol::native
/// \brief OS-specific abstractions to keep Sol portable.

#ifndef SOL_NATIVE_H
#define SOL_NATIVE_H

#include <string>
#include "SolVec.h"

namespace sol
{
    
    class Framebuffer;
    
    namespace native
    {
        
        /// Don't call this directly. Instead get the cached value using Manager::getResourcePath()
        std::string getResourcePath();
    
        /// Don't call this directly. Instead get the cached value using Manager::isRetinaDisplay()
        bool isRetinaDisplay();
        
        /// Convert screen coordinates to world coordinates.
        Vec2f screenToWorld(const Vec2f& loc);
        
        /// Convert world coordinates to OpenGL ES coordinates (points).
        Vec2f worldToGLPoints(const Vec2f& loc);
        
        /// Convert world coordinates to OpenGL ES coordinates (pixels).
        /// Same as worldToGLPoints(const Vec2f&) if non-retina display.
        Vec2f worldToGLPixels(const Vec2f& loc);
        
        /// Get the default framebuffer that is created and managed by Sol.
        Framebuffer& getDefaultFramebuffer();
        
        /// Retrieve a named boolean value from defaults.
        bool defaultsGetBool(const std::string& key);
        
        /// Retrieve a named floating-point value from defaults.
        float defaultsGetFloat(const std::string& key);
        
        /// Retrieve a named integer value from defaults.
        int defaultsGetInt(const std::string& key);
        
        /// Store a named boolean value in defaults.
        void defaultsSetBool(const std::string& key, bool b);
        
        /// Store a named floating-point value in defaults.
        void defaultsSetFloat(const std::string& key, float f);
        
        /// Store a named integer value in defaults.
        void defaultsSetInt(const std::string& key, int i);
    
    }
}
    
#endif