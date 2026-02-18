# OpenCL Kernels

A collection of OpenCL kernel implementations focused on image processing and parallel computing algorithms. This repository provides educational examples and practical demonstrations of OpenCL programming for GPU acceleration.

## Table of Contents

- [Overview](#overview)
- [Projects](#projects)
- [Prerequisites](#prerequisites)
- [Building and Installation](#building-and-installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## Overview

This repository contains multiple OpenCL-based projects demonstrating various algorithms optimized for parallel execution on GPU devices. Each project is self-contained with its own documentation and examples.

OpenCL (Open Computing Language) is a framework for writing programs that execute across heterogeneous platforms consisting of CPUs, GPUs, and other processors. These examples showcase how to leverage OpenCL for image processing and graph algorithms.

## Projects

### [OpenCL_Box_Blur](./OpenCL_Box_Blur)
An image blurring program that applies a box blur filter using GPU acceleration. Supports multiple passes for enhanced blurring effects.

**Features:**
- GPU-accelerated box blur algorithm
- Configurable number of blur passes
- RGBA image support with alpha channel preservation

### [OpenCL_Edge_Detection](./OpenCL_Edge_Detection)
Edge detection implementation with configurable brightness thresholds for fine-grained control over feature detection.

**Features:**
- Brightness threshold-based edge detection
- Preserves or suppresses features based on brightness characteristics
- Optimized for astronomical and scientific imaging

### [OpenCL_Graph_Traversal](./OpenCL_Graph_Traversal)
Parallel Breadth-First Search (BFS) implementation for graph traversal using OpenCL.

**Features:**
- Parallel BFS traversal on GPU
- Adjacency matrix-based graph representation
- Efficient for large-scale graph processing

### [OpenCL_Device_Information](./OpenCL_Device_Information)
Utility tool to query and display OpenCL device capabilities and properties.

**Features:**
- Lists all available OpenCL devices
- Displays device specifications (memory, compute units, etc.)
- Useful for debugging and hardware discovery

## Prerequisites

### Required Software
- **C++ Compiler**: MSVC (Visual Studio 2019+), GCC 7+, or Clang 10+
- **OpenCL SDK**: 
  - Intel OpenCL SDK, AMD APP SDK, or NVIDIA CUDA Toolkit
  - OpenCL headers and libraries (version 1.2 or higher)
- **CMake** (optional): For cross-platform builds (version 3.10+)

### Required Libraries
- **STB Image Library**: Already included in projects that require it
  - `stb_image.h` for image loading
  - `stb_image_write.h` for image writing

### Hardware Requirements
- OpenCL-compatible device (GPU, CPU, or accelerator)
- Minimum 2GB RAM
- For image processing projects: Additional memory based on image size

## Building and Installation

### Windows (Visual Studio)

Each project includes a Visual Studio solution file (`.sln`):

1. Open the project's `.sln` file in Visual Studio
2. Select your target configuration (Debug/Release)
3. Build the solution (F7 or Build > Build Solution)
4. The executable will be in `x64/Debug/` or `x64/Release/`

### Linux/macOS (Command Line)

For manual compilation:

```bash
# Navigate to project directory
cd OpenCL_Box_Blur

# Compile (example for Box Blur)
g++ -o box_blur main.cpp STB_Image_Load.cpp STB_Image_Write.cpp -lOpenCL -I/path/to/opencl/headers -L/path/to/opencl/libs

# Run
./box_blur image.png
```

**Note**: Adjust paths to OpenCL headers and libraries based on your installation.

### Using CMake (Cross-Platform)

While individual Visual Studio projects are provided, you can create a CMake build system if needed for cross-platform compilation.

## Usage

### General Pattern

Most image processing projects follow this usage pattern:

```bash
./program_name <input_image>
```

The processed image is saved with a descriptive suffix (e.g., `_blur.jpg`, `_edge_detection.png`).

### Examples

```bash
# Box Blur
./OpenCL_Box_Blur image.png
# Output: image_blur.jpg

# Edge Detection
./OpenCL_Edge_Detection photo.png
# Output: photo_edge_detection.jpg

# Device Information
./OpenCL_Device_Information
# Displays device information in console

# Graph Traversal
./OpenCL_Graph_Traversal
# Displays BFS traversal results in console
```

See individual project READMEs for specific usage details and parameters.

## Project Structure

```
OpenCL_Kernels/
├── README.md                          # This file
├── LICENSE                            # CC0 1.0 Universal License
├── CONTRIBUTING.md                    # Contribution guidelines
├── OpenCL_Box_Blur/                   # Box blur project
│   ├── README.md
│   ├── main.cpp
│   ├── STB_Image_Load.h/cpp
│   ├── STB_Image_Write.h/cpp
│   └── *.sln, *.vcxproj               # Visual Studio files
├── OpenCL_Edge_Detection/             # Edge detection project
│   ├── README.md
│   ├── main.cpp
│   └── ...
├── OpenCL_Graph_Traversal/            # Graph traversal project
│   ├── README.md
│   ├── main.cpp
│   └── ...
└── OpenCL_Device_Information/         # Device info utility
    ├── README.md
    ├── main.cpp
    └── ...
```

Each project directory is self-contained with its own source files, build configuration, and documentation.

## Contributing

Contributions are welcome! Please see [CONTRIBUTING.md](./CONTRIBUTING.md) for guidelines on:
- Reporting bugs
- Suggesting enhancements
- Submitting pull requests
- Code style conventions

## License

This project is licensed under the CC0 1.0 Universal License - see the [LICENSE](./LICENSE) file for details.

This means the code is in the public domain and you can use it freely for any purpose without attribution (though attribution is appreciated).

## Acknowledgments

- Sample images in the Box Blur and Edge Detection projects are courtesy of GRANTECAN S.A.
- STB Image libraries by Sean Barrett (Public Domain)
