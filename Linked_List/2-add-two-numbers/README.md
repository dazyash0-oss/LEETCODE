<h2><a href="https://leetcode.com/problems/add-two-numbers">Add Two Numbers</a></h2> <img src='https://img.shields.io/badge/Difficulty-Medium-orange' alt='Difficulty: Medium' /><hr><p>You are given two <strong>non-empty</strong> linked lists representing two non-negative integers. The digits are stored in <strong>reverse order</strong>, and each of their nodes contains a single digit. Add the two numbers and return the sum&nbsp;as a linked list.</p>

<p>You may assume the two numbers do not contain any leading zero, except the number 0 itself.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2020/10/02/addtwonumber1.jpg" style="width: 483px; height: 342px;" />
<pre>
<strong>Input:</strong> l1 = [2,4,3], l2 = [5,6,4]
<strong>Output:</strong> [7,0,8]
<strong>Explanation:</strong> 342 + 465 = 807.
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> l1 = [0], l2 = [0]
<strong>Output:</strong> [0]
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
<strong>Output:</strong> [8,9,9,9,0,0,0,1]
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li>The number of nodes in each linked list is in the range <code>[1, 100]</code>.</li>
	<li><code>0 &lt;= Node.val &lt;= 9</code></li>
	<li>It is guaranteed that the list represents a number that does not have leading zeros.</li>
</ul>


---
---

## Key Approach Notes

* **Dummy Head Technique:**
* Using `dummyHead` avoids special-case code for instantiating the first node of the output list.
* The actual result starts at `dummyHead->next`, and `dummyHead` is deleted at the end to prevent memory leaks.


* **Simulating Column Addition:**
* At each step, it extracts the current digits (`digit1` and `digit2`). If a list has reached its end (`nullptr`), its digit is treated as `0`.
* **Sum calculation:** $\text{sum} = \text{digit1} + \text{digit2} + \text{carry}$
* **New node digit:** $\text{digit} = \text{sum} \bmod 10$
* **Next carry:** $\text{carry} = \lfloor \text{sum} / 10 \rfloor$


* **Loop Termination Condition:**
* `while (l1 != nullptr || l2 != nullptr || carry != 0)`
* Checking `carry != 0` ensures that an extra node is created if the final sum creates a trailing carry (e.g., $99 + 1 = 100$).


* **Complexity:**
* **Time Complexity:** $O(\max(N, M))$, where $N$ and $M$ are the lengths of `l1` and `l2`.
* **Space Complexity:** $O(\max(N, M))$ to construct the new linked list.



---

## Visual Diagram

### Example: Add $342 + 465 = 807$

Stored in reverse:

`l1`: $2 \to 4 \to 3$ (represents 342)

`l2`: $5 \to 6 \to 4$ (represents 465)

```text
Initial Setup:
dummyHead -> [0]
tail --------^
carry = 0


Iteration 1: (2 + 5 + 0 = 7)
l1 node: 2 | l2 node: 5 | carry: 0 -> sum = 7
digit = 7 % 10 = 7, carry = 7 / 10 = 0

dummyHead -> [0] -> [7]
                    ^
                   tail
l1 moves to 4, l2 moves to 6


Iteration 2: (4 + 6 + 0 = 10)
l1 node: 4 | l2 node: 6 | carry: 0 -> sum = 10
digit = 10 % 10 = 0, carry = 10 / 10 = 1

dummyHead -> [0] -> [7] -> [0]
                           ^
                          tail
l1 moves to 3, l2 moves to 4


Iteration 3: (3 + 4 + 1 = 8)
l1 node: 3 | l2 node: 4 | carry: 1 -> sum = 8
digit = 8 % 10 = 8, carry = 8 / 10 = 0

dummyHead -> [0] -> [7] -> [0] -> [8]
                                  ^
                                 tail
l1 moves to null, l2 moves to null


Result Extraction:
Return dummyHead->next -> [7] -> [0] -> [8]  (represents 807)

```

---

### Special Edge Case: Extra Carry at the End ($99 + 1 = 100$)

`l1`: $9 \to 9$

`l2`: $1$

```text
Iteration 1: 9 + 1 + 0 = 10 -> Node(0), carry = 1
Iteration 2: 9 + 0 + 1 = 10 -> Node(0), carry = 1
Iteration 3: (l1 and l2 are null, but carry = 1) -> Node(1), carry = 0

Output: 0 -> 0 -> 1 (represents 100)

```
