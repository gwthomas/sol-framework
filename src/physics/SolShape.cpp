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

#include "SolShape.h"
#if SOL_USE_PHYSICS

#   include "SolScene.h"
#   include "SolSpace.h"

namespace sol
{
    namespace physics
    {
        
        void Shape::onAdd(Scene& scene)
        {
            scene.getSpace()->addShape(*this);
            SceneNode::onAdd(scene);
        }
        
        void Shape::onRemove()
        {
            _scene->getSpace()->removeShape(*this);
            SceneNode::onRemove();
        }
        
        CircleShape::CircleShape(Body& body, float radius, const Vec2f& offset) :
            Shape(body)
        {
            _shape = cpCircleShapeNew(body, radius, offset);
            cpShapeSetUserData(_shape, this);
        }
        
        SegmentShape::SegmentShape(Body& body, const Vec2f& a, const Vec2f& b, float radius) :
            Shape(body)
        {
            _shape = cpSegmentShapeNew(body, a, b, radius);
            cpShapeSetUserData(_shape, this);
        }
        
        PolyShape::PolyShape(Body& body, float width, float height) :
            Shape(body),
            _verts(nullptr)
        {
            _shape = cpBoxShapeNew(body, width, height);
            cpShapeSetUserData(_shape, this);
        }
        
        PolyShape::PolyShape(Body& body, int numVerts, Vec2f* verts, const Vec2f& offset) :
            Shape(body)
        {
            _verts = new cpVect[numVerts];
            
            for (int i = 0; i < numVerts; i++)
            {
                _verts[i] = verts[i];
            }
            
            _shape = cpPolyShapeNew(body, numVerts, _verts, offset);
            cpShapeSetUserData(_shape, this);
        }
    }
}

#endif // SOL_USE_PHYSICS