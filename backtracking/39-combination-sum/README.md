<h2><a href="https://leetcode.com/problems/combination-sum">Combination Sum</a></h2> <img src='https://img.shields.io/badge/Difficulty-Medium-orange' alt='Difficulty: Medium' /><hr><p>Given an array of <strong>distinct</strong> integers <code>candidates</code> and a target integer <code>target</code>, return <em>a list of all <strong>unique combinations</strong> of </em><code>candidates</code><em> where the chosen numbers sum to </em><code>target</code><em>.</em> You may return the combinations in <strong>any order</strong>.</p>

<p>The <strong>same</strong> number may be chosen from <code>candidates</code> an <strong>unlimited number of times</strong>. Two combinations are unique if the <span data-keyword="frequency-array">frequency</span> of at least one of the chosen numbers is different.</p>

<p>The test cases are generated such that the number of unique combinations that sum up to <code>target</code> is less than <code>150</code> combinations for the given input.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> candidates = [2,3,6,7], target = 7
<strong>Output:</strong> [[2,2,3],[7]]
<strong>Explanation:</strong>
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> candidates = [2,3,5], target = 8
<strong>Output:</strong> [[2,2,2,2],[2,3,3],[3,5]]
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> candidates = [2], target = 1
<strong>Output:</strong> []
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

---
---

**Core Concept**
This C++ algorithm solves the **Combination Sum** problem (finding all unique combinations of candidate numbers that sum to a target value, allowing the same number to be reused endlessly). It uses a **Include/Exclude Decision Tree** pattern executed via **Depth-First Search (DFS) with Backtracking**.

---

**Key Technical Takeaways (Study Notes)**

* **Binary Choice Decision Model:** At each recursive step, the algorithm makes two decisions for the current candidate element (`candidates[idx]`):
1. **Include:** Add `candidates[idx]` to the current path, keep the index at `idx` (allowing reuse), and update `total`.
2. **Exclude:** Skip `candidates[idx]` and increment to `idx + 1` to move on to the next available number.


* **Base Case Terminations:**
* **Success:** `total == target` adds a copy of the valid `comb` vector to `res`.
* **Pruning:** `total > target` stops searching deeper down an invalid branch where the sum exceeded the limit.
* **Boundary:** `idx >= candidates.size()` stops searching when no more candidate numbers are left to evaluate.


* **Backtracking Dynamic:** `comb.pop_back()` undoes the choice made during the **Include** branch before testing the **Exclude** branch, keeping space consumption low.

---

**Step-by-Step Example Walkthrough**

Consider the following input:

* **Candidates (`candidates`):** `[2, 3]`
* **Target (`target`):** `7`

```
Step 1: Recursive Path Execution
--------------------------------------------------
Root: combinationSum([2, 3], target=7)

- Include 2: comb=[2], total=2
  - Include 2: comb=[2, 2], total=4
    - Include 2: comb=[2, 2, 2], total=6
      - Include 2: comb=[2, 2, 2, 2], total=8 (total > target -> Backtrack!)
      - Exclude 2 -> Try 3 (idx=1): comb=[2, 2, 2, 3], total=9 (total > target -> Backtrack!)
    - Exclude 2 -> Try 3 (idx=1): comb=[2, 2, 3], total=7 (total == target -> Save [2, 2, 3]!)
  - Exclude 2 -> Try 3 (idx=1): comb=[2, 3], total=5
    - Include 3: comb=[2, 3, 3], total=8 (total > target -> Backtrack!)
    - Exclude 3 (idx=2 out of bounds -> Backtrack!)
- Exclude 2 -> Try 3 (idx=1): comb=[3], total=3
  - Include 3: comb=[3, 3], total=6
    - Include 3: comb=[3, 3, 3], total=9 (total > target -> Backtrack!)
    - Exclude 3 (idx=2 out of bounds -> Backtrack!)

Result: [[2, 2, 3]]

```

---

**Complexity Analysis**

* **Time Complexity:** $O(2^T)$, where $T$ is the target value divided by the smallest candidate value. This bounds the maximum depth of the recursive tree.
* **Space Complexity:** $O(T)$ auxiliary space for the recursion stack and the tracking vector `comb`.

<ul>
	<li><code>1 &lt;= candidates.length &lt;= 30</code></li>
	<li><code>2 &lt;= candidates[i] &lt;= 40</code></li>
	<li>All elements of <code>candidates</code> are <strong>distinct</strong>.</li>
	<li><code>1 &lt;= target &lt;= 40</code></li>
</ul>
