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

// adapted from Krzysztof Zablocki's article

precision mediump float;

uniform vec4 uTint;
uniform ivec2 uScreenSize;
uniform sampler2D sTexture;

varying vec2 vTextureCoord;

void main()
{
    vec2 onePixel = vec2(1.0 / float(uScreenSize.x), 1.0 / float(uScreenSize.y));
    vec3 color = vec3(0.5);
    color -= texture2D(sTexture, vTextureCoord - onePixel).rgb * 5.0;
    color += texture2D(sTexture, vTextureCoord + onePixel).rgb * 5.0;
    color = vec3((color.r + color.g + color.b) / 3.0);
    gl_FragColor = vec4(color, 1.0) * uTint;
}