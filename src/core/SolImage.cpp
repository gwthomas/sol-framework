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

////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 Jonathan Dummer
 
 Image helper functions
 
 MIT license
 */

#include <stdlib.h>
#include <math.h>

/*	Upscaling the image uses simple bilinear interpolation	*/
int
up_scale_image
(
 const unsigned char* const orig,
 int width, int height, int channels,
 unsigned char* resampled,
 int resampled_width, int resampled_height
 )
{
	float dx, dy;
	int x, y, c;
    
    /* error(s) check	*/
    if ( 	(width < 1) || (height < 1) ||
        (resampled_width < 2) || (resampled_height < 2) ||
        (channels < 1) ||
        (NULL == orig) || (NULL == resampled) )
    {
        /*	signify badness	*/
        return 0;
    }
    /*
     for each given pixel in the new map, find the exact location
     from the original map which would contribute to this guy
     */
    dx = (width - 1.0f) / (resampled_width - 1.0f);
    dy = (height - 1.0f) / (resampled_height - 1.0f);
    for ( y = 0; y < resampled_height; ++y )
    {
    	/* find the base y index and fractional offset from that	*/
    	float sampley = y * dy;
    	int inty = (int)sampley;
    	/*	if( inty < 0 ) { inty = 0; } else	*/
		if( inty > height - 2 ) { inty = height - 2; }
		sampley -= inty;
        for ( x = 0; x < resampled_width; ++x )
        {
			float samplex = x * dx;
			int intx = (int)samplex;
			int base_index;
			/* find the base x index and fractional offset from that	*/
			/*	if( intx < 0 ) { intx = 0; } else	*/
			if( intx > width - 2 ) { intx = width - 2; }
			samplex -= intx;
			/*	base index into the original image	*/
			base_index = (inty * width + intx) * channels;
            for ( c = 0; c < channels; ++c )
            {
            	/*	do the sampling	*/
				float value = 0.5f;
				value += orig[base_index]
                *(1.0f-samplex)*(1.0f-sampley);
				value += orig[base_index+channels]
                *(samplex)*(1.0f-sampley);
				value += orig[base_index+width*channels]
                *(1.0f-samplex)*(sampley);
				value += orig[base_index+width*channels+channels]
                *(samplex)*(sampley);
				/*	move to the next channel	*/
				++base_index;
            	/*	save the new value	*/
            	resampled[y*resampled_width*channels+x*channels+c] =
                (unsigned char)(value);
            }
        }
    }
    /*	done	*/
    return 1;
}

int
invert_image_y
(
 unsigned char *image,
 int width, int height, int channels
 )
{
    int i, j;
    /* error check */
	if( (!image) || (width < 1) || (height < 1) )
	{
		return 0;
	}
    for( j = 0; j*2 < height; ++j )
    {
        int index1 = j * width * channels;
        int index2 = (height - 1 - j) * width * channels;
        for( i = width * channels; i > 0; --i )
        {
            unsigned char temp = image[index1];
            image[index1] = image[index2];
            image[index2] = temp;
            ++index1;
            ++index2;
        }
    }
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SolFileBuffer.h"
#include "SolGL.h"
#include "SolImage.h"
#include "SolManager.h"
#include "SolNative.h"
#include "SolUtil.h"

#define STBI_FAILURE_USERMSG 1
#include "stb_image.h"

namespace sol
{
    
    using std::string;
    
    Image::~Image()
    {
        SOL_SAFE_DELETE_ARRAY(_pixels);
    }
    
    bool Image::load()
    {
        bool has2x = _filename.find("@2x") != string::npos;
        bool retina;
        
        if (Manager::instance().isRetinaDisplay())
        {
            if (has2x) retina = true;
            else
            {
                size_t lastPeriod = _filename.find_last_of('.');
                string name2x = _filename;
                name2x.insert(lastPeriod, "@2x");
                
                // check if the 2x file exists. might there be a better way to do this?
                File f(Manager::instance().getResourcePath() + name2x, "rb");
                
                if (f)
                {
                    // the 2x version exists!
                    retina = true;
                    _filename = name2x;
                }
                else retina = false;
                    // the 2x version doesn't exist
            }
        }
        else
        {
            if (has2x) SOL_ERROR("Trying to load retina image, but screen is not retina");
            retina = false;
        }
        
        int width, height, components;
        unsigned int format;
        unsigned char* data = stbi_load((Manager::instance().getResourcePath() + _filename).c_str(), &width, &height, &components, 0);
        
        if (!data)
        {
            // something went wrong. find out what
            SOL_ERROR("Failed to load image " << _filename << " because " << stbi_failure_reason());
            return false;
        }
            
        invert_image_y(data, width, height, components);
        
        switch (components)
        {
            case 1:
                format = GL_ALPHA;
                break;
                
            case 2:
                format = GL_LUMINANCE_ALPHA;
                break;
                    
            case 3:
                format = GL_RGB;
                break;
                    
            case 4:
                format = GL_RGBA;
                break;
                    
            default:
                format = 0;
                SOL_ERROR("Bad image format");
                break;
        }
        
        bool loaded = _texture.image2D(data, format, Vec2i(width, height), retina);
        
        if (loaded)
        {
            int pixelCount = width * height;
            _size.x = width; _size.y = height;
            _pixels = new Colorc[pixelCount];
            
            switch (format)
            {
                case GL_ALPHA:
                    for (int i = 0; i < pixelCount; i++)
                    {
                        _pixels[i] = Colorc(255, 255, 255, data[i]);
                    }
                    break;
                    
                case GL_LUMINANCE_ALPHA:
                    for (int i = 0; i < pixelCount; i++)
                    {
                        _pixels[i] = Colorc(data[i * 2], data[i * 2], data[i * 2], data[i * 2 + 1]);
                    }
                    break;
                    
                case GL_RGB:
                    for (int i = 0; i < pixelCount; i++)
                    {
                        _pixels[i] = Colorc(data[i * 3], data[i * 3 + 1], data[i * 3 + 2], 255);
                    }
                    break;
                    
                case GL_RGBA:
                    for (int i = 0; i < pixelCount; i++)
                    {
                        _pixels[i] = Colorc(data[i * 4], data[i * 4 + 1], data[i * 4 + 2], data[i * 4 + 3]);
                    }
                    break;
                    
                default:
                    break;
            }
        }
        
        stbi_image_free(data);
        return loaded;
    }
    
}