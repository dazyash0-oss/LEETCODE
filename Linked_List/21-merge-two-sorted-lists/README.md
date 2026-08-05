<h2><a href="https://leetcode.com/problems/merge-two-sorted-lists">Merge Two Sorted Lists</a></h2> <img src='https://img.shields.io/badge/Difficulty-Easy-brightgreen' alt='Difficulty: Easy' /><hr><p>You are given the heads of two sorted linked lists <code>list1</code> and <code>list2</code>.</p>

<p>Merge the two lists into one <strong>sorted</strong> list. The list should be made by splicing together the nodes of the first two lists.</p>

<p>Return <em>the head of the merged linked list</em>.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2020/10/03/merge_ex1.jpg" style="width: 662px; height: 302px;" />
<pre>
<strong>Input:</strong> list1 = [1,2,4], list2 = [1,3,4]
<strong>Output:</strong> [1,1,2,3,4,4]
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> list1 = [], list2 = []
<strong>Output:</strong> []
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> list1 = [], list2 = [0]
<strong>Output:</strong> [0]
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li>The number of nodes in both lists is in the range <code>[0, 50]</code>.</li>
	<li><code>-100 &lt;= Node.val &lt;= 100</code></li>
	<li>Both <code>list1</code> and <code>list2</code> are sorted in <strong>non-decreasing</strong> order.</li>
</ul>


---
---

## Key Approach Notes

* **Dummy Head Technique:**
* Using `dummy` simplifies node insertion at the start so you don't need `if-else` conditions to handle creating/setting the merged list's initial head.
* The actual head of the result is stored in `dummy->next`, and `dummy` is freed with `delete` at the end to prevent a memory leak.


* **Iterative Comparison:**
* Compares current nodes (`list1->val` vs. `list2->val`).
* Attaches the smaller node to `tail->next` and moves the corresponding list pointer forward.


* **Appending Remaining Nodes:**
* Once one list runs out (`nullptr`), the loops append the remaining nodes of the other list.
* *Optimization Note:* Since both inputs are linked lists, the second and third `while` loops can be simplified to a direct pointer assignment: `if (list1 != nullptr) tail->next = list1; else tail->next = list2;` (no need to iterate through them node-by-node).


* **Complexity:**
* **Time Complexity:** $O(N + M)$, where $N$ and $M$ are the lengths of `list1` and `list2`.
* **Space Complexity:** $O(1)$ auxiliary space, since it rearranges existing nodes in-place rather than allocating new ones.



---

## Visual Diagram

### Example: `list1 = [1, 2, 4]` and `list2 = [1, 3, 4]`

```text
Initial Setup:
dummy -> [0]
tail ----^
list1: [1] -> [2] -> [4]
list2: [1] -> [3] -> [4]


Step 1: Compare list1 (1) <= list2 (1) -> attach list1
dummy -> [0] -> [1]
                 ^
                tail
list1: [2] -> [4]
list2: [1] -> [3] -> [4]


Step 2: Compare list1 (2) > list2 (1) -> attach list2
dummy -> [0] -> [1] -> [1]
                        ^
                       tail
list1: [2] -> [4]
list2: [3] -> [4]


Step 3: Compare list1 (2) <= list2 (3) -> attach list1
dummy -> [0] -> [1] -> [1] -> [2]
                               ^
                              tail
list1: [4]
list2: [3] -> [4]


Step 4: Compare list1 (4) > list2 (3) -> attach list2
dummy -> [0] -> [1] -> [1] -> [2] -> [3]
                                      ^
                                     tail
list1: [4]
list2: [4]


Step 5: Compare list1 (4) <= list2 (4) -> attach list1
dummy -> [0] -> [1] -> [1] -> [2] -> [3] -> [4]
                                             ^
                                            tail
list1: nullptr
list2: [4]


Step 6: Main loop finishes (list1 is null). Append remaining list2:
dummy -> [0] -> [1] -> [1] -> [2] -> [3] -> [4] -> [4] -> nullptr
                                                    ^
                                                   tail

Result: Return dummy->next (Head points to 1) -> [1, 1, 2, 3, 4, 4]

```
