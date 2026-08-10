<h2><a href="https://leetcode.com/problems/binary-tree-level-order-traversal">Binary Tree Level Order Traversal</a></h2> <img src='https://img.shields.io/badge/Difficulty-Medium-orange' alt='Difficulty: Medium' /><hr><p>Given the <code>root</code> of a binary tree, return <em>the level order traversal of its nodes&#39; values</em>. (i.e., from left to right, level by level).</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2021/02/19/tree1.jpg" style="width: 277px; height: 302px;" />
<pre>
<strong>Input:</strong> root = [3,9,20,null,null,15,7]
<strong>Output:</strong> [[3],[9,20],[15,7]]
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> root = [1]
<strong>Output:</strong> [[1]]
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> root = []
<strong>Output:</strong> []
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li>The number of nodes in the tree is in the range <code>[0, 2000]</code>.</li>
	<li><code>-1000 &lt;= Node.val &lt;= 1000</code></li>
</ul>


---
---

## 2. Approach & Intuition

Level order traversal uses **Breadth-First Search (BFS)**, which visits nodes layer by layer from top to bottom, left to right.

### Key Trick: Tracking Level Boundaries (`int size = q.size()`)

A standard BFS uses a FIFO queue to process nodes, but plain BFS doesn't naturally separate nodes level by level.

1. At the start of each level's loop, `q.size()` tells you **exactly how many nodes belong to the current level**.
2. By snapshotting `int size = q.size()`, you can run a fixed `for` loop `size` times to process only the nodes of the current level.
3. Any new child nodes pushed to the queue during this loop are added behind the current batch, forming the *next* level.

---

## 3. Detailed Notes & Complexity

### Complexity Analysis

* **Time Complexity:** $O(N)$, where $N$ is the total number of nodes in the binary tree. Every node is enqueued and dequeued exactly once.
* **Space Complexity:** $O(W)$, where $W$ is the maximum width (maximum number of nodes at any level) of the tree.
* In a balanced full binary tree, the bottom level contains roughly $N/2$ nodes, giving $O(N)$ worst-case space for the queue.



### Common Level-Order Pattern Variations

| Variation | Quick Adjustment to Template |
| --- | --- |
| **Zigzag Level Order (LeetCode 103)** | Toggle a boolean flag per level; reverse the `level` vector or insert from back when flag is set. |
| **Level Order II / Bottom-Up (LeetCode 107)** | Run identical BFS, then `reverse(ans.begin(), ans.end())` at the end. |
| **Right Side View (LeetCode 199)** | Only capture the last element in the `for` loop (`i == size - 1`). |
| **Average of Levels (LeetCode 637)** | Sum values inside the `for` loop and calculate `sum / size`. |

---
