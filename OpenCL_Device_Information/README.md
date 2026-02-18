# OpenCL Device Information

A utility tool for querying and displaying information about OpenCL-capable devices on your system. This program helps you discover available OpenCL platforms and devices, along with their capabilities and specifications.

## Description

This tool queries all OpenCL devices available on your system and displays detailed information about each one, including:

- **Device Name**: The name/model of the device
- **Vendor**: The manufacturer (e.g., Intel, NVIDIA, AMD)
- **Device Version**: OpenCL version supported by the device
- **Driver Version**: Version of the installed driver
- **Global Memory Size**: Total available device memory in bytes
- **Max Compute Units**: Number of parallel compute units

This information is essential for:
- Verifying OpenCL installation and device availability
- Understanding device capabilities before running OpenCL programs
- Debugging OpenCL application issues
- Selecting the appropriate device for your workload

## Building

### Windows (Visual Studio)

1. Open `OpenCL_Device_Information.sln` in Visual Studio
2. Select your build configuration (Debug or Release)
3. Build the solution (F7 or Build > Build Solution)
4. The executable will be created in `x64/Debug/` or `x64/Release/`

### Linux/macOS (Command Line)

```bash
# Compile
g++ -o device_info main.cpp -lOpenCL

# Or with explicit paths to OpenCL
g++ -o device_info main.cpp -I/path/to/opencl/include -L/path/to/opencl/lib -lOpenCL
```

## Usage

Simply run the executable without any arguments:

```bash
./OpenCL_Device_Information
```

### Example Output

```
Device 1:
Device Name: Intel(R) UHD Graphics 630
Vendor: Intel(R) Corporation
Device Version: OpenCL 3.0
Driver Version: 27.20.100.9466
Global Memory Size: 13476503552 bytes
Max Compute Units: 24

Device 2:
Device Name: Intel(R) Core(TM) i7-9750H CPU @ 2.60GHz
Vendor: Intel(R) Corporation
Device Version: OpenCL 2.1
Driver Version: 2021.13.11.0.23_042959
Global Memory Size: 16882147328 bytes
Max Compute Units: 12
```

## Troubleshooting

### No Devices Found

If the program displays no devices or crashes:

1. **Verify OpenCL Installation**: Ensure OpenCL runtime is installed
   - Windows: Usually installed with GPU drivers
   - Linux: Install OpenCL ICD loader and vendor-specific implementations
   - macOS: OpenCL is included with the OS

2. **Update GPU Drivers**: Outdated drivers may not expose OpenCL devices properly

3. **Check for Multiple Platforms**: The current implementation queries the first platform. Systems with multiple OpenCL implementations may require platform enumeration.

### Build Errors

- **Missing OpenCL headers**: Install OpenCL SDK or development packages
  - Ubuntu/Debian: `sudo apt-get install opencl-headers ocl-icd-opencl-dev`
  - Fedora: `sudo dnf install opencl-headers ocl-icd-devel`
  
- **Linker errors**: Ensure OpenCL library path is correct in your build configuration

## Technical Details

The program uses the OpenCL C API to:
1. Query available platforms using `clGetPlatformIDs()`
2. Enumerate devices on the first platform using `clGetDeviceIDs()`
3. Query device properties using `clGetDeviceInfo()`
4. Display formatted output for each device

## Use Cases

- **Pre-flight Check**: Run before executing other OpenCL programs to verify device availability
- **Device Selection**: Identify which devices are available for computation
- **Performance Planning**: Check memory and compute unit availability for workload planning
- **Cross-Platform Development**: Verify OpenCL setup on different systems

## See Also

- [OpenCL_Box_Blur](../OpenCL_Box_Blur) - Image processing example
- [OpenCL_Edge_Detection](../OpenCL_Edge_Detection) - Edge detection example
- [OpenCL_Graph_Traversal](../OpenCL_Graph_Traversal) - Graph algorithm example
