<h2><a href="https://leetcode.com/problems/median-of-two-sorted-arrays">Median of Two Sorted Arrays</a></h2> <img src='https://img.shields.io/badge/Difficulty-Hard-red' alt='Difficulty: Hard' /><hr><p>Given two sorted arrays <code>nums1</code> and <code>nums2</code> of size <code>m</code> and <code>n</code> respectively, return <strong>the median</strong> of the two sorted arrays.</p>

<p>The overall run time complexity should be <code>O(log (m+n))</code>.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> nums1 = [1,3], nums2 = [2]
<strong>Output:</strong> 2.00000
<strong>Explanation:</strong> merged array = [1,2,3] and median is 2.
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> nums1 = [1,2], nums2 = [3,4]
<strong>Output:</strong> 2.50000
<strong>Explanation:</strong> merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>nums1.length == m</code></li>
	<li><code>nums2.length == n</code></li>
	<li><code>0 &lt;= m &lt;= 1000</code></li>
	<li><code>0 &lt;= n &lt;= 1000</code></li>
	<li><code>1 &lt;= m + n &lt;= 2000</code></li>
	<li><code>-10<sup>6</sup> &lt;= nums1[i], nums2[i] &lt;= 10<sup>6</sup></code></li>
</ul>


---
---

## 💡 Key Intuition

The median of a combined sorted array splits all elements into two equal halves:

* **Left Half:** Contains $\lfloor \frac{n_1 + n_2 + 1}{2} \rfloor$ elements, all of which must be $\le$ every element in the **Right Half**.

Instead of merging the two arrays, we can binary search for the correct **partition index** in the smaller array (`nums1`).

For a given cut point `cut1` in `nums1`:

* `cut1` elements come from `nums1` for the left half.
* `cut2 = partition - cut1` elements must come from `nums2` for the left half.

```
nums1: [ ...  l1 ] | [ r1  ... ]
nums2: [ ...  l2 ] | [ r2  ... ]

```

A partition is valid **if and only if**:

1. $l_1 \le r_2$
2. $l_2 \le r_1$

Because `nums1` and `nums2` are already sorted, $l_1 \le r_1$ and $l_2 \le r_2$ are naturally true.

---

## 🛠️ Step-by-Step Approach

1. **Ensure $n_1 \le n_2$:** Swap inputs if `nums1` is larger than `nums2`. This guarantees the binary search range is minimal, resulting in $O(\log(\min(m, n)))$ time complexity and preventing negative cut indices.
2. **Define Left Half Size:** Set `partition = (n1 + n2 + 1) / 2`.
3. **Binary Search Range:** Initialize `left = 0` and `right = n1`.
4. **Evaluate Cuts:**
* Calculate `cut1 = (left + right) / 2` and `cut2 = partition - cut1`.
* Extract boundary elements:
* $l_1 = \text{nums1}[cut1 - 1]$ (or $-\infty$ if $cut1 = 0$)
* $r_1 = \text{nums1}[cut1]$ (or $+\infty$ if $cut1 = n_1$)
* $l_2 = \text{nums2}[cut2 - 1]$ (or $-\infty$ if $cut2 = 0$)
* $r_2 = \text{nums2}[cut2]$ (or $+\infty$ if $cut2 = n_2$)




5. **Adjust Search Space:**
* If **$l_1 \le r_2$ and $l_2 \le r_1$**, we found the target partition!
* If total length is **odd**: $\text{Median} = \max(l_1, l_2)$
* If total length is **even**: $\text{Median} = \frac{\max(l_1, l_2) + \min(r_1, r_2)}{2.0}$


* If **$l_1 > r_2$**, we took too many elements from `nums1`. Move left: `right = cut1 - 1`.
* If **$l_2 > r_1$**, we took too few elements from `nums1`. Move right: `left = cut1 + 1`.



---

## 🔍 Notes & Improvements

 solution works well and correctly implements the core partition logic! A few small refinements can make it cleaner and more robust:

1. **Redundant Edge Cases:** The explicit `n1 == 0` and `n2 == 0` checks are redundant. The boundary guard values (`INT_MIN` / `INT_MAX`) handle empty array scenarios automatically during the binary search loops.
2. **Loop Structure:** Using a standard `while (left1 <= right1)` loop is preferred over `do-while` for standard binary search practice.



---

## ⏱️ Complexity Analysis

| Metric | Complexity | Explanation |
| --- | --- | --- |
| **Time Complexity** | **$O(\log(\min(m, n)))$** | We perform binary search exclusively on the smaller array of size $\min(m, n)$. Each step cuts the search space in half. |
| **Space Complexity** | **$O(1)$** | Memory usage is constant since we only use integer variables (`cut1`, `cut2`, $l_1$, $r_1$, $l_2$, $r_2$) without allocating additional dynamic memory. |
