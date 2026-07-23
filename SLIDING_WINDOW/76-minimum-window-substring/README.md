<h2><a href="https://leetcode.com/problems/minimum-window-substring">Minimum Window Substring</a></h2> <img src='https://img.shields.io/badge/Difficulty-Hard-red' alt='Difficulty: Hard' /><hr><p>Given two strings <code>s</code> and <code>t</code> of lengths <code>m</code> and <code>n</code> respectively, return <em>the <strong>minimum window</strong></em> <span data-keyword="substring-nonempty"><strong><em>substring</em></strong></span><em> of </em><code>s</code><em> such that every character in </em><code>t</code><em> (<strong>including duplicates</strong>) is included in the window</em>. If there is no such substring, return <em>the empty string </em><code>&quot;&quot;</code>.</p>

<p>The testcases will be generated such that the answer is <strong>unique</strong>.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> s = &quot;ADOBECODEBANC&quot;, t = &quot;ABC&quot;
<strong>Output:</strong> &quot;BANC&quot;
<strong>Explanation:</strong> The minimum window substring &quot;BANC&quot; includes &#39;A&#39;, &#39;B&#39;, and &#39;C&#39; from string t.
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> s = &quot;a&quot;, t = &quot;a&quot;
<strong>Output:</strong> &quot;a&quot;
<strong>Explanation:</strong> The entire string s is the minimum window.
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> s = &quot;a&quot;, t = &quot;aa&quot;
<strong>Output:</strong> &quot;&quot;
<strong>Explanation:</strong> Both &#39;a&#39;s from t must be included in the window.
Since the largest window of s only has one &#39;a&#39;, return empty string.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>m == s.length</code></li>
	<li><code>n == t.length</code></li>
	<li><code>1 &lt;= m, n &lt;= 10<sup>5</sup></code></li>
	<li><code>s</code> and <code>t</code> consist of uppercase and lowercase English letters.</li>
</ul>

<p>&nbsp;</p>
<p><strong>Follow up:</strong> Could you find an algorithm that runs in <code>O(m + n)</code> time?</p>

---
---

## Approach Breakdown

The goal is to find the shortest substring in `s` that contains all the characters (including duplicates) present in `t`.

### Key Intuition

1. **Frequency Tracking:**
* Build a hash map (`charCount`) of required character counts from string `t`.
* Use `targetCharsRemaining` to keep track of how many characters from `t` still need to be matched in the current window.


2. **Expand the Window (`endIndex` loop):**
* Move `endIndex` to the right, adding `s[endIndex]` to the window.
* Decrement its count in `charCount`. If the character was still needed (`charCount[ch] > 0`), decrement `targetCharsRemaining`.


3. **Shrink the Window (`startIndex` loop):**
* Once `targetCharsRemaining == 0`, a valid window is found.
* Shrink the window from the left (`startIndex`) as much as possible while maintaining validity (i.e., until dropping `s[startIndex]` would cause a needed character count to fall below what `t` requires).
* Update `minWindow` if the current valid window length (`endIndex - startIndex + 1`) is smaller than the best recorded so far.


4. **Advance Past Validity:**
* Drop the starting character `s[startIndex]` to search for the next possible smaller valid window, incrementing `targetCharsRemaining` back up and advancing `startIndex`.



---

## Complexity Analysis

| Complexity | Measure | Reason |
| --- | --- | --- |
| **Time Complexity** | $\mathcal{O}(\Vert{}s\Vert{} + \Vert{}t\Vert{})$ | Building the hash map takes $\mathcal{O}(\Vert{}t\Vert{})$ time. In the main loop, both `endIndex` and `startIndex` traverse the string `s` at most once. Hash map operations take $\mathcal{O}(1)$ on average. |
| **Space Complexity** | $\mathcal{O}(K)$ | Uses a hash map to store frequencies. $K$ represents the number of unique characters in `t` (and `s`), which is at most $O(1)$ constant space (52 for ASCII English letters or 256 for extended ASCII). |
