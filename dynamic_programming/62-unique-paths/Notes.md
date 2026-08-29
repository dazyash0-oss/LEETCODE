This code solves the **Unique Paths** problem using **Dynamic Programming with Space Optimization** in **$O(m \cdot n)$ time** and **$O(n)$ space**.

---

## Code Analysis & How It Works

1. **Base Case (`aboveRow(n, 1)`)**: Initialize a 1D vector representing the top row. Every cell in the first row and first column can only be reached in **1 way** (moving strictly right or strictly down).
2. **State Transition**: To reach cell `(row, col)`, a robot can only arrive from:
* **Left**: `currentRow[col - 1]`
* **Above**: `aboveRow[col]`
* **Formula**: `currentRow[col] = currentRow[col - 1] + aboveRow[col]`


3. **Space Optimization**: Instead of maintaining a full $m \times n$ 2D matrix, the code only keeps track of the previous row (`aboveRow`), updating it row by row.

---

## Space-Optimized Alternative (1D Vector In-Place)

You can optimize the space further to use a single 1D vector instead of two vectors (`aboveRow` and `currentRow`):

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);

        for (int row = 1; row < m; row++) {
            for (int col = 1; col < n; col++) {
                dp[col] += dp[col - 1]; // dp[col] is 'above', dp[col-1] is 'left'
            }
        }

        return dp[n - 1];
    }
};

```

---

## Combinatorics Alternative ($O(m)$ or $O(n)$ Time, $O(1)$ Space)

Since the robot must take exactly $(m - 1)$ down steps and $(n - 1)$ right steps (total $m + n - 2$ steps), this is a combinations problem: $\binom{m + n - 2}{m - 1}$.

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        long ans = 1;
        int totalSteps = m + n - 2;
        int k = min(m - 1, n - 1); // Minimize loop iterations

        for (int i = 1; i <= k; i++) {
            ans = ans * (totalSteps - k + i) / i;
        }

        return ans;
    }
};

```

---

## Unique Paths Cheat Sheet

### 1. Key Concepts

* **Recurrence Relation**:

$$dp[i][j] = dp[i-1][j] + dp[i][j-1]$$


* **Combinatorics Formula**:

$$\text{Unique Paths} = \binom{(m-1) + (n-1)}{m-1} = \frac{(m + n - 2)!}{(m - 1)! \cdot (n - 1)!}$$



### 2. Grid DP Variants Cheat Sheet

| Problem Variant | Recurrence Relation / Core Modification | Space Complexity |
| --- | --- | --- |
| **Standard Unique Paths** | `dp[j] += dp[j - 1]` | $O(n)$ |
| **Unique Paths II (Obstacles)** | If `grid[i][j] == 1` $\rightarrow$ `dp[j] = 0`; else standard transition | $O(n)$ |
| **Minimum Path Sum** | `dp[j] = grid[i][j] + min(dp[j], dp[j - 1])` | $O(n)$ |

### 3. Complexity Summary

* **DP Approach**: $O(m \cdot n)$ time, $O(n)$ auxiliary space.
* **Combinatorics Approach**: $O(\min(m, n))$ time, $O(1)$ space.
