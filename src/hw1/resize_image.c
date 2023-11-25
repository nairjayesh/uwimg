#include <math.h>
#include "image.h"


/*

  Line of 0 - 4 pixels is scaled to
  Line of 0 - 10 pixels - but, what should the values of 0 - 10 pixel be?
  Target       Source
  0            0 
  1            1/10
  2            2/10 
  Reference: https://courses.cs.vt.edu/~masc1044/L17-Rotation/ScalingNN.html 
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
            - 1 pixel in target ~ 4/7 pixels in source image
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
    // TODO
    return 0;
}

image bilinear_resize(image im, int h, int w)
{
    // TODO
    return make_image(1,1,1); // <- probably delete this
}

