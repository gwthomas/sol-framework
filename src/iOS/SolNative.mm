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

#include <Foundation/Foundation.h>
#include "SolManager.h"
#include "SolNative.h"

namespace sol
{
    namespace native
    {
        
        using std::string;
                        
        string getResourcePath()
        {
            string ret = [[[NSBundle mainBundle] resourcePath] fileSystemRepresentation];
            return ret + "/";
        }
        
        bool isRetinaDisplay()
        {
            UIScreen *screen = [UIScreen mainScreen];
            return [screen respondsToSelector:@selector(scale)] && [screen scale] == 2.0;
        }
        
        Vec2f screenToWorld(const Vec2f& loc)
        {
            Vec2i screenSize = Manager::instance().getScreenSizePoints();
            float halfw = screenSize.x / 2, halfh = screenSize.y / 2;
            
            return Manager::instance().getOrientation() == Portrait ? Vec2f(loc.x - halfw, screenSize.y - loc.y - halfh)
                                                                    : Vec2f(loc.y - halfw, loc.x - halfh);
        }
        
        Vec2f worldToGLPoints(const Vec2f& loc)
        {
            Vec2i screenSize = Manager::instance().getScreenSizePoints();
            float halfw = screenSize.x / 2, halfh = screenSize.y / 2;
            Vec2f points = Manager::instance().getOrientation() == Portrait ? Vec2f(loc.x + halfw, loc.y + halfh)
                                                                            : Vec2f(loc.y + halfh, halfw - loc.x);
            return points;
        }
        
        Vec2f worldToGLPixels(const Vec2f& loc)
        {
            Vec2f points = worldToGLPoints(loc);
            return Manager::instance().isRetinaDisplay() ? points * 2.0f : points;
        }
        
        bool defaultsGetBool(const std::string& key)
        {
            NSString* string = [NSString stringWithUTF8String:key.c_str()];
            return [[NSUserDefaults standardUserDefaults] boolForKey:string];
        }
        
        float defaultsGetFloat(const std::string& key)
        {
            NSString* string = [NSString stringWithUTF8String:key.c_str()];
            return [[NSUserDefaults standardUserDefaults] floatForKey:string];
        }
        
        int defaultsGetInt(const std::string& key)
        {
            NSString* string = [NSString stringWithUTF8String:key.c_str()];
            return [[NSUserDefaults standardUserDefaults] integerForKey:string];
        }
        
        void defaultsSetBool(const std::string& key, bool b)
        {
            NSString* string = [NSString stringWithUTF8String:key.c_str()];
            return [[NSUserDefaults standardUserDefaults] setBool:b forKey:string];
        }
        
        void defaultsSetFloat(const std::string& key, float f)
        {
            NSString* string = [NSString stringWithUTF8String:key.c_str()];
            return [[NSUserDefaults standardUserDefaults] setFloat:f forKey:string];
        }
        
        void defaultsSetInt(const std::string& key, int i)
        {
            NSString* string = [NSString stringWithUTF8String:key.c_str()];
            return [[NSUserDefaults standardUserDefaults] setInteger:i forKey:string];
        }
        
    }
}