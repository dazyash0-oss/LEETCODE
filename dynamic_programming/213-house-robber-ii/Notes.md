This C++ solution solves the **House Robber II** problem (LeetCode 213), where houses are arranged in a **circle**.

### Core Approach: Split into Two Linear Subproblems

Because the houses are arranged in a circle, robbing the first house means you cannot rob the last house, and vice versa.

1. **Break the Circle:** You reduce the circular problem into two standard linear **House Robber I** subproblems:
* **Option A:** Consider houses from index `0` to `n - 2` (excluding the last house).
* **Option B:** Consider houses from index `1` to `n - 1` (excluding the first house).


2. **Take the Maximum:** The answer is `max(Option A, Option B)`.
3. **Linear DP Optimization (`getMax`):** Tracks two values to achieve $O(1)$ space:
* `prevRob`: Maximum money robbed up to 2 houses ago.
* `maxRob`: Maximum money robbed up to 1 house ago.
* **State Transition:** $\text{temp} = \max(\text{maxRob}, \text{prevRob} + \text{nums}[i])$



---

### Complexity Breakdown

* **Time Complexity:** $O(N)$ — Iterates through the array twice.
* **Space Complexity:** $O(1)$ — Uses only two tracking variables instead of an extra DP table.

---

### House Robber Cheatsheet

| Problem Variant | Constraint | Key Logic / Formula | Space Complexity |
| --- | --- | --- | --- |
| **House Robber I** (Linear) | Cannot rob adjacent houses. | $dp[i] = \max(dp[i-1], dp[i-2] + \text{nums}[i])$ | $O(1)$ optimized |
| **House Robber II** (Circular) | House $0$ and House $N-1$ are adjacent. | $\max(\text{Rob}(0 \dots N-2), \text{Rob}(1 \dots N-1))$ | $O(1)$ optimized |
| **House Robber III** (Tree) | Houses are in a Binary Tree; cannot rob direct parent-child. | DFS returning pair: `{robThisNode, skipThisNode}` | $O(H)$ recursion stack |
