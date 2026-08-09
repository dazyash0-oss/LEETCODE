<h2><a href="https://leetcode.com/problems/validate-binary-search-tree">Validate Binary Search Tree</a></h2> <img src='https://img.shields.io/badge/Difficulty-Medium-orange' alt='Difficulty: Medium' /><hr><p>Given the <code>root</code> of a binary tree, <em>determine if it is a valid binary search tree (BST)</em>.</p>

<p>A <strong>valid BST</strong> is defined as follows:</p>

<ul>
	<li>The left <span data-keyword="subtree">subtree</span> of a node contains only nodes with keys&nbsp;<strong>strictly less than</strong> the node&#39;s key.</li>
	<li>The right subtree of a node contains only nodes with keys <strong>strictly greater than</strong> the node&#39;s key.</li>
	<li>Both the left and right subtrees must also be binary search trees.</li>
</ul>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2020/12/01/tree1.jpg" style="width: 302px; height: 182px;" />
<pre>
<strong>Input:</strong> root = [2,1,3]
<strong>Output:</strong> true
</pre>

<p><strong class="example">Example 2:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2020/12/01/tree2.jpg" style="width: 422px; height: 292px;" />
<pre>
<strong>Input:</strong> root = [5,1,4,null,null,3,6]
<strong>Output:</strong> false
<strong>Explanation:</strong> The root node&#39;s value is 5 but its right child&#39;s value is 4.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li>The number of nodes in the tree is in the range <code>[1, 10<sup>4</sup>]</code>.</li>
	<li><code>-2<sup>31</sup> &lt;= Node.val &lt;= 2<sup>31</sup> - 1</code></li>
</ul>


### Approach & Concept

The code solves **LeetCode 98: Validate Binary Search Tree** using a **Top-Down Recursive DFS with Range Validation (Bounding Constraint)** approach.

The core idea is that for a binary tree to be a valid BST, it is **not enough** for a node's value to just be greater than its left child and smaller than its right child. Every node must satisfy global bounds derived from all its ancestors:

1. **Range Maintenance:** Each node must lie strictly within an allowed open interval `(minimum, maximum)`.
2. **Left Subtree Update:** When moving to `node->left`, all values in that branch must be strictly smaller than `node->val`. The new upper bound becomes `node->val` while the lower bound stays `minimum`.
3. **Right Subtree Update:** When moving to `node->right`, all values in that branch must be strictly greater than `node->val`. The new lower bound becomes `node->val` while the upper bound stays `maximum`.
4. **Base Case:** An empty node (`!node`) is inherently a valid BST, so it returns `true`.
5. **Validation Failure:** If `node->val <= minimum` or `node->val >= maximum`, the tree breaks BST properties, returning `false`.

*(Note: `LONG_MIN` and `LONG_MAX` are used to handle edge cases where tree node values equal `INT_MIN` or `INT_MAX`.)*

---

### Complexity Analysis

* **Time Complexity:** $\mathcal{O}(N)$, where $N$ is the total number of nodes in the binary tree. Every node is visited at most once.
* **Space Complexity:** $\mathcal{O}(H)$, where $H$ is the height of the tree, representing call stack usage.
* Best/Average case (Balanced tree): $\mathcal{O}(\log N)$
* Worst case (Skewed tree): $\mathcal{O}(N)$



---

### Recursion Template Used

This solution follows the **Top-Down DFS / Preorder Recursion with Range Propagation** template.

#### Template Structure

```cpp
bool solveTree(TreeNode* node, DataType lowBound, DataType highBound) {
    // 1. Base Case: Reached null without breaking rules
    if (node == nullptr) {
        return true;
    }

    // 2. Preorder Check: Validate current node against propagated state/bounds
    if (/* node->val violates lowBound or highBound */) {
        return false;
    }

    // 3. Downward Propagation: Recurse left and right with updated constraints
    bool leftValid = solveTree(node->left, lowBound, node->val);
    bool rightValid = solveTree(node->right, node->val, highBound);

    // 4. Combine results
    return leftValid && rightValid;
}

```
