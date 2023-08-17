#include <CL/cl.h>
#include <iostream>
#include <string>

void printDeviceProperty(cl_device_id device,
                         cl_device_info property,
                         const std::string& propertyName) {
  size_t propertySize;
  clGetDeviceInfo(device, property, 0, NULL, &propertySize);

  char* propertyValue = new char[propertySize];
  clGetDeviceInfo(device, property, propertySize, propertyValue, NULL);

  std::cout << propertyName << ": " << propertyValue << std::endl;

  delete[] propertyValue;
}

void printDeviceProperties(cl_device_id device) {
  printDeviceProperty(device, CL_DEVICE_NAME, "Device Name");
  printDeviceProperty(device, CL_DEVICE_VENDOR, "Vendor");
  printDeviceProperty(device, CL_DEVICE_VERSION, "Device Version");
  printDeviceProperty(device, CL_DRIVER_VERSION, "Driver Version");

  cl_ulong globalMemSize;
  clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(globalMemSize),
                  &globalMemSize, NULL);
  std::cout << "Global Memory Size: " << globalMemSize << " bytes" << std::endl;

  cl_uint maxComputeUnits;
  clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(maxComputeUnits),
                  &maxComputeUnits, NULL);
  std::cout << "Max Compute Units: " << maxComputeUnits << std::endl;

  std::cout << std::endl;
}

int main() {
  cl_platform_id platform;
  clGetPlatformIDs(1, &platform, NULL);

  cl_device_id devices[10];
  cl_uint deviceCount;
  clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 10, devices, &deviceCount);

  for (cl_uint i = 0; i < deviceCount; i++) {
    std::cout << "Device " << i + 1 << ":" << std::endl;
    printDeviceProperties(devices[i]);
  }

  return 0;
}
