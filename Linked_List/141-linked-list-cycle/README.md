<h2><a href="https://leetcode.com/problems/linked-list-cycle">Linked List Cycle</a></h2> <img src='https://img.shields.io/badge/Difficulty-Easy-brightgreen' alt='Difficulty: Easy' /><hr><p>Given <code>head</code>, the head of a linked list, determine if the linked list has a cycle in it.</p>

<p>There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the&nbsp;<code>next</code>&nbsp;pointer. Internally, <code>pos</code>&nbsp;is used to denote the index of the node that&nbsp;tail&#39;s&nbsp;<code>next</code>&nbsp;pointer is connected to.&nbsp;<strong>Note that&nbsp;<code>pos</code>&nbsp;is not passed as a parameter</strong>.</p>

<p>Return&nbsp;<code>true</code><em> if there is a cycle in the linked list</em>. Otherwise, return <code>false</code>.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist.png" style="width: 300px; height: 97px; margin-top: 8px; margin-bottom: 8px;" />
<pre>
<strong>Input:</strong> head = [3,2,0,-4], pos = 1
<strong>Output:</strong> true
<strong>Explanation:</strong> There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).
</pre>

<p><strong class="example">Example 2:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist_test2.png" style="width: 141px; height: 74px;" />
<pre>
<strong>Input:</strong> head = [1,2], pos = 0
<strong>Output:</strong> true
<strong>Explanation:</strong> There is a cycle in the linked list, where the tail connects to the 0th node.
</pre>

<p><strong class="example">Example 3:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist_test3.png" style="width: 45px; height: 45px;" />
<pre>
<strong>Input:</strong> head = [1], pos = -1
<strong>Output:</strong> false
<strong>Explanation:</strong> There is no cycle in the linked list.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li>The number of the nodes in the list is in the range <code>[0, 10<sup>4</sup>]</code>.</li>
	<li><code>-10<sup>5</sup> &lt;= Node.val &lt;= 10<sup>5</sup></code></li>
	<li><code>pos</code> is <code>-1</code> or a <strong>valid index</strong> in the linked-list.</li>
</ul>

<p>&nbsp;</p>
<p><strong>Follow up:</strong> Can you solve it using <code>O(1)</code> (i.e. constant) memory?</p>


---
---

## Key Approach Notes

* **Two-Pointer Technique:**
* **`slow` pointer (Tortoise):** Moves **1 step** at a time (`slow = slow->next`).
* **`fast` pointer (Hare):** Moves **2 steps** at a time (`fast = fast->next->next`).


* **Core Intuition:**
* If there is **no cycle**, `fast` will eventually reach the end of the list (`nullptr`), returning `false`.
* If there **is a cycle**, both pointers will enter the loop. Because `fast` gains 1 step on `slow` during every iteration, the relative distance between them decreases by 1 step each turn, guaranteeing they will eventually meet (`fast == slow`).


* **Complexity:**
* **Time Complexity:** $O(N)$, where $N$ is the number of nodes. If a cycle exists, `fast` catches up to `slow` in $O(K)$ iterations (where $K$ is the length of the cycle).
* **Space Complexity:** $O(1)$ auxiliary space, since it only uses two pointer variables.



---

## Visual Diagram

### Case 1: Linked List with a Cycle

Consider the list `1 -> 2 -> 3 -> 4 -> 2` (loop back to node 2):

```text
Step 0 (Initialization):
[1] -> [2] -> [3] -> [4]
 ^                     |
 S,F                   v
  |<-------------------|

Step 1: slow moves 1 step to 2, fast moves 2 steps to 3
[1] -> [2] -> [3] -> [4]
        ^      ^       |
        S      F       v
  |<-------------------|

Step 2: slow moves 1 step to 3, fast moves 2 steps to 2
[1] -> [2] -> [3] -> [4]
        ^      ^       |
        F      S       v
  |<-------------------|

Step 3: slow moves 1 step to 4, fast moves 2 steps to 4
[1] -> [2] -> [3] -> [4]
                       |
                      S,F  <-- Fast and Slow MEET! (Return true)
  |<-------------------|

```

---

### Case 2: Linear Linked List (No Cycle)

Consider `1 -> 2 -> 3 -> nullptr`:

```text
Step 0: S and F start at [1].
Step 1: S moves to [2], F moves to [3].
Step 2: F->next is nullptr. Loop terminates and returns false.

```
