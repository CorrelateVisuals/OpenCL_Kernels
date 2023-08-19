# Box Blur
An OpenCL-based image blurring program that applies a box blur filter to input images. The code leverages the OpenCL framework to perform the blurring operation efficiently on GPU devices. The program loads an image file, processes it through a box blur kernel, and outputs the blurred image. The blur effect is achieved by averaging the pixel values within a specified neighborhood for each pixel, resulting in a smoother appearance. The code supports multiple passes of the box blur filter for enhanced blurring, and the output images are saved with a "_blur.jpg" suffix. The repository aims to provide a clear and streamlined implementation of the box blur algorithm using OpenCL, making it suitable for educational purposes and further development.

![Image](https://github.com/CorrelateVisuals/OpenCL_Methods/blob/main/OpenCL_Box_Blur/M20.PNG?raw=true)
Original © GRANTECAN S.A.
```
Object Name: 	M20, The Trifid Nebula
Telescope:	Grantecan / Nasmyth-B
Instrument:	OSIRIS
Filter:	    G (481nm), R (641nm), Z (970nm)
Color:	    Blue (G), Green (R), Red (Z)
Exposure:	5 x 10 secs (G and R), 2 x 10 secs (Z). R applied with luminance
Field of View:	Approx. 8.0' x 8.0'
Orientation:	North is up, East is left
Position:	RA(J2000.0) = 18h02m23s
Dec(J2000.0) = -23°01'50"
```
![Image](https://github.com/CorrelateVisuals/OpenCL_Methods/blob/main/OpenCL_Box_Blur/M20_blur.PNG?raw=true)
Greyscale © GRANTECAN S.A.
