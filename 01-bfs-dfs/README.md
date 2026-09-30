# Assignment 1: BFS and DFS

## Objective

Implement **Breadth-First Search (BFS)** and **Depth-First Search (DFS)**
for a graph represented as an adjacency list.

## Requirements

- Represent the graph using an adjacency list.
- Accept a starting vertex.
- Perform BFS from the selected vertex.
- Perform DFS from the selected vertex.
- Display the traversal order.

## Implementation

### Graph Representation

The graph is stored as an adjacency list using:

```cpp
std::unordered_map<std::string, std::vector<std::string>> adjList_;
```

Vertices are labeled with string identifiers (e.g., `"A"`, `"B"`). Each
vertex maps to a list of its adjacent vertices. The graph supports both
**directed** and **undirected** edges.

### BFS (Breadth-First Search)

- Uses a `std::queue<std::string>`.
- Maintains a `std::unordered_set<std::string>` for visited vertices.
- Visits vertices level by level: all neighbors of a vertex are enqueued
  before any of their neighbors.

**Algorithm:**
1. Mark the start vertex as visited and enqueue it.
2. While the queue is not empty:
   - Dequeue a vertex and add it to the traversal order.
   - For each unvisited neighbor, mark it visited and enqueue it.

### DFS (Depth-First Search)

Two implementations are provided:

1. **Recursive DFS** — uses the call stack.
2. **Iterative DFS** — uses an explicit `std::stack<std::string>`.

Both maintain a visited set. DFS explores as far as possible down each
branch before backtracking.

**Algorithm (recursive):**
1. Mark the current vertex as visited and add it to the traversal order.
2. For each unvisited neighbor, recursively call DFS.

## Usage

```bash
g++ -std=c++17 -Wall -Wextra -o bfs-dfs main.cpp
./bfs-dfs
```

Select either a sample graph or build one interactively.

## Sample Graph

```
    A --- B --- E
    |     |
    D --- C
```

Expected output (starting from `A`):

```
BFS: A B D C E
DFS: A B C E D
```

*(Exact order depends on adjacency list storage order.)*

## Test Cases

| # | Description | Input |
|---|-------------|-------|
| 1 | Small connected graph | Sample graph, start `A` |
| 2 | Graph with multiple branches | Interactive graph with branching |
| 3 | Disconnected vertices | Vertex with no edges |
| 4 | Different starting vertices | Start from `B`, `C`, etc. |

## Complexity Analysis

| Metric | BFS | DFS |
|--------|-----|-----|
| **Time** | O(V + E) | O(V + E) |
| **Space** | O(V) | O(V) |

- `V` = number of vertices, `E` = number of edges.
- The queue/stack and visited set each store at most `V` vertices.
