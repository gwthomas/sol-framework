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

#ifndef SOL_FILEBUFFER_H
#define SOL_FILEBUFFER_H

#include <vector>
#include "SolFile.h"

namespace sol
{
    
    template<class T>
    class FileBuffer : public Noncopyable
    {
    public:
        ~FileBuffer() { close(); }
        
        const std::vector<T>& getBuffer() const { return _buffer; }
        const T* getData() const { return _buffer.data(); }
        T* getData() { return _buffer.data(); }
        
        bool open(const std::string& path, const std::string& mode, bool plus1 = false);
        bool openText(const std::string& path, const std::string& mode);
        void close();
        
    private:
        File _f;
        std::vector<T> _buffer;
    };
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    template<class T>
    bool FileBuffer<T>::open(const std::string& path, const std::string& mode, bool plus1)
    {
        close();
        
        _f.open(path, mode);
        
        if (_f)
        {
            // get the file size
            long size = _f.getSize();
            
            _buffer.reserve(plus1 ? size + 1 : size);
            
            if (size != _f.read(_buffer.data(), sizeof(T), size))
            {
                SOL_PRINT("Failed to read file at " << path);
                close();
            }
            
            return true;
        }
        else
        {
            SOL_PRINT("Failed to open file at " << path);
            close();
            return false;
        }
    }
    
    template<class T>
    bool FileBuffer<T>::openText(const std::string& path, const std::string& mode)
    {
        if (open(path, mode, true))
        {
            _buffer[_buffer.capacity() - 1] = '\0';
            return true;
        }
        
        return false;
    }
    
    template<class T>
    void FileBuffer<T>::close()
    {
        _f.close();
        _buffer.clear();
    }
    
}

#endif