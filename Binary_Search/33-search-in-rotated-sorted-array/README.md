<h2><a href="https://leetcode.com/problems/search-in-rotated-sorted-array">Search in Rotated Sorted Array</a></h2> <img src='https://img.shields.io/badge/Difficulty-Medium-orange' alt='Difficulty: Medium' /><hr><p>There is an integer array <code>nums</code> sorted in ascending order (with <strong>distinct</strong> values).</p>

<p>Prior to being passed to your function, <code>nums</code> is <strong>possibly left rotated</strong> at an unknown index <code>k</code> (<code>1 &lt;= k &lt; nums.length</code>) such that the resulting array is <code>[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]</code> (<strong>0-indexed</strong>). For example, <code>[0,1,2,4,5,6,7]</code> might be left rotated by&nbsp;<code>3</code>&nbsp;indices and become <code>[4,5,6,7,0,1,2]</code>.</p>

<p>Given the array <code>nums</code> <strong>after</strong> the possible rotation and an integer <code>target</code>, return <em>the index of </em><code>target</code><em> if it is in </em><code>nums</code><em>, or </em><code>-1</code><em> if it is not in </em><code>nums</code>.</p>

<p>You must write an algorithm with <code>O(log n)</code> runtime complexity.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<pre><strong>Input:</strong> nums = [4,5,6,7,0,1,2], target = 0
<strong>Output:</strong> 4
</pre><p><strong class="example">Example 2:</strong></p>
<pre><strong>Input:</strong> nums = [4,5,6,7,0,1,2], target = 3
<strong>Output:</strong> -1
</pre><p><strong class="example">Example 3:</strong></p>
<pre><strong>Input:</strong> nums = [1], target = 0
<strong>Output:</strong> -1
</pre>
<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= nums.length &lt;= 5000</code></li>
	<li><code>-10<sup>4</sup> &lt;= nums[i] &lt;= 10<sup>4</sup></code></li>
	<li>All values of <code>nums</code> are <strong>unique</strong>.</li>
	<li><code>nums</code> is an ascending array that is possibly rotated.</li>
	<li><code>-10<sup>4</sup> &lt;= target &lt;= 10<sup>4</sup></code></li>
</ul>


---
---

## 💡 Key Intuition

When a sorted array is rotated at a pivot point (e.g., `[4, 5, 6, 7, 0, 1, 2]`), dividing it in half at index `mid` guarantees that **at least one of the two sub-arrays will always be completely sorted**.

```
Array: [ 4,  5,  6,  7,  0,  1,  2 ]
                 ^ mid = 7

Left Sub-array  [4, 5, 6, 7] -> SORTED (nums[low] <= nums[mid])
Right Sub-array [0, 1, 2]    -> UN-SORTED

```

Because one side is guaranteed to be sorted, we can easily check if our `target` lies within the sorted side's range. If it does, we narrow our search to that side; if it doesn't, we eliminate it and search the other side.

---

## 🛠️ Step-by-Step Approach

1. **Initialize Pointers:** Set `low = 0` and `high = nums.size() - 1`.
2. **Loop Condition:** Continue while `low <= high`.
3. **Calculate Midpoint:** Find `mid = low + (high - low) / 2`.
4. **Target Check:** If `nums[mid] == target`, return `mid`.
5. **Identify the Sorted Half:**
* **If `nums[low] <= nums[mid]` (Left Half is Sorted):**
* Check if `target` falls within the left range: `nums[low] <= target < nums[mid]`.
* **Yes:** Search left side (`high = mid - 1`).
* **No:** Search right side (`low = mid + 1`).


* **Else (Right Half is Sorted):**
* Check if `target` falls within the right range: `nums[mid] < target <= nums[high]`.
* **Yes:** Search right side (`low = mid + 1`).
* **No:** Search left side (`high = mid - 1`).




6. **Not Found:** If the loop terminates without finding the target, return `-1`.

---

## 🔍 Code Review & Small Improvement

Your overall logic is completely correct! The algorithm properly handles the rotated search space.

### Minor Detail: Midpoint Calculation

In your code:

```cpp
int mid = (low + high) / 2;

```

While this works fine for small arrays, `(low + high)` can potentially cause **integer overflow** if the array size is extremely large. Changing it to:

```cpp
int mid = low + (high - low) / 2;

```

is safer C++ practice.

---

## ⏱️ Complexity Analysis

| Metric | Complexity | Explanation |
| --- | --- | --- |
| **Time Complexity** | **$O(\log n)$** | In every iteration, we eliminate half of the search space regardless of which sub-array is sorted. |
| **Space Complexity** | **$O(1)$** | Operates strictly in-place with a few index pointer variables (`low`, `high`, `mid`). |

---
