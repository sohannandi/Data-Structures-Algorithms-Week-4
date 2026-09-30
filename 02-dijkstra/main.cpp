/**
 * Assignment 2: Dijkstra's Shortest Path Algorithm
 *
 * Finds the shortest path from a source vertex to every other vertex
 * in a weighted graph with non-negative edge weights.
 *
 * Uses an adjacency list with a min-priority queue for efficiency:
 *   Time:  O((V + E) log V)
 *   Space: O(V)
 *
 * Compile: g++ -std=c++17 -Wall -Wextra -o dijkstra main.cpp
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <limits>
#include <algorithm>
#include <iomanip>

// A large value representing "infinity" (unreachable).
const long long INF = std::numeric_limits<long long>::max();

// ---------------------------------------------------------------------------
// WeightedGraph class
//
// Represented as an adjacency list:
//   unordered_map<Vertex, vector<pair<Vertex, Weight>>>
// Each edge stores a destination vertex and a non-negative weight.
// ---------------------------------------------------------------------------
class WeightedGraph {
public:
    // Add a weighted edge. If undirected (default), add it in both directions.
    void addEdge(const std::string& from, const std::string& to,
                 long long weight, bool undirected = true) {
        if (weight < 0) {
            std::cerr << "Error: Dijkstra does not support negative edge weights.\n";
            std::cerr << "  Edge " << from << " -> " << to
                      << " with weight " << weight << " ignored.\n";
            return;
        }
        adjList_[from].emplace_back(to, weight);
        // Ensure both vertices exist in the map
        adjList_.try_emplace(to, std::vector<std::pair<std::string, long long>>{});
        if (undirected) {
            adjList_[to].emplace_back(from, weight);
        }
    }

    // Check if a vertex exists.
    bool hasVertex(const std::string& vertex) const {
        return adjList_.count(vertex) > 0;
    }

    // Get all vertex labels.
    std::vector<std::string> getVertices() const {
        std::vector<std::string> vertices;
        for (const auto& [vertex, _] : adjList_) {
            vertices.push_back(vertex);
        }
        return vertices;
    }

    // Print the adjacency list.
    void printAdjacencyList() const {
        std::cout << "Weighted Adjacency List:\n";
        for (const auto& [vertex, neighbors] : adjList_) {
            std::cout << "  " << vertex << " -> ";
            for (const auto& [dest, weight] : neighbors) {
                std::cout << "(" << dest << ", " << weight << ") ";
            }
            std::cout << "\n";
        }
    }

    // Get a reference to the adjacency list (for external use).
    const std::unordered_map<std::string,
        std::vector<std::pair<std::string, long long>>>& adjList() const {
        return adjList_;
    }

private:
    std::unordered_map<std::string,
        std::vector<std::pair<std::string, long long>>> adjList_;
};

// ---------------------------------------------------------------------------
// DijkstraResult
//
// Holds the output of Dijkstra's algorithm:
//   - distances: shortest distance from source to each vertex
//   - predecessors: previous vertex on the shortest path (for path reconstruction)
// ---------------------------------------------------------------------------
struct DijkstraResult {
    std::unordered_map<std::string, long long> distances;
    std::unordered_map<std::string, std::string> predecessors;
};

// ---------------------------------------------------------------------------
// Dijkstra's Algorithm
//
// Computes the shortest path from `source` to every reachable vertex in
// `graph`. Uses a min-priority queue (std::priority_queue with reversed
// ordering) to always expand the closest unvisited vertex.
//
// Returns a DijkstraResult containing distances and predecessors.
// ---------------------------------------------------------------------------
DijkstraResult dijkstra(const WeightedGraph& graph, const std::string& source) {
    DijkstraResult result;

    if (!graph.hasVertex(source)) {
        std::cerr << "Error: Source vertex '" << source << "' not found.\n";
        return result;
    }

    // Min-priority queue: (distance, vertex).
    // We use std::greater to get the smallest distance on top.
    using QueueItem = std::pair<long long, std::string>;
    std::priority_queue<QueueItem, std::vector<QueueItem>, std::greater<QueueItem>> pq;

    // Initialize: distance to source is 0, all others are infinity.
    result.distances[source] = 0;
    pq.push({0, source});

    // Track visited vertices to avoid reprocessing.
    std::unordered_set<std::string> visited;

    while (!pq.empty()) {
        auto [dist, current] = pq.top();
        pq.pop();

        // Skip if we've already found a shorter path to this vertex.
        if (visited.count(current)) {
            continue;
        }
        visited.insert(current);

        // Examine each neighbor of the current vertex.
        for (const auto& [neighbor, weight] : graph.adjList().at(current)) {
            if (visited.count(neighbor)) {
                continue;
            }

            long long newDist = dist + weight;
            // If we found a shorter path, update and enqueue.
            if (!result.distances.count(neighbor) || newDist < result.distances[neighbor]) {
                result.distances[neighbor] = newDist;
                result.predecessors[neighbor] = current;
                pq.push({newDist, neighbor});
            }
        }
    }

    return result;
}

// ---------------------------------------------------------------------------
// Reconstruct the shortest path from source to target using predecessors.
//
// Returns a vector of vertex labels in order from source to target.
// If no path exists, returns an empty vector.
// ---------------------------------------------------------------------------
std::vector<std::string> reconstructPath(const DijkstraResult& result,
                                         const std::string& source,
                                         const std::string& target) {
    std::vector<std::string> path;

    // If the target was never reached, there is no path.
    if (!result.distances.count(target)) {
        return path;
    }

    // Walk backwards from target to source using predecessors.
    std::string current = target;
    while (current != source) {
        path.push_back(current);
        if (!result.predecessors.count(current)) {
            // No predecessor means no path exists (shouldn't happen if target
            // was reached, but guard against infinite loops).
            return std::vector<std::string>();
        }
        current = result.predecessors.at(current);
    }
    path.push_back(source);

    // Reverse to get source -> target order.
    std::reverse(path.begin(), path.end());
    return path;
}

// ---------------------------------------------------------------------------
// Print all shortest distances and paths from the source.
// ---------------------------------------------------------------------------
void printAllDistances(const DijkstraResult& result,
                       const std::string& source,
                       const WeightedGraph& graph) {
    std::cout << "\n--- Shortest Distances from '" << source << "' ---\n";
    std::cout << std::left << std::setw(15) << "Vertex"
              << std::setw(15) << "Distance"
              << "Path\n";
    std::cout << std::string(60, '-') << "\n";

    for (const auto& [vertex, _] : graph.adjList()) {
        if (vertex == source) {
            std::cout << std::setw(15) << vertex
                      << std::setw(15) << "0"
                      << vertex << "\n";
            continue;
        }

        if (!result.distances.count(vertex)) {
            std::cout << std::setw(15) << vertex
                      << std::setw(15) << "Unreachable"
                      << "(no path)\n";
        } else {
            auto path = reconstructPath(result, source, vertex);
            std::cout << std::setw(15) << vertex
                      << std::setw(15) << result.distances.at(vertex);
            for (size_t i = 0; i < path.size(); ++i) {
                if (i > 0) std::cout << " -> ";
                std::cout << path[i];
            }
            std::cout << "\n";
        }
    }
}

// ---------------------------------------------------------------------------
// Build a sample weighted graph (Indian cities).
// ---------------------------------------------------------------------------
WeightedGraph buildSampleGraph() {
    WeightedGraph g;
    // Undirected weighted graph of Indian cities
    g.addEdge("Kolkata", "Delhi", 13);
    g.addEdge("Kolkata", "Mumbai", 18);
    g.addEdge("Delhi", "Mumbai", 14);
    g.addEdge("Delhi", "Pune", 15);
    g.addEdge("Mumbai", "Pune", 9);
    g.addEdge("Mumbai", "Bangalore", 10);
    g.addEdge("Pune", "Bangalore", 8);
    g.addEdge("Bangalore", "Chennai", 7);
    g.addEdge("Chennai", "Kolkata", 20);
    return g;
}

// ---------------------------------------------------------------------------
// Main
// ---------------------------------------------------------------------------
int main() {
    std::cout << "========================================\n";
    std::cout << "  Dijkstra's Shortest Path Algorithm\n";
    std::cout << "========================================\n\n";

    WeightedGraph graph = buildSampleGraph();

    // --- Display graph ---
    graph.printAdjacencyList();

    // --- List available vertices ---
    std::vector<std::string> vertices = graph.getVertices();
    std::cout << "\nAvailable cities/vertices:\n";
    for (size_t i = 0; i < vertices.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << vertices[i] << "\n";
    }

    // --- Select source ---
    std::string source;
    std::cout << "\nEnter source vertex: ";
    std::cin >> source;

    if (!graph.hasVertex(source)) {
        std::cerr << "Error: Source '" << source << "' is not a valid vertex.\n";
        return 1;
    }

    // --- Run Dijkstra ---
    std::cout << "\nCalculating shortest paths...\n";
    DijkstraResult result = dijkstra(graph, source);

    // --- Print all distances ---
    printAllDistances(result, source, graph);

    // --- Select destination ---
    std::string target;
    std::cout << "\nEnter destination vertex: ";
    std::cin >> target;

    if (!graph.hasVertex(target)) {
        std::cerr << "Error: Destination '" << target << "' is not a valid vertex.\n";
        return 1;
    }

    // --- Show shortest path to destination ---
    std::cout << "\n--- Shortest Path: " << source << " -> " << target << " ---\n";

    if (!result.distances.count(target)) {
        std::cout << "No path exists from '" << source << "' to '" << target << "'.\n";
    } else {
        auto path = reconstructPath(result, source, target);

        std::cout << "Path: ";
        for (size_t i = 0; i < path.size(); ++i) {
            if (i > 0) std::cout << " -> ";
            std::cout << path[i];
        }
        std::cout << "\n";
        std::cout << "Total Distance: " << result.distances.at(target) << "\n";
    }

    // --- Complexity ---
    std::cout << "\n--- Complexity ---\n";
    std::cout << "Time:  O((V + E) log V)\n";
    std::cout << "Space: O(V)\n";

    std::cout << "\n========================================\n";
    std::cout << "  Dijkstra Complete\n";
    std::cout << "========================================\n";

    return 0;
}
