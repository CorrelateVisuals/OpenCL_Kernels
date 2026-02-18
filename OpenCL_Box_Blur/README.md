# OpenCL Box Blur

An OpenCL-based image blurring program that applies a box blur filter to input images using GPU acceleration.

## Description

This program leverages the OpenCL framework to perform blurring operations efficiently on GPU devices. The blur effect is achieved by averaging the pixel values within a 3x3 neighborhood for each pixel, resulting in a smoother appearance. The implementation supports multiple passes of the box blur filter for enhanced blurring effects.

**Key Features:**
- GPU-accelerated box blur using OpenCL
- RGBA image format support with alpha channel preservation
- Multiple blur passes (configurable via `numPasses` constant)
- Automatic output file generation with `_blur.jpg` suffix

## Building

### Windows (Visual Studio)

1. Open `OpenCL_Box_Blur.sln` in Visual Studio
2. Select your build configuration (Debug or Release)
3. Build the solution (F7 or Build > Build Solution)
4. The executable will be in `x64/Debug/` or `x64/Release/`

### Linux/macOS (Command Line)

```bash
# Compile
g++ -o box_blur main.cpp STB_Image_Load.cpp STB_Image_Write.cpp -lOpenCL

# Or with explicit OpenCL paths
g++ -o box_blur main.cpp STB_Image_Load.cpp STB_Image_Write.cpp \
    -I/path/to/opencl/include -L/path/to/opencl/lib -lOpenCL
```

## Usage

```bash
./OpenCL_Box_Blur <input_image_path>
```

### Example

```bash
./OpenCL_Box_Blur M20.PNG
```

This will create `M20_blur.jpg` in the same directory.

### Supported Image Formats

**Input**: PNG, JPG, BMP, TGA, and other formats supported by STB Image
**Output**: JPG format

### Configuring Blur Intensity

The number of blur passes is set at compile time via the `numPasses` constant in `main.cpp`:

```cpp
const int numPasses = 100;  // Adjust this value for more/less blur
```

- **Low values (1-10)**: Subtle blur, preserves detail
- **Medium values (10-50)**: Moderate blur
- **High values (50-200)**: Heavy blur, significant smoothing

Recompile after changing this value.

## Algorithm Details

The box blur algorithm works by:

1. For each pixel in the image:
   - Sum the RGB values of the pixel and its 8 neighbors (3x3 kernel)
   - Divide by the count of valid neighbors
   - Write the averaged value to the output

2. Multiple passes:
   - The output of one pass becomes the input for the next
   - Each pass further smooths the image

The OpenCL kernel executes in parallel across all pixels, providing significant speedup compared to CPU-based implementations.

## Performance

Approximate processing times (depends on hardware and image size):

- **4K image (3840×2160)**: ~50-200ms per pass on modern GPU
- **HD image (1920×1080)**: ~15-50ms per pass on modern GPU
- **VGA image (640×480)**: ~2-5ms per pass on modern GPU

For 100 passes, multiply accordingly. GPU acceleration provides 10-100x speedup over CPU implementations.

## Example Images

### Original Image

![Image](https://github.com/CorrelateVisuals/OpenCL_Methods/blob/main/OpenCL_Box_Blur/M20.PNG?raw=true)

**Image Credit**: © GRANTECAN S.A.

```
Object Name:    M20, The Trifid Nebula
Telescope:      Grantecan / Nasmyth-B
Instrument:     OSIRIS
Filter:         G (481nm), R (641nm), Z (970nm)
Color:          Blue (G), Green (R), Red (Z)
Exposure:       5 x 10 secs (G and R), 2 x 10 secs (Z). R applied with luminance
Field of View:  Approx. 8.0' x 8.0'
Orientation:    North is up, East is left
Position:       RA(J2000.0) = 18h02m23s
                Dec(J2000.0) = -23°01'50"
```

### After 100 Blur Passes

![Image](https://github.com/CorrelateVisuals/OpenCL_Methods/blob/main/OpenCL_Box_Blur/M20_blur.PNG?raw=true)

**Result**: Blurred with 100 passes © GRANTECAN S.A.

## Troubleshooting

### Common Issues

**"Usage: Image Box Blur <filename>"**
- Cause: No input file specified
- Solution: Provide an image file path as argument

**Program crashes or no output file**
- Verify OpenCL device is available (use [OpenCL_Device_Information](../OpenCL_Device_Information))
- Check input image file exists and is readable
- Ensure sufficient GPU memory for the image size

**Poor performance**
- Check if OpenCL is using GPU vs CPU (CPU fallback is much slower)
- Reduce number of passes for faster results
- Consider resizing very large images before processing

## See Also

- [OpenCL_Edge_Detection](../OpenCL_Edge_Detection) - Edge detection implementation
- [OpenCL_Device_Information](../OpenCL_Device_Information) - Check OpenCL devices

