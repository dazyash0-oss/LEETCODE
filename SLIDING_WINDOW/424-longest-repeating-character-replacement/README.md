<h2><a href="https://leetcode.com/problems/longest-repeating-character-replacement">Longest Repeating Character Replacement</a></h2> <img src='https://img.shields.io/badge/Difficulty-Medium-orange' alt='Difficulty: Medium' /><hr><p>You are given a string <code>s</code> and an integer <code>k</code>. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most <code>k</code> times.</p>

<p>Return <em>the length of the longest substring containing the same letter you can get after performing the above operations</em>.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> s = &quot;ABAB&quot;, k = 2
<strong>Output:</strong> 4
<strong>Explanation:</strong> Replace the two &#39;A&#39;s with two &#39;B&#39;s or vice versa.
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> s = &quot;AABABBA&quot;, k = 1
<strong>Output:</strong> 4
<strong>Explanation:</strong> Replace the one &#39;A&#39; in the middle with &#39;B&#39; and form &quot;AABBBBA&quot;.
The substring &quot;BBBB&quot; has the longest repeating letters, which is 4.
There may exists other ways to achieve this answer too.</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

---
---

## Approach Breakdown

The goal is to find the length of the longest substring containing the same character after replacing at most $k$ characters.

### Key Intuition

1. **Window Condition:** For any valid substring, the number of character replacements needed is:

$$\text{Replacements Needed} = \text{Window Size} - \text{Max Frequency}$$



where $\text{Max Frequency}$ is the count of the single most frequent character inside that window.
2. **Expanding the Window (`right` pointer):**
* Increment the frequency of `s[right]`.
* Update `maxFreq` with the highest frequency of any single character seen in the window so far.


3. **Shrinking/Shift Condition (`left` pointer):**
* If $(\text{Window Size} - \text{maxFreq}) > k$, the window contains too many "other" characters to replace.
* Instead of shrinking the window completely, we simply **shift** the window right by incrementing `left` once and decrementing `freq[s[left]]`.
* *Clever trick:* We don't need to re-evaluate or decrement `maxFreq` when shrinking because the window size only grows when we find a new, larger valid window (i.e., when `maxFreq` reaches a new record high).


4. **Final Result:** At the end of the loop, the maximum valid window size is preserved, which is given by `s.size() - left`.

---

## Walkthrough Example

Let's trace `s = "AABABBA"`, `k = 1`.

```
Index:    0   1   2   3   4   5   6
String:   A   A   B   A   B   B   A

```

| `right` | `s[right]` | `freq['A']`, `freq['B']` | `maxFreq` | Window Size | Formula: `size - maxFreq` | Action | Window `[left, right]` |
| --- | --- | --- | --- | --- | --- | --- | --- |
| **0** | A | A: 1, B: 0 | 1 | 1 | $1 - 1 = 0 \le 1$ | Valid | `"A"` |
| **1** | A | A: 2, B: 0 | 2 | 2 | $2 - 2 = 0 \le 1$ | Valid | `"AA"` |
| **2** | B | A: 2, B: 1 | 2 | 3 | $3 - 2 = 1 \le 1$ | Valid | `"AAB"` |
| **3** | A | A: 3, B: 1 | 3 | 4 | $4 - 3 = 1 \le 1$ | Valid | `"AABA"` |
| **4** | B | A: 3, B: 2 | 3 | 5 | $5 - 3 = 2 > 1$ | **Invalid!** Shift `left` (0 $\to$ 1) | `"ABAB"` |
| **5** | B | A: 2, B: 3 | 3 | 5 | $5 - 3 = 2 > 1$ | **Invalid!** Shift `left` (1 $\to$ 2) | `"BABB"` |
| **6** | A | A: 3, B: 2 | 3 | 5 | $5 - 3 = 2 > 1$ | **Invalid!** Shift `left` (2 $\to$ 3) | `"ABBA"` |

* **Final Return:** `s.size() - left` = $7 - 3 = \mathbf{4}$ (corresponds to `"AABA"` or `"ABBB"`).

---

## Complexity Analysis

| Complexity | Measure | Reason |
| --- | --- | --- |
| **Time Complexity** | $\mathcal{O}(n)$ | The `right` pointer iterates through the string once ($n$ steps). The `left` pointer moves at most $n$ times. Each check takes $\mathcal{O}(1)$ time. |
| **Space Complexity** | $\mathcal{O}(1)$ | Uses a fixed-size frequency array of length 26 to store uppercase English letter counts. |

<ul>
	<li><code>1 &lt;= s.length &lt;= 10<sup>5</sup></code></li>
	<li><code>s</code> consists of only uppercase English letters.</li>
	<li><code>0 &lt;= k &lt;= s.length</code></li>
</ul>
