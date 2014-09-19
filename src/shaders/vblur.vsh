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

uniform mat3 uTransform;

attribute vec2 aPosition;
attribute vec2 aTextureCoord;

varying vec2 vTextureCoord;
varying vec2 vBlurTextureCoords[14];

vec2 mult(mat3 transform, vec2 position)
{
    return vec2(transform[0].x * position.x + transform[1].x * position.y + transform[2].x,
                transform[0].y * position.x + transform[1].y * position.y + transform[2].y);
}

void main()
{
    gl_Position = vec4(mult(uTransform, aPosition), 0.0, 1.0);
    
    vTextureCoord = aTextureCoord;
    
    vBlurTextureCoords[0]  = vTextureCoord + vec2(0.0, -0.028);
    vBlurTextureCoords[1]  = vTextureCoord + vec2(0.0, -0.024);
    vBlurTextureCoords[2]  = vTextureCoord + vec2(0.0, -0.020);
    vBlurTextureCoords[3]  = vTextureCoord + vec2(0.0, -0.016);
    vBlurTextureCoords[4]  = vTextureCoord + vec2(0.0, -0.012);
    vBlurTextureCoords[5]  = vTextureCoord + vec2(0.0, -0.008);
    vBlurTextureCoords[6]  = vTextureCoord + vec2(0.0, -0.004);
    vBlurTextureCoords[7]  = vTextureCoord + vec2(0.0,  0.004);
    vBlurTextureCoords[8]  = vTextureCoord + vec2(0.0,  0.008);
    vBlurTextureCoords[9]  = vTextureCoord + vec2(0.0,  0.012);
    vBlurTextureCoords[10] = vTextureCoord + vec2(0.0,  0.016);
    vBlurTextureCoords[11] = vTextureCoord + vec2(0.0,  0.020);
    vBlurTextureCoords[12] = vTextureCoord + vec2(0.0,  0.024);
    vBlurTextureCoords[13] = vTextureCoord + vec2(0.0,  0.028);
}