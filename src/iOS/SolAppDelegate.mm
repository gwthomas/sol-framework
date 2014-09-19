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

#import "SolAppDelegate.h"
#include "SolManager.h"
#include "SolScene.h"

@implementation SolAppDelegate

@synthesize _window;

using namespace sol;

- (BOOL)application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions
{        
    CGRect screenSize = [[UIScreen mainScreen] bounds];
    
    Manager::instance().init0(Vec2i(screenSize.size.width, screenSize.size.height));
    
    _window = [[UIWindow alloc] initWithFrame:screenSize];
    [_window makeKeyAndVisible];
    
    _vc = [[SolViewController alloc] initWithFrame:screenSize];
    _window.rootViewController = _vc;
    
    [self startLoop];
    Manager::instance().init1();
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
        
    [self stopLoop];
    Manager::instance().pause();
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
     */
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    /*
     Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
     */
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
        
    [self startLoop];
    Manager::instance().resume();
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    /*
     Called when the application is about to terminate.
     Save data if appropriate.
     See also applicationDidEnterBackground:.
     */
        
    [self stopLoop];
    Manager::instance().deinit();
}

- (void)startLoop
{
    [self stopLoop];
    
    _fps = Manager::instance().fps;
    
#if USE_DISPLAY_LINK
    if (!_displayLink)
    {
        _displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(mainLoop)];
        _displayLink.frameInterval = int(60.0 / _fps);
        [_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    }
#else
    if (!_timer)
    {
        _timer = [NSTimer scheduledTimerWithTimeInterval:1.0 / _fps target:self selector:@selector(mainLoop) userInfo:nil repeats:TRUE];
    }
#endif
}

- (void)stopLoop
{
#if USE_DISPLAY_LINK
    if (_displayLink)
    {
        [_displayLink invalidate];
        _displayLink = nil;
    }
#else
    if (_timer)
    {
        [_timer invalidate];
        _timer = nil;
    }
#endif
}

- (void)mainLoop
{
    if (!Manager::instance().isRunning()) return;
    
    if (fabsf(Manager::instance().fps - _fps) > 0.0001)
    {
        [self startLoop];
    }
        
    Manager::instance().update();
        
    if (Manager::instance().renderNewFrame)
    {
        [_vc set];
        Manager::instance().render();
        [_vc present];
    }
}

- (void)dealloc
{
    [_window release];
    _window = nil;
    [_vc release];
    _vc = nil;
    [super dealloc];
}

@end