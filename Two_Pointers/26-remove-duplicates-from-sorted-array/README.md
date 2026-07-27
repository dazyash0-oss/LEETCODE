<h2><a href="https://leetcode.com/problems/remove-duplicates-from-sorted-array">Remove Duplicates from Sorted Array</a></h2> <img src='https://img.shields.io/badge/Difficulty-Easy-brightgreen' alt='Difficulty: Easy' /><hr><p>Given an integer array <code>nums</code> sorted in <strong>non-decreasing order</strong>, remove the duplicates <a href="https://en.wikipedia.org/wiki/In-place_algorithm" target="_blank"><strong>in-place</strong></a> such that each unique element appears only <strong>once</strong>. The <strong>relative order</strong> of the elements should be kept the <strong>same</strong>.</p>

<p>Consider the number of <em>unique elements</em> in&nbsp;<code>nums</code> to be <code>k<strong>​​​​​​​</strong></code>​​​​​​​. <meta charset="UTF-8" />After removing duplicates, return the number of unique elements&nbsp;<code>k</code>.</p>

<p><meta charset="UTF-8" />The first&nbsp;<code>k</code>&nbsp;elements of&nbsp;<code>nums</code>&nbsp;should contain the unique numbers in <strong>sorted order</strong>. The remaining elements beyond index&nbsp;<code>k - 1</code>&nbsp;can be ignored.</p>

<p><strong>Custom Judge:</strong></p>

<p>The judge will test your solution with the following code:</p>

<pre>
int[] nums = [...]; // Input array
int[] expectedNums = [...]; // The expected answer with correct length

int k = removeDuplicates(nums); // Calls your implementation

assert k == expectedNums.length;
for (int i = 0; i &lt; k; i++) {
    assert nums[i] == expectedNums[i];
}
</pre>

<p>If all assertions pass, then your solution will be <strong>accepted</strong>.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> nums = [1,1,2]
<strong>Output:</strong> 2, nums = [1,2,_]
<strong>Explanation:</strong> Your function should return k = 2, with the first two elements of nums being 1 and 2 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> nums = [0,0,1,1,1,2,2,3,3,4]
<strong>Output:</strong> 5, nums = [0,1,2,3,4,_,_,_,_,_]
<strong>Explanation:</strong> Your function should return k = 5, with the first five elements of nums being 0, 1, 2, 3, and 4 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= nums.length &lt;= 3 * 10<sup>4</sup></code></li>
	<li><code>-100 &lt;= nums[i] &lt;= 100</code></li>
	<li><code>nums</code> is sorted in <strong>non-decreasing</strong> order.</li>
</ul>
---
---

## The Approach

1. **Base Case:**
If the vector is empty, return `0` immediately.
2. **Initialize Two Pointers:**
* **`i` (Slow Pointer / Write Index):** Tracks where the next unique element should be placed. Starts at index `1` because the first element (`nums[0]`) is always unique relative to itself.
* **`j` (Fast Pointer / Read Index):** Scans through the array from left to right (starts at index `1`).


3. **In-Place Modification:**
* Compare the current element `nums[j]` with the last confirmed unique element `nums[i - 1]`.
* **If `nums[j] != nums[i - 1]`:** You've found a new unique number. Write it into the slot `nums[i]` and increment `i` to reserve the next slot.
* **If `nums[j] == nums[i - 1]`:** It's a duplicate. Skip it by letting the loop increment `j` without updating `i`.


4. **Return Result:**
When `j` finishes scanning, `i` holds the total count of unique elements, and the first `i` positions in `nums` hold those unique values in their original order.

---

## Complexity Analysis

### Time Complexity: $\mathcal{O}(N)$

* The fast pointer `j` iterates through the array of size $N$ exactly once.
* All operations inside the loop (comparisons and assignments) run in $\mathcal{O}(1)$ constant time.

### Space Complexity: $\mathcal{O}(1)$

* Modifies the array **in-place**.
* Only uses two integer variables (`i` and `j`), requiring no additional memory regardless of the array size.
