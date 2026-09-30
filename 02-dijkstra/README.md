# Assignment 2: Dijkstra's Shortest Path Algorithm

## Objective

Find the shortest path between vertices in a weighted graph using **Dijkstra's Algorithm**.

## Requirements

- Represent a weighted graph.
- Accept/select a source vertex.
- Calculate the shortest distance from the source to every reachable vertex.
- Display the shortest distance and corresponding path.

## Implementation

### Graph Representation

The weighted graph uses an adjacency list where each edge stores a destination
vertex and a weight:

```cpp
std::unordered_map<
    std::string,
    std::vector<std::pair<std::string, long long>>
> adjList_;
```

### Algorithm

Dijkstra's algorithm uses a **min-priority queue** to always process the
closest unvisited vertex first:

1. Initialize distances: distance to source = 0, all others = ∞.
2. Push the source vertex into the priority queue.
3. While the queue is not empty:
   - Pop the vertex with the smallest distance.
   - For each neighbor, if a shorter path is found through the current vertex,
     update the distance and push to the queue.
4. Track predecessors to reconstruct paths.

### Key Functions

- `dijkstra()`: Computes shortest distances and predecessors.
- `reconstructPath()`: Builds the path from source to target using predecessors.

### Constraints

- **Edge weights must be non-negative.** Dijkstra's algorithm fails with
  negative weights. Negative edges are detected and rejected at insertion.
- **Unreachable vertices** are reported appropriately.

## Usage

```bash
g++ -std=c++17 -Wall -Wextra -o dijkstra main.cpp
./dijkstra
```

## Sample Graph (Indian Cities)

```
Kolkata ---13--- Delhi ---14--- Mumbai ---9--- Pune
     |                        |
     |18                      |8
     |                        |
Bangalore ---10--- Mumbai ---8--- Chennai
       \                    /
        \                  /
         \                /
          20             7
            \            /
             Chennai ---7--- Bangalore
```

### Example Output

```
Available cities/vertices:
  1. Kolkata
  2. Delhi
  3. Mumbai
  4. Pune
  5. Bangalore
  6. Chennai

Enter source vertex: Kolkata

Calculating shortest paths...

Shortest Distances from 'Kolkata':
Vertex          Distance        Path
------------------------------------------------------------
Kolkata         0               Kolkata
Delhi           13              Kolkata -> Delhi
Mumbai          18              Kolkata -> Mumbai
Pune            27              Kolkata -> Mumbai -> Pune
Bangalore       28              Kolkata -> Mumbai -> Bangalore
Chennai         35              Kolkata -> Mumbai -> Bangalore -> Chennai

Enter destination vertex: Pune

--- Shortest Path: Kolkata -> Pune ---
Path: Kolkata -> Mumbai -> Pune
Total Distance: 27
```

## Test Cases

| # | Description | Source | Destination | Expected |
|---|-------------|--------|-------------|----------|
| 1 | Simple connected weighted graph | Any | Any (reachable) | Correct shortest path |
| 2 | Multiple possible routes | Kolkata | Pune | Kolkata -> Mumbai -> Pune (27) |
| 3 | Unreachable destination | (add isolated vertex) | Isolated | "No path exists" |
| 4 | Negative edge input | Invalid | — | Error message, edge ignored |
| 5 | Same source and destination | Delhi | Delhi | Distance: 0 |

## Complexity Analysis

### Using Min-Priority Queue (Heap-based)

```
Time:  O((V + E) log V)
Space: O(V)
```

Where:
- `V` = number of vertices
- `E` = number of edges

The priority queue operations take O(log V) each. Each vertex is extracted
once, and each edge is relaxed at most once.

### Using Simple Array (No Priority Queue)

```
Time:  O(V²)
```

This simpler implementation (not used here) would be better for dense graphs
with small V, but the heap version is efficient for sparse graphs.

## Notes

- The algorithm uses `long long` to store distances, avoiding overflow for
  large graphs with many edges.
- `INF` is set to `LLONG_MAX` for unreachable vertices.
- If a path doesn't exist, `reconstructPath()` returns an empty vector.