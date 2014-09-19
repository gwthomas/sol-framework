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

#import <UIKit/UIKit.h>
#include "SolConfig.h"

@class EAGLContext;

namespace sol
{
    class Framebuffer;
    class Renderbuffer;
}

@interface SolGLView : UIView
#if SOL_USE_ACCELEROMETER
    <UIAccelerometerDelegate>
#endif
{    
    sol::Framebuffer* _framebuffer;
    sol::Renderbuffer* _colorbuffer;
    
    UITouch *_touches[SOL_MAX_TOUCHES];
}

@property (nonatomic, retain) EAGLContext *context;

- (void)setFramebuffer;
- (BOOL)presentFramebuffer;

@end