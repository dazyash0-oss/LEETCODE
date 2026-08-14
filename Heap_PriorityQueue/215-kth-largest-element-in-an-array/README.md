<h2><a href="https://leetcode.com/problems/kth-largest-element-in-an-array">Kth Largest Element in an Array</a></h2> <img src='https://img.shields.io/badge/Difficulty-Medium-orange' alt='Difficulty: Medium' /><hr><p>Given an integer array <code>nums</code> and an integer <code>k</code>, return <em>the</em> <code>k<sup>th</sup></code> <em>largest element in the array</em>.</p>

<p>Note that it is the <code>k<sup>th</sup></code> largest element in the sorted order, not the <code>k<sup>th</sup></code> distinct element.</p>

<p>Can you solve it without sorting?</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<pre><strong>Input:</strong> nums = [3,2,1,5,6,4], k = 2
<strong>Output:</strong> 5
</pre><p><strong class="example">Example 2:</strong></p>
<pre><strong>Input:</strong> nums = [3,2,3,1,2,4,5,5,6], k = 4
<strong>Output:</strong> 4
</pre>
<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= k &lt;= nums.length &lt;= 10<sup>5</sup></code></li>
	<li><code>-10<sup>4</sup> &lt;= nums[i] &lt;= 10<sup>4</sup></code></li>
</ul>


---
---

## **Approach Notes**

### **Max-Heap Strategy (Your Approach)**

1. **Build Heap:** Push all $N$ elements into a `std::priority_queue` (Max-Heap by default in C++).
2. **Extract K-1 Elements:** Pop the maximum element $K - 1$ times.
3. **Target Element:** The element remaining at `pq.top()` is the $K$-th largest element in the array.

---

## **Complexity Analysis**

Let $N$ be the total size of `nums`.

* **Time Complexity:**
* **Pushing all elements:** $\mathcal{O}(N \log N)$ (or $\mathcal{O}(N)$ if built using heapify/constructor).
* **Popping $K-1$ times:** $\mathcal{O}(K \log N)$.
* **Overall Time:** **$\mathcal{O}(N \log N)$** in worst case.


* **Space Complexity:** **$\mathcal{O}(N)$** to store all $N$ elements in the priority queue.

---

## **Heap Trade-offs: Min-Heap vs. Max-Heap**

While your Max-Heap approach works, a **Min-Heap bounded to size $K$** is preferred in interviews due to optimal space and time guarantees.



### **Comparison Table**

| Strategy | Time Complexity | Space Complexity | Best Used When |
| --- | --- | --- | --- |
| **Max-Heap** (Your Code) | $\mathcal{O}(N + K \log N)$ | $\mathcal{O}(N)$ | $K$ is small and $N$ fits easily in memory. |
| **Min-Heap of Size $K$** | $\mathcal{O}(N \log K)$ | $\mathcal{O}(K)$ | $K \ll N$ or stream of continuous inputs. |
| **QuickSelect** | $\mathcal{O}(N)$ average | $\mathcal{O}(1)$ auxiliary | Standard in-place array partitioning. |
