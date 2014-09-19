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
attribute float aInterpolation;
attribute vec4 aStartColor;
attribute vec4 aEndColor;
attribute float aStartSize;
attribute float aEndSize;

varying vec4 vColor;

vec2 mult(mat3 transform, vec2 position)
{
    return vec2(transform[0].x * position.x + transform[1].x * position.y + transform[2].x,
                transform[0].y * position.x + transform[1].y * position.y + transform[2].y);
}

void main()
{
    gl_Position = vec4(mult(uTransform, aPosition), 0.0, 1.0);

    gl_PointSize = aStartSize + (aEndSize - aStartSize) * aInterpolation;
    vColor = aStartColor + (aEndColor - aStartColor) * aInterpolation;
}