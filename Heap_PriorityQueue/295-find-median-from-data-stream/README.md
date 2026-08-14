<h2><a href="https://leetcode.com/problems/find-median-from-data-stream">Find Median from Data Stream</a></h2> <img src='https://img.shields.io/badge/Difficulty-Hard-red' alt='Difficulty: Hard' /><hr><p>The <strong>median</strong> is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.</p>

<ul>
	<li>For example, for <code>arr = [2,3,4]</code>, the median is <code>3</code>.</li>
	<li>For example, for <code>arr = [2,3]</code>, the median is <code>(2 + 3) / 2 = 2.5</code>.</li>
</ul>

<p>Implement the MedianFinder class:</p>

<ul>
	<li><code>MedianFinder()</code> initializes the <code>MedianFinder</code> object.</li>
	<li><code>void addNum(int num)</code> adds the integer <code>num</code> from the data stream to the data structure.</li>
	<li><code>double findMedian()</code> returns the median of all elements so far. Answers within <code>10<sup>-5</sup></code> of the actual answer will be accepted.</li>
</ul>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input</strong>
[&quot;MedianFinder&quot;, &quot;addNum&quot;, &quot;addNum&quot;, &quot;findMedian&quot;, &quot;addNum&quot;, &quot;findMedian&quot;]
[[], [1], [2], [], [3], []]
<strong>Output</strong>
[null, null, null, 1.5, null, 2.0]

<strong>Explanation</strong>
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>-10<sup>5</sup> &lt;= num &lt;= 10<sup>5</sup></code></li>
	<li>There will be at least one element in the data structure before calling <code>findMedian</code>.</li>
	<li>At most <code>5 * 10<sup>4</sup></code> calls will be made to <code>addNum</code> and <code>findMedian</code>.</li>
</ul>

<p>&nbsp;</p>
<p><strong>Follow up:</strong></p>

<ul>
	<li>If all integer numbers from the stream are in the range <code>[0, 100]</code>, how would you optimize your solution?</li>
	<li>If <code>99%</code> of all integer numbers from the stream are in the range <code>[0, 100]</code>, how would you optimize your solution?</li>
</ul>

---
---

## **Approach Notes**

### **Core Idea: Two Heaps Splitting the Data**

Instead of keeping a fully sorted array (which takes $\mathcal{O}(N)$ to insert each new number), divide the numbers into two halves using two heaps:

1. **`maxHeap` (Left Half):** Stores the **smaller half** of the numbers.
* `maxHeap.top()` gives the **largest value of the lower half**.


2. **`minHeap` (Right Half):** Stores the **larger half** of the numbers.
* `minHeap.top()` gives the **smallest value of the upper half**.



By keeping the numbers split at the exact midpoint, the median is always available in $\mathcal{O}(1)$ time directly from the tops of the two heaps.

---

## **Two-Heap Invariants & Balance Mechanics**

To ensure the algorithm works correctly, two invariants are strictly maintained during every `addNum` call:

### **1. Ordering Invariant**

> Every element in `maxHeap` must be $\le$ every element in `minHeap`.

* **How your code enforces this:**
When a new number arrives, it is first pushed to `maxHeap`. Then, `maxHeap.top()` is immediately transferred to `minHeap`. This guarantees that any large value that doesn't belong in the lower half automatically routes to the upper half.

### **2. Size-Balance Invariant**

> Either `maxHeap.size() == minHeap.size()` (even number of total elements)
> or `maxHeap.size() == minHeap.size() + 1` (odd number of total elements).

* **How your code enforces this:**
If `minHeap` ever ends up larger than `maxHeap`, pop the smallest element from `minHeap` and push it back to `maxHeap`.

---

### **Calculating Median (`findMedian`)**

* **Odd total elements:** `maxHeap` has 1 more element than `minHeap`.
$$\text{Median} = \text{maxHeap.top()}$$


* **Even total elements:** Both heaps have the exact same size.
$$\text{Median} = \frac{\text{maxHeap.top()} + \text{minHeap.top()}}{2.0}$$



---

## **Complexity Analysis**

| Operation | Time Complexity | Reason |
| --- | --- | --- |
| **`addNum(num)`** | $\mathcal{O}(\log N)$ | At most 3 heap insertions/removals per call. |
| **`findMedian()`** | $\mathcal{O}(1)$ | Only inspects `maxHeap.top()` and `minHeap.top()`. |
| **Space Complexity** | $\mathcal{O}(N)$ | Stores $N$ total elements split across both heaps. |
