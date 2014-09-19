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

#include "SolBlur.h"
#include "SolProgram.h"
#include "SolSprite.h"

namespace sol
{
     
    Blur::Blur()
    {
        Program* hprog = ResourceManager::instance().getResource<Program>("hblur|blur");
        Program* vprog = ResourceManager::instance().getResource<Program>("vblur|blur");
        Vec2i screenSize = Manager::instance().getScreenSizePixels();
        bool retina = Manager::instance().isRetinaDisplay();
        Vec2i size(std::min(screenSize.x, screenSize.y), std::max(screenSize.x, screenSize.y));
                    
        for (int i = 0; i <= 1; i++)
        {
            _texture[i].setup(GL_RGB, size, retina);
            
            _blur[i] = new Sprite(_texture[i].getTexture());
            _blur[i]->defaultRegion(); // update size and texture coords
            _blur[i]->useBufferObjects();
        }
        
        _blur[0]->program = hprog;
        _blur[1]->program = vprog;
    }
    
    Blur::~Blur()
    {
        delete _blur[0];
        delete _blur[1];
    }
    
    void Blur::render(std::function<void ()> renderFunc)
    {
        Framebuffer& framebuffer = getCurrentFramebuffer();
        
        _texture[0].clearColor(framebuffer.getClearColor());
        _texture[1].clearColor(framebuffer.getClearColor());
        
        // render basic scene
        _texture[0].render(renderFunc);
        
        bool landscape = false;
        
        if (Manager::instance().getOrientation() == Landscape)
        {
            landscape = true;
            Manager::instance().setOrientation(Portrait); // temporarily render in portait to avoid rotation
        }
        
        // render scene with horizontal blur
        _texture[1].render([this]() { _blur[0]->render(); });
        
        // render scene with vertical blur
        framebuffer.clear();
        _blur[1]->render();
        
        if (landscape)
        {
            Manager::instance().setOrientation(Landscape);
        }
    }
        
}