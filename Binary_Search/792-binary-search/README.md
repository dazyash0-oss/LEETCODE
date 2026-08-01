<h2><a href="https://leetcode.com/problems/binary-search">Binary Search</a></h2> <img src='https://img.shields.io/badge/Difficulty-Easy-brightgreen' alt='Difficulty: Easy' /><hr><p>Given an array of integers <code>nums</code> which is sorted in ascending order, and an integer <code>target</code>, write a function to search <code>target</code> in <code>nums</code>. If <code>target</code> exists, then return its index. Otherwise, return <code>-1</code>.</p>

<p>You must write an algorithm with <code>O(log n)</code> runtime complexity.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> nums = [-1,0,3,5,9,12], target = 9
<strong>Output:</strong> 4
<strong>Explanation:</strong> 9 exists in nums and its index is 4
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> nums = [-1,0,3,5,9,12], target = 2
<strong>Output:</strong> -1
<strong>Explanation:</strong> 2 does not exist in nums so return -1
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= nums.length &lt;= 10<sup>4</sup></code></li>
	<li><code>-10<sup>4</sup> &lt; nums[i], target &lt; 10<sup>4</sup></code></li>
	<li>All the integers in <code>nums</code> are <strong>unique</strong>.</li>
	<li><code>nums</code> is sorted in ascending order.</li>
</ul>


---
---

## 💡 Key Intuition

Binary search leverages the fact that the array is **already sorted**. Instead of scanning every element sequentially (linear search), we repeatedly divide the search space in half by comparing the `target` value to the middle element (`nums[mid]`):

* If `nums[mid] == target`: We found the element.
* If `nums[mid] < target`: The target must lie in the **right half**, so discard the left half.
* If `nums[mid] > target`: The target must lie in the **left half**, so discard the right half.

This logarithmically narrows down the possibilities until the target is found or the search space becomes empty.

---

## 🛠️ Step-by-Step Approach

1. **Initialize Pointers:** Set `left = 0` and `right = nums.size() - 1` to define the boundary of the active search space.
2. **Loop Condition:** Continue while `left <= right`. (Using `<=` ensures single-element search spaces are evaluated).
3. **Calculate Middle Index:**
* Use `mid = left + (right - left) / 2` instead of `(left + right) / 2` to prevent potential integer overflow when `left` and `right` are large.


4. **Evaluate `nums[mid]`:**
* **Match:** If `nums[mid] == target`, return `mid`.
* **Target Larger:** If `nums[mid] < target`, update `left = mid + 1`.
* **Target Smaller:** If `nums[mid] > target`, update `right = mid - 1`.


5. **Not Found:** If the loop terminates without finding `target`, return `-1`.

---

## 🔍 Code Review



* **Overflow Prevention:** Using `int mid = left + (right - left) / 2;` is the standard best practice in C++ to prevent integer overflow.
* **Boundary Adjustments:** Correctly using `left = mid + 1` and `right = mid - 1` prevents infinite loops when narrowing the search range.
* **Base Condition:** `left <= right` correctly handles arrays of size 1 and edge searches.

---

## ⏱️ Complexity Analysis

| Metric | Complexity | Explanation |
| --- | --- | --- |
| **Time Complexity** | **$O(\log n)$** | In each iteration, the algorithm halves the remaining search range $n \to n/2 \to n/4 \dots$, resulting in logarithmic time. |
| **Space Complexity** | **$O(1)$** | The search is performed iteratively in-place without auxiliary data structures or recursive stack calls. |

---
