/*
 *
 * Copyright (c) 2012 Garrett Thomas
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the use o this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin o this software must not be misrepresented; you must not claim that you wrote the original software.
 *    I you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */

#ifndef SOL_CIRCLE_H
#define SOL_CIRCLE_H

#include "SolRenderComponents.h"
#include "SolRenderObject.h"

namespace sol
{
    
    class Circle : public RenderObject
    {
    public:
        Colorf fill = whiteColorf();
        Colorf edge = blackColorf();
        float edgeWidth = 0.0;
        
        Circle(float radius);
        
        float getRadius() const { return _radius; }
        
        void setRadius(float radius) { _radius = radius; _needsCalc = true; }
        void setRotation(float rotation) override {}
        
        void update() override;
        void render() override;
        
    private:
        VertexPositionArray _positions;
        bool _needsCalc = false;
        
        float _radius;
        
        int _centerUniformLocation = -1;
        int _radiusUniformLocation = -1;
        int _edgeWidthUniformLocation = -1;
        int _fillColorUniformLocation = -1;
        int _edgeColorUniformLocation = -1;
    };
    
}

#endif