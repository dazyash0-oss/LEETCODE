<h2><a href="https://leetcode.com/problems/is-subsequence">Is Subsequence</a></h2> <img src='https://img.shields.io/badge/Difficulty-Easy-brightgreen' alt='Difficulty: Easy' /><hr><p>Given two strings <code>s</code> and <code>t</code>, return <code>true</code><em> if </em><code>s</code><em> is a <strong>subsequence</strong> of </em><code>t</code><em>, or </em><code>false</code><em> otherwise</em>.</p>

<p>A <strong>subsequence</strong> of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., <code>&quot;ace&quot;</code> is a subsequence of <code>&quot;<u>a</u>b<u>c</u>d<u>e</u>&quot;</code> while <code>&quot;aec&quot;</code> is not).</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<pre><strong>Input:</strong> s = "abc", t = "ahbgdc"
<strong>Output:</strong> true
</pre><p><strong class="example">Example 2:</strong></p>
<pre><strong>Input:</strong> s = "axc", t = "ahbgdc"
<strong>Output:</strong> false
</pre>
<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>0 &lt;= s.length &lt;= 100</code></li>
	<li><code>0 &lt;= t.length &lt;= 10<sup>4</sup></code></li>
	<li><code>s</code> and <code>t</code> consist only of lowercase English letters.</li>
</ul>

<p>&nbsp;</p>
<strong>Follow up:</strong> Suppose there are lots of incoming <code>s</code>, say <code>s<sub>1</sub>, s<sub>2</sub>, ..., s<sub>k</sub></code> where <code>k &gt;= 10<sup>9</sup></code>, and you want to check one by one to see if <code>t</code> has its subsequence. In this scenario, how would you change your code?


---
---

# Approach: Two-Pointer Greedy Matching

A subsequence of a string is a new string formed from the original string by deleting some (or none) of the characters without disturbing the relative positions of the remaining characters.

1. **Dual Pointers:** The algorithm sets up two independent pointers: `sp` (tracking the index of string `s`) and `tp` (tracking the index of string `t`), both initialized to `0`.
2. **Linear Scan:** The `while` loop scans through both strings simultaneously. It terminates as soon as either pointer runs out of bounds (`sp < s.length() && tp < t.length()`).
3. **Greedy Matching:**
* Inside the loop, it checks if the characters at the current pointer positions match (`s[sp] == t[tp]`).
* If they match, it means we found the next required character of `s` inside `t`. The pointer `sp` is then advanced to look for the *next* character of `s`.
* Regardless of whether there is a match or not, the pointer `tp` is *always* advanced (`tp++`). This greedily searches through `t` to find matches in the correct relative order.


4. **Final Check:** After the loop ends, the function returns `sp == s.length()`. If `sp` successfully reached the end of string `s`, it proves that all characters of `s` were found sequentially inside `t`, meaning `s` is a valid subsequence.

---

## Complexities

### Time Complexity: $O(m)$

* **Why:** Where $m$ is the length of the target string `t`, and $n$ is the length of the string `s`. The `while` loop advances the pointer `tp` exactly once per iteration. In the worst-case scenario, the loop will run until `tp` reaches the end of `t`. Therefore, the time complexity is bounded by the length of the longer string, which is $O(m)$.

### Space Complexity: $O(1)$ (Constant Space)

* **Why:** The algorithm performs all operations entirely in-place. It only uses two integer pointer variables (`sp` and `tp`), requiring a fixed, nominal amount of memory that does not scale with the sizes of the input strings.
