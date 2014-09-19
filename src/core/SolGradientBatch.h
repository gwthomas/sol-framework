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

#ifndef SOL_GRADIENTBATCH_H
#define SOL_GRADIENTBATCH_H

#include <vector>
#include "SolRenderComponents.h"
#include "SolRenderObject.h"

namespace sol
{
    
    class Gradient;
    
    class GradientBatch : public RenderObject
    {
    public:
        GradientBatch();
        ~GradientBatch();
                
        Gradient& create();
        void destroy(Gradient& gradient);
        
        void useBufferObjects(bool positions = true, bool colors = true, bool indices = true);
        
        void render() override;
        
    private:
        VertexPositionArray _positions;
        VertexColorArray _colors;
        IndexArray _indices;
        
        std::vector<Gradient*> _gradients;
        bool _sizeChanged = false;
                
        void copyVertices();
    };
    
}

#endif