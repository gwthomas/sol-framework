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

#ifndef SOL_RESOURCES_H
#define SOL_RESOURCES_H

#include <map>
#include <string>

#include "SolUtil.h"

namespace sol
{
    
    class Resource : public Noncopyable
    {
        friend class ResourceManager;
        
    public:
        const std::string& getFilename() const { return _filename; }
        
    protected:
        Resource(const std::string& filename) : _filename(filename) {}
        virtual ~Resource() = default;
        
        std::string _filename;
        
        virtual bool load() = 0;
    };
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    class ResourceManager : public Noncopyable
    {        
        friend class Manager;
        
    public:
        static ResourceManager& instance();
        
        template<class T>
        T* getResource(const std::string& filename);
        
        void destroyResource(const std::string& filename);
        void destroyAllResourceManager();
                
    private:
        std::map<std::string, Resource*> _resources;
    };
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    template<class T>
    T* ResourceManager::getResource(const std::string& filename)
    {
        T* ret = (T*)_resources[filename];
        
        if (!ret)
        {
            ret = new T(filename);
            
            if (ret->load()) _resources[filename] = ret;
            else
            {
                SOL_ERROR("Resource " << filename << " could not be loaded.");
                SOL_SAFE_DELETE(ret);
            }
        }
        
        return ret;
    }
    
}

#endif