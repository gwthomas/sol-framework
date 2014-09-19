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
#ifndef SOL_ANIMATEDSPRITE_H
#define SOL_ANIMATEDSPRITE_H

#include <queue>
#include "SolSprite.h"

namespace sol
{
    
    class Animation;
    
    class AnimatedSprite : public Sprite
    {
    public:
        bool playing = true;
        
        AnimatedSprite(Texture& texture) : Sprite(texture) { update(); }
        AnimatedSprite(const std::string& imageName) : Sprite(imageName) { update(); }
        
        bool hasCurrentAnimation() const { return _currentAnimation.first != nullptr; }
        
        void setTimePerFrame(float timePerFrame) { _timePerFrame = timePerFrame; }
        void setDefaultFrame(const AABBi& defaultFrame) { _defaultFrame = defaultFrame; }
        
        void enqueueAnimation(Animation& animation, int count);
        
        void update();
        
    private:        
        std::queue<std::pair<Animation*, int> > _animationQueue;
        std::pair<Animation*, int> _currentAnimation;
        unsigned int _currentFrameIndex = 0;
        
        float _timePerFrame = 1.0;
        float _timeSinceLastFrameChange = 0.0;
        
        AABBi _defaultFrame;
    };
    
}

#endif