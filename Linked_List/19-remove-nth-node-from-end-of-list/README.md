<h2><a href="https://leetcode.com/problems/remove-nth-node-from-end-of-list">Remove Nth Node From End of List</a></h2> <img src='https://img.shields.io/badge/Difficulty-Medium-orange' alt='Difficulty: Medium' /><hr><p>Given the <code>head</code> of a linked list, remove the <code>n<sup>th</sup></code> node from the end of the list and return its head.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2020/10/03/remove_ex1.jpg" style="width: 542px; height: 222px;" />
<pre>
<strong>Input:</strong> head = [1,2,3,4,5], n = 2
<strong>Output:</strong> [1,2,3,5]
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> head = [1], n = 1
<strong>Output:</strong> []
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> head = [1,2], n = 1
<strong>Output:</strong> [1]
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li>The number of nodes in the list is <code>sz</code>.</li>
	<li><code>1 &lt;= sz &lt;= 30</code></li>
	<li><code>0 &lt;= Node.val &lt;= 100</code></li>
	<li><code>1 &lt;= n &lt;= sz</code></li>
</ul>

<p>&nbsp;</p>
<p><strong>Follow up:</strong> Could you do this in one pass?</p>

---
---

## Key Approach Notes

* **Two Pointers with Fixed Offset:**
* **`ptr` (Lead Pointer):** Advanced $n$ steps ahead of `head` first. This creates a gap of size $n$ between `ptr` and `temp`.
* **`temp` (Lag Pointer):** Starts at `head`. Once `ptr` has moved $n$ steps, both pointers advance together one step at a time until `ptr` reaches the last node (`ptr->next == nullptr`).


* **Why the Gap Works:**
* When `ptr` reaches the tail (node at index $L - 1$, where $L$ is total length), `temp` sits exactly at index $L - n - 1$ — which is the node **immediately preceding** the one to be removed.


* **Edge Case Handled (Removing the Head):**
* `if (!ptr) return head->next;`
* If after advancing $n$ steps `ptr` becomes `nullptr`, it means $n = L$ (we need to remove the head node). The code directly returns `head->next`.


* **Complexity:**
* **Time Complexity:** $O(L)$, where $L$ is the number of nodes (single-pass traversal).
* **Space Complexity:** $O(1)$ auxiliary space.



---

## Visual Diagram

### Example: Remove $n = 2^{\text{nd}}$ node from end of `1 -> 2 -> 3 -> 4 -> 5`

Target to remove: Node `4` (2nd from end). Node preceding target: Node `3`.

```text
Step 1: Advance `ptr` by n = 2 steps
[1] -> [2] -> [3] -> [4] -> [5] -> nullptr
 ^             ^
temp          ptr
(gap of 2 nodes between temp and ptr)


Step 2: Move both pointers until ptr->next is nullptr

Iteration 1:
[1] -> [2] -> [3] -> [4] -> [5] -> nullptr
        ^             ^
       temp          ptr

Iteration 2: ptr->next is nullptr, loop ends!
[1] -> [2] -> [3] -> [4] -> [5] -> nullptr
               ^             ^
              temp          ptr
              (Node before target)


Step 3: Skip target node (temp->next = temp->next->next)
[1] -> [2] -> [3] --------- [5] -> nullptr
               |             ^
               +--> [4] -----+ (unlinked)

```

### Edge Case: Remove $n = 5^{\text{th}}$ node from end (Head removal)

```text
List: 1 -> 2 -> 3 -> 4 -> 5, n = 5

Advance `ptr` 5 steps:
[1] -> [2] -> [3] -> [4] -> [5] -> nullptr
 ^                                   ^
temp                                ptr (becomes nullptr!)

Condition `if (!ptr)` triggers -> returns head->next (Node 2).
Result: 2 -> 3 -> 4 -> 5

```
