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

#include "SolFile.h"

namespace sol
{
    
    bool File::open(const std::string& filename, const std::string& mode)
    {
        _filename = filename;
        _mode = mode;
        _handle = fopen(filename.c_str(), mode.c_str());
        return isOpen();
    }
    
    long File::getSize() const
    {
        if (!isOpen()) return 0;
        
        long pos = ftell(_handle);
        fseek(_handle, 0, SEEK_END);
        long len = ftell(_handle);
        fseek(_handle, pos, SEEK_SET);
        
        return len;
    }
    
    size_t File::read(void* ptr, size_t size, size_t count)
    {
        return isOpen() ? fread(ptr, size, count, _handle) : 0;
    }
    
}