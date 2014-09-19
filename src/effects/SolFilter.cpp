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

#include "SolFilter.h"
#include "SolProgram.h"

namespace sol
{
    
    using std::string;
        
    Filter::Filter(const string& program, const std::vector<std::string>& params) :
        _spr(_texture.getTexture())
    {
        _prog = ResourceManager::instance().getResource<Program>(program);
        assert(_prog);
        
        for (const string& param : params)
        {
            _parameters[param] = _prog->getUniformLocation(param);
        }
        
        Vec2i screenSize = Manager::instance().getScreenSizePixels();
        bool retina = Manager::instance().isRetinaDisplay();
        Vec2i size(std::min(screenSize.x, screenSize.y), std::max(screenSize.x, screenSize.y));            
        
        _texture.setup(GL_RGB, size, retina);
        
        _spr.program = _prog;
        _spr.defaultRegion(); // update size and texture coords
        _spr.useBufferObjects();
    }
    
    void Filter::prepare()
    {
        _prog->use();
    }
    
    void Filter::render(std::function<void ()> renderFunc)
    {
        Framebuffer& framebuffer = getCurrentFramebuffer();
        
        // render scene into offscreen fbo
        _texture.clearColor(framebuffer.getClearColor());
        _texture.render(renderFunc);
        
        bool landscape = false;
        
        if (Manager::instance().getOrientation() == Landscape)
        {
            landscape = true;
            Manager::instance().setOrientation(Portrait); // temporarily render in portait to avoid rotation
        }
                    
        // render inverted image back into default framebuffer
        framebuffer.clear();
        _spr.render();
        
        if (landscape)
        {
            Manager::instance().setOrientation(Landscape);
        }
    }
        
}