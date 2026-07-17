<h2><a href="https://leetcode.com/problems/merge-strings-alternately">Merge Strings Alternately</a></h2> <img src='https://img.shields.io/badge/Difficulty-Easy-brightgreen' alt='Difficulty: Easy' /><hr><p>You are given two strings <code>word1</code> and <code>word2</code>. Merge the strings by adding letters in alternating order, starting with <code>word1</code>. If a string is longer than the other, append the additional letters onto the end of the merged string.</p>

<p>Return <em>the merged string.</em></p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> word1 = &quot;abc&quot;, word2 = &quot;pqr&quot;
<strong>Output:</strong> &quot;apbqcr&quot;
<strong>Explanation:</strong>&nbsp;The merged string will be merged as so:
word1:  a   b   c
word2:    p   q   r
merged: a p b q c r
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> word1 = &quot;ab&quot;, word2 = &quot;pqrs&quot;
<strong>Output:</strong> &quot;apbqrs&quot;
<strong>Explanation:</strong>&nbsp;Notice that as word2 is longer, &quot;rs&quot; is appended to the end.
word1:  a   b 
word2:    p   q   r   s
merged: a p b q   r   s
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> word1 = &quot;abcd&quot;, word2 = &quot;pq&quot;
<strong>Output:</strong> &quot;apbqcd&quot;
<strong>Explanation:</strong>&nbsp;Notice that as word1 is longer, &quot;cd&quot; is appended to the end.
word1:  a   b   c   d
word2:    p   q 
merged: a p b q c   d
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= word1.length, word2.length &lt;= 100</code></li>
	<li><code>word1</code> and <code>word2</code> consist of lowercase English letters.</li>
</ul>

---
---

# Approach: Two-Pointer Simulation with Single Loop

The problem requires merging two strings by alternating characters, starting with `word1`. If one string is longer than the other, the additional characters should just be appended to the end.

1. **Unified Pointer (`i`):** Instead of managing separate indices for both strings, this solution smartly uses a single index `i` initialized to `0`. Since we are alternating characters at the exact same index positions, one variable is all we need.
2. **Flexible Loop Condition:** The loop runs as long as `i` is less than the length of *either* `word1` OR `word2` (`i < word1.length() || i < word2.length()`). This ensures the loop won't stop early if one string runs out of characters.
3. **Safe Bounds Checking:** Inside the loop, two independent `if` statements check if `i` is still within the valid range for each string:
* If `i` is within `word1`, its character is appended.
* If `i` is within `word2`, its character is appended.


4. **Natural Appending:** When the shorter string is completely exhausted, its corresponding `if` condition simply evaluates to `false`. The loop continues, seamlessly appending only the remaining characters of the longer string until it finishes.

---

## Complexities

### Time Complexity: $O(n + m)$

* **Why:** The loop runs exactly $\max(n, m)$ times, where $n$ is the length of `word1` and $m$ is the length of `word2`. Inside the loop, appending a character to a string takes $O(1)$ amortized time. Therefore, the total time spent is directly proportional to the total number of characters across both strings, resulting in a linear time complexity of $O(n + m)$.

### Space Complexity: $O(1)$ or $O(n + m)$

* **Why:**
* **Auxiliary Space:** The algorithm only uses a few primitive variables (`i`) which take up $O(1)$ constant space. No extra data structures are created.
* **Output Space:** If we count the space required for the output, the `result` string stores exactly $n + m$ characters, which takes $O(n + m)$ space. In interview contexts, memory used strictly for the mandatory return value is usually excluded from auxiliary space analysis, making it effectively $O(1)$.
