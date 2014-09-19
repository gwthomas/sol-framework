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

#include "SolAudio.h"
#include "SolFont.h"
#include "SolGL.h"
#include "SolImage.h"
#include "SolManager.h"
#include "SolNative.h"
#include "SolProgram.h"
#include "SolRenderable.h"
#include "SolResourceManager.h"
#include "SolShader.h"

namespace sol
{
    
    using std::map;
    using std::string;
    
    ResourceManager& ResourceManager::instance()
    {
        static ResourceManager instance;
        return instance;
    }
    
    void ResourceManager::destroyResource(const string& filename)
    {
        string name(filename);
        Resource* resource = _resources[name];
        
        if (resource)
        {
            _resources.erase(name);
            delete resource;
        }
    }
    
    void ResourceManager::destroyAllResourceManager()
    {
        for (auto it = _resources.begin(); it != _resources.end(); ++it)
        {
            delete it->second;
        }
        
        _resources.clear();
    }
    
}