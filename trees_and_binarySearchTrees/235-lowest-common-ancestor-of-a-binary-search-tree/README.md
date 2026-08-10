<h2><a href="https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree">Lowest Common Ancestor of a Binary Search Tree</a></h2> <img src='https://img.shields.io/badge/Difficulty-Medium-orange' alt='Difficulty: Medium' /><hr><p>Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.</p>

<p>According to the <a href="https://en.wikipedia.org/wiki/Lowest_common_ancestor" target="_blank">definition of LCA on Wikipedia</a>: &ldquo;The lowest common ancestor is defined between two nodes <code>p</code> and <code>q</code> as the lowest node in <code>T</code> that has both <code>p</code> and <code>q</code> as descendants (where we allow <strong>a node to be a descendant of itself</strong>).&rdquo;</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2018/12/14/binarysearchtree_improved.png" style="width: 200px; height: 190px;" />
<pre>
<strong>Input:</strong> root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
<strong>Output:</strong> 6
<strong>Explanation:</strong> The LCA of nodes 2 and 8 is 6.
</pre>

<p><strong class="example">Example 2:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2018/12/14/binarysearchtree_improved.png" style="width: 200px; height: 190px;" />
<pre>
<strong>Input:</strong> root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
<strong>Output:</strong> 2
<strong>Explanation:</strong> The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> root = [2,1], p = 2, q = 1
<strong>Output:</strong> 2
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li>The number of nodes in the tree is in the range <code>[2, 10<sup>5</sup>]</code>.</li>
	<li><code>-10<sup>9</sup> &lt;= Node.val &lt;= 10<sup>9</sup></code></li>
	<li>All <code>Node.val</code> are <strong>unique</strong>.</li>
	<li><code>p != q</code></li>
	<li><code>p</code> and <code>q</code> will exist in the BST.</li>
</ul>

---
---

## 2. Approach & Intuition

The core strategy relies on the **Binary Search Tree (BST) ordering property**: for any node $N$, all nodes in its left subtree have values strictly less than $N$, and all nodes in its right subtree have values strictly greater than $N$.

### Key Insight: The "Split Point"

The Lowest Common Ancestor (LCA) is the highest node in the tree where `p` and `q` are no longer located in the same subtree. As you walk down from the root, there are three possible scenarios for the current node:

1. **Both `p` and `q` are larger than `root`:** The LCA must lie strictly in the **right** subtree. Move `root = root->right`.
2. **Both `p` and `q` are smaller than `root`:** The LCA must lie strictly in the **left** subtree. Move `root = root->left`.
3. **Values split across `root` (or one equals `root`):** This happens when:
* One node is on the left and the other is on the right (`p->val < root->val` and `q->val > root->val`).
* `root` itself is equal to `p` or `q` (a node can be an ancestor of itself).


At this precise node, `p` and `q` diverge. Therefore, the current `root` is guaranteed to be the lowest common ancestor.

---

## 3. Detailed Notes & Complexity

### Complexity Analysis

* **Time Complexity:** $O(H)$, where $H$ is the height of the tree.
* **Best/Average Case (Balanced BST):** $O(\log N)$ steps because half of the remaining subtree is eliminated at each decision point.
* **Worst Case (Skewed BST):** $O(N)$ if the tree degenerates into a single long branch (e.g., linked list structure).


* **Space Complexity:** $O(1)$ auxiliary space for the iterative solution, as it only updates a pointer rather than allocating additional memory.

### Comparison: Iterative vs. Recursive

| Aspect | Iterative Approach (Your Code) | Recursive Approach |
| --- | --- | --- |
| **Space Complexity** | $O(1)$ | $O(H)$ due to implicit call stack |
| **Overflow Risk** | None | Risk of stack overflow on deeply skewed trees |
| **Readability** | High (clean while loop) | High (concise 4-liner) |

---
