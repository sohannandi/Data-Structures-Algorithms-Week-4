/**
 * Mini Project: City Path Finder
 *
 * Models cities as graph nodes and finds the shortest route
 * between two cities using Dijkstra's algorithm.
 *
 * City = Node
 * Road = Edge
 * Road Distance = Edge Weight
 *
 * Compile: g++ -std=c++17 -Wall -Wextra -o city-path main.cpp
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

// A large value representing "infinity" for unreachable cities.
const long long INF = std::numeric_limits<long long>::max();

// ===========================================================================
// CityGraph class
//
// Stores cities as nodes and roads as weighted edges.
// The graph is undirected by default (roads work both ways).
// ===========================================================================
class CityGraph {
public:
    // Add a city to the graph (no-op if already exists).
    void addCity(const std::string& city) {
        adjList_[city];  // Creates entry if not present.
    }

    // Add a road (edge) between two cities with a given distance.
    // Roads are undirected by default (bidirectional).
    void addRoad(const std::string& from, const std::string& to,
                  long long distance, bool undirected = true) {
        if (distance < 0) {
            std::cerr << "Error: Negative road distance ("
                      << distance << ") between " << from
                      << " and " << to << " is not allowed.\n";
            return;
        }
        adjList_[from].emplace_back(to, distance);
        if (undirected) {
            adjList_[to].emplace_back(from, distance);
        }
        // Ensure both cities exist.
        adjList_.try_emplace(to, std::vector<std::pair<std::string, long long>>{});
        adjList_.try_emplace(from, std::vector<std::pair<std::string, long long>>{});
    }

    // Check if a city exists.
    bool hasCity(const std::string& city) const {
        return adjList_.count(city) > 0;
    }

    // Return a list of all cities.
    std::vector<std::string> getCities() const {
        std::vector<std::string> cities;
        for (const auto& [city, _] : adjList_) {
            cities.push_back(city);
        }
        return cities;
    }

    // Print all cities.
    void printCities() const {
        std::cout << "Available Cities:\n";
        std::vector<std::string> cities = getCities();
        for (size_t i = 0; i < cities.size(); ++i) {
            std::cout << "  " << (i + 1) << ". " << cities[i] << "\n";
        }
    }

    // Print the adjacency list with distances.
    void printRoads() const {
        std::cout << "Road Map:\n";
        for (const auto& [city, neighbors] : adjList_) {
            for (const auto& [dest, dist] : neighbors) {
                std::cout << "  " << city << " --(" << dist
                          << " km)--> " << dest << "\n";
            }
        }
    }

    // Get a reference to the adjacency list (for Dijkstra).
    const std::unordered_map<std::string,
        std::vector<std::pair<std::string, long long>>>& adjList() const {
        return adjList_;
    }

private:
    std::unordered_map<std::string,
        std::vector<std::pair<std::string, long long>>> adjList_;
};

// ===========================================================================
// DijkstraResult
// ===========================================================================
struct DijkstraResult {
    std::unordered_map<std::string, long long> distances;
    std::unordered_map<std::string, std::string> predecessors;
};

// ===========================================================================
// Dijkstra's algorithm on the CityGraph.
//
// Returns shortest distances from source to all reachable cities
// and predecessor map for path reconstruction.
// ===========================================================================
DijkstraResult dijkstra(const CityGraph& graph, const std::string& source) {
    DijkstraResult result;

    if (!graph.hasCity(source)) {
        std::cerr << "Error: City '" << source << "' not found.\n";
        return result;
    }

    using QueueItem = std::pair<long long, std::string>;
    std::priority_queue<QueueItem, std::vector<QueueItem>,
                        std::greater<QueueItem>> pq;

    result.distances[source] = 0;
    pq.push({0, source});

    std::unordered_set<std::string> visited;

    while (!pq.empty()) {
        auto [dist, current] = pq.top();
        pq.pop();

        if (visited.count(current)) continue;
        visited.insert(current);

        for (const auto& [neighbor, weight] : graph.adjList().at(current)) {
            if (visited.count(neighbor)) continue;

            long long newDist = dist + weight;
            if (!result.distances.count(neighbor) || newDist < result.distances[neighbor]) {
                result.distances[neighbor] = newDist;
                result.predecessors[neighbor] = current;
                pq.push({newDist, neighbor});
            }
        }
    }

    return result;
}

// ===========================================================================
// Reconstruct the shortest path from source to target.
// ===========================================================================
std::vector<std::string> reconstructPath(const DijkstraResult& result,
                                            const std::string& source,
                                            const std::string& target) {
    std::vector<std::string> path;

    if (!result.distances.count(target)) {
        return path;
    }

    std::string current = target;
    while (current != source) {
        path.push_back(current);
        current = result.predecessors.at(current);
    }
    path.push_back(source);
    std::reverse(path.begin(), path.end());
    return path;
}

// ===========================================================================
// Build the sample city graph.
//
// Indian cities with realistic-ish road distances.
// ===========================================================================
CityGraph buildCityGraph() {
    CityGraph graph;

    // Add cities
    graph.addCity("Kolkata");
    graph.addCity("Delhi");
    graph.addCity("Mumbai");
    graph.addCity("Pune");
    graph.addCity("Bangalore");
    graph.addCity("Chennai");
    graph.addCity("Hyderabad");
    graph.addCity("Jaipur");
    graph.addCity("Ahmedabad");
    graph.addCity("Lucknow");

    // Add roads with distances (in km, approximate)
    // Main routes
    graph.addRoad("Kolkata", "Delhi", 13);
    graph.addRoad("Kolkata", "Mumbai", 18);
    graph.addRoad("Delhi", "Mumbai", 14);
    graph.addRoad("Delhi", "Pune", 15);
    graph.addRoad("Mumbai", "Pune", 9);
    graph.addRoad("Mumbai", "Bangalore", 10);
    graph.addRoad("Pune", "Bangalore", 8);
    graph.addRoad("Bangalore", "Chennai", 7);
    graph.addRoad("Chennai", "Kolkata", 20);

    // Additional connections
    graph.addRoad("Delhi", "Jaipur", 10);
    graph.addRoad("Jaipur", "Ahmedabad", 12);
    graph.addRoad("Ahmedabad", "Mumbai", 11);
    graph.addRoad("Delhi", "Lucknow", 7);
    graph.addRoad("Lucknow", "Kolkata", 14);
    graph.addRoad("Hyderabad", "Bangalore", 9);
    graph.addRoad("Hyderabad", "Chennai", 6);
    graph.addRoad("Hyderabad", "Mumbai", 16);

    return graph;
}

// ===========================================================================
// Display a route in a readable format.
// ===========================================================================
void displayRoute(const std::vector<std::string>& path,
                   long long totalDistance) {
    std::cout << "Shortest Route:\n";
    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0) std::cout << " -> ";
        std::cout << path[i];
    }
    std::cout << "\n";
    std::cout << "Total Distance: " << totalDistance << " km\n";
}

// ===========================================================================
// Main: interactive City Path Finder application.
// ===========================================================================
int main() {
    std::cout << "========================================\n";
    std::cout << "      City Path Finder\n";
    std::cout << "========================================\n\n";

    // --- Build the city graph ---
    CityGraph graph = buildCityGraph();

    // --- Display available cities ---
    graph.printCities();

    // --- Get source city ---
    std::string source;
    std::cout << "\nEnter source city: ";
    std::getline(std::cin, source);

    if (!graph.hasCity(source)) {
        std::cerr << "Error: City '" << source << "' not found.\n";
        std::cout << "Available cities are listed above.\n";
        return 1;
    }

    // --- Get destination city ---
    std::string destination;
    std::cout << "Enter destination city: ";
    std::getline(std::cin, destination);

    if (!graph.hasCity(destination)) {
        std::cerr << "Error: City '" << destination << "' not found.\n";
        std::cout << "Available cities are listed above.\n";
        return 1;
    }

    // --- Same city check ---
    if (source == destination) {
        std::cout << "\nSource and destination are the same city.\n";
        std::cout << "Shortest Route: " << source << "\n";
        std::cout << "Total Distance: 0 km\n";
        return 0;
    }

    // --- Run Dijkstra ---
    std::cout << "\nCalculating shortest route...\n";
    DijkstraResult result = dijkstra(graph, source);

    // --- Display result ---
    std::cout << "\n--- Shortest Path: " << source
              << " -> " << destination << " ---\n";

    if (!result.distances.count(destination)) {
        std::cout << "No route exists from '" << source
                  << "' to '" << destination << "'.\n";
        std::cout << "These cities are disconnected.\n";
    } else {
        auto path = reconstructPath(result, source, destination);
        displayRoute(path, result.distances.at(destination));
    }

    // --- Show all distances from source ---
    std::cout << "\n--- All Distances from '" << source << "' ---\n";
    std::cout << std::left << std::setw(18) << "City"
              << std::setw(12) << "Distance"
              << "Route\n";
    std::cout << std::string(70, '-') << "\n";

    for (const auto& [city, _] : graph.adjList()) {
        std::cout << std::setw(18) << city;
        if (!result.distances.count(city)) {
            std::cout << std::setw(12) << "Unreachable"
                      << "  (no route)\n";
        } else {
            std::cout << std::setw(12) << result.distances.at(city) << " km\n";
            std::cout << std::setw(22) << "" << "(route) ";
            auto path = reconstructPath(result, source, city);
            for (size_t i = 0; i < path.size(); ++i) {
                if (i > 0) std::cout << " -> ";
                std::cout << path[i];
            }
            std::cout << "\n";
        }
    }

    // --- Complexity ---
    std::cout << "\n--- Complexity ---\n";
    std::cout << "Time:  O((V + E) log V)\n";
    std::cout << "Space: O(V)\n";

    std::cout << "\n========================================\n";
    std::cout << "  City Path Finder Complete\n";
    std::cout << "========================================\n";

    return 0;
}
