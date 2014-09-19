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

#include "SolFont.h"
#include "SolGL.h"
#include "SolImage.h"
#include "SolLabel.h"
#include "SolProgram.h"

namespace sol
{
    
    using std::string;
        
    Label::Label(Font& font) :
        Label()
    {
        setFont(font);
    }
    
    Label::Label(const string& fontName) :
        Label(*ResourceManager::instance().getResource<Font>(fontName))
    {}
    
    Label::Label()
    {
        program = ResourceManager::instance().getResource<Program>("default_p_tc");
        _attribs |= (PositionAttribFlag | TextureCoordAttribFlag);
    }
    
    void Label::setText(const string& text)
    {
        if (_text == text) return;
        
        _text = text;
        _charCount = 0;
        
        for (int i = 0; i < text.length(); i++)
        {
            char val = _text[i];
            if (SOL_FONT_FIRST_CHAR <= val && val <= SOL_FONT_LAST_CHAR) _charCount++;
        }
        
        _positions.alloc(_charCount * 4);
        _textureCoords.alloc(_charCount * 4);
        _indices.alloc(_charCount * 6);
        
        for (int i = 0; i < _charCount; i++)
        {            
            _indices[i * 6] = i * 4;
            _indices[i * 6 + 1] = i * 4 + 1;
            _indices[i * 6 + 2] = i * 4 + 2;
            _indices[i * 6 + 3] = i * 4 + 2;
            _indices[i * 6 + 4] = i * 4 + 1;
            _indices[i * 6 + 5] = i * 4 + 3;
        }
        
        setNeedsCalc();
    }
    
    void Label::setFont(Font& font)
    {
        if (_font == &font) return;
        
        _font = &font;
        _texture = &font.getTexture();
        setNeedsCalc();
    }
    
    void Label::setAlignment(Alignment alignment)
    {
        if (_alignment == alignment) return;
        
        _alignment = alignment;
        setNeedsCalc();
    }
    
    void Label::setWidth(float width)
    {
        if (_width == width) return;
        
        _width = width;
        setNeedsCalc();
    }
    
    void Label::setPadding(float padding)
    {
        if (_padding == padding) return;
        
        _padding = padding;
        setNeedsCalc();
    }
    
    void Label::update()
    {
        if (_needsCalc && _font)
        {
            calcVertices();
            determineHeight();
            float offset = getVerticalOffset();
            for (int i = 0; i < _charCount*4; i++) _positions[i].y += offset;
            setNeedsCalc(false);
        }
    }
    
    void Label::useBufferObjects(bool positions, bool textureCoords, bool indices)
    {
        if (positions)     _positions.useVBO();
        if (textureCoords) _textureCoords.useVBO();
        if (indices)       _indices.useVBO();
    }
    
    void Label::render()
    {
        if (!_font || _text == "") return;
        
        Matrix trans = _combinedTransform;
        Colorf tmpTint = tint;
        assert(_positions.submit());
        assert(_textureCoords.submit());
        assert(_indices.submit());
        
        if (shadowOffset)
        {
            _combinedTransform = _combinedTransform * Matrix().translation(shadowOffset);
            tint = blackColorf(tint.a);
            prerender();
            glDrawElements(GL_TRIANGLES, _indices.getCount(), GL_UNSIGNED_SHORT, _indices.getPointer());
        }
        
        _combinedTransform = trans;
        tint = tmpTint;
        prerender();
        glDrawElements(GL_TRIANGLES, _indices.getCount(), GL_UNSIGNED_SHORT, _indices.getPointer());
    }
    
    void Label::determineHeight()
    {
        if (_charCount == 0)
        {
            _height = 0.0;
            return;
        }
        
        float min = 1000000.0, max = -1000000.0;
        
        for (int i = 0; i < _charCount * 4; i++)
        {
            if (_positions[i].y > max) max = _positions[i].y;
            if (_positions[i].y < min) min = _positions[i].y;
        }
        
        _height = max - min;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    void SimpleLabel::calcVertices()
    {
        Vec2f penPos = getStartPenPos();
        int offset = 0;
        
        for (int i = 0; i < _text.size(); i++)
        {
            char val = _text[i];
            float advance;
            
            if (SOL_FONT_FIRST_CHAR <= val && val <= SOL_FONT_LAST_CHAR)
            {
                _font->vertexDataForCharacter(val, penPos, _positions.getData() + offset * 4, _textureCoords.getData() + offset * 4);
                advance = _font->getCharWidth(val) + _padding;
                offset++;
            }
            else if (val == ' ') advance = float(_font->getSize()) * SOL_LABEL_SPACE_FACTOR;
            else advance = 0.0;
            
            penPos.x += advance;
        }
    }
    
    Vec2f SimpleLabel::getStartPenPos()
    {
        if (_alignment == AlignLeft)
        {
            return Vec2f(-_width * 0.5, 0.0);
        }
        else if (_alignment == AlignCenter)
        {
            Vec2f ret(0.0, 0.0);
            
            for (int i = 0; i < _text.size(); i++)
            {
                char val = _text[i];
                float advance;
                
                if (SOL_FONT_FIRST_CHAR <= val && val <= SOL_FONT_LAST_CHAR)
                {
                    advance = _font->getCharWidth(val);
                }
                else if (val == ' ') advance = float(_font->getSize()) * SOL_LABEL_SPACE_FACTOR;
                else advance = 0.0;
                
                ret.x -= advance * 0.5;
            }
            
            ret.x -= _padding * 0.5 * float(_charCount - 1);
            
            return ret;
        }
        
        return Vec2f();
    }
    
    float SimpleLabel::getVerticalOffset()
    {
        return _font->getVerticalOffset();
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    void TextArea::setSpacing(float spacing)
    {
        if (_spacing == spacing) return;
        
        _spacing = spacing;
        setNeedsCalc();
    }
    
    void TextArea::calcVertices()
    {
        _lineCount = 1;
        
        Vec2f penPos(-_width * 0.5, 0.0);
        int offset = 0;
        
        for (int i = 0; i < _text.size(); i++)
        {
            char val = _text[i];
            float advance;
            
            if (_width > 0.0 && penPos.x + nextWordWidth(i) > _width * 0.5) nextLine(penPos);
            
            if (SOL_FONT_FIRST_CHAR <= val && val <= SOL_FONT_LAST_CHAR)
            {
                _font->vertexDataForCharacter(val, penPos, _positions.getData() + offset * 4, _textureCoords.getData() + offset * 4);
                advance = _font->getCharWidth(val) + _padding;
                offset++;
            }
            else if (val == '\n')
            {
                nextLine(penPos);
                advance = 0.0;
            }
            else if (val == ' ') advance = float(_font->getSize()) * SOL_LABEL_SPACE_FACTOR;
            else advance = 0.0;
            
            penPos.x += advance;
        }
    }
    
    float TextArea::getVerticalOffset()
    {
        return _font->getVerticalOffset() + (float(_lineCount-1) * (float(_font->getSize()) * _spacing + _padding)) * 0.5;
    }
    
    float TextArea::nextWordWidth(int index)
    {
        float width = 0.0;
        
        for (int i = index; i < _text.size(); i++)
        {
            char val = _text[i];
            
            if (SOL_FONT_FIRST_CHAR <= val && val <= SOL_FONT_LAST_CHAR)
            {
                width += _font->getCharWidth(val);
                width += _padding;
            }
            else break;
        }
        
        width -= _padding; // compensate for extra padding of last character
        return width;
    }
    
    void TextArea::nextLine(Vec2f& penPos)
    {
        penPos.x = -_width * 0.5;
        penPos.y -= float(_font->getSize()) * _spacing + _padding;
        _lineCount++;
    }
    
}