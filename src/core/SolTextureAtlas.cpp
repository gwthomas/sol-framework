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

#include "SolTextureAtlas.h"
#if SOL_USE_XML

#include "SolFileBuffer.h"
#include "SolImage.h"
#include "SolManager.h"
#include "SolXML.h"

namespace sol
{
    
    using std::string;

    bool TextureAtlas::load()
    {
        FileBuffer<char> f;
        
        if (!f.openText((Manager::instance().getResourcePath() + _filename), "r"))
        {
            SOL_ERROR("Failed to open sprite sheet " << _filename);
            return false;
        }
        
        rapidxml::xml_document<> doc;
        doc.parse<0>(f.getData());
        
        rapidxml::xml_node<>* root = doc.first_node();
        
        const char* imagePath = root->first_attribute("imagePath")->value();
        Image* image = ResourceManager::instance().getResource<Image>(imagePath);
        
        if (!image)
        {
            SOL_ERROR("Image " << imagePath << " specified by sprite sheet " << _filename << " does not exist");
            return false;
        }
        
        int imageHeight = atoi(root->first_attribute("height")->value());
        
        for (rapidxml::xml_node<>* node = root->first_node(); node != nullptr; node = node->next_sibling())
        {
            const char* n = node->first_attribute("n")->value();
            int x = atoi(node->first_attribute("x")->value());
            int y = atoi(node->first_attribute("y")->value());
            int w = atoi(node->first_attribute("w")->value());
            int h = atoi(node->first_attribute("h")->value());
            
            _textureMap[n] = AABBi(Vec2i(x, imageHeight - y - h), Vec2i(w, h));
        }
        
        _texture = &image->getTexture();
        
        return true;
    }
    
}

#endif