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

#include "SolAnimatedSprite.h"
#include "SolAnimation.h"

namespace sol
{
    
    using std::string;
    
    void AnimatedSprite::enqueueAnimation(Animation& animation, int count)
    {
        if (count != 0)
        {
            _animationQueue.push(std::make_pair(&animation, count));
        }
    }
    
    void AnimatedSprite::update()
    {
        if (playing)
        {
            if (hasCurrentAnimation())
            {
                _timeSinceLastFrameChange += Manager::instance().dt();
                
                if (_timeSinceLastFrameChange >= _timePerFrame)
                {
                    textureRegion(_currentAnimation.first->getFrame(_currentFrameIndex++));
                    _timeSinceLastFrameChange = 0.0;
                }
                
                if (_currentFrameIndex > _currentAnimation.first->getFrameCount())
                {
                    if (--_currentAnimation.second != 0)
                    {
                        _timeSinceLastFrameChange = _timePerFrame;
                        _currentFrameIndex = 0;
                    }
                    else _currentAnimation.first = nullptr;
                    
                    update(); // a little recursion to avoid code redundancy
                    return;
                }
            }
            else
            {                
                if (!_animationQueue.empty())
                {
                    _currentAnimation = _animationQueue.front();
                    _animationQueue.pop();
                    _texture = &_currentAnimation.first->getTexture();
                    _timeSinceLastFrameChange = _timePerFrame;
                    _currentFrameIndex = 0;
                    
                    update(); // a little recursion to avoid code redundancy
                    return; 
                }
                else textureRegion(_defaultFrame);
            }
        }
                
        Sprite::update();
    }
    
}