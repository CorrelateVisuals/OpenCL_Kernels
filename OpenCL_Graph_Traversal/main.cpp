
#pragma OPENCL EXTENSION CL_KHR_fp64 : enable
#include <CL/opencl.h>
#include <iostream>

#define MAX_NODES 10

const char* BFS_OpenCL = R"(
    __kernel void bfs(__global int* graph, __global int* visited, __global int* queue, int startNode, int numNodes) {
        int gid = get_global_id(0);
        
        if (gid < numNodes) {
            if (gid == startNode) {
                visited[gid] = 1;
                queue[0] = gid;
            }
            
            for (int i = 0; i < numNodes; ++i) {
                if (graph[gid * numNodes + i] && !visited[i]) {
                    visited[i] = 1;
                    int index = atomic_add(&queue[0], 1);
                    queue[index] = i;
                }
            }
        }
    }
)";

int main() {
  int graph[MAX_NODES][MAX_NODES] = {
      {0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 1, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  int numNodes = MAX_NODES;
  int startNode = 0;

  cl_int err;

  cl_platform_id platform;
  err = clGetPlatformIDs(1, &platform, NULL);

  cl_device_id device;
  err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);

  cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);

  cl_command_queue queue = clCreateCommandQueue(context, device, 0, &err);

  cl_program program =
      clCreateProgramWithSource(context, 1, &BFS_OpenCL, NULL, &err);
  err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);

  cl_kernel kernel = clCreateKernel(program, "bfs", &err);

  int visited[MAX_NODES] = {0};
  visited[startNode] = 1;

  int queueData[MAX_NODES] = {0};
  queueData[0] = startNode;

  cl_mem graphBuffer =
      clCreateBuffer(context, CL_MEM_READ_ONLY,
                     sizeof(int) * MAX_NODES * MAX_NODES, NULL, &err);
  cl_mem visitedBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE,
                                        sizeof(int) * MAX_NODES, NULL, &err);
  cl_mem queueBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE,
                                      sizeof(int) * MAX_NODES, NULL, &err);

  err = clEnqueueWriteBuffer(queue, graphBuffer, CL_TRUE, 0,
                             sizeof(int) * MAX_NODES * MAX_NODES, graph, 0,
                             NULL, NULL);
  err = clEnqueueWriteBuffer(queue, visitedBuffer, CL_TRUE, 0,
                             sizeof(int) * MAX_NODES, visited, 0, NULL, NULL);
  err = clEnqueueWriteBuffer(queue, queueBuffer, CL_TRUE, 0,
                             sizeof(int) * MAX_NODES, queueData, 0, NULL, NULL);

  err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &graphBuffer);
  err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &visitedBuffer);
  err = clSetKernelArg(kernel, 2, sizeof(cl_mem), &queueBuffer);
  err = clSetKernelArg(kernel, 3, sizeof(int), &startNode);
  err = clSetKernelArg(kernel, 4, sizeof(int), &numNodes);

  size_t globalSize = numNodes;
  err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0,
                               NULL, NULL);
  err = clFinish(queue);

  err = clEnqueueReadBuffer(queue, visitedBuffer, CL_TRUE, 0,
                            sizeof(int) * MAX_NODES, visited, 0, NULL, NULL);

  std::cout << "Visited nodes during BFS starting from node " << startNode
            << ": ";
  for (int i = 0; i < MAX_NODES; ++i) {
    if (visited[i])
      std::cout << i << " ";
  }
  std::cout << std::endl;

  clReleaseMemObject(graphBuffer);
  clReleaseMemObject(visitedBuffer);
  clReleaseMemObject(queueBuffer);

  clReleaseKernel(kernel);
  clReleaseProgram(program);
  clReleaseCommandQueue(queue);
  clReleaseContext(context);

  return 0;
}
