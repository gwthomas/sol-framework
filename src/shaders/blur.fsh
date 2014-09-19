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

precision mediump float;

uniform sampler2D sTexture;

varying vec2 vTextureCoord;
varying vec2 vBlurTextureCoords[14];

void main()
{
    gl_FragColor = vec4(0.0);
    gl_FragColor += texture2D(sTexture, vBlurTextureCoords[0])  * 0.0044299121055113265;
    gl_FragColor += texture2D(sTexture, vBlurTextureCoords[1])  * 0.00895781211794;
    gl_FragColor += texture2D(sTexture, vBlurTextureCoords[2])  * 0.0215963866053;
    gl_FragColor += texture2D(sTexture, vBlurTextureCoords[3])  * 0.0443683338718;
    gl_FragColor += texture2D(sTexture, vBlurTextureCoords[4])  * 0.0776744219933;
    gl_FragColor += texture2D(sTexture, vBlurTextureCoords[5])  * 0.115876621105;
    gl_FragColor += texture2D(sTexture, vBlurTextureCoords[6])  * 0.147308056121;
    gl_FragColor += texture2D(sTexture, vTextureCoord)          * 0.159576912161;
    gl_FragColor += texture2D(sTexture, vBlurTextureCoords[7])  * 0.147308056121;
    gl_FragColor += texture2D(sTexture, vBlurTextureCoords[8])  * 0.115876621105;
    gl_FragColor += texture2D(sTexture, vBlurTextureCoords[9])  * 0.0776744219933;
    gl_FragColor += texture2D(sTexture, vBlurTextureCoords[10]) * 0.0443683338718;
    gl_FragColor += texture2D(sTexture, vBlurTextureCoords[11]) * 0.0215963866053;
    gl_FragColor += texture2D(sTexture, vBlurTextureCoords[12]) * 0.00895781211794;
    gl_FragColor += texture2D(sTexture, vBlurTextureCoords[13]) * 0.0044299121055113265;
}