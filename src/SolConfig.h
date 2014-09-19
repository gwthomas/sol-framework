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

/// \file SolConfig.h
/// \brief You can (and probably will) modify this file to suit your needs under the permission of the license.

#ifndef SOL_CONFIG_H
#define SOL_CONFIG_H

/// Orientation of the screen when the application launches. Must be Portrait or Landscape.
#define SOL_DEFAULT_ORIENTATION Portrait

/// Default frames per second. 30.0 or 60.0 is typical but a different value could be used.
#define SOL_DEFAULT_FPS 60.0

/// Maximum number of touches that the input handler will track.
#define SOL_MAX_TOUCHES 1

/// Maximum number of texture units that can be bound at once.
#define SOL_MAX_TEXTURE_UNITS 8

/// Enable if you want to integrate iAds
#define SOL_USE_ADS 0

/// Enable if acceleration info is required.
#define SOL_USE_ACCELEROMETER 1

/// Enable if physics (using chipmunk) is required.
#define SOL_USE_PHYSICS 1

/// Enable if XML parsing (required for texture atlases) is required.
#define SOL_USE_XML 1

/// Enable if stb_vorbis can't play an ogg audio file.
#define SOL_USE_REFERENCE_VORBIS 1

/// Size in bytes of buffer for audio streams.
#define SOL_AUDIO_STREAM_BUFFER_SIZE (4096 * 16)

/// The width of the textures that will be used to store font bitmaps.
#define SOL_FONT_TEXTURE_WIDTH 512

/// The height of the textures that will be used to store font bitmaps.
#define SOL_FONT_TEXTURE_HEIGHT 512

/// The first ASCII character that will be rendered into font bitmaps.
#define SOL_FONT_FIRST_CHAR '!'

/// The last ASCII character that will be rendered into font bitmaps.
#define SOL_FONT_LAST_CHAR ('~' + 1)

/// Determines how much space to put for the ' ' character
#define SOL_LABEL_SPACE_FACTOR 0.4

#endif