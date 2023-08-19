#include <CL/opencl.h>
#include <iostream>

#include "STB_Image_Load.h"
#include "STB_Image_Write.h"

const char* EdgeDetection_OpenCL = R"(
    __kernel void edgeDetection(__global uchar* inputImageRGBA, __global uchar* outputImageRGBA, int width, int height) {
        int x = get_global_id(0);
        int y = get_global_id(1);

        if (x < width && y < height) {
            int rSum = 0, gSum = 0, bSum = 0;
            int count = 0;

            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        int pixelIndex = (ny * width + nx) * 4; 

                        rSum += inputImageRGBA[pixelIndex];
                        gSum += inputImageRGBA[pixelIndex + 1];
                        bSum += inputImageRGBA[pixelIndex + 2];
                        count++;
                    }
                }
            }

            int outputIndex = (y * width + x) * 4; 
            uchar avgBrightness = (uchar)((rSum + gSum + bSum) / (3 * count));
            uchar upperThreshold = (uchar)(255 * 0.7); 
            uchar lowerThreshold = (uchar)(255 * 0.5); 

            uchar whiteColor = 255;
            uchar blackColor = 0;

            uchar color = (avgBrightness >= lowerThreshold && avgBrightness <= upperThreshold) ? whiteColor : blackColor;

            outputImageRGBA[outputIndex] = color;
            outputImageRGBA[outputIndex + 1] = color;
            outputImageRGBA[outputIndex + 2] = color;
            outputImageRGBA[outputIndex + 3] = inputImageRGBA[outputIndex + 3]; 
        }
    }
)";

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Usage: Image Edge Detection <filename>" << std::endl;
    return -1;
  }

  int width, height;

  std::cout << "Loading image file ... ";
  unsigned char* imageData =
      stbi_load(argv[1], &width, &height, NULL, STBI_default);
  if (!imageData) {
    std::cout << "Failed to open \"" << argv[1] << "\"";
    return -1;
  }
  std::cout << "Done" << std::endl;

  cl_int err;

  cl_platform_id platform;
  err = clGetPlatformIDs(1, &platform, NULL);

  cl_device_id device;
  err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);

  cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
  cl_command_queue queue = clCreateCommandQueue(context, device, 0, &err);

  cl_program program =
      clCreateProgramWithSource(context, 1, &EdgeDetection_OpenCL, NULL, &err);
  err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);

  cl_kernel kernel = clCreateKernel(program, "edgeDetection", &err);

  size_t globalSize[2] = {static_cast<size_t>(width),
                          static_cast<size_t>(height)};

  cl_mem inputBuffer =
      clCreateBuffer(context, CL_MEM_READ_ONLY,
                     sizeof(cl_uchar4) * width * height, NULL, &err);
  cl_mem outputBuffer =
      clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                     sizeof(cl_uchar4) * width * height, NULL, &err);

  err = clEnqueueWriteBuffer(queue, inputBuffer, CL_TRUE, 0,
                             sizeof(cl_uchar4) * width * height, imageData, 0,
                             NULL, NULL);

  err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer);
  err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
  err = clSetKernelArg(kernel, 2, sizeof(int), &width);
  err = clSetKernelArg(kernel, 3, sizeof(int), &height);

  err = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, globalSize, NULL, 0,
                               NULL, NULL);
  err = clFinish(queue);

  unsigned char* outputImageData =
      new unsigned char[sizeof(cl_uchar4) * width * height];
  err = clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0,
                            sizeof(cl_uchar4) * width * height, outputImageData,
                            0, NULL, NULL);

  std::string fileNameOut = argv[1];
  std::string baseFileName =
      fileNameOut.substr(0, fileNameOut.find_last_of("."));
  std::string newFileName = baseFileName + "_edge_detection.PNG";
  stbi_write_png(newFileName.c_str(), width, height, 4, outputImageData,
                 sizeof(cl_uchar4) * width);

  clReleaseMemObject(inputBuffer);
  clReleaseMemObject(outputBuffer);
  clReleaseKernel(kernel);
  clReleaseProgram(program);
  clReleaseCommandQueue(queue);
  clReleaseContext(context);

  stbi_image_free(imageData);
  delete[] outputImageData;

  return 0;
}
