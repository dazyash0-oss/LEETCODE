<h2><a href="https://leetcode.com/problems/subsets">Subsets</a></h2> <img src='https://img.shields.io/badge/Difficulty-Medium-orange' alt='Difficulty: Medium' /><hr><p>Given an integer array <code>nums</code> of <strong>unique</strong> elements, return <em>all possible</em> <span data-keyword="subset"><em>subsets</em></span> <em>(the power set)</em>.</p>

<p>The solution set <strong>must not</strong> contain duplicate subsets. Return the solution in <strong>any order</strong>.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> nums = [1,2,3]
<strong>Output:</strong> [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> nums = [0]
<strong>Output:</strong> [[],[0]]
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= nums.length &lt;= 10</code></li>
	<li><code>-10 &lt;= nums[i] &lt;= 10</code></li>
	<li>All the numbers of&nbsp;<code>nums</code> are <strong>unique</strong>.</li>
</ul>


Here is how your recursive backtracking algorithm works step-by-step using a concrete example.

---

### How the Algorithm Works

At each element in `nums`, the function makes two choices:

1. **Include** `nums[index]` in the current subset, then recurse on `index + 1`.
2. **Exclude** `nums[index]` (by popping it out), then recurse on `index + 1`.

Once `index` reaches `nums.size()`, a complete subset path is formed and appended to `res`.

---

### Example Trace: `nums = [1, 2]`

For `nums = [1, 2]`, there are $2^2 = 4$ total subsets. Here is how the recursive decision tree executes:

```text
                        createSubset(index = 0, subset = [])
                                   /                    \
                       [Include 1]                        [Exclude 1]
                                 /                                \
             createSubset(index = 1, subset = [1])       createSubset(index = 1, subset = [])
                      /               \                           /               \
          [Include 2]                   [Exclude 2]   [Include 2]                   [Exclude 2]
                /                             \             /                             \
createSubset(2, [1, 2])          createSubset(2, [1])  createSubset(2, [2])          createSubset(2, [])
  -> Push [1, 2]                   -> Push [1]            -> Push [2]                   -> Push []

```

---

### Step-by-Step Execution Sequence

1. **Start:** `createSubset(0, [])`
* Push `1` $\rightarrow$ call `createSubset(1, [1])`


2. **Branch 1 (Include 1):**
* Push `2` $\rightarrow$ call `createSubset(2, [1, 2])`
* **Base Case Hit (`index == 2`):** Save `[1, 2]` to `res`. Backtrack to `index = 1`.
* Pop `2` $\rightarrow$ `subset` becomes `[1]`
* Recurse without 2 $\rightarrow$ call `createSubset(2, [1])`
* **Base Case Hit (`index == 2`):** Save `[1]` to `res`. Backtrack to `index = 0`.


3. **Branch 2 (Exclude 1):**
* Pop `1` $\rightarrow$ `subset` becomes `[]`
* Recurse without 1 $\rightarrow$ call `createSubset(1, [])`
* Push `2` $\rightarrow$ call `createSubset(2, [2])`
* **Base Case Hit (`index == 2`):** Save `[2]` to `res`. Backtrack to `index = 1`.
* Pop `2` $\rightarrow$ `subset` becomes `[]`
* Recurse without 2 $\rightarrow$ call `createSubset(2, [])`
* **Base Case Hit (`index == 2`):** Save `[]` to `res`.



**Final Result:** `res = [[1, 2], [1], [2], []]`
