<h2><a href="https://leetcode.com/problems/permutations">Permutations</a></h2> <img src='https://img.shields.io/badge/Difficulty-Medium-orange' alt='Difficulty: Medium' /><hr><p>Given an array <code>nums</code> of distinct integers, return all the possible <span data-keyword="permutation-array">permutations</span>. You can return the answer in <strong>any order</strong>.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<pre><strong>Input:</strong> nums = [1,2,3]
<strong>Output:</strong> [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
</pre><p><strong class="example">Example 2:</strong></p>
<pre><strong>Input:</strong> nums = [0,1]
<strong>Output:</strong> [[0,1],[1,0]]
</pre><p><strong class="example">Example 3:</strong></p>
<pre><strong>Input:</strong> nums = [1]
<strong>Output:</strong> [[1]]
</pre>
<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= nums.length &lt;= 6</code></li>
	<li><code>-10 &lt;= nums[i] &lt;= 10</code></li>
	<li>All the integers of <code>nums</code> are <strong>unique</strong>.</li>
</ul>

---
---

**Core Concept**
This C++ algorithm solves the **Permutations** problem (generating all possible orderings of an array of distinct integers). It uses an **In-Place Swap Backtracking Pattern** to build permutations level-by-level without using extra memory for a "visited" array.

---

**Key Technical Takeaways (Study Notes)**

* **In-Place Permutation Strategy:** Instead of creating a new path array, the code reorders `nums` in place. The index `start` divides the array into two sections:
* Left of `start`: The fixed prefix built so far.
* `start` to end: The remaining candidate numbers available for the next slot.


* **The Swap-Backtracking Loop:**
1. **Swap (`swap(nums[start], nums[i])`):** Places candidate `nums[i]` into the current slot `start`.
2. **Recurse (`backtrack(..., start + 1, ...)`):** Fixes the current choice and moves to the next position.
3. **Un-swap (`swap(nums[start], nums[i])`):** Restores the original array order before the next loop iteration (backtracking).


* **Base Case:** When `start == nums.size()`, the current arrangement of `nums` is a complete, unique permutation, so it is copied into `res`.

---

**Step-by-Step Example Walkthrough**

Consider the following input:

* **Input Array (`nums`):** `[1, 2, 3]`

```
Step 1: Recursive Execution Tree
--------------------------------------------------
Root: start = 0, nums = [1, 2, 3]

1. Loop i = 0 (swap index 0 with 0 -> [1, 2, 3]):
   - Call backtrack(start = 1, nums = [1, 2, 3])
     - i = 1: swap index 1 with 1 -> [1, 2, 3]
       - Call backtrack(start = 2) -> i = 2: swap 2 with 2 -> start = 3 (Base Case! Save [1, 2, 3])
     - Backtrack (un-swap)
     - i = 2: swap index 1 with 2 -> [1, 3, 2]
       - Call backtrack(start = 2) -> start = 3 (Base Case! Save [1, 3, 2])
     - Backtrack (un-swap -> [1, 2, 3])

2. Loop i = 1 (swap index 0 with 1 -> [2, 1, 3]):
   - Call backtrack(start = 1, nums = [2, 1, 3])
     - Generates permutations starting with 2:
       -> Save [2, 1, 3]
       -> Save [2, 3, 1]
   - Backtrack (un-swap -> [1, 2, 3])

3. Loop i = 2 (swap index 0 with 2 -> [3, 2, 1]):
   - Call backtrack(start = 1, nums = [3, 2, 1])
     - Generates permutations starting with 3:
       -> Save [3, 2, 1]
       -> Save [3, 1, 2]
   - Backtrack (un-swap -> [1, 2, 3])

Result: [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 2, 1], [3, 1, 2]]

```

---

**Complexity Analysis**

* **Time Complexity:** $O(N \cdot N!)$, where $N$ is the number of elements. There are $N!$ total permutations, and copying each completed array of size $N$ into `res` takes $O(N)$ time.
* **Space Complexity:** $O(N)$ auxiliary space for the recursion call stack (depth of $N$). No extra array memory is used during element selection due to in-place swapping.
