#include <math.h>
#include "image.h"


/*
  Helpful Reference: https://courses.cs.vt.edu/~masc1044/L17-Rotation/ScalingNN.html 
*/

float nn_interpolate(image im, int c, float h, float w)
{
    return get_pixel(im, c, round(h), round(w));
} 


image nn_resize(image im, int h, int w)
{
    image im_resize = make_image(im.c, h, w); 
    /*
        - (Scale transformation) 1st we find by what to scale the co-ordinates: 
            - 7 pixels in target ~ 4 pixels in source image 
            - 1 pixwel in target ~ 4/7 pixels in source image
        - (Translation) 2nd we find by what to shift the images to ensure that the co-ordinates are same
            - 
    */  
    float scale_w, scale_h, displace_w, displace_h, new_x, new_y;
    scale_w = (float)im.w /w;
    scale_h = (float)im.h/h; 
    displace_w = -0.5 + 0.5*scale_w; 
    displace_h = -0.5 + 0.5*scale_h;   

    for (int c = 0; c < im_resize.c; ++c)
    {
        for (int x = 0; x < im_resize.h; ++x)
        {
            for (int y = 0; y < im_resize.w; ++y)
            { 
                new_x = x*scale_h + displace_h; 
                new_y = y*scale_w + displace_w; 
                set_pixel(im_resize, c, x, y, nn_interpolate(im, c, new_x, new_y));
            }
        } 
    }
    return im_resize;
}

float bilinear_interpolate(image im, int c, float h, float w)
{
    float x = h; 
    float y = w; 
    // Calculating the co-rodinates; 
    int x1 = ceil(h);
    int x2 = floor(h);
    int y1 = ceil(w);
    int y2 = floor(w); 

    // Performing 1st linear interpolation for mid-points;
    // TODO: Solve the Black-Box
    float R1 = (((x2 - x) / (x2 - x1)) * get_pixel(im, c, x1, y1)) + (((x - x1) / (x2 - x1)) * get_pixel(im, c, x2, y1)); 
    float R2 = (((x2 - x) / (x2 - x1)) * get_pixel(im, c, x1, y2)) + (((x - x1) / (x2 - x1)) * get_pixel(im, c, x2, y2)); 

    // Performing 2nd linear interpolation for unknown pixel_value; 
    float P = (((y2 - y) / (y2 - y1)) * R1) + (((y - y1) / (y2 - y1)) * R2); 
    return P;
}

image bilinear_resize(image im, int h, int w)
{
    image im_resize = make_image(im.c, h, w);
    // TODO: Solve the Black-Box
    float scale_w, scale_h, displace_w, displace_h, new_x, new_y;
    scale_w = (float)im.w /w;
    scale_h = (float)im.h/h; 
    displace_w = -0.5 + 0.5*scale_w; 
    displace_h = -0.5 + 0.5*scale_h;

    for (int c = 0; c < im_resize.c; ++c)
    {
        for (int x = 0; x < im_resize.h; ++x)
        {
            for (int y = 0; y < im_resize.w; ++y)
            { 
                new_x = x*scale_h + displace_h; 
                new_y = y*scale_w + displace_w; 
                set_pixel(im_resize, c, x, y, bilinear_interpolate(im, c, new_x, new_y));
            }
        } 
    }
    return im_resize;
}
