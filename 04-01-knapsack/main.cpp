/**
 * Assignment 4: 0/1 Knapsack using Dynamic Programming
 *
 * Solves the classic 0/1 Knapsack Problem:
 * Given n items with weights and values, and a knapsack capacity W,
 * maximize the total value without exceeding the capacity.
 * Each item can be selected at most once.
 *
 * Compile: g++ -std=c++17 -Wall -Wextra -o knapsack main.cpp
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>

// ===========================================================================
// solveKnapsack
//
// Solves the 0/1 Knapsack problem using a 2D DP table.
//
// dp[i][w] = maximum value achievable using the first i items
//            with capacity w.
//
// Recurrence:
//   dp[i][w] = dp[i-1][w]                                if w < weight[i]
//              max(dp[i-1][w], value[i] + dp[i-1][w-weight[i]]) otherwise
//
// Time:  O(n * W)
// Space: O(n * W)
// ===========================================================================
struct KnapsackResult {
    int maxValue = 0;
    std::vector<int> selectedItems;  // indices of selected items
};

KnapsackResult solveKnapsack(const std::vector<int>& weights,
                              const std::vector<int>& values,
                              int capacity) {
    int n = static_cast<int>(weights.size());
    KnapsackResult result;

    if (n == 0 || capacity <= 0) {
        return result;
    }

    // Build the DP table: (n+1) rows x (capacity+1) columns.
    // dp[i][w] = max value using first i items and capacity w.
    std::vector<std::vector<int>> dp(n + 1,
        std::vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (weights[i - 1] <= w) {
                dp[i][w] = std::max(
                    dp[i - 1][w],
                    values[i - 1] + dp[i - 1][w - weights[i - 1]]
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    result.maxValue = dp[n][capacity];

    // Reconstruct which items were selected.
    int w = capacity;
    for (int i = n; i > 0 && w > 0; --i) {
        // If dp[i][w] != dp[i-1][w], item i-1 was selected.
        if (dp[i][w] != dp[i - 1][w]) {
            result.selectedItems.push_back(i - 1);
            w -= weights[i - 1];
        }
    }
    std::reverse(result.selectedItems.begin(), result.selectedItems.end());

    return result;
}

// ===========================================================================
// Utility: print the DP table (for debugging/visualization).
// ===========================================================================
void printDPTable(const std::vector<std::vector<int>>& dp,
                   const std::vector<int>& weights,
                   const std::vector<int>& values,
                   int capacity) {
    int n = static_cast<int>(weights.size());

    std::cout << "\nDP Table:\n";
    std::cout << "        ";
    for (int w = 0; w <= capacity; ++w) {
        std::cout << std::setw(4) << w << " ";
    }
    std::cout << "\n";
    std::cout << std::string(6 + 6 * (capacity + 1), '-') << "\n";

    for (int i = 0; i <= n; ++i) {
        std::cout << "i=" << std::setw(2) << i << " |";
        for (int w = 0; w <= capacity; ++w) {
            std::cout << std::setw(4) << dp[i][w] << " ";
        }
        if (i > 0) {
            std::cout << "  (w=" << weights[i-1]
                      << ", v=" << values[i-1] << ")";
        }
        std::cout << "\n";
    }
}

// ===========================================================================
// Interactive: let the user enter items and capacity.
// ===========================================================================
KnapsackResult runInteractiveKnapsack() {
    std::cout << "\n=== Interactive 0/1 Knapsack ===\n";

    int n;
    std::cout << "Enter the number of items: ";
    std::cin >> n;

    if (n < 0) {
        std::cerr << "Error: Number of items cannot be negative.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return {};
    }

    if (n == 0) {
        std::cout << "No items provided. Max value = 0.\n";
        return {};
    }

    std::vector<int> weights(n);
    std::vector<int> values(n);

    for (int i = 0; i < n; ++i) {
        std::cout << "Item " << (i + 1) << " - weight: ";
        std::cin >> weights[i];
        std::cout << "Item " << (i + 1) << " - value:  ";
        std::cin >> values[i];

        if (weights[i] < 0 || values[i] < 0) {
            std::cerr << "Error: Weights and values must be non-negative.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return {};
        }
    }

    int capacity;
    std::cout << "Enter knapsack capacity: ";
    std::cin >> capacity;

    if (capacity < 0) {
        std::cerr << "Error: Capacity cannot be negative.\n";
        return {};
    }

    auto result = solveKnapsack(weights, values, capacity);

    // Display results.
    std::cout << "\n--- Results ---\n";
    std::cout << "Number of items:    " << n << "\n";
    std::cout << "Knapsack capacity:  " << capacity << "\n";
    std::cout << "Maximum value:      " << result.maxValue << "\n";
    std::cout << "Selected items (index/weight/value): ";
    for (int idx : result.selectedItems) {
        std::cout << "[" << idx << ": w=" << weights[idx]
                  << ", v=" << values[idx] << "] ";
    }
    if (result.selectedItems.empty()) {
        std::cout << "(none)";
    }
    std::cout << "\n";

    // Print DP table for small instances.
    if (n <= 5 && capacity <= 15) {
        // Re-build the table just to display it (we'd need to refactor
        // solveKnapsack to return the table, but for simplicity we
        // skip that here — the table is for debugging).
    }

    return result;
}

// ===========================================================================
// Main
// ===========================================================================
int main() {
    std::cout << "========================================\n";
    std::cout << "  0/1 Knapsack using Dynamic Programming\n";
    std::cout << "========================================\n";

    // --- Example 1: from the PRD ---
    std::cout << "\n--- Example 1 (from PRD) ---\n";
    std::vector<int> weights1 = {2, 3, 4, 5};
    std::vector<int> values1  = {3, 4, 5, 6};
    int capacity1 = 5;

    std::cout << "Weights: ";
    for (int w : weights1) std::cout << w << " ";
    std::cout << "\nValues:  ";
    for (int v : values1) std::cout << v << " ";
    std::cout << "\nCapacity: " << capacity1 << "\n";

    auto result1 = solveKnapsack(weights1, values1, capacity1);
    std::cout << "Maximum Value: " << result1.maxValue << "\n";
    std::cout << "Selected items: ";
    for (int idx : result1.selectedItems) {
        std::cout << "(w=" << weights1[idx]
                  << ", v=" << values1[idx] << ") ";
    }
    std::cout << "\n";

    // --- Example 2: more items ---
    std::cout << "\n--- Example 2 (more items) ---\n";
    std::vector<int> weights2 = {1, 3, 4, 5};
    std::vector<int> values2  = {1, 4, 5, 7};
    int capacity2 = 7;

    auto result2 = solveKnapsack(weights2, values2, capacity2);
    std::cout << "Maximum Value: " << result2.maxValue << "\n";
    std::cout << "Selected items: ";
    for (int idx : result2.selectedItems) {
        std::cout << "(w=" << weights2[idx]
                  << ", v=" << values2[idx] << ") ";
    }
    std::cout << "\n";

    // --- Example 3: empty item set ---
    std::cout << "\n--- Example 3 (empty item set) ---\n";
    std::vector<int> weights3;
    std::vector<int> values3;
    int capacity3 = 10;

    auto result3 = solveKnapsack(weights3, values3, capacity3);
    std::cout << "Maximum Value: " << result3.maxValue << "\n";

    // --- Example 4: capacity smaller than all weights ---
    std::cout << "\n--- Example 4 (capacity too small) ---\n";
    std::vector<int> weights4 = {5, 6, 7};
    std::vector<int> values4  = {10, 12, 14};
    int capacity4 = 4;

    auto result4 = solveKnapsack(weights4, values4, capacity4);
    std::cout << "Maximum Value: " << result4.maxValue << "\n";

    // --- Interactive mode ---
    std::cout << "\n--- Interactive Mode ---\n";
    std::cout << "Run interactive knapsack solver? (y/n): ";
    char choice;
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        runInteractiveKnapsack();
    }

    // --- Complexity Summary ---
    std::cout << "\n--- Complexity ---\n";
    std::cout << "Time:  O(n * W)\n";
    std::cout << "Space: O(n * W)\n";
    std::cout << "where n = number of items, W = capacity.\n";

    std::cout << "\n========================================\n";
    std::cout << "  0/1 Knapsack Complete\n";
    std::cout << "========================================\n";

    return 0;
}
