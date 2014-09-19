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

#ifndef SOL_PHYSICS_SHAPE_H
#define SOL_PHYSICS_SHAPE_H

#include "SolConfig.h"
#if SOL_USE_PHYSICS

#   include "SolBody.h"
#   include "SolVec.h"

namespace sol
{
    namespace physics
    {
        
        class Body;
        
        class Shape : public SceneNode
        {
        public:            
            virtual ~Shape() { cpShapeFree(_shape); }
            
            Body& getBody() const { return _body; }
            
            bool getSensor() const { return bool(cpShapeGetSensor(_shape)); }
            float getElasticity() const { return cpShapeGetElasticity(_shape); }
            float getFriction() const { return cpShapeGetFriction(_shape); }
            Vec2f getSurfaceVelocity() const { return Vec2f(cpShapeGetSurfaceVelocity(_shape)); }
            unsigned int getGroup() const { return cpShapeGetGroup(_shape); }
            unsigned int getLayers() const { return cpShapeGetLayers(_shape); }
            
            void setSensor(bool sensor) { cpShapeSetSensor(_shape, int(sensor)); }
            void setElasticity(float elasticity) { cpShapeSetElasticity(_shape, elasticity); }
            void setFriction(float friction) { cpShapeSetFriction(_shape, friction); }
            void setSurfaceVelocity(const Vec2f& surfaceVelocity) { cpShapeSetSurfaceVelocity(_shape, surfaceVelocity); }
            void setGroup(unsigned int group) { cpShapeSetGroup(_shape, group); }
            void setLayers(unsigned int layers) { cpShapeSetLayers(_shape, layers); }
            
            operator cpShape*() const { return _shape; }
            
        protected:
            cpShape* _shape = nullptr;
            
            Body& _body;
            
            Shape(Body& body) : _body(body) {}
            
            void onAdd(Scene& scene) override;
            void onRemove() override;
        };
        
        class CircleShape : public Shape
        {
        public:
            CircleShape(Body& body, float radius, const Vec2f& offset);
            
            Vec2f getOffset() const { return Vec2f(cpCircleShapeGetOffset(_shape)); }
            float getRadius() const { return cpCircleShapeGetRadius(_shape); }
        };
        
        class SegmentShape : public Shape
        {
        public:
            SegmentShape(Body& body, const Vec2f& a, const Vec2f& b, float radius);
            
            Vec2f getA() const { return Vec2f(cpSegmentShapeGetA(_shape)); }
            Vec2f getB() const { return Vec2f(cpSegmentShapeGetB(_shape)); }
            Vec2f getNormal() const { return Vec2f(cpSegmentShapeGetNormal(_shape)); }
            float getRadius() const { return cpSegmentShapeGetRadius(_shape); }
        };
        
        class PolyShape : public Shape
        {
        public:
            PolyShape(Body& body, float width, float height);
            PolyShape(Body& body, int numVerts, Vec2f* verts, const Vec2f& offset);
            ~PolyShape() { SOL_SAFE_DELETE_ARRAY(_verts); }
            
            int getNumVerts() const { return cpPolyShapeGetNumVerts(_shape); }
            Vec2f getVert(int index) const { return Vec2f(cpPolyShapeGetVert(_shape, index)); }
            
        private:
            cpVect* _verts;
        };
        
    }
}

#endif // SOL_USE_PHYSICS

#endif