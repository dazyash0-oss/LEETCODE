<h2><a href="https://leetcode.com/problems/find-minimum-in-rotated-sorted-array">Find Minimum in Rotated Sorted Array</a></h2> <img src='https://img.shields.io/badge/Difficulty-Medium-orange' alt='Difficulty: Medium' /><hr><p>Suppose an array of length <code>n</code> sorted in ascending order is <strong>rotated</strong> between <code>1</code> and <code>n</code> times. For example, the array <code>nums = [0,1,2,4,5,6,7]</code> might become:</p>

<ul>
	<li><code>[4,5,6,7,0,1,2]</code> if it was rotated <code>4</code> times.</li>
	<li><code>[0,1,2,4,5,6,7]</code> if it was rotated <code>7</code> times.</li>
</ul>

<p>Notice that <strong>rotating</strong> an array <code>[a[0], a[1], a[2], ..., a[n-1]]</code> 1 time results in the array <code>[a[n-1], a[0], a[1], a[2], ..., a[n-2]]</code>.</p>

<p>Given the sorted rotated array <code>nums</code> of <strong>unique</strong> elements, return <em>the minimum element of this array</em>.</p>

<p>You must write an algorithm that runs in&nbsp;<code>O(log n) time</code>.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> nums = [3,4,5,1,2]
<strong>Output:</strong> 1
<strong>Explanation:</strong> The original array was [1,2,3,4,5] rotated 3 times.
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> nums = [4,5,6,7,0,1,2]
<strong>Output:</strong> 0
<strong>Explanation:</strong> The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> nums = [11,13,15,17]
<strong>Output:</strong> 11
<strong>Explanation:</strong> The original array was [11,13,15,17] and it was rotated 4 times. 
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>n == nums.length</code></li>
	<li><code>1 &lt;= n &lt;= 5000</code></li>
	<li><code>-5000 &lt;= nums[i] &lt;= 5000</code></li>
	<li>All the integers of <code>nums</code> are <strong>unique</strong>.</li>
	<li><code>nums</code> is sorted and rotated between <code>1</code> and <code>n</code> times.</li>
</ul>

---
---

## 💡 Key Intuition

In a rotated sorted array, the minimum element acts as the **inflection point** (the pivot where the rotation happens). Everything to the left of the minimum belongs to the "higher" sorted chunk, and everything from the minimum onward belongs to the "lower" sorted chunk.

Instead of comparing `nums[mid]` with `nums[left]`, we compare `nums[mid]` directly with **`nums[right]`**:

```
Example: [ 4,  5,  6,  7,  0,  1,  2 ]
                  ^ mid = 7, right = 2
Since nums[mid] (7) > nums[right] (2), the minimum MUST lie to the right of mid.

```

* **If `nums[mid] > nums[right]`:** The pivot point lies strictly in the right half `(mid + 1 to right)`. We drop the left half.
* **If `nums[mid] <= nums[right]`:** The right half is sorted normally, meaning `nums[mid]` could be the minimum, or the minimum is to the left of `mid`. We narrow our search space to `(left to mid)`.

---

## 🛠️ Step-by-Step Approach

1. **Initialize Pointers:** Set `left = 0` and `right = nums.size() - 1`.
2. **Loop Condition:** Continue while `left < right` (note the strict `<` instead of `<=`).
* *Why?* We contract the search space until `left` and `right` converge on the single smallest element.


3. **Calculate Midpoint:** `mid = left + (right - left) / 2`.
4. **Compare with Boundary:**
* **`nums[mid] > nums[right]`:** The minimum element must be to the right of `mid`. Set `left = mid + 1`.
* **`nums[mid] <= nums[right]`:** `nums[mid]` might be the minimum itself, or the minimum is further left. Set `right = mid`.


5. **Return Result:** When `left == right`, the loop terminates. Return `nums[left]` (or `nums[right]`).

---

## 🔍 Code Review & Assessment


* **Loop Invariant (`left < right`):** Correctly avoids an infinite loop when `right = mid`.
* **Index Assignment:** `left = mid + 1` safely skips `mid` because `nums[mid] > nums[right]` proves `mid` cannot be the minimum. `right = mid` retains `mid` because it could potentially be the minimum.
* **Overflow Protection:** Using `left + (right - left) / 2` is safe.

---

## ⏱️ Complexity Analysis

| Metric | Complexity | Explanation |
| --- | --- | --- |
| **Time Complexity** | **$O(\log n)$** | In each iteration, the search interval is cut in half. |
| **Space Complexity** | **$O(1)$** | Memory usage is constant since only three index variables (`left`, `right`, `mid`) are used. |

---
