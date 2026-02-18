# OpenCL Graph Traversal

A parallel Breadth-First Search (BFS) implementation using OpenCL for efficient graph traversal on GPU devices.

## Description

This program demonstrates how to leverage OpenCL for parallel graph algorithms. It implements Breadth-First Search (BFS) traversal on a graph represented by an adjacency matrix, utilizing the GPU to explore multiple nodes simultaneously.

**Key Features:**
- Parallel BFS traversal using OpenCL
- Adjacency matrix-based graph representation
- Efficient for large-scale graph processing
- Example graph included for demonstration

## Algorithm Overview

Breadth-First Search is a fundamental graph traversal algorithm that:
1. Starts from a source node
2. Explores all neighbors at the current depth before moving to the next level
3. Marks nodes as visited to avoid cycles

The OpenCL implementation parallelizes the exploration of nodes at each BFS level, providing significant speedup for large graphs.

## Building

### Windows (Visual Studio)

1. Open `OpenCL_Graph_Traversel.sln` in Visual Studio
2. Select your build configuration (Debug or Release)
3. Build the solution (F7 or Build > Build Solution)
4. The executable will be in `x64/Debug/` or `x64/Release/`

### Linux/macOS (Command Line)

```bash
# Compile
g++ -o graph_traversal main.cpp -lOpenCL

# Or with explicit OpenCL paths
g++ -o graph_traversal main.cpp \
    -I/path/to/opencl/include -L/path/to/opencl/lib -lOpenCL
```

## Usage

The program runs without command-line arguments and uses a predefined graph:

```bash
./OpenCL_Graph_Traversel
```

### Example Output

```
BFS Traversal Order:
Node 0
Node 1
Node 2
Node 3
Node 4
Node 5
...
```

The output shows the order in which nodes are visited during BFS traversal from the starting node.

## Modifying the Graph

To use your own graph, modify the adjacency matrix in `main.cpp`:

```cpp
// Example: Graph with 4 nodes
int numNodes = 4;
int adjacencyMatrix[] = {
    0, 1, 1, 0,  // Node 0 connects to nodes 1, 2
    1, 0, 0, 1,  // Node 1 connects to nodes 0, 3
    1, 0, 0, 1,  // Node 2 connects to nodes 0, 3
    0, 1, 1, 0   // Node 3 connects to nodes 1, 2
};
```

**Matrix format:**
- Value `1` at position `[i][j]` means edge exists from node `i` to node `j`
- Value `0` means no edge
- For undirected graphs, the matrix should be symmetric

## Performance Characteristics

BFS performance depends on:
- **Graph size**: Number of nodes and edges
- **Graph density**: Sparse vs. dense graphs
- **GPU characteristics**: Memory bandwidth and compute units

**Typical performance:**
- **Small graphs (< 1000 nodes)**: May be faster on CPU due to overhead
- **Medium graphs (1000-10000 nodes)**: 5-20x speedup on GPU
- **Large graphs (> 10000 nodes)**: 20-100x speedup on GPU

The parallel implementation excels with dense graphs where many nodes can be processed simultaneously at each BFS level.

## Algorithm Details

### BFS Kernel Operation

The OpenCL kernel performs the following steps:

1. **Initialization**: Mark starting node as visited
2. **Level Expansion**: For each BFS level:
   - Process all nodes in current frontier in parallel
   - Check each node's neighbors
   - Add unvisited neighbors to next frontier
   - Mark newly discovered nodes as visited
3. **Termination**: Stop when no new nodes are discovered

### Data Structures

- **Adjacency Matrix**: 2D array representing graph structure
- **Visited Array**: Tracks which nodes have been visited
- **Frontier Arrays**: Current and next level nodes to process
- **Distance Array**: (Optional) Stores distance from source node

## Use Cases

- **Social Network Analysis**: Finding connections, shortest paths
- **Route Planning**: Navigation and pathfinding
- **Network Analysis**: Analyzing connectivity in computer networks
- **Web Crawling**: Traversing link structures
- **Dependency Resolution**: Build systems, package managers

## Extending the Implementation

### Adding Distance Tracking

To track the distance (number of edges) from the source to each node:

1. Add a distance array
2. Update distances when marking nodes as visited
3. Output distances along with traversal order

### Converting to Dijkstra's Algorithm

The BFS structure can be extended to Dijkstra's shortest path algorithm by:
- Adding edge weights to the adjacency matrix
- Using a priority queue instead of simple FIFO frontier
- Updating distances based on edge weights

### Bidirectional BFS

For finding paths between two specific nodes:
- Run BFS from both source and target simultaneously
- Terminate when the frontiers meet
- Can provide ~2x speedup for pathfinding

## Troubleshooting

### Common Issues

**Program crashes or produces incorrect output**
- Verify adjacency matrix size matches `numNodes * numNodes`
- Check OpenCL device availability (use [OpenCL_Device_Information](../OpenCL_Device_Information))
- Ensure sufficient GPU memory for the graph size

**Poor performance**
- For small graphs, CPU might be faster due to GPU overhead
- Check if using GPU vs CPU fallback
- Consider using sparse matrix representation for very large sparse graphs

**Out of memory errors**
- Adjacency matrix size grows as O(n²), limiting graph size
- For large graphs, use adjacency list representation instead
- Consider graph partitioning for massive graphs

## See Also

- [OpenCL_Device_Information](../OpenCL_Device_Information) - Check OpenCL device capabilities
- [OpenCL Programming Guide](https://www.khronos.org/opencl/) - Official OpenCL documentation

