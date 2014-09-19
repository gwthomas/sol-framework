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

#include "SolBufferObjects.h"
#include "SolNative.h"
#include "SolScene.h"

namespace sol
{
    
    void Scene::update()
    {
        if (_root.hasDirtyDepth())
        {
            _renderer.setNeedsReorder();
            _inputManager.setNeedsReorder();
        }
        
        _root.updateAll();
    }
    
    void Scene::render()
    {
        native::getDefaultFramebuffer().setClearColor(_clearColor);
        _renderer.prerender();
        _renderer.renderAll();
    }
    
#if SOL_USE_ADS
    void Scene::onAdEvent(AdEvent event)
    {
        switch (event)
        {
            case AdActivated:
                Manager::instance().pause();
                break;
                
            case AdDeactivated:
                Manager::instance().resume();
                break;
            
            default:
                break;
        }
    }
#endif
    
}