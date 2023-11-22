#include <math.h>
#include "image.h"



float nn_interpolate(image im, int c, float h, float w)
{ 
    return get_pixel(im, c, round(h), round(w));
} 

// TODO: Bug in resize calculation, fix it - go over proper text's that explain the algorithm 

image nn_resize(image im, int h, int w)
{
    image im_resize = make_image(im.c, h, w); 
    float scale_h = im.h / h; 
    float scale_w = im.w / w; 
    for (size_t c = 0; c < im_resize.c; ++c)
    {
        for (size_t x = 0; x < im_resize.h; ++x)
        {
            for (size_t y = 0; y < im_resize.w; ++y)
            {
                set_pixel(im_resize, c, x, y, nn_interpolate(im, c, x*scale_h, y*scale_w));
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

