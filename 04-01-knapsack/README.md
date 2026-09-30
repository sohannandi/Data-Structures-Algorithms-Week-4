# Assignment 4: 0/1 Knapsack using Dynamic Programming

## Objective

Implement the **0/1 Knapsack Problem using Dynamic Programming**.

## Problem Definition

Given:
- `n` items.
- Weight of every item.
- Value of every item.
- Maximum knapsack capacity `W`.

Determine the maximum total value that can be placed in the knapsack
without exceeding its capacity.

Each item can either be:
- Selected once, or
- Not selected.

An item cannot be selected more than once.

## Requirements

- Accept item weights.
- Accept item values.
- Accept the knapsack capacity.
- Build the DP solution.
- Calculate the maximum achievable value.
- Display the result clearly.
- (Optional) Reconstruct which items were selected.

## Implementation

### DP Table Definition

Define `dp[i][w]` as:
- `i` = number of items considered (first `i` items).
- `w` = current capacity.

`dp[i][w]` = maximum value achievable using the first `i` items
              with capacity exactly `w`.

### Recurrence Relation

For item `i` (1-indexed) with weight `wt[i-1]` and value `val[i-1]`:

```
if w < wt[i-1]:
    dp[i][w] = dp[i-1][w]                          // item doesn't fit
else:
    dp[i][w] = max(
        dp[i-1][w],                                // don't take item i
        val[i-1] + dp[i-1][w - wt[i-1]]            // take item i
    )
```

### Base Cases
- `dp[0][w] = 0` for all `w` (no items → zero value)
- `dp[i][0] = 0` for all `i` (zero capacity → zero value)

### Algorithm
1. Initialize a `(n+1) × (W+1)` DP table with zeros.
2. Fill the table row by row using the recurrence.
3. The answer is in `dp[n][W]`.
4. Reconstruct selected items by tracing backwards from `dp[n][W]`.

## Usage

```bash
g++ -std=c++17 -Wall -Wextra -o knapsack main.cpp
./knapsack
```

## Example from PRD

```
Weights: 2 3 4 5
Values:  3 4 5 6
Capacity: 5
```

**Output:**
```
Maximum Value: 7
Selected items: [0: w=2, v=3] [1: w=3, v=4]
```

Explanation: Select items 0 and 1 (weights 2+3=5, values 3+4=7).

## Test Cases

| # | Description | Weights | Values | Capacity | Expected Max Value |
|---|-------------|---------|--------|----------|---------------------|
| 1 | PRD Example | 2,3,4,5 | 3,4,5,6 | 5 | 7 |
| 2 | Empty items | — | — | any | 0 |
| 3 | Capacity 0 | any | any | 0 | 0 |
| 4 | Capacity too small | 5,6,7 | 10,12,14 | 4 | 0 |
| 5 | Capacity large | 1,2,3 | 6,10,12 | 100 | 28 (all items) |
| 6 | Single item fits | 5 | 10 | 10 | 10 |
| 7 | Single item too big | 5 | 10 | 4 | 0 |

## Complexity Analysis

Let `n` = number of items, `W` = knapsack capacity.

- **Time Complexity:** O(n × W)
  - We fill a table of size (n+1) × (W+1).
  - Each cell takes O(1) time to compute.

- **Space Complexity:** O(n × W)
  - The DP table stores (n+1) × (W+1) integers.
  - Can be optimized to O(W) by using two rows only (current and previous).

## Notes

- Weights and values are assumed to be non-negative integers.
- The solution returns both the maximum value and the list of
  selected item indices (via backtracking).
- For very large `W`, the space-optimized version (O(W) space)
  would be preferred.