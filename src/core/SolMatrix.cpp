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

#include "SolMatrix.h"

namespace sol
{
    
    Matrix& Matrix::identity()
    {
        if (!_identity)
        {
            _values[0] = 1.0; _values[3] = 0.0; _values[6] = 0.0;
            _values[1] = 0.0; _values[4] = 1.0; _values[7] = 0.0;
            _values[2] = 0.0; _values[5] = 0.0; _values[8] = 1.0;
        
            _identity = true;
        }
    
        return *this;
    }
    
    Matrix& Matrix::ortho(float left, float right, float bottom, float top)
    {
        _values[0] = 2.0 / (right - left); _values[3] = 0.0;                  _values[6] = -(right + left) / (right - left);
        _values[1] = 0.0;                  _values[4] = 2.0 / (top - bottom); _values[7] = -(top + bottom) / (top - bottom);
        _values[2] = 0.0;                  _values[5] = 0.0;                  _values[8] = 1.0;
        
        _identity = false;
        
        return *this;
    }
    
    Matrix& Matrix::translation(const Vec2f& amount)
    {
        if (amount)
        {            
            _values[0] = 1.0; _values[3] = 0.0; _values[6] = amount.x;
            _values[1] = 0.0; _values[4] = 1.0; _values[7] = amount.y;
            _values[2] = 0.0; _values[5] = 0.0; _values[8] = 1.0;
            
            _identity = false;
        }
        else identity();
        
        return *this;
    }
    
    Matrix& Matrix::scaling(const Vec2f& amount)
    {
        if (amount)
        {
            _values[0] = amount.x; _values[3] = 0.0;      _values[6] = 0.0;
            _values[1] = 0.0;      _values[4] = amount.y; _values[7] = 0.0;
            _values[2] = 0.0;      _values[5] = 0.0;      _values[8] = 1.0;
            
            _identity = false;
        }
        else identity();
        
        return *this;
    }
    
    Matrix& Matrix::rotation(float amount)
    {
        if (amount)
        {
            float rad = degreesToRadians(amount);
            float s = std::sin(rad);
            float c = std::cos(rad);
            
            _values[0] = c;   _values[3] = -s;  _values[6] = 0.0;
            _values[1] = s;   _values[4] = c;   _values[7] = 0.0;
            _values[2] = 0.0; _values[5] = 0.0; _values[8] = 1.0;
            
            _identity = false;
        }
        else identity();
        
        return *this;
    }
    
    Matrix& Matrix::transform(const Vec2f& translate, const Vec2f& scale, float rotate)
    {
        float rad = degreesToRadians(rotate);
        float s = (rotate == 0.0 ? 0.0 : std::sin(rad));
        float c = (rotate == 0.0 ? 1.0 : std::cos(rad));
            
        _values[0] = c * scale.x; _values[3] = -s * scale.y; _values[6] = translate.x;
        _values[1] = s * scale.x; _values[4] = c * scale.y;  _values[7] = translate.y;
        _values[2] = 0.0;         _values[5] = 0.0;          _values[8] = 1.0;
        
        _identity = false;
        
        return *this;
    }
    
    Matrix Matrix::operator*(const Matrix& mat) const
    {
        if (_identity) return mat;
        else if (mat.isIdentity()) return *this;
        else
        {
            Matrix ret;
            
            ret[0] = _values[0] * mat[0] + _values[3] * mat[1] + _values[6] * mat[2];
            ret[1] = _values[1] * mat[0] + _values[4] * mat[1] + _values[7] * mat[2];
            ret[2] = _values[2] * mat[0] + _values[5] * mat[1] + _values[8] * mat[2];
            ret[3] = _values[0] * mat[3] + _values[3] * mat[4] + _values[6] * mat[5];
            ret[4] = _values[1] * mat[3] + _values[4] * mat[4] + _values[7] * mat[5];
            ret[5] = _values[2] * mat[3] + _values[5] * mat[4] + _values[8] * mat[5];
            ret[6] = _values[0] * mat[6] + _values[3] * mat[7] + _values[6] * mat[8];
            ret[7] = _values[1] * mat[6] + _values[4] * mat[7] + _values[7] * mat[8];
            ret[8] = _values[2] * mat[6] + _values[5] * mat[7] + _values[8] * mat[8];
            
            ret.setIdentity(false);
            
            return ret;
        }
    }
    
    Vec2f Matrix::operator*(const Vec2f& vec) const
    {
        if (_identity) return vec;
        else
        {
            Vec2f ret;
            
            ret.x = _values[0] * vec.x + _values[3] * vec.y + _values[6];
            ret.y = _values[1] * vec.x + _values[4] * vec.y + _values[7];
            
            return ret;
        }
    }
    
}