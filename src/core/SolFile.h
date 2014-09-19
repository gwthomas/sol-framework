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

#ifndef SOL_FILE_H
#define SOL_FILE_H

#include <cstdio>
#include <string>
#include "SolUtil.h"

namespace sol
{
    
    class File : public Noncopyable
    {
    public:
        File(const std::string& filename, const std::string& mode) { open(filename, mode); }
        File() = default;
        ~File() { close(); }
        
        bool isOpen() const { return _handle != nullptr; }
        FILE* getHandle() const { return _handle; }
        const std::string& getFilename() const { return _filename; }
        const std::string& getMode() const { return _mode; }
        long getSize() const;
        
        bool open(const std::string& filename, const std::string& mode);
        void close() { if (isOpen()) fclose(_handle); }
        
        size_t read(void* ptr, size_t size, size_t count);
        
        operator bool() const { return isOpen(); }
        
    private:
        FILE* _handle = nullptr;
        std::string _filename;
        std::string _mode;
    };
    
}

#endif