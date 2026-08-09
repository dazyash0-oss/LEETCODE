<h2><a href="https://leetcode.com/problems/invert-binary-tree">Invert Binary Tree</a></h2> <img src='https://img.shields.io/badge/Difficulty-Easy-brightgreen' alt='Difficulty: Easy' /><hr><p>Given the <code>root</code> of a binary tree, invert the tree, and return <em>its root</em>.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2021/03/14/invert1-tree.jpg" style="width: 500px; height: 165px;" />
<pre>
<strong>Input:</strong> root = [4,2,7,1,3,6,9]
<strong>Output:</strong> [4,7,2,9,6,3,1]
</pre>

<p><strong class="example">Example 2:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2021/03/14/invert2-tree.jpg" style="width: 500px; height: 120px;" />
<pre>
<strong>Input:</strong> root = [2,1,3]
<strong>Output:</strong> [2,3,1]
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> root = []
<strong>Output:</strong> []
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li>The number of nodes in the tree is in the range <code>[0, 100]</code>.</li>
	<li><code>-100 &lt;= Node.val &lt;= 100</code></li>
</ul>

### Approach & Concept

The code solves **LeetCode 226: Invert Binary Tree** using a **Depth-First Search (DFS) / Preorder-Postorder Tree Traversal** approach.

The core idea is to recursively visit every node in the tree and swap its left and right children:

1. **Base Case:** If the current node (`root`) is `nullptr` (or `NULL`), return `nullptr`. This stops the recursion at leaf boundaries.
2. **Recursive Traversal:** Recursively call `invertTree` on the left child and right child to invert both subtrees.
3. **Swap Operation:** Swap the pointers of `root->left` and `root->right` using a temporary variable `temp`.
4. **Return:** Return the updated `root` pointer back to the parent caller.

*(Note: Because the swap happens **after** the recursive calls, this specific order acts as a **Postorder Traversal** (`Left -> Right -> Root`), though swapping **before** recursive calls in a Preorder fashion (`Root -> Left -> Right`) produces the exact same result.)*

---

### Complexity Analysis

* **Time Complexity:** $\mathcal{O}(N)$, where $N$ is the total number of nodes in the binary tree. Every node is visited exactly once.
* **Space Complexity:** $\mathcal{O}(H)$, where $H$ is the height of the tree. This accounts for the recursive call stack space.
* Best/Average case (Balanced tree): $\mathcal{O}(\log N)$
* Worst case (Skewed tree): $\mathcal{O}(N)$



---

### Recursion Template Used

This solution follows the standard **Divide and Conquer / Dynamic Programming on Trees (Postorder Recursion)** template.

#### Template Structure

```cpp
ReturnType solveTree(TreeNode* root) {
    // 1. Base Case: Boundary check
    if (root == nullptr) {
        return base_value;
    }

    // 2. Divide: Recursive calls on left and right subtrees
    ReturnType leftResult = solveTree(root->left);
    ReturnType rightResult = solveTree(root->right);

    // 3. Conquer / Process: Combine results at the current root
    // [Perform local operations, e.g., swap, aggregate value, etc.]

    // 4. Return result to parent caller
    return currentResult;
}

```
