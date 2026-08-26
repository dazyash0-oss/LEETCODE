This C++ code solves the **House Robber** problem using Dynamic Programming in $O(n)$ time and $O(n)$ space.

### Key Logic & Core Concept

The goal is to maximize the money robbed without alerting security by robbing two adjacent houses.

At each house `i`, you face a single decision:

1. **Skip house `i`:** Your total stays equal to the maximum robbed up to the previous house: `dp[i-1]`.
2. **Rob house `i`:** You add `nums[i]` to the maximum robbed up to house `i-2`: `nums[i] + dp[i-2]`.

**Recurrence Relation:**


$$dp[i] = \max(dp[i-1], \, nums[i] + dp[i-2])$$

---

### Code Execution Breakdown

```cpp
int n = nums.size();
if (n == 1) return nums[0]; // Base Case: Only 1 house, rob it.

```

1. **Base Cases (`dp[0]` and `dp[1]`):**
* `dp[0] = nums[0]`: For the first house, your best choice is to rob it.
* `dp[1] = max(nums[0], nums[1])`: For two houses, pick whichever has more money.


2. **DP Loop:**
* Loops from index `2` to `n - 1`, filling out `dp[i]` using the recurrence relation.


3. **Result:**
* `dp[n - 1]` holds the ultimate maximum loot possible across all `n` houses.



---

### Dynamic Programming Cheatsheet

| Metric | Details |
| --- | --- |
| **Problem Type** | 1D Dynamic Programming / Optimization |
| **State Definition** | `dp[i]` = Maximum money you can rob from houses `0` through `i` |
| **Base Cases** | `dp[0] = nums[0]`, `dp[1] = max(nums[0], nums[1])` |
| **State Transition** | `dp[i] = max(dp[i-1], nums[i] + dp[i-2])` |
| **Time Complexity** | **$O(n)$** — Single pass through array of length $n$ |
| **Space Complexity** | **$O(n)$** — Tabulation array of size $n$ |

---

### Space Optimization Tip ($O(1)$ Space)

Notice that computing `dp[i]` only depends on `dp[i-1]` and `dp[i-2]`. You can drop the vector entirely and track just two variables:

```cpp
int rob(vector<int>& nums) {
    int prev2 = 0, prev1 = 0;
    for (int num : nums) {
        int temp = max(prev1, num + prev2);
        prev2 = prev1;
        prev1 = temp;
    }
    return prev1;
}

```
