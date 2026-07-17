<h2><a href="https://leetcode.com/problems/roman-to-integer">Roman to Integer</a></h2> <img src='https://img.shields.io/badge/Difficulty-Easy-brightgreen' alt='Difficulty: Easy' /><hr><p>Roman numerals are represented by seven different symbols:&nbsp;<code>I</code>, <code>V</code>, <code>X</code>, <code>L</code>, <code>C</code>, <code>D</code> and <code>M</code>.</p>

<pre>
<strong>Symbol</strong>       <strong>Value</strong>
I             1
V             5
X             10
L             50
C             100
D             500
M             1000</pre>

<p>For example,&nbsp;<code>2</code> is written as <code>II</code>&nbsp;in Roman numeral, just two ones added together. <code>12</code> is written as&nbsp;<code>XII</code>, which is simply <code>X + II</code>. The number <code>27</code> is written as <code>XXVII</code>, which is <code>XX + V + II</code>.</p>

<p>Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not <code>IIII</code>. Instead, the number four is written as <code>IV</code>. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as <code>IX</code>. There are six instances where subtraction is used:</p>

<ul>
	<li><code>I</code> can be placed before <code>V</code> (5) and <code>X</code> (10) to make 4 and 9.&nbsp;</li>
	<li><code>X</code> can be placed before <code>L</code> (50) and <code>C</code> (100) to make 40 and 90.&nbsp;</li>
	<li><code>C</code> can be placed before <code>D</code> (500) and <code>M</code> (1000) to make 400 and 900.</li>
</ul>

<p>Given a roman numeral, convert it to an integer.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> s = &quot;III&quot;
<strong>Output:</strong> 3
<strong>Explanation:</strong> III = 3.
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> s = &quot;LVIII&quot;
<strong>Output:</strong> 58
<strong>Explanation:</strong> L = 50, V= 5, III = 3.
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> s = &quot;MCMXCIV&quot;
<strong>Output:</strong> 1994
<strong>Explanation:</strong> M = 1000, CM = 900, XC = 90 and IV = 4.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= s.length &lt;= 15</code></li>
	<li><code>s</code> contains only&nbsp;the characters <code>(&#39;I&#39;, &#39;V&#39;, &#39;X&#39;, &#39;L&#39;, &#39;C&#39;, &#39;D&#39;, &#39;M&#39;)</code>.</li>
	<li>It is <strong>guaranteed</strong>&nbsp;that <code>s</code> is a valid roman numeral in the range <code>[1, 3999]</code>.</li>
</ul>

---
---

# Approach: Left-to-Right Scan with Look-Ahead

The core logic relies on a simple observation of Roman numeral rules: usually, symbols are placed from largest to smallest. However, when a **smaller** value symbol appears **before a larger** value symbol, it indicates subtraction (e.g., `IV` is $5 - 1 = 4$).

1. **Hash Map Lookup:** The code uses an `unordered_map` to store the fixed values of individual Roman characters (`I` to `M`) for quick $O(1)$ lookups.
2. **Look-Ahead Comparison:** The algorithm iterates through the string `s` from left to right. For each character at index `i`:
* It fetches the current symbol's value (`curr`).
* It checks if there is a next character (`i + 1 < s.size()`). If yes, it fetches its value (`next`); otherwise, it sets `next` to `0`.


3. **Conditional Math:**
* **Subtraction Case:** If `curr < next`, it means we are encountering a subtractive pair (like `IX` or `CD`). Instead of waiting to process them together, the code cleanly subtracts `curr` from the `result` immediately.
* **Addition Case:** If `curr >= next`, it follows the standard rule, and `curr` is added to the `result`.



---

## Complexities

### Time Complexity: $O(n)$

* **Why:** The algorithm loops through the string `s` exactly once, where $n$ is the length of the string. Inside the loop, looking up values in an `unordered_map` takes $O(1)$ average time complexity. Therefore, the time scales linearly with the length of the input string.
* *(Note: In the context of LeetCode constraints where the valid Roman input is capped up to 3999, the max length of the string is 15, making this practically $O(1)$ in execution, but theoretically $O(n)$ based on string size).*

### Space Complexity: $O(1)$ (Constant Space)

* **Why:** The `unordered_map` stores exactly 7 key-value pairs (`I`, `V`, `X`, `L`, `C`, `D`, `M`). Because the size of this map is fixed and never changes regardless of how long the input string `s` is, it consumes $O(1)$ auxiliary space.
