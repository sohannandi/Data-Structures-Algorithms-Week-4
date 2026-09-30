# Mini Project: City Path Finder

## Objective

Build a small C++ application that models cities as graph nodes
and finds the shortest route between two cities using **Dijkstra's algorithm**.

## Core Concept

- **City = Node**
- **Road = Edge**
- **Road Distance = Edge Weight**

## Functional Requirements

1. Store a set of cities.
2. Store connections between cities.
3. Store a distance/weight for each connection.
4. Allow the user to select a source city.
5. Allow the user to select a destination city.
6. Find the shortest route.
7. Calculate the total route distance.
8. Display the route in the correct order.
9. Handle cases where no route exists.
10. Provide clear console output.

## Implementation

### Graph Representation

Cities are stored as string labels in an adjacency list:

```cpp
std::unordered_map<std::string, std::vector<std::pair<std::string, long long>>>
```

### Dijkstra's Algorithm

The `dijkstra()` function computes shortest distances from a source city.
The `reconstructPath()` function uses predecessor tracking to build
the actual route.

### Features

- **Input validation:** Checks if cities exist in the graph.
- **Same city:** Returns distance 0 if source == destination.
- **Disconnected cities:** Reports "No route exists" appropriately.
- **Negative weights:** Rejected at edge insertion.
- **All distances display:** Shows shortest distances from source to every city.

## Usage

```bash
g++ -std=c++17 -Wall -Wextra -o city-path main.cpp
./city-path
```

## Sample Output

```
========================================
      City Path Finder
========================================

Available Cities:
  1. Kolkata
  2. Delhi
  3. Mumbai
  4. Pune
  5. Bangalore
  6. Chennai
  7. Hyderabad
  8. Jaipur
  9. Ahmedabad
  10. Lucknow

Enter source city: Kolkata
Enter destination city: Pune

Calculating shortest route...

--- Shortest Path: Kolkata -> Pune ---
Shortest Route: Kolkata -> Mumbai -> Pune
Total Distance: 27 km

--- All Distances from 'Kolkata' ---
City                Distance    Route
----------------------------------------------------------------------
Kolkata             0           Kolkata
Delhi               13          Kolkata -> Delhi
Mumbai              18          Kolkata -> Mumbai
Pune                27          Kolkata -> Mumbai -> Pune
Bangalore           28          Kolkata -> Mumbai -> Bangalore
Chennai             35          Kolkata -> Mumbai -> Bangalore -> Chennai
Hyderabad           41          Kolkata -> Mumbai -> Bangalore -> Hyderabad
Jaipur              23          Kolkata -> Delhi -> Jaipur
Ahmedabad           35          Kolkata -> Delhi -> Jaipur -> Ahmedabad
Lucknow             21          Kolkata -> Delhi -> Lucknow

--- Complexity ---
Time:  O((V + E) log V)
Space: O(V)

========================================
  City Path Finder Complete
========================================
```

## Test Cases

| # | Description | Source | Destination | Expected |
|---|-------------|--------|-------------|----------|
| 1 | Direct route | Kolkata | Mumbai | Distance 18 |
| 2 | Multi-city route | Kolkata | Pune | Kolkata -> Mumbai -> Pune |
| 3 | Multiple possible routes | Delhi | Pune | Delhi -> Mumbai -> Pune |
| 4 | No available route | (isolated city) | Any | "No route exists" |
| 5 | Same city | Kolkata | Kolkata | Distance 0 |
| 6 | Invalid city | (non-existent) | Any | Error message |
| 7 | Negative distance | Any | Any | Error, edge ignored |

## Complexity Analysis

| Metric | Complexity |
|--------|------------|
| Time | O((V + E) log V) |
| Space | O(V) |

## Edge Cases Handled

- **Empty graph:** No cities to traverse.
- **Same source and destination:** Distance = 0.
- **No route:** "No route exists" message.
- **Invalid input:** Error message with available cities listed.
- **Negative weights:** Rejected at edge insertion.
