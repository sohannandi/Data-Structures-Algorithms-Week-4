# Week 4 - Graphs & Dynamic Programming

**Week:** 4
**Primary Topics:** Graph Algorithms, Dynamic Programming
**Implementation Language:** C++ (C++17)

## Objective

This project implements fundamental **Graph Algorithms** and **Dynamic Programming (DP)**
concepts in C++, covering graph representation, traversal, shortest-path computation,
and classic DP problems. It culminates in a practical mini-project: the **City Path Finder**.

## Assignments Included

| # | Assignment | Description |
|---|-----------|-------------|
| 1 | BFS & DFS | Graph traversal using Breadth-First and Depth-First Search |
| 2 | Dijkstra | Shortest-path algorithm for weighted graphs |
| 3 | Fibonacci DP | Fibonacci via Memoization (top-down) and Tabulation (bottom-up) |
| 4 | 0/1 Knapsack | Classic DP optimization problem |
| 5 | City Path Finder | Mini-project applying Dijkstra to find the shortest route between cities |

## Technologies Used

- **Language:** C++17
- **Standard Library:** `<iostream>`, `<vector>`, `<queue>`, `<stack>`, `<unordered_map>`,
  `<unordered_set>`, `<limits>`, `<algorithm>`, `<string>`, `<iomanip>`

## Project Structure

```text
week-4/
├── README.md
├── 01-bfs-dfs/
│   ├── main.cpp
│   └── README.md
├── 02-dijkstra/
│   ├── main.cpp
│   └── README.md
├── 03-fibonacci-dp/
│   ├── main.cpp
│   └── README.md
├── 04-01-knapsack/
│   ├── main.cpp
│   └── README.md
└── 05-city-path-finder/
    ├── main.cpp
    └── README.md
```

## How to Compile & Run

Each assignment is a standalone program. Compile with any C++17-compatible compiler.

```bash
# Compile each assignment (from the week-4 directory)
g++ -std=c++17 -Wall -Wextra -o bfs-dfs      01-bfs-dfs/main.cpp
g++ -std=c++17 -Wall -Wextra -o dijkstra    02-dijkstra/main.cpp
g++ -std=c++17 -Wall -Wextra -o fibonacci   03-fibonacci-dp/main.cpp
g++ -std=c++17 -Wall -Wextra -o knapsack    04-01-knapsack/main.cpp
g++ -std=c++17 -WallWextra -o city-path     05-city-path-finder/main.cpp

# Run
./bfs-dfs
./dijkstra
./fibonacci
./knapsack
./city-path
```

> **On Windows (MSVC):** use `cl /std:c++17 main.cpp` or compile via your IDE.

## Example Outputs

### 1. BFS & DFS
```
BFS: A B C D E
DFS: A B D E C
```

### 2. Dijkstra
```
Shortest Path: Kolkata -> Mumbai -> Pune
Total Distance: 9 km
```

### 3. Fibonacci DP
```
Memoization  fib(20) = 6765  (time: 0.01 ms)
Tabulation   fib(20) = 6765  (time: 0.00 ms)
```

### 4. 0/1 Knapsack
```
Maximum Value: 7
Selected Items (value/weight): (3/2) (4/3)
```

### 5. City Path Finder
```
Available Cities:
1. Kolkata
2. Delhi
3. Mumbai
4. Pune

Enter source city: Kolkata
Enter destination city: Pune

Shortest Route: Kolkata -> Mumbai -> Pune
Total Distance: 9 km
```

## Complexity Analysis

| Algorithm | Time Complexity | Space Complexity |
|-----------|---------------|------------------|
| BFS | O(V + E) | O(V) |
| DFS | O(V + E) | O(V) (recursion stack) |
| Dijkstra (priority queue) | O((V + E) log V) | O(V) |
| Fibonacci - Memoization | O(n) | O(n) |
| Fibonacci - Tabulation | O(n) | O(n) — optimizable to O(1) |
| 0/1 Knapsack | O(n * W) | O(n * W) |

Where `V` = vertices, `E` = edges, `n` = items, `W` = knapsack capacity.

## Testing

Each program handles edge cases such as:
- Empty or disconnected graphs
- Unreachable destinations
- Invalid user input (negative weights, negative Fibonacci n, etc.)
- Same source and destination
- Capacity constraints (knapsack)

See each subdirectory's `README.md` for detailed test cases and complexity notes.

## Mini Project: City Path Finder

The **City Path Finder** ([05-city-path-finder/](05-city-path-finder/)) models a set of
Indian cities as nodes in a weighted graph, where roads between cities carry a
distance (edge weight). It uses **Dijkstra's algorithm** to compute and display the
shortest route between any two cities, including the total distance and the sequence
of cities visited.

See [05-city-path-finder/README.md](05-city-path-finder/README.md) for details.

## Development Order

Implemented in the order recommended by the PRD:

1. Graph Representation (shared concept)
2. BFS
3. DFS
4. Dijkstra
5. Fibonacci - Memoization
6. Fibonacci - Tabulation
7. 0/1 Knapsack
8. City Path Finder (integrates Dijkstra into a practical app)
9. Testing
10. Documentation
