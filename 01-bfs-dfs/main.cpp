/**
 * Assignment 1: Graph Traversal - BFS and DFS
 *
 * Demonstrates Breadth-First Search (BFS) and Depth-First Search (DFS)
 * on a graph represented as an adjacency list.
 *
 * BFS uses a queue and explores vertices level by level.
 * DFS uses recursion and explores as deep as possible before backtracking.
 *
 * Compile: g++ -std=c++17 -Wall -Wextra -o bfs-dfs main.cpp
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <limits>

// ---------------------------------------------------------------------------
// Graph class
//
// Represented as an adjacency list:
//   unordered_map<Vertex, vector<Vertex>>
// where Vertex is a string label (e.g. "A", "B").
// The graph stores edges and supports both directed and undirected graphs.
// ---------------------------------------------------------------------------
class Graph {
public:
    // Add an edge between two vertices.
    // If undirected is true (default), the edge is added in both directions.
    void addEdge(const std::string& from, const std::string& to,
                 bool undirected = true) {
        adjList_[from].push_back(to);
        // Ensure both vertices exist in the map even if they have no out-edges yet
        if (!adjList_.count(to)) {
            adjList_[to] = {};
        }
        if (!adjList_.count(from)) {
            adjList_[from] = {};
        }
        if (undirected) {
            adjList_[to].push_back(from);
        }
    }

    // Breadth-First Search from a starting vertex.
    // Returns the traversal order as a vector of vertex labels.
    std::vector<std::string> bfs(const std::string& start) const {
        std::vector<std::string> traversal;
        if (!adjList_.count(start)) {
            std::cerr << "Error: Starting vertex '" << start << "' not found.\n";
            return traversal;
        }

        std::unordered_set<std::string> visited;
        std::queue<std::string> q;

        q.push(start);
        visited.insert(start);

        while (!q.empty()) {
            std::string current = q.front();
            q.pop();
            traversal.push_back(current);

            // Visit all adjacent vertices that haven't been visited yet
            for (const std::string& neighbor : adjList_.at(current)) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }

        return traversal;
    }

    // Depth-First Search (recursive) from a starting vertex.
    // Returns the traversal order as a vector of vertex labels.
    std::vector<std::string> dfs(const std::string& start) const {
        std::vector<std::string> traversal;
        if (!adjList_.count(start)) {
            std::cerr << "Error: Starting vertex '" << start << "' not found.\n";
            return traversal;
        }

        std::unordered_set<std::string> visited;
        dfsHelper(start, visited, traversal);
        return traversal;
    }

    // Depth-First Search (iterative) using an explicit stack.
    // Returns the traversal order as a vector of vertex labels.
    std::vector<std::string> dfsIterative(const std::string& start) const {
        std::vector<std::string> traversal;
        if (!adjList_.count(start)) {
            std::cerr << "Error: Starting vertex '" << start << "' not found.\n";
            return traversal;
        }

        std::unordered_set<std::string> visited;
        std::stack<std::string> s;

        s.push(start);

        while (!s.empty()) {
            std::string current = s.top();
            s.pop();

            if (visited.count(current)) {
                continue;
            }

            visited.insert(current);
            traversal.push_back(current);

            // Push neighbors onto the stack in reverse order so that
            // they are visited in the same order as the recursive version
            const std::vector<std::string>& neighbors = adjList_.at(current);
            for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it) {
                if (!visited.count(*it)) {
                    s.push(*it);
                }
            }
        }

        return traversal;
    }

    // Print all vertices and their adjacency lists (for debugging/visualization).
    void printAdjacencyList() const {
        std::cout << "Adjacency List:\n";
        for (const auto& [vertex, neighbors] : adjList_) {
            std::cout << "  " << vertex << " -> ";
            if (neighbors.empty()) {
                std::cout << "(no neighbors)";
            }
            for (const std::string& neighbor : neighbors) {
                std::cout << neighbor << " ";
            }
            std::cout << "\n";
        }
    }

    // Check if a vertex exists in the graph.
    bool hasVertex(const std::string& vertex) const {
        return adjList_.count(vertex) > 0;
    }

    // Return a list of all vertex labels.
    std::vector<std::string> getVertices() const {
        std::vector<std::string> vertices;
        for (const auto& [vertex, _] : adjList_) {
            vertices.push_back(vertex);
        }
        return vertices;
    }

private:
    std::unordered_map<std::string, std::vector<std::string>> adjList_;

    // Recursive helper for DFS.
    void dfsHelper(const std::string& vertex,
                   std::unordered_set<std::string>& visited,
                   std::vector<std::string>& traversal) const {
        visited.insert(vertex);
        traversal.push_back(vertex);

        for (const std::string& neighbor : adjList_.at(vertex)) {
            if (!visited.count(neighbor)) {
                dfsHelper(neighbor, visited, traversal);
            }
        }
    }
};

// ---------------------------------------------------------------------------
// Utility: print a traversal result
// ---------------------------------------------------------------------------
void printTraversal(const std::string& label,
                    const std::vector<std::string>& traversal) {
    std::cout << label;
    if (traversal.empty()) {
        std::cout << "(empty)";
    }
    for (const std::string& vertex : traversal) {
        std::cout << " " << vertex;
    }
    std::cout << "\n";
}

// ---------------------------------------------------------------------------
// Build a sample graph for demonstration.
//
//     A --- B --- E
//     |     |
//     D --- C
//
// Starting from A, the expected outputs are:
//   BFS: A B D C E
//   DFS: A B C E D  (order depends on adjacency list ordering)
// ---------------------------------------------------------------------------
Graph buildSampleGraph() {
    Graph g;
    g.addEdge("A", "B");
    g.addEdge("A", "D");
    g.addEdge("B", "C");
    g.addEdge("B", "E");
    g.addEdge("C", "D");
    g.addEdge("C", "E");
    return g;
}

// ---------------------------------------------------------------------------
// Interactive mode: let the user build and traverse a graph.
// ---------------------------------------------------------------------------
Graph buildInteractiveGraph() {
    Graph g;

    std::cout << "\n=== Interactive Graph Builder ===\n";
    std::cout << "Enter the number of edges: ";
    int numEdges = 0;
    std::cin >> numEdges;

    if (numEdges < 0) {
        std::cerr << "Error: Number of edges cannot be negative.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return g;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "For each edge, enter: <source> <destination> "
                 "[d/u] (d=directed, u=undirected, default=u)\n";
    for (int i = 0; i < numEdges; ++i) {
        std::string from, to;
        char type = 'u';
        std::cout << "Edge " << (i + 1) << ": ";
        std::cin >> from >> to >> type;

        bool undirected = (type == 'u' || type == 'U' || type == 'U');
        g.addEdge(from, to, undirected);
    }

    return g;
}

// ---------------------------------------------------------------------------
// Main
// ---------------------------------------------------------------------------
int main() {
    std::cout << "========================================\n";
    std::cout << "  Graph Traversal: BFS and DFS\n";
    std::cout << "========================================\n\n";

    // --- Choose mode ---
    std::cout << "Select mode:\n";
    std::cout << "  1. Use sample graph\n";
    std::cout << "  2. Build a graph interactively\n";
    std::cout << "Enter choice (1 or 2): ";

    int choice = 0;
    std::cin >> choice;

    Graph graph = buildSampleGraph();

    if (choice == 2) {
        graph = buildInteractiveGraph();
    }

    if (graph.getVertices().empty()) {
        std::cout << "The graph is empty. Nothing to traverse.\n";
        return 0;
    }

    // --- Display graph ---
    std::cout << "\n--- Graph ---\n";
    graph.printAdjacencyList();

    // --- Choose starting vertex ---
    std::vector<std::string> vertices = graph.getVertices();
    std::cout << "\nAvailable vertices: ";
    for (const std::string& v : vertices) {
        std::cout << v << " ";
    }
    std::cout << "\n";

    std::string start;
    std::cout << "Enter starting vertex: ";
    std::cin >> start;

    if (!graph.hasVertex(start)) {
        std::cerr << "Error: Vertex '" << start << "' does not exist in the graph.\n";
        return 1;
    }

    // --- Run BFS ---
    std::cout << "\n--- BFS (Breadth-First Search) ---\n";
    auto bfsResult = graph.bfs(start);
    printTraversal("BFS:", bfsResult);

    // --- Run DFS (recursive) ---
    std::cout << "\n--- DFS (Depth-First Search, recursive) ---\n";
    auto dfsResult = graph.dfs(start);
    printTraversal("DFS:", dfsResult);

    // --- Run DFS (iterative) ---
    std::cout << "\n--- DFS (Depth-First Search, iterative) ---\n";
    auto dfsIterResult = graph.dfsIterative(start);
    printTraversal("DFS (iterative):", dfsIterResult);

    // --- Complexity summary ---
    std::cout << "\n--- Complexity ---\n";
    std::cout << "BFS  - Time: O(V + E), Space: O(V)\n";
    std::cout << "DFS  - Time: O(V + E), Space: O(V) [recursion stack]\n";

    std::cout << "\n========================================\n";
    std::cout << "  Graph Traversal Complete\n";
    std::cout << "========================================\n";

    return 0;
}
