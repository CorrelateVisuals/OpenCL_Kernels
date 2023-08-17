#include <CL/cl.h>
#include <fstream>
#include <iostream>
#include <sstream>

std::string loadProgram(const std::string& filename) {
  std::ifstream file(filename);
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

int main() {
  cl_platform_id platform;
  clGetPlatformIDs(1, &platform, NULL);

  cl_device_id device;
  clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);

  cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
  cl_command_queue queue = clCreateCommandQueue(context, device, 0, NULL);

  std::string programSource = loadProgram("convolution.cl");
  const char* programCString = programSource.c_str();
  cl_program program =
      clCreateProgramWithSource(context, 1, &programCString, NULL, NULL);
  clBuildProgram(program, 1, &device, NULL, NULL, NULL);
  cl_kernel kernel = clCreateKernel(program, "convolution", NULL);

  float image[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  float kernelData[9] = {0, -1, 0, -1, 5, -1, 0, -1, 0};

  cl_mem imageBuffer =
      clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                     sizeof(float) * 9, image, NULL);
  cl_mem kernelBuffer =
      clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                     sizeof(float) * 9, kernelData, NULL);
  cl_mem resultBuffer =
      clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * 9, NULL, NULL);

  clSetKernelArg(kernel, 0, sizeof(cl_mem), &imageBuffer);
  clSetKernelArg(kernel, 1, sizeof(cl_mem), &kernelBuffer);
  clSetKernelArg(kernel, 2, sizeof(cl_mem), &resultBuffer);

  size_t globalWorkSize[1] = {9};
  clEnqueueNDRangeKernel(queue, kernel, 1, NULL, globalWorkSize, NULL, 0, NULL,
                         NULL);

  float result[9];
  clEnqueueReadBuffer(queue, resultBuffer, CL_TRUE, 0, sizeof(float) * 9,
                      result, 0, NULL, NULL);

  clReleaseMemObject(imageBuffer);
  clReleaseMemObject(kernelBuffer);
  clReleaseMemObject(resultBuffer);
  clReleaseKernel(kernel);
  clReleaseProgram(program);
  clReleaseCommandQueue(queue);
  clReleaseContext(context);

  for (int i = 0; i < 9; i++) {
    std::cout << result[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}
