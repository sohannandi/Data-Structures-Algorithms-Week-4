/**
 * Assignment 3: Fibonacci using Dynamic Programming
 *
 * Implements three approaches to computing Fibonacci numbers:
 *   1. Naive recursive (exponential time) — for comparison.
 *   2. Memoization (top-down) — recursive with a cache.
 *   3. Tabulation (bottom-up) — iterative with a DP table.
 *
 * Compile: g++ -std=c++17 -Wall -Wextra -o fibonacci main.cpp
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <chrono>
#include <stdexcept>
#include <cstdint>

// ===========================================================================
// 1. Naive Recursive Fibonacci (no DP)
//
// This version recalculates the same sub-problems repeatedly, resulting
// in an exponential time complexity of O(2^n). It is only included for
// comparison purposes.
// ===========================================================================
int64_t fibNaive(int n) {
    if (n < 0) {
        throw std::invalid_argument("fib: n must be non-negative.");
    }
    if (n <= 1) return n;
    return fibNaive(n - 1) + fibNaive(n - 2);
}

// ===========================================================================
// 2. Fibonacci with Memoization (Top-Down)
//
// Recursion is used, but results are stored in a cache (unordered_map)
// so each sub-problem is computed only once.
//
// Time:  O(n)
// Space: O(n) — cache + recursion stack
// ===========================================================================
int64_t fibMemoHelper(int n, std::unordered_map<int, int64_t>& cache) {
    // Base cases
    if (n == 0) return 0;
    if (n == 1) return 1;

    // If we've already computed fib(n), return it from the cache.
    auto it = cache.find(n);
    if (it != cache.end()) {
        return it->second;
    }

    // Otherwise, compute recursively and store in the cache.
    int64_t result = fibMemoHelper(n - 1, cache)
                   + fibMemoHelper(n - 2, cache);
    cache[n] = result;
    return result;
}

int64_t fibMemoization(int n) {
    if (n < 0) {
        throw std::invalid_argument("fibMemoization: n must be non-negative.");
    }
    std::unordered_map<int, int64_t> cache;
    return fibMemoHelper(n, cache);
}

// ===========================================================================
// 3. Fibonacci with Tabulation (Bottom-Up)
//
// Iteratively builds the solution from the base cases upward, filling
// a DP array as we go.
//
// Time:  O(n)
// Space: O(n) for the DP array
//         (can be optimized to O(1) if only the last two values are kept)
// ===========================================================================
int64_t fibTabulation(int n) {
    if (n < 0) {
        throw std::invalid_argument("fibTabulation: n must be non-negative.");
    }
    if (n == 0) return 0;
    if (n == 1) return 1;

    std::vector<int64_t> dp(n + 1, 0);
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

// ===========================================================================
// Optimized Tabulation (O(1) space)
//
// Instead of storing the entire DP array, we only keep the last two
// values. This reduces space from O(n) to O(1).
// ===========================================================================
int64_t fibTabulationOptimized(int n) {
    if (n < 0) {
        throw std::invalid_argument("fibTabulationOptimized: n must be non-negative.");
    }
    if (n == 0) return 0;
    if (n == 1) return 1;

    int64_t prev2 = 0;  // dp[i-2]
    int64_t prev1 = 1;  // dp[i-1]

    for (int i = 2; i <= n; ++i) {
        int64_t current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return prev1;
}

// ===========================================================================
// Helper: measure execution time of a function call.
// ===========================================================================
template <typename Func>
auto measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    int64_t result = func();
    auto end = std::chrono::high_resolution_clock::now();
    double durationMs =
        std::chrono::duration<double, std::milli>(end - start).count();
    return std::make_pair(result, durationMs);
}

// ===========================================================================
// Display all three approaches side-by-side for a given n.
// ===========================================================================
void runComparison(int n) {
    std::cout << "\n--- fib(" << n << ") ---\n";

    // Naive (only for small n to avoid excessive runtime).
    if (n <= 40) {
        auto [resultNaive, timeNaive] = measureTime([n]() {
            return fibNaive(n);
        });
        std::cout << "Naive:       " << resultNaive
                  << "  (" << std::fixed << std::setprecision(3)
                  << timeNaive << " ms)\n";
    } else {
        std::cout << "Naive:       skipped (n > 40 too slow)\n";
    }

    // Memoization.
    auto [resultMemo, timeMemo] = measureTime([n]() {
        return fibMemoization(n);
    });
    std::cout << "Memoization: " << resultMemo
              << "  (" << std::fixed << std::setprecision(3)
              << timeMemo << " ms)\n";

    // Tabulation.
    auto [resultTab, timeTab] = measureTime([n]() {
        return fibTabulation(n);
    });
    std::cout << "Tabulation:  " << resultTab
              << "  (" << std::fixed << std::setprecision(3)
              << timeTab << " ms)\n";

    // Optimized tabulation (O(1) space).
    auto [resultOpt, timeOpt] = measureTime([n]() {
        return fibTabulationOptimized(n);
    });
    std::cout << "Tabulation(O(1)): " << resultOpt
              << "  (" << std::fixed << std::setprecision(3)
              << timeOpt << " ms)\n";
}

// ===========================================================================
// Main: test multiple Fibonacci values and compare the three approaches.
// ===========================================================================
int main() {
    std::cout << "========================================\n";
    std::cout << "  Fibonacci using Dynamic Programming\n";
    std::cout << "========================================\n";

    // --- Test with multiple values ---
    std::vector<int> testValues = {0, 1, 5, 10, 20, 30, 40};

    for (int n : testValues) {
        runComparison(n);
    }

    // --- Interactive mode ---
    std::cout << "\n--- Interactive Mode ---\n";
    std::cout << "Enter a value of n to compute fib(n) "
                 "(or -1 to quit): ";

    int n;
    while (std::cin >> n && n != -1) {
        if (n < 0) {
            std::cerr << "Error: n must be non-negative.\n";
        } else {
            try {
                auto [result, time] = measureTime([n]() {
                    return fibTabulation(n);
                });
                std::cout << "fib(" << n << ") = " << result
                          << "  (tabulation, "
                          << std::fixed << std::setprecision(3)
                          << time << " ms)\n";
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        }
        std::cout << "Enter n (or -1 to quit): ";
    }

    // --- Complexity Summary ---
    std::cout << "\n--- Complexity Analysis ---\n";
    std::cout << "Approach          Time        Space\n";
    std::cout << "---------------------------------------\n";
    std::cout << "Naive Recursive   O(2^n)      O(n) stack\n";
    std::cout << "Memoization       O(n)        O(n)\n";
    std::cout << "Tabulation        O(n)        O(n)\n";
    std::cout << "Tabulation (opt)  O(n)        O(1)\n";

    std::cout << "\n========================================\n";
    std::cout << "  Fibonacci Complete\n";
    std::cout << "========================================\n";

    return 0;
}
