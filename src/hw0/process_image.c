#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

#define PIXEL_AT(image, c, h, w) (image).data[(c)*(image).h*(image).w + (h)*(image).w + (w)] 

// How do I say stuff in C?
// First few implementations should help manipulate the dog-image. 

float get_pixel(image im, int c, int h, int w)
{
    // TODO returns the value at channel c, row h and column w
    // Ensure that co-ordinates are valid 
    float value = PIXEL_AT(im ,c ,h ,w);
    return value;
}

void set_pixel(image im, int c, int h, int w, float v)
{
    // TODO Fill this in
    PIXEL_AT(im, c, h, w) = v; 
}

image copy_image(image im)
{
    image copy = make_image(im.c, im.h, im.w);
    // TODO Fill this in
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(1, im.h, im.w);
    // TODO Fill this in
    return gray;
}

void shift_image(image im, int c, float v)
{
    // TODO Fill this in
}

void clamp_image(image im)
{
    // TODO Fill this in
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

void rgb_to_hsv(image im)
{
    // TODO Fill this in
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
}
