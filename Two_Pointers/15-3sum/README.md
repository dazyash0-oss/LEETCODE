<h2><a href="https://leetcode.com/problems/3sum">3Sum</a></h2> <img src='https://img.shields.io/badge/Difficulty-Medium-orange' alt='Difficulty: Medium' /><hr><p>Given an integer array nums, return all the triplets <code>[nums[i], nums[j], nums[k]]</code> such that <code>i != j</code>, <code>i != k</code>, and <code>j != k</code>, and <code>nums[i] + nums[j] + nums[k] == 0</code>.</p>

<p>Notice that the solution set must not contain duplicate triplets.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> nums = [-1,0,1,2,-1,-4]
<strong>Output:</strong> [[-1,-1,2],[-1,0,1]]
<strong>Explanation:</strong> 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> nums = [0,1,1]
<strong>Output:</strong> []
<strong>Explanation:</strong> The only possible triplet does not sum up to 0.
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> nums = [0,0,0]
<strong>Output:</strong> [[0,0,0]]
<strong>Explanation:</strong> The only possible triplet sums up to 0.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>3 &lt;= nums.length &lt;= 3000</code></li>
	<li><code>-10<sup>5</sup> &lt;= nums[i] &lt;= 10<sup>5</sup></code></li>
</ul>

---
---

## The Approach

1. **Sort the Array:**
Sorting rearranges the elements in non-decreasing order. This allows us to use two pointers ($j$ and $k$) to shrink the search space based on whether our sum is too large or too small.
2. **Fix the First Element ($nums[i]$):**
Iterate through the array with index $i$. This element serves as the anchor for each potential triplet.
3. **Skip Outer Duplicates:**
If $nums[i]$ is identical to $nums[i-1]$, skip it (`continue`). This prevents finding duplicate triplets with the same starting value.
4. **Two-Pointer Search ($j$ and $k$):**
Set $j = i + 1$ (left pointer) and $k = \text{nums.size}() - 1$ (right pointer):
* **`total > 0`:** The sum is too large. Decrease $k$ to lower the sum.
* **`total < 0`:** The sum is too small. Increase $j$ to raise the sum.
* **`total == 0`:** You found a valid triplet! Push `{nums[i], nums[j], nums[k]}` into the results, increment $j$, and skip any identical subsequent elements for $j$ to prevent duplicate triplets.



---

## Complexity Analysis

### Time Complexity: $\mathcal{O}(N^2)$

* **Sorting:** Takes $\mathcal{O}(N \log N)$, where $N$ is the number of elements in `nums`.
* **Nested Loops:** The outer `for` loop runs $N$ times. For each iteration, the inner `while` loop moves $j$ and $k$ toward each other, doing at most $\mathcal{O}(N)$ operations in total across all pointer movements.
* **Overall:** $\mathcal{O}(N \log N) + \mathcal{O}(N^2) = \mathcal{O}(N^2)$.

### Space Complexity: $\mathcal{O}(1)$ or $\mathcal{O}(N)$

* **Auxiliary Space:** Ignoring the memory required for the output list `res`, the algorithm only uses a few integer variables (`i`, `j`, `k`, `total`), which is $\mathcal{O}(1)$ extra space.
* **Sorting Space:** Depending on the language implementation (C++ `std::sort` typically uses IntroSort), sorting may take $\mathcal{O}(\log N)$ stack space.

---

## Edge Case / Subtle Optimization Tip

Your current code works well, but there are two small enhancements worth keeping in mind:

1. **Early Termination (Optimization):**
Since the array is sorted, if $nums[i] > 0$, no three positive numbers can sum to `0`. You can safely break out of the outer loop early:
```cpp
if (nums[i] > 0) break;

```


2. **Pointer Boundary Safety:**
In your duplicate-skipping loop after finding a match:
```cpp
while (j < k && nums[j] == nums[j-1]) {
    j++;
}

```


Checking `j < k` first before indexing `nums[j]` prevents out-of-bounds access.
