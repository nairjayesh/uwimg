* 27/11/2023 *



* 25/11/2023 *

I worked on the failing tests in NN_resize function. I suspected that the values that were getting updated, were not to the right pixel position as the NN_interpolation function worked, and passed all the tests. The problem was in assigning the values to the right pixels.

Right Pixels: Before starting on this, I was unaware of concept of *Affine Transformations* or the math behind different transformations. There were two key steps that were required. Previously, I scaled the image using the ratio:
- (float)(source_dimension)/(target_dimension) to find the factor by which
  to scale.
- then, I multiplied this with the current pixel value of the target_image while iterating over each pixel, and setting the values using the nn_interpolate function.
- ** Problem **: Tests didn't pass, there was another key factor - translating the pixel co-ordinates.

  *** CONFUSION ***
I donot fully understand how the translation / offset worked here - but as per the lecture - pixel co-ordinates actually start from (-0.5, -0.5) once they are scaled, instead of (0.0, 0.0)

Here's the equation I saw from a github repository:
    displace_w = -0.5 + 0.5*scale_w; 
    displace_h = -0.5 + 0.5*scale_h;   

-0.5, -0.5 are the start points for a pixel's stored data. 

***** NEED TO SOLVE FOR THIS UNKNOWN PIECE *****

// Experimented with opening for 100x scaling and windows says the file is curropted or format is not supported. - lol // 

Resources looked up:
- Affine Transformations;
  - LEIOS: https://www.youtube.com/watch?v=E3Phj6J287o
  - OpenCV: https://docs.opencv.org/4.x/d4/d61/tutorial_warp_affine.html
  - OpenCV Reources: https://docs.opencv.org/4.x/d7/da8/tutorial_table_of_content_imgproc.html
  - https://people.computing.clemson.edu/~dhouse/courses/401/notes/affines-matrices.pdf
- Lecture - Resizing: https://www.youtube.com/watch?v=hpqrDUuk7HY&t=3071s
https://courses.cs.vt.edu/~masc1044/L17-Rotation/ScalingNN.html

Nxt up: Bilinear Interpolation
- Requires more lookups than Nearest Neighbors's

Q's: What would the individual pixels - when zoomed upclose look like:
- NN: Square // Rectangle
- Bilinear: Star with 4 nodes
- Bicubic: More smoother

Resource: http://supercomputingblog.com/graphics/coding-bilinear-interpolation/





