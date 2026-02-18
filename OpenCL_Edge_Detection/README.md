# OpenCL Edge Detection

An OpenCL-based edge detection program that identifies edges in images using configurable brightness thresholds. This implementation provides fine-grained control over feature detection by considering both upper and lower brightness limits.

## Description

This program uses GPU acceleration through OpenCL to detect edges in images. The algorithm analyzes pixel brightness and determines whether a pixel should be set to white or black to highlight or suppress specific features within the image. This approach is particularly useful for:

- **Astronomical imaging**: Highlighting nebula structures and stellar features
- **Scientific visualization**: Identifying boundaries and structures
- **Image analysis**: Extracting edge information for further processing

**Key Features:**
- GPU-accelerated edge detection
- Dual threshold control (upper and lower brightness)
- RGBA image format support
- Automatic output file generation with `_edge_detection.jpg` suffix

## Building

### Windows (Visual Studio)

1. Open `OpenCL_Edge_Detection.sln` in Visual Studio
2. Select your build configuration (Debug or Release)
3. Build the solution (F7 or Build > Build Solution)
4. The executable will be in `x64/Debug/` or `x64/Release/`

### Linux/macOS (Command Line)

```bash
# Compile
g++ -o edge_detection main.cpp STB_Image_Load.cpp STB_Image_Write.cpp -lOpenCL

# Or with explicit OpenCL paths
g++ -o edge_detection main.cpp STB_Image_Load.cpp STB_Image_Write.cpp \
    -I/path/to/opencl/include -L/path/to/opencl/lib -lOpenCL
```

## Usage

```bash
./OpenCL_Edge_Detection <input_image_path>
```

### Example

```bash
./OpenCL_Edge_Detection M61.PNG
```

This will create `M61_edge_detection.jpg` in the same directory.

### Supported Image Formats

**Input**: PNG, JPG, BMP, TGA, and other formats supported by STB Image  
**Output**: JPG format

## Algorithm Details

The edge detection algorithm works by:

1. **Brightness Calculation**: For each pixel, calculate average brightness from RGB values
2. **Threshold Comparison**: 
   - If brightness is above the upper threshold → Set pixel to white (edge detected)
   - If brightness is below the lower threshold → Set pixel to black (background)
   - Otherwise → Intermediate handling based on gradient

3. **Parallel Processing**: All pixels are processed simultaneously on the GPU

### Configuring Thresholds

The brightness thresholds can be adjusted in `main.cpp` before compilation. Look for threshold constants in the OpenCL kernel definition and modify as needed for your specific use case.

**Typical threshold values:**
- **High contrast images**: Lower threshold = 30, Upper threshold = 200
- **Low contrast images**: Lower threshold = 10, Upper threshold = 100
- **Astronomical images**: Lower threshold = 5, Upper threshold = 50

## Performance

Edge detection is a computationally simple operation that benefits significantly from GPU parallelization:

- **4K image (3840×2160)**: ~10-30ms on modern GPU
- **HD image (1920×1080)**: ~3-10ms on modern GPU
- **VGA image (640×480)**: ~1-2ms on modern GPU

GPU acceleration typically provides 20-100x speedup over CPU-based implementations.

## Example Images

### Original Image

![Image](https://github.com/CorrelateVisuals/OpenCL_Methods/blob/main/OpenCL_Edge_Detection/M61.PNG?raw=true)

**Image Credit**: © GRANTECAN S.A.

```
Object Name:    Messier 61 / NGC 4303
Telescope:      Grantecan / Cassegrain
Instrument:     OSIRIS (OSIRIS+)
Filter:         G (481nm), R (641nm), I (770 nm), Z (970 nm)
Color:          Blue (R), Green (G), Red (I+Z)
Exposure:       5 and 30 secs (G, R, I, Z)
Field of View:  Approx. 6' x 6'
Orientation:    North is up, East is left
Position:       RA(J2000.0) = 12h21m55s
                Dec(J2000.0) = 04°28'28"
Image processing: Carlos Luna
```

### After Edge Detection

![Image](https://github.com/CorrelateVisuals/OpenCL_Methods/blob/main/OpenCL_Edge_Detection/M61_edge_detection.PNG?raw=true)

**Result**: Edge detection applied © GRANTECAN S.A.

## Troubleshooting

### Common Issues

**"Usage" message displayed**
- Cause: No input file specified
- Solution: Provide an image file path as command-line argument

**Output image is entirely white or black**
- Cause: Threshold values may be inappropriate for your image
- Solution: Adjust threshold values in the code and recompile

**Program crashes or no output**
- Verify OpenCL device is available (use [OpenCL_Device_Information](../OpenCL_Device_Information))
- Check input image file exists and is readable
- Ensure sufficient GPU memory for the image

**Edges not clearly visible**
- Increase contrast between thresholds
- Try preprocessing the image (contrast adjustment, noise reduction)
- Experiment with different threshold combinations

## Use Cases

- **Astrophotography**: Highlighting stellar structures, nebulae boundaries
- **Medical Imaging**: Detecting tissue boundaries, anomalies
- **Object Detection**: Preprocessing for shape recognition
- **Scientific Analysis**: Boundary detection in microscopy, satellite imagery

## See Also

- [OpenCL_Box_Blur](../OpenCL_Box_Blur) - Image blurring implementation
- [OpenCL_Device_Information](../OpenCL_Device_Information) - Check OpenCL devices

