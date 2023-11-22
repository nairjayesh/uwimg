#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"
#include <stdlib.h>

#define PIXEL_AT(image, c, h, w)\
    (image).data[(c)*(image).h*(image).w + (h)*(image).w + (w)] 

#define PIXEL_BOUND(image, c, h, w)					\
    ((c >= 0 && c < image.c) && (h >= 0 && h < image.h) && (w >= 0 && w < image.w))

#define PIXEL_VALUE_BOUND(image, c, h, w)\
    (PIXEL_AT(image, c, h, w) <= 1 && PIXEL_AT(image, c, h, w) >= 0)



const float luma_R = 0.299;
const float luma_G = 0.587;
const float luma_B = 0.114; 



float max_color(float a, float b, float c)
{
    float max = a;
    if (b > max) { max = b; }
    if (c > max) { max = c; } 
    return max;
}

float min_color(float a, float b, float c)
{
    float min = a;
    if (b < min) { min = b; }
    if (c < min) { min = c; }
    return min;
}

float get_pixel(image im, int c, int h, int w)
{
    // Ensure that co-ordinates are valid 
    if (!(PIXEL_BOUND(im, c, h, w)))
	{
	    if (c < 0) { c = 0; }
	    else if (c >= im.c) { c = im.c - 1; }
	    if (h < 0) { h = 0; }
	    else if (h >= im.h) { h = im.h - 1; }
	    if (w < 0) { w = 0; }
	    else if (w >= im.w) { w = im.w - 1; }
	}
    return PIXEL_AT(im ,c ,h ,w);
}

void set_pixel(image im, int c, int h, int w, float v)
{
    // Exit the program if found; 
    if (!(PIXEL_BOUND(im, c, h, w))) { return;}
    // Set the pixel value if all conditions are valid
    PIXEL_AT(im, c, h, w) = v; 
}

image copy_image(image im)
{
    image copy = make_image(im.c, im.h, im.w);
    memcpy(copy.data, im.data, sizeof(float)*im.c*im.h*im.w);
    return copy;
}

// REVIEW: Tests for grayscale and no-red images are faliing post changes
// TODO: Change the implementation to make the color-bar to grayscale work.

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(1, im.h, im.w);
    // Converting 3 Channels to 1
    // Y' = 0.299 R' + 0.587 G' + 0.114 B'
    // You don't need to iterate through channels
    	    for (size_t h = 0; h < im.h; ++h)
		{
		    for (size_t w = 0; w < im.w; ++w)
			{
			    // Each pixel is a combination of all three channels
			    PIXEL_AT(gray, 0, h, w) = 0.299*PIXEL_AT(im, 0, h, w) +
				                      0.587*PIXEL_AT(im, 1, h, w) +
				                      0.114*PIXEL_AT(im, 2, h, w);  
			}
    }
    return gray;
}

void shift_image(image im, int c, float v)
{
    // Previous test failed: because I iterated over the funciton with channel as well.
    for (size_t h = 0; h < im.h; ++h)
	{
	 for (size_t w = 0; w < im.w; ++w)
	     {
		  PIXEL_AT(im, c, h, w) += v;  
	     }
       }
}

// Given the problem of overflow - what typically takes place in a photo-editing
// software?
// What use-cases can shifting values of pixel have?
// Incearsing brightness?
// Increasing contrast?
// In each cases - what does the maximum value depend upon in a hardware?
// In software - it depends upon the maximum memory size allocated, what about hardware?
// Guess: Some display screen parameter? - Which might explain Samsung's screen's? 

void clamp_image(image im)
{
    for (size_t c = 0; c < im.c; ++c)
	{
	    for (size_t h = 0; h < im.h; ++h)
		{
		    for (size_t w = 0; w < im.w; ++w)
			{
			    if (!(PIXEL_VALUE_BOUND(im, c, h, w)))
				{
				    if (PIXEL_AT(im, c, h, w) >= 1)
					{ PIXEL_AT(im, c, h, w) = 1; }
				    else if (PIXEL_AT(im, c, h, w) <= 0)
					{ PIXEL_AT(im, c, h, w) = 0; } 
				}
			}
		}
	 }
}

// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}


void update_hue(image im, float hue_temp, float s, float v, size_t h, size_t w)
{
    float hue; 
    if ( hue_temp < 0) { hue = (hue_temp/6) + 1; }
    else { hue = hue_temp / 6; }
    PIXEL_AT(im, 0, h, w) = hue;
    PIXEL_AT(im, 1, h, w) = s;
    PIXEL_AT(im, 2, h, w) = v;    
}

void rgb_to_hsv(image im)
{
    float hue_temp = 0;
    float S,R,G,B; 
    //image hsv = make_image(im.c, im.h, im.w);
    for (size_t h = 0; h < im.h; ++h)
		{
		    for (size_t w = 0; w < im.w; ++w)
			{
			    R = PIXEL_AT(im, 0, h, w);
			    G = PIXEL_AT(im, 1, h, w);
			    B = PIXEL_AT(im, 2, h, w); 
			    float V = max_color(R, G, B);
			    float M = min_color(R, G, B);
			    float C = V - M; // C as given in hw0 README
			    // 
			    if (V == 0)
				{
				    S = 0; 
				}
			    else
				{
				    S = C / V;  
				} 
			    if (C == 0)
				{
				    hue_temp = 0; 				    
				}
			    else if (V == R)
				{
				    hue_temp = ((G - B)/C);
				}
			    
			    else if (V == G)
				{
				    hue_temp = ((B - R)/C) + 2;
				}
			    else
				{
				    hue_temp = ((R - G)/C) + 4;
				}
			    update_hue(im, hue_temp, S, V, h, w);
		}
	}
}

void hsv_to_rgb(image im)
{
    float H,S,V;
    
    
    
}



// Log the questions and project development:
// You are trying to learn key-ideas in image-processing
// How they came to be evolved and what the low-level processing
// really looks like.
// Teaching computers to see! 

