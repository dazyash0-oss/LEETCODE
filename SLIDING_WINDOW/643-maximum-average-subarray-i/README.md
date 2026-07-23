<h2><a href="https://leetcode.com/problems/maximum-average-subarray-i">Maximum Average Subarray I</a></h2> <img src='https://img.shields.io/badge/Difficulty-Easy-brightgreen' alt='Difficulty: Easy' /><hr><p>You are given an integer array <code>nums</code> consisting of <code>n</code> elements, and an integer <code>k</code>.</p>

<p>Find a contiguous subarray whose <strong>length is equal to</strong> <code>k</code> that has the maximum average value and return <em>this value</em>. Any answer with a calculation error less than <code>10<sup>-5</sup></code> will be accepted.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> nums = [1,12,-5,-6,50,3], k = 4
<strong>Output:</strong> 12.75000
<strong>Explanation:</strong> Maximum average is (12 - 5 - 6 + 50) / 4 = 51 / 4 = 12.75
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> nums = [5], k = 1
<strong>Output:</strong> 5.00000
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>n == nums.length</code></li>
	<li><code>1 &lt;= k &lt;= n &lt;= 10<sup>5</sup></code></li>
	<li><code>-10<sup>4</sup> &lt;= nums[i] &lt;= 10<sup>4</sup></code></li>
</ul>


---
---

## Approach Breakdown

To find the maximum average of any contiguous subarray of length $k$, we only need to find the **maximum sum** of a contiguous subarray of length $k$. Dividing that maximum sum by $k$ gives the maximum average.

### Key Intuition

1. **First Window Initialization:** Compute the sum of the first $k$ elements (`nums[0]` through `nums[k-1]`) and set `maxSum` equal to this initial sum.
2. **Slide the Window:** Instead of re-calculating the sum of all $k$ elements from scratch at every step (which would take $\mathcal{O}(k)$ per window), slide the window one element to the right:
* **Subtract** the element leaving the window on the left (`nums[i - k]`).
* **Add** the element entering the window on the right (`nums[i]`).
* Update `maxSum` if the new running `sum` is larger.


3. **Compute Average:** Convert `maxSum` to a double and divide by $k$.

---

## Complexity Analysis

| Complexity | Measure | Reason |
| --- | --- | --- |
| **Time Complexity** | $\mathcal{O}(n)$ | We iterate through the array twice: once to sum the first $k$ elements, and once from index $k$ to $n-1$. Each step takes $\mathcal{O}(1)$ time. |
| **Space Complexity** | $\mathcal{O}(1)$ | Uses only a few scalar variables (`sum`, `maxSum`, `i`), requiring no additional dynamic memory allocation. |
