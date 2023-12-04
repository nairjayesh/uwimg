* 4/12/2023 *

I implemented the box_filter and normalization funciton. Used the sum-based normalization.

- Thinking about convolution operations.
  - How to look around the different parts of the image grid - for the kernel and the source image?
  - How to set it for the target image?
  - How to loop over both kernel and target image - simultaneously?


* 28/11/2023 *

Why should the kernals be added upto 1: - Review the lecture once again.

- Edges and Features, lectures.

  - Cross-Correlation is the easier one to do - as the filter is in the
    "rigth position".
  - Convolution is the actual one in which you have to "flip" the kernel
    along vertical and horizontal directions - and then apply to the image.

Q1) What does that mean mathematically? Can I apply both and check the results and why is one more widely used in the industry than the other?

Q2) See - Mathematical properties of convolutions; Are convolutions the same size as the target image - size? // I don't think it's necesaary, as they can be used to smooth the images.

= Edges: 



* 27/11/2023 *

I worked on the Bilinear Interpolation - the way image outcome today was smooth - was good to see. All tests passed - atleast the one's defined by the lecturer; I have issues with two things:
  - Algorithm Black-Box:
    For Bilinear Algorithm, I understand the gist of it, performing two linear interpolations over the pixel values of nearest neightbors to get the final value: ** I donot yet understand the nitty-gritty of the equation **
    eg-1: x2 - x / x2 - x1 * (Pixel_AT (x1,y1)) - Why is the unknown value x
    subtracted from x2: How should I interpret it? And then multiplied by
    P_AT 1?
    
    Imagine; trying to find the weighted average - based on how far the point is from the last pixel:
    why is it divided by x2 - x1 -- I'm asking what are the properties of these funcitons here : why are they used?

    eg-1: Main reason why the tests are passing is because in the resize functions, the code is translating the image by some amount, as written in the below ** CONFUSION ** tag. This is the pain-point!


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





