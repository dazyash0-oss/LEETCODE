<h2><a href="https://leetcode.com/problems/sliding-window-maximum">Sliding Window Maximum</a></h2> <img src='https://img.shields.io/badge/Difficulty-Hard-red' alt='Difficulty: Hard' /><hr><p>You are given an array of integers&nbsp;<code>nums</code>, there is a sliding window of size <code>k</code> which is moving from the very left of the array to the very right. You can only see the <code>k</code> numbers in the window. Each time the sliding window moves right by one position.</p>

<p>Return <em>the max sliding window</em>.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> nums = [1,3,-1,-3,5,3,6,7], k = 3
<strong>Output:</strong> [3,3,5,5,6,7]
<strong>Explanation:</strong> 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       <strong>3</strong>
 1 [3  -1  -3] 5  3  6  7       <strong>3</strong>
 1  3 [-1  -3  5] 3  6  7      <strong> 5</strong>
 1  3  -1 [-3  5  3] 6  7       <strong>5</strong>
 1  3  -1  -3 [5  3  6] 7       <strong>6</strong>
 1  3  -1  -3  5 [3  6  7]      <strong>7</strong>
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> nums = [1], k = 1
<strong>Output:</strong> [1]
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

---
---

## Approach Breakdown

The goal is to find the maximum element in every sliding window of size $k$. A naive solution checking all elements in each window takes $\mathcal{O}(n \cdot k)$ time. Using a monotonic deque brings this down to $\mathcal{O}(n)$.

### Key Intuition

1. **Store Indices, Not Values:** Store the *indices* of array elements in the deque instead of their values. This makes it easy to check whether an element has fallen out of the left side of the sliding window.
2. **Maintain Decreasing Order:** Ensure the deque always holds elements in **strictly decreasing order** of their values from front to back:
* The front of the deque (`dq.front()`) will **always hold the index of the maximum element** in the current window.
* When a new element `nums[i]` comes in, any smaller (or equal) elements at the back of the deque will *never* be the maximum for the current or future windows (since `nums[i]` is larger and lasts longer). So, pop them off the back (`dq.pop_back()`).


3. **Window Maintenance:**
* **Slide Out Old Elements:** Before pushing index `i`, check if the front element has moved out of the current window (`dq.front() <= i - k`). If so, pop it from the front (`dq.pop_front()`).
* **Push Current Index:** Push `i` to the back of the deque.
* **Collect Result:** Once `i` reaches $k - 1$ (the end of the first complete window), the front of the deque holds the maximum for that window. Record `nums[dq.front()]`.



---

## Complexity Analysis

| Complexity | Measure | Reason |
| --- | --- | --- |
| **Time Complexity** | $\mathcal{O}(n)$ | Each index $0$ to $n-1$ is pushed into the deque **exactly once** and popped **at most once**. Even though there is a nested `while` loop, the total number of `pop_back()` operations across the entire execution is bounded by $n$. |
| **Space Complexity** | $\mathcal{O}(k)$ | At any given time, the deque stores at most $k$ indices (the size of the window). <br>

<br>*(Note: Auxiliary space for the `ans` array is $\mathcal{O}(n - k + 1)$ to hold the output).* |

<ul>
	<li><code>1 &lt;= nums.length &lt;= 10<sup>5</sup></code></li>
	<li><code>-10<sup>4</sup> &lt;= nums[i] &lt;= 10<sup>4</sup></code></li>
	<li><code>1 &lt;= k &lt;= nums.length</code></li>
</ul>
