<h2><a href="https://leetcode.com/problems/top-k-frequent-elements">Top K Frequent Elements</a></h2> <img src='https://img.shields.io/badge/Difficulty-Medium-orange' alt='Difficulty: Medium' /><hr><p>Given an integer array <code>nums</code> and an integer <code>k</code>, return <em>the</em> <code>k</code> <em>most frequent elements</em>. You may return the answer in <strong>any order</strong>.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<div class="example-block">
<p><strong>Input:</strong> <span class="example-io">nums = [1,1,1,2,2,3], k = 2</span></p>

<p><strong>Output:</strong> <span class="example-io">[1,2]</span></p>
</div>

<p><strong class="example">Example 2:</strong></p>

<div class="example-block">
<p><strong>Input:</strong> <span class="example-io">nums = [1], k = 1</span></p>

<p><strong>Output:</strong> <span class="example-io">[1]</span></p>
</div>

<p><strong class="example">Example 3:</strong></p>

<div class="example-block">
<p><strong>Input:</strong> <span class="example-io">nums = [1,2,1,2,1,2,3,1,3,2], k = 2</span></p>

<p><strong>Output:</strong> <span class="example-io">[1,2]</span></p>
</div>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= nums.length &lt;= 10<sup>5</sup></code></li>
	<li><code>-10<sup>4</sup> &lt;= nums[i] &lt;= 10<sup>4</sup></code></li>
	<li><code>k</code> is in the range <code>[1, the number of unique elements in the array]</code>.</li>
	<li>It is <strong>guaranteed</strong> that the answer is <strong>unique</strong>.</li>
</ul>

<p>&nbsp;</p>
<p><strong>Follow up:</strong> Your algorithm&#39;s time complexity must be better than <code>O(n log n)</code>, where n is the array&#39;s size.</p>



---
---

## **Approach Notes**

### **3-Step Strategy**

1. **Frequency Mapping:** Iterate through `nums` to build a map storing `{element -> frequency}`.
2. **Priority Ordering:** Push each `{frequency, element}` pair into a Max-Heap. Storing frequency as the first value ensures the heap prioritizes numbers by occurrence count.
3. **Top-K Extraction:** Extract the top $K$ elements from the heap into the result vector.

### **Why `pair<int, int>`?**

* By default, C++ `std::pair` compares the `first` element before `second`.
* Storing `{frequency, element}` means the priority queue automatically sorts elements from **highest frequency to lowest frequency** without requiring a custom comparator.

---

## **Heap Notes**

### **Max-Heap (`priority_queue<pair<int,int>>`)**

* **Default Behavior:** In C++, `std::priority_queue` is a **Max-Heap** by default.
* **Top Property:** `pq.top()` always yields the largest pair currently in the heap.
* **Key Operations:**
* `push()`: Insert element $\rightarrow \mathcal{O}(\log U)$
* `top()`: Access largest element $\rightarrow \mathcal{O}(1)$
* `pop()`: Remove largest element $\rightarrow \mathcal{O}(\log U)$



---

## **Heap Optimizations (Min-Heap vs. Max-Heap)**

| Metric | Max-Heap (Your Approach) | Min-Heap (Optimized) |
| --- | --- | --- |
| **Heap Size** | Stores **all $U$ unique elements** | Capped at **$K$ elements** |
| **Heap Push Time** | $\mathcal{O}(U \log U)$ | $\mathcal{O}(U \log K)$ |
| **Heap Pop Time** | $\mathcal{O}(K \log U)$ | $\mathcal{O}(K \log K)$ |
| **Eviction Logic** | Extract $K$ times after filling | Evict smallest whenever `heap.size() > K` |

### **Min-Heap Declaration in C++**

```cpp
// Orders pairs in ascending order (smallest frequency at top)
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

```
