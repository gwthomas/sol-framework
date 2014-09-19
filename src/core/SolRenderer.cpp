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

#include "SolGL.h"
#include "SolManager.h"
#include "SolProgram.h"
#include "SolRenderable.h"
#include "SolRenderComponents.h"
#include "SolRenderer.h"
#include "SolScene.h"
#include "SolTexture.h"

namespace sol
{
    
    using std::vector;
    
    bool compareDepth(Renderable* r1, Renderable* r2)
    {
        return r1->getAbsoluteDepth() > r2->getAbsoluteDepth();
    }
    
    void Renderer::addRenderable(Renderable& rend)
    {
        _renderables.push_back(&rend);
        setNeedsReorder();
    }
    
    void Renderer::removeRenderable(Renderable& rend)
    {
        for (auto b = _renderables.begin(), e = _renderables.end(); b != e; ++b)
        {
            if (*b == &rend)
            {
                _renderables.erase(b);
                return;
            }
        }
    }
        
    void Renderer::prerender()
    {
        if (_needsReorder)
        {
            std::sort(_renderables.begin(), _renderables.end(), &compareDepth);
            setNeedsReorder(false);
        }
    }
    
    void Renderer::renderAll() const
    {
        for (Renderable* rend : _renderables)
        {
            if (rend->autorender) rend->render();
        }
    }
    
}