#include <CL/cl.h>
#include <iostream>

void printDeviceProperties(cl_device_id device) {
  char name[1024];
  clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(name), name, NULL);

  cl_ulong totalGlobalMem, sharedMemPerBlock, totalConstMem;
  cl_uint regsPerBlock, warpSize, memPitch, maxThreadsPerBlock, major, minor,
      clockRate, textureAlignment, deviceOverlap, multiProcessorCount;
  size_t maxThreadsDim[3], maxGridSize[3], maxTexture1D, maxTexture2D[2],
      maxTexture3D[3];
  clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(totalGlobalMem),
                  &totalGlobalMem, NULL);
  clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(sharedMemPerBlock),
                  &sharedMemPerBlock, NULL);
  clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE,
                  sizeof(maxThreadsPerBlock), &maxThreadsPerBlock, NULL);
  clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(maxThreadsDim),
                  &maxThreadsDim, NULL);
  clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS,
                  sizeof(multiProcessorCount), &multiProcessorCount, NULL);

  std::cout << "Device Name: " << name << std::endl;
  std::cout << "Total Global Memory: " << totalGlobalMem << " bytes"
            << std::endl;
  std::cout << "Shared Memory Per Block: " << sharedMemPerBlock << " bytes"
            << std::endl;
}

int main() {
  cl_platform_id platform;
  clGetPlatformIDs(1, &platform, NULL);

  cl_device_id devices[10];
  cl_uint deviceCount;
  clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 10, devices, &deviceCount);

  for (cl_uint i = 0; i < deviceCount; i++) {
    printDeviceProperties(devices[i]);
    std::cout << std::endl;
  }

  return 0;
}
