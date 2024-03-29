#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#define TWOPI 6.2831853

void l1_normalize(image im)
{
    float sum =  0.0;
    float normalize = 0.0; 
    for (size_t c = 0; c < im.c; ++c)
    {
        for (size_t h = 0; h < im.h; ++h)
        {
            for (size_t w = 0; w < im.h; ++w)
            {
                sum = sum + get_pixel(im, c, h, w); 
            }
        }
    }
    normalize = (float)(1 / sum); 
    for (size_t c = 0; c < im.c; ++c)
    {
        for (size_t h = 0; h < im.h; ++h)
        {
            for (size_t w = 0; w < im.h; ++w)
            {
                set_pixel(im, c, h, w, (get_pixel(im, c, h, w)*normalize));
            }
        }
    } 
}

image make_box_filter(int w)
{
    image filter = make_image(1, w, w); 
    for (size_t c = 0; c < filter.c; ++c)
    {
        for (size_t h = 0; h < filter.h; ++h)
        {
            for (size_t w = 0; w < filter.w; ++w)
            {
                set_pixel(filter, c, h, w, 1.0); 
            }
        }
    }
    l1_normalize(filter); 
    return filter;
}

image convolve_image(image im, image filter, int preserve)
{
    // TODO
    return make_image(1,1,1);
}

image make_highpass_filter()
{
    // TODO
    return make_image(1,1,1);
}

image make_sharpen_filter()
{
    // TODO
    return make_image(1,1,1);
}

image make_emboss_filter()
{
    // TODO
    return make_image(1,1,1);
}

// Question 2.2.1: Which of these filters should we use preserve when we run our convolution and which ones should we not? Why?
// Answer: TODO

// Question 2.2.2: Do we have to do any post-processing for the above filters? Which ones and why?
// Answer: TODO

image make_gaussian_filter(float sigma)
{
    // TODO
    return make_image(1,1,1);
}

image add_image(image a, image b)
{
    // TODO
    return make_image(1,1,1);
}

image sub_image(image a, image b)
{
    // TODO
    return make_image(1,1,1);
}

image make_gx_filter()
{
    // TODO
    return make_image(1,1,1);
}

image make_gy_filter()
{
    // TODO
    return make_image(1,1,1);
}

void feature_normalize(image im)
{
    // TODO
}

image *sobel_image(image im)
{
    // TODO
    return calloc(2, sizeof(image));
}

image colorize_sobel(image im)
{
    // TODO
    return make_image(1,1,1);
}
