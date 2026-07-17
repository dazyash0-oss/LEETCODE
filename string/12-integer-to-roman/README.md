<h2><a href="https://leetcode.com/problems/integer-to-roman">Integer to Roman</a></h2> <img src='https://img.shields.io/badge/Difficulty-Medium-orange' alt='Difficulty: Medium' /><hr><p>Seven different symbols represent Roman numerals with the following values:</p>

<table>
	<thead>
		<tr>
			<th>Symbol</th>
			<th>Value</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>I</td>
			<td>1</td>
		</tr>
		<tr>
			<td>V</td>
			<td>5</td>
		</tr>
		<tr>
			<td>X</td>
			<td>10</td>
		</tr>
		<tr>
			<td>L</td>
			<td>50</td>
		</tr>
		<tr>
			<td>C</td>
			<td>100</td>
		</tr>
		<tr>
			<td>D</td>
			<td>500</td>
		</tr>
		<tr>
			<td>M</td>
			<td>1000</td>
		</tr>
	</tbody>
</table>

<p>Roman numerals are formed by appending&nbsp;the conversions of&nbsp;decimal place values&nbsp;from highest to lowest. Converting a decimal place value into a Roman numeral has the following rules:</p>

<ul>
	<li>If the value does not start with 4 or&nbsp;9, select the symbol of the maximal value that can be subtracted from the input, append that symbol to the result, subtract its value, and convert the remainder to a Roman numeral.</li>
	<li>If the value starts with 4 or 9 use the&nbsp;<strong>subtractive form</strong>&nbsp;representing&nbsp;one symbol subtracted from the following symbol, for example,&nbsp;4 is 1 (<code>I</code>) less than 5 (<code>V</code>): <code>IV</code>&nbsp;and 9 is 1 (<code>I</code>) less than 10 (<code>X</code>): <code>IX</code>.&nbsp;Only the following subtractive forms are used: 4 (<code>IV</code>), 9 (<code>IX</code>),&nbsp;40 (<code>XL</code>), 90 (<code>XC</code>), 400 (<code>CD</code>) and 900 (<code>CM</code>).</li>
	<li>Only powers of 10 (<code>I</code>, <code>X</code>, <code>C</code>, <code>M</code>) can be appended consecutively at most 3 times to represent multiples of 10. You cannot append 5&nbsp;(<code>V</code>), 50 (<code>L</code>), or 500 (<code>D</code>) multiple times. If you need to append a symbol&nbsp;4 times&nbsp;use the <strong>subtractive form</strong>.</li>
</ul>

<p>Given an integer, convert it to a Roman numeral.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<div class="example-block">
<p><strong>Input:</strong> <span class="example-io">num = 3749</span></p>

<p><strong>Output:</strong> <span class="example-io">&quot;MMMDCCXLIX&quot;</span></p>

<p><strong>Explanation:</strong></p>

<pre>
3000 = MMM as 1000 (M) + 1000 (M) + 1000 (M)
 700 = DCC as 500 (D) + 100 (C) + 100 (C)
  40 = XL as 10 (X) less of 50 (L)
   9 = IX as 1 (I) less of 10 (X)
Note: 49 is not 1 (I) less of 50 (L) because the conversion is based on decimal places
</pre>
</div>

<p><strong class="example">Example 2:</strong></p>

<div class="example-block">
<p><strong>Input:</strong> <span class="example-io">num = 58</span></p>

<p><strong>Output:</strong> <span class="example-io">&quot;LVIII&quot;</span></p>

<p><strong>Explanation:</strong></p>

<pre>
50 = L
 8 = VIII
</pre>
</div>

<p><strong class="example">Example 3:</strong></p>

<div class="example-block">
<p><strong>Input:</strong> <span class="example-io">num = 1994</span></p>

<p><strong>Output:</strong> <span class="example-io">&quot;MCMXCIV&quot;</span></p>

<p><strong>Explanation:</strong></p>

<pre>
1000 = M
 900 = CM
  90 = XC
   4 = IV
</pre>
</div>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= num &lt;= 3999</code></li>
</ul>

This is a clean, optimal, and standard greedy approach to solving the **Integer to Roman** problem.

---

# Approach: Greedy Algorithm

The problem requires converting an integer into its Roman numeral representation. Roman numerals are written largest to smallest from left to right. Because of this structural property, a **greedy approach** works perfectly: we always want to use the largest possible Roman numeral value at any given step.

1. **Mapping Values to Symbols:** We store all unique Roman numeral symbols along with their corresponding integer values in a descending-ordered list (`valueSymbols`). This list explicitly includes the standard subtraction cases (like 900 for "CM", 40 for "XL") to natively handle the subtractive logic without complex conditional checks.
2. **Iterative Reduction:** We iterate through our mapped pairs. For each pair:
* A `while` loop checks if the remaining `num` is greater than or equal to the current `value`.
* If it is, we append the matching `symbol` to our result string `res` and subtract `value` from `num`.
* The `while` loop repeats until `num` is smaller than the current `value`, at which point the outer `for` loop moves to the next smaller Roman numeral.


3. **Early Exit:** The `if (num == 0) break;` optimization ensures that if the number hits zero before checking smaller symbols (e.g., matching exactly `2000` to `"MM"`), the loop terminates early.

---

## Complexities

### Time Complexity: $O(1)$ (Constant Time)

* **Why:** Although there is a nested loop (`while` inside `for`), the total number of operations is strictly bounded by a hard upper limit.
* The outer loop always runs a maximum of 13 times (the number of elements in `valueSymbols`).
* The inner `while` loop runs at most a few times per symbol. For example, since the maximum input constraint for this LeetCode problem is typically $3999$, the symbol `"M"` (1000) can be appended at most 3 times. Other symbols like `"CM"` or `"D"` can only appear once per number.
* Because the execution steps do not scale with an arbitrarily large $N$, the time complexity is constant.

### Space Complexity: $O(1)$ (Constant Space)

* **Why:** The `valueSymbols` vector is a fixed size of 13 elements, which uses a trivial, fixed amount of memory.
* The output string `res` takes up a maximum of 15 characters (for the number 3888: `"MMMDCCCLXXXVIII"`). Since this maximum size is fixed and independent of any scaling input, the auxiliary space complexity is $O(1)$.
