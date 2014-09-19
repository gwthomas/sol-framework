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

#import <QuartzCore/QuartzCore.h>
#import <UIKit/UIKit.h>
#import "SolGLView.h"
#include "SolBufferObjects.h"
#include "SolNative.h"
#include "SolManager.h"
#include "SolScene.h"

namespace sol
{
    namespace native
    {
        
        Framebuffer* gDefaultFramebuffer = nullptr;
    
        Framebuffer& getDefaultFramebuffer()
        {
            return *gDefaultFramebuffer;
        }
    
    }
}

@interface SolGLView (PrivateMethods)
- (void)createFramebuffer;
- (void)deleteFramebuffer;
@end

@implementation SolGLView

@synthesize context;

using namespace sol;

// you must implement this method
+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)frame
{    
	if ((self = [super initWithFrame:frame]))
    {
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        
        self.multipleTouchEnabled = TRUE;
        
        if (Manager::instance().isRetinaDisplay()) self.contentScaleFactor = 2.0;
        
        eaglLayer.opaque = TRUE;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                            [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking,
                                            kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat,
                                        nil];
        
        self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        
        if (!self.context) SOL_ERROR("Failed to create ES context");
        else if (![EAGLContext setCurrentContext:context]) SOL_ERROR("Failed to set ES context current");
                
        [self setFramebuffer];
        
        for (int i = 0; i < SOL_MAX_TOUCHES; i++) _touches[i] = nil;
            
#if SOL_USE_ACCELEROMETER
        UIAccelerometer *accelerometer = [UIAccelerometer sharedAccelerometer];
        accelerometer.delegate = self;
        accelerometer.updateInterval = 1.0 / SOL_DEFAULT_FPS;
#endif
    }
    
    return self;
}

- (void)dealloc
{
    [self deleteFramebuffer];    
    [context release];
    [super dealloc];
}

- (void)setContext:(EAGLContext *)newContext
{
    if (context != newContext)
    {
        [self deleteFramebuffer];
        [context release];
        context = [newContext retain];
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)createFramebuffer
{
    if (context && !_framebuffer)
    {
        [EAGLContext setCurrentContext:context];
                
        // create default framebuffer
        _framebuffer = new Framebuffer();
        _framebuffer->bind();
        native::gDefaultFramebuffer = _framebuffer;
        
        // create color renderbuffer
        _colorbuffer = new Renderbuffer();
        _colorbuffer->bind();
        [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer *)self.layer];
        _framebuffer->attachColorBuffer(*_colorbuffer);
        
        if (!_framebuffer->isComplete())
        {
            SOL_ERROR("Failed to make complete framebuffer: ");
            
            switch (glCheckFramebufferStatus(GL_FRAMEBUFFER))
            {
                case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                    SOL_PRINT("\tIncomplete attachment");
                    break;
                    
                case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                    SOL_PRINT("\tMissing attachment");
                    break;
                    
                case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
                    SOL_PRINT("\tIncomplete dimensions");
                    break;
                    
                case GL_FRAMEBUFFER_UNSUPPORTED:
                    SOL_PRINT("\tUnsupported");
                    break;
                    
                default:
                    SOL_PRINT("\twtf");
                    break;
            }
        }
        
        Vec2i screenSize = Manager::instance().getScreenSizePixels();
        glViewport(0.0, 0.0, std::min(screenSize.x, screenSize.y), std::max(screenSize.x, screenSize.y));
    }
}

- (void)deleteFramebuffer
{
    if (context)
    {
        [EAGLContext setCurrentContext:context];
        SOL_SAFE_DELETE(_framebuffer);
        SOL_SAFE_DELETE(_colorbuffer);
        native::gDefaultFramebuffer = nullptr;
    }
}

- (void)setFramebuffer
{
    if (context)
    {
        [EAGLContext setCurrentContext:context];
        if (!_framebuffer) [self createFramebuffer];
        _framebuffer->clear();
        
    }
}

- (BOOL)presentFramebuffer
{    
    if (context)
    {
        [EAGLContext setCurrentContext:context];
        _colorbuffer->bind();
        return [context presentRenderbuffer:GL_RENDERBUFFER];
    }
    
    return FALSE;
}

#if SOL_USE_ACCELEROMETER
- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration
{
    Vec3f tilt = Manager::instance().getOrientation() == Portrait ? Vec3f( acceleration.x, acceleration.y, acceleration.z)
                                                                  : Vec3f(-acceleration.y, acceleration.x, acceleration.z);
    InputManager* handler = InputManager::currentInstance();
    if (handler) handler->tilt(tilt);
}
#endif

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    for (UITouch *touch in touches)
    {
        CGPoint loc = [touch locationInView:self];
        Vec2f worldLoc = native::screenToWorld(Vec2f(loc.x, loc.y));
                
        for (int i = 0; i < SOL_MAX_TOUCHES; i++)
        {
            if (!_touches[i])
            {
                _touches[i] = touch;
                InputManager* handler = InputManager::currentInstance();
                if (handler) handler->touchDown(i, worldLoc);
                break;
            }
        }
    }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{    
    for (UITouch *touch in touches)
    {
        CGPoint loc = [touch locationInView:self];
        Vec2f worldLoc = native::screenToWorld(Vec2f(loc.x, loc.y));
        
        for (int i = 0; i < SOL_MAX_TOUCHES; i++)
        {
            if (_touches[i] == touch)
            {
                InputManager* handler = InputManager::currentInstance();
                if (handler) handler->touchMoved(i, worldLoc);
                break;
            }
        }
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{    
    for (UITouch *touch in touches)
    {        
        for (int i = 0; i < SOL_MAX_TOUCHES; i++)
        {
            if (_touches[i] == touch)
            {
                _touches[i] = nil;
                InputManager* handler = InputManager::currentInstance();
                if (handler) handler->touchUp(i);
                break;
            }
        }
    }
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self touchesEnded:touches withEvent:nil];
}

@end
