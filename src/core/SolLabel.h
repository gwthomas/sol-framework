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

#ifndef SOL_LABEL_H
#define SOL_LABEL_H

#include "SolRenderComponents.h"
#include "SolRenderObject.h"

namespace sol
{
    
    class Font;
    
    class Label : public RenderObject
    {
    public:
        enum Alignment
        {
            AlignLeft,
            AlignCenter
        };
        
        Vec2f shadowOffset;
        
        Label(Font& font);
        Label(const std::string& fontName);
        Label();
        
        Font& getFont() const { return *_font; }
        Alignment getAlignment() const { return _alignment; }
        const std::string& getText() const { return _text; }
        float getWidth() const { return _width; }
        float getHeight() const { return _height; }
        float getPadding() const { return _padding; }
        
        void setFont(Font& font);
        void setAlignment(Alignment alignment);
        void setText(const std::string& text);
        void setWidth(float width);
        void setPadding(float padding);
        
        void useBufferObjects(bool positions = true, bool textureCoords = true, bool indices = true);
        
        void update() override;
        void render() override;
        
    protected:
        VertexPositionArray _positions;
        VertexTextureCoordArray _textureCoords;
        IndexArray _indices;
        
        Font* _font = nullptr;
        
        float _width = 0.0;
        float _height; // can't be set manually; calculated
        float _padding = 0.0;
        
        Alignment _alignment = AlignLeft;
        std::string _text;
        unsigned int _charCount = 0;
        
        bool _needsCalc = false;
        
        // internal use
        void setNeedsCalc(bool needsCalc = true) { _needsCalc = needsCalc; }
        void determineHeight();
        virtual void calcVertices() = 0;
        virtual float getVerticalOffset() = 0;
    };
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    class SimpleLabel : public Label
    {
    public:
        SimpleLabel(Font& font) : Label(font) {}
        SimpleLabel(const std::string& fontName) : Label(fontName) {}
        SimpleLabel() = default;
        
    private:
        // internal use
        void calcVertices() override;
        Vec2f getStartPenPos();
        float getVerticalOffset() override;
    };
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    class TextArea : public Label
    {
    public:
        TextArea(Font& font) : Label(font) {}
        TextArea(const std::string& fontName) : Label(fontName) {}
        TextArea() = default;
        
        float getSpacing() const { return _spacing; }
        
        void setSpacing(float spacing);
        
    private:        
        float _spacing = 1.0;
        unsigned int _lineCount = 1;
        
        // internal use
        void calcVertices() override;
        float getVerticalOffset() override;
        float nextWordWidth(int index);
        void nextLine(Vec2f& penPos);
    };
    
}

#endif