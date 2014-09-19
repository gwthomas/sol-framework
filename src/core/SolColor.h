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

#ifndef SOL_COLOR_H
#define SOL_COLOR_H

#include "SolUtil.h"

namespace sol
{
    
    template<class T>
    struct Color
    {
        T r = 0;
        T g = 0;
        T b = 0;
        T a = 0;
        
        Color(T r, T g, T b, T a) : r(r), g(g), b(b), a(a) {}
                
        Color() = default;
        
        template<class U>
        Color<U> cast() const { return Color<U>(U(r), U(g), U(b), U(a)); }
        
        Color<T> operator*(T scale) const { return Color<T>(r * scale, g * scale, b * scale, a * scale); }
        Color<T> operator/(T scale) const { return Color<T>(r / scale, g / scale, b / scale, a / scale); }
        
        bool operator == (const Color<T>& color) const { return r == color.r && g == color.g && b == color.b && a == color.a; }
        bool operator != (const Color<T>& color) const { return r != color.r || g != color.g || b != color.b || a != color.a; }
        
        friend std::ostream& operator<<(std::ostream& os, const Color<T>& color)
        {
            os << "R: " << color.r << ", G: " << color.g << ", B: " << color.b << ", A: " << color.a;
            return os;
        }
    };
    
    typedef Color<float> Colorf;
    typedef Color<unsigned char> Colorc;
    
    inline Colorf redColorf(float a = 1.0)   { return Colorf(1.0, 0.0, 0.0, a); }
    inline Colorf greenColorf(float a = 1.0) { return Colorf(0.0, 1.0, 0.0, a); }
    inline Colorf blueColorf(float a = 1.0)  { return Colorf(0.0, 0.0, 1.0, a); }
    inline Colorf orangeColorf(float a = 1.0) { return Colorf(1.0, 0.5, 0.0, a); }
    inline Colorf purpleColorf(float a = 1.0) { return Colorf(1.0, 0.0, 1.0, a); }
    inline Colorf yellowColorf(float a = 1.0) { return Colorf(1.0, 1.0, 0.0, a); }
    inline Colorf blackColorf(float a = 1.0) { return Colorf(0.0, 0.0, 0.0, a); }
    inline Colorf whiteColorf(float a = 1.0) { return Colorf(1.0, 1.0, 1.0, a); }
    inline Colorf greyColorf(float c, float a = 1.0)  { return Colorf(c, c, c, a); }
        
    inline Colorc redColorc(unsigned char a = 255)    { return Colorc(255,   0,   0, a); }
    inline Colorc greenColorc(unsigned char a = 255)  { return Colorc(  0, 255,   0, a); }
    inline Colorc blueColorc(unsigned char a = 255)   { return Colorc(  0,   0, 255, a); }
    inline Colorc orangeColorc(unsigned char a = 255) { return Colorc(255, 128,   0, a); }
    inline Colorc purpleColorc(unsigned char a = 255) { return Colorc(255,   0, 255, a); }
    inline Colorc yellowColorc(unsigned char a = 255) { return Colorc(255, 255,   0, a); }
    inline Colorc blackColorc(unsigned char a = 255)  { return Colorc(  0,   0,   0, a); }
    inline Colorc whiteColorc(unsigned char a = 255)  { return Colorc(255, 255, 255, a); }
    inline Colorc greyColorc(unsigned char c, unsigned char a = 255)   { return Colorc(c, c, c, a); }
    
}

#endif