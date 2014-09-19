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

#include "SolBody.h"
#if SOL_USE_PHYSICS

#   include "SolScene.h"
#   include "SolSpace.h"

namespace sol
{
    namespace physics
    {
        
        Body::Body(float m, float i) :
            _body(&_theBody),
            _static(false)
        {
            cpBodyInit(_body, m, i);
            cpBodySetUserData(_body, this);
        }
        
        Body::Body() :
            _body(&_theBody),
            _static(true)
        {
            cpBodyInitStatic(_body);
            cpBodySetUserData(_body, this);
        }
        
        void Body::onAdd(Scene& scene)
        {
            if (!_static) scene.getSpace()->addBody(*this);
            SceneNode::onAdd(scene);
        }
        
        void Body::onRemove()
        {
            if (!_static) _scene->getSpace()->addBody(*this);
            SceneNode::onRemove();
        }
        
        void Body::update()
        {
            SceneNode::setPosition(getPos());
            SceneNode::setRotation(getAngle());
        }
        
    }
}

#endif // SOL_USE_PHYSICS