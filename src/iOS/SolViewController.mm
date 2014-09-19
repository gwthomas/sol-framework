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

#import "SolViewController.h"
#include "SolManager.h"

@implementation SolViewController

using namespace sol;

- (SolViewController*)initWithFrame:(CGRect)frame
{
    if ((self = [super init]))
    {
        _glview = [[SolGLView alloc] initWithFrame:frame];
        self.view = _glview;
        
#if SOL_USE_ADS
        if ([ADBannerView instancesRespondToSelector:@selector(initWithAdType:)])
        {
            _adview = [[ADBannerView alloc] initWithAdType:ADAdTypeBanner];
        }
        else
        {
            _adview = [[ADBannerView alloc] init];
        }
        
        _adview.currentContentSizeIdentifier = ADBannerContentSizeIdentifierPortrait;
        _adview.delegate = self;
        _adview.hidden = true; // hidden initially. will show when an ad is loaded
        [self.view addSubview:_adview];
#endif
    }
    
    return self;
    
}

- (void)dealloc
{
    [super dealloc];
    [_glview release];
    _glview = nil;
#if SOL_USE_ADS
    [_adview release];
    _adview = nil;
#endif
}

- (void)set
{
#if SOL_USE_AFDS
    _adview.hidden = !AdManager::instance().showAds || !AdManager::instance().hasAd();
#endif
    [_glview setFramebuffer];
}

- (void)present
{
    [_glview presentFramebuffer];
}

#if SOL_USE_ADS
- (void)bannerViewActionDidFinish:(ADBannerView*)banner
{
    AdManager::instance().adEvent(AdDeactivated);
}

- (BOOL)bannerViewActionShouldBegin:(ADBannerView*)banner willLeaveApplication:(BOOL)willLeave
{
    AdManager::instance().adEvent(AdActivated);
    return YES;
}

- (void)bannerViewDidLoadAd:(ADBannerView *)banner
{
    AdManager::instance().adEvent(AdLoaded);
    _hasAd = TRUE;
}

- (void)bannerView:(ADBannerView *)banner didFailToReceiveAdWithError:(NSError *)error
{
    AdManager::instance().adEvent(AdFailed);
    _hasAd = false;
}
#endif

@end