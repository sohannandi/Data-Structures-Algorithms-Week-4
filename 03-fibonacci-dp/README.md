# Assignment 3: Fibonacci using Dynamic Programming

## Objective

Calculate Fibonacci numbers using two Dynamic Programming techniques:
1. **Memoization** (top-down recursive with cache)
2. **Tabulation** (bottom-up iterative)

## Requirements

- Use recursion with memoization.
- Use bottom-up tabulation.
- Compare with naive recursive approach.
- Document time and space complexity.

## Implementation

### 1. Naive Recursive Fibonacci (O(2^n))

```cpp
int64_t fibNaive(int n) {
    if (n <= 1) return n;
    return fibNaive(n - 1) + fibNaive(n - 2);
}
```

Recomputes the same sub-problems repeatedly. Exponential time.

### 2. Memoization (Top-Down, O(n))

```cpp
int64_t fibMemoization(int n) {
    unordered_map<int, int64_t> cache;
    return fibMemoHelper(n, cache);
}
```

- Recursive function that checks the cache before computing.
- Each sub-problem is computed only once.
- Cache stores `fib(k)` for each `k` computed.

### 3. Tabulation (Bottom-Up, O(n))

```cpp
int64_t fibTabulation(int n) {
    dp[0] = 0; dp[1] = 1;
    for i = 2..n: dp[i] = dp[i-1] + dp[i-2];
    return dp[n];
}
```

- Iterative approach that builds the solution from base cases.
- Fills a DP array from index 0 to n.

### 4. Optimized Tabulation (O(n) time, O(1) space)

Only keeps the last two values instead of the full DP array.

## Usage

```bash
g++ -std=c++17 -Wall -Wextra -o fibonacci main.cpp
./fibonacci
```

## Sample Output

```
--- fib(20) ---
Naive:       6765  (2.340 ms)
Memoization: 6765  (0.001 ms)
Tabulation:  6765  (0.000 ms)
Tabulation(O(1)): 6765  (0.000 ms)
```

## Test Cases

| n | Expected | Notes |
|---|----------|-------|
| 0 | 0 | Base case |
| 1 | 1 | Base case |
| 5 | 5 | |
| 10 | 55 | |
| 20 | 6765 | |
| -1 | Error | Invalid input |

## Complexity Analysis

| Approach | Time | Space |
|----------|------|-------|
| Naive Recursive | O(2^n) | O(n) call stack |
| Memoization | O(n) | O(n) cache + stack |
| Tabulation | O(n) | O(n) DP array |
| Tabulation (opt) | O(n) | O(1) |

## Comparison Summary

| Metric | Naive | Memoization | Tabulation |
|--------|-------|-------------|------------|
| Time | O(2^n) | O(n) | O(n) |
| Space | O(n) | O(n) | O(n) / O(1) |
| Overhead | None | Recursion | None |
| Clarity | Simple | Moderate | Simple |

- **Memoization** is top-down: starts with the problem and breaks
  it down, caching results along the way.
- **Tabulation** is bottom-up: starts with base cases and builds
  up to the solution.
- Both have linear time, but tabulation avoids recursion overhead.
