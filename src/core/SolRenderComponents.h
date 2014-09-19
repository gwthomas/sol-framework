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

#ifndef SOL_RENDERCOMPONENTS_H
#define SOL_RENDERCOMPONENTS_H

#include <vector>
#include "SolColor.h"
#include "SolVec.h"
#include "SolBufferObjects.h"

namespace sol
{
    
    const int kPositionAttribLocation = 1;
    const int kTextureCoordAttribLocation = 2;
    const int kColorAttribLocation = 3;
    const int kParticleInterpolationAttribLocation = 4;
    const int kParticleStartColorAttribLocation = 5;
    const int kParticleEndColorAttribLocation = 6;
    const int kParticleStartSizeAttribLocation = 7;
    const int kParticleEndSizeAttribLocation = 8;
    
    enum AttribFlag
    {
        PositionAttribFlag     = 1 << 0,
        TextureCoordAttribFlag = 1 << 1,
        ColorAttribFlag        = 1 << 2,
        ParticleAttribsFlag    = 1 << 3
    };
    
    void useVertexAttribs(unsigned int attribs);
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    template <class T, unsigned int SIZE, unsigned int GL_TYPE, unsigned char NORMALIZED, int LOCATION = -1>
    class VertexAttribArray : public Noncopyable
    {
    public:
        ~VertexAttribArray() { clear(); SOL_SAFE_DELETE(_vbo); }
        
        int getLocation() const { return _location; }
        const std::vector<T>& getBuffer() const { return _buffer; }
        std::vector<T>& getBuffer() { return _buffer; }
        const T* getData() const { return _buffer.data(); }
        T* getData() { return _buffer.data(); }
        unsigned int getCount() const { return _buffer.size(); }
        
        bool hasValidLocation() const { return _location != -1; }
        bool isBuffered() const { return _vbo != nullptr; }
        bool isDirty() const { return _dirty; }
        
        void setLocation(int location) { _location = location; }
        
        void setDirty(bool dirty = true) { _dirty = isBuffered() ? dirty : false; }
        
        T& operator[](unsigned int index) { return _buffer[index]; }
        const T& operator[](unsigned int index) const { return _buffer[index]; }
        
        void alloc(unsigned int count);
        void clear() { _buffer.clear(); _dirty = true; }
        void add(const T& val) { _buffer.push_back(val); }
        
        void useVBO();
        
        bool submit();
        
    private:
        int _location = LOCATION;
        
        std::vector<T> _buffer;
        
        VBO* _vbo = nullptr;
        bool _dirty = false; // true if vbo needs to be updated
    };
    
    typedef VertexAttribArray<Vec2f, 2, GL_FLOAT, GL_FALSE, kPositionAttribLocation> VertexPositionArray;
    typedef VertexAttribArray<Vec2f, 2, GL_FLOAT, GL_FALSE, kTextureCoordAttribLocation> VertexTextureCoordArray;
    typedef VertexAttribArray<Colorc, 4, GL_UNSIGNED_BYTE, GL_TRUE, kColorAttribLocation> VertexColorArray;
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    class IndexArray : public Noncopyable
    {
    public:
        ~IndexArray() { clear(); SOL_SAFE_DELETE(_vbo); }
        
        const std::vector<unsigned short>& getBuffer() const { return _buffer; }
        std::vector<unsigned short>& getBuffer() { return _buffer; }
        const unsigned short* getData() const { return _buffer.data(); }
        const unsigned short* getPointer() const { return isBuffered() ? nullptr : getData(); }
        unsigned int getCount() const { return _buffer.size(); }
        
        bool isBuffered() const { return _vbo != nullptr; }
        bool isDirty() const { return _dirty; }
        
        void setDirty(bool dirty = true) { _dirty = isBuffered() ? dirty : false; }
        
        unsigned short& operator[](unsigned int index) { return _buffer[index]; }
        unsigned short operator[](unsigned int index) const { return _buffer[index]; }
        
        void alloc(unsigned int count);
        void clear() { _buffer.clear(); _dirty = true; }
        void add(unsigned short val) { _buffer.push_back(val); }
        
        void useVBO();
        
        bool submit();
        
    private:
        std::vector<unsigned short> _buffer;
        
        VBO* _vbo = nullptr;
        bool _dirty = false; // true if vbo needs to be updated
    };
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    template <class T, unsigned int SIZE, unsigned int GL_TYPE, unsigned char NORMALIZED, int LOCATION>
    void VertexAttribArray<T, SIZE, GL_TYPE, NORMALIZED, LOCATION>::alloc(unsigned int count)
    {
        clear();
        _buffer.reserve(count);
        
        for (int i = 0; i < count; i++) _buffer.emplace_back();
    }
    
    template <class T, unsigned int SIZE, unsigned int GL_TYPE, unsigned char NORMALIZED, int LOCATION>
    void VertexAttribArray<T, SIZE, GL_TYPE, NORMALIZED, LOCATION>::useVBO()
    {
        if (!_vbo)
        {
            _vbo = new VBO(GL_ARRAY_BUFFER);
            _dirty = true;
        }
    }
    
    template <class T, unsigned int SIZE, unsigned int GL_TYPE, unsigned char NORMALIZED, int LOCATION>
    bool VertexAttribArray<T, SIZE, GL_TYPE, NORMALIZED, LOCATION>::submit()
    {
        if (!hasValidLocation() || (_buffer.empty() && _vbo == nullptr))
        {
            return false;
        }
        
        if (_vbo)
        {
            _vbo->bind();
            
            if (_dirty && !_buffer.empty())
            {
                _vbo->data(_buffer.size() * sizeof(T), _buffer.data(), GL_STATIC_DRAW);
            }
            
            glVertexAttribPointer(_location, SIZE, GL_TYPE, NORMALIZED, 0, 0);
        }
        else
        {
            VBO::unbind(GL_ARRAY_BUFFER);
            glVertexAttribPointer(_location, SIZE, GL_TYPE, NORMALIZED, 0, _buffer.data());
        }
        
        setDirty(false);
        
        return true;
    }
    
}

#endif