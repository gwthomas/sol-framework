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

#ifndef SOL_GRADIENT_H
#define SOL_GRADIENT_H

#include "SolColor.h"
#include "SolQuad.h"

namespace sol
{
    
    class GradientBatch;
    
    class Gradient : public Quad
    {
        friend class GradientBatch;
        
    public:
        Gradient();
        
        void setColor(unsigned int index, const Colorc& color);
        void setColor(const Colorc& color) { for (int i = 0; i <= 3; i++) setColor(i, color); }
        
        void render() override;
        
    private:
        VertexColorArray _colors;
        
        GradientBatch* _batch = nullptr;
        
        // called by friend GradientBatch
        Gradient(GradientBatch& batch);
        const VertexColorArray& getColors() const { return _colors; }
    };
    
}

#endif