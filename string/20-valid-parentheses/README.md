<h2><a href="https://leetcode.com/problems/valid-parentheses">Valid Parentheses</a></h2> <img src='https://img.shields.io/badge/Difficulty-Easy-brightgreen' alt='Difficulty: Easy' /><hr><p>Given a string <code>s</code> containing just the characters <code>&#39;(&#39;</code>, <code>&#39;)&#39;</code>, <code>&#39;{&#39;</code>, <code>&#39;}&#39;</code>, <code>&#39;[&#39;</code> and <code>&#39;]&#39;</code>, determine if the input string is valid.</p>

<p>An input string is valid if:</p>

<ol>
	<li>Open brackets must be closed by the same type of brackets.</li>
	<li>Open brackets must be closed in the correct order.</li>
	<li>Every close bracket has a corresponding open bracket of the same type.</li>
</ol>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<div class="example-block">
<p><strong>Input:</strong> <span class="example-io">s = &quot;()&quot;</span></p>

<p><strong>Output:</strong> <span class="example-io">true</span></p>
</div>

<p><strong class="example">Example 2:</strong></p>

<div class="example-block">
<p><strong>Input:</strong> <span class="example-io">s = &quot;()[]{}&quot;</span></p>

<p><strong>Output:</strong> <span class="example-io">true</span></p>
</div>

<p><strong class="example">Example 3:</strong></p>

<div class="example-block">
<p><strong>Input:</strong> <span class="example-io">s = &quot;(]&quot;</span></p>

<p><strong>Output:</strong> <span class="example-io">false</span></p>
</div>

<p><strong class="example">Example 4:</strong></p>

<div class="example-block">
<p><strong>Input:</strong> <span class="example-io">s = &quot;([])&quot;</span></p>

<p><strong>Output:</strong> <span class="example-io">true</span></p>
</div>

<p><strong class="example">Example 5:</strong></p>

<div class="example-block">
<p><strong>Input:</strong> <span class="example-io">s = &quot;([)]&quot;</span></p>

<p><strong>Output:</strong> <span class="example-io">false</span></p>
</div>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= s.length &lt;= 10<sup>4</sup></code></li>
	<li><code>s</code> consists of parentheses only <code>&#39;()[]{}&#39;</code>.</li>
</ul>

---
---

# Approach: Stack Data Structure

The core rule of matching brackets is that the *most recently opened* bracket must be the *first one closed*. A stack is the perfect data structure for this because the last element pushed onto it is always the first one accessible at the top.

1. **Processing Open Brackets:** We iterate through the string character by character. If the character is an opening bracket (`(`, `{`, or `[`), we push it onto our stack `st`. This essentially saves it for later, waiting for its corresponding closing partner.
2. **Handling Closing Brackets:** When we encounter a closing bracket (the `else` block), we have to evaluate two critical failure conditions:
* **Empty Stack Check:** If the stack is empty (`st.empty()`), it means we found a closing bracket with absolutely no opening bracket preceding it (e.g., `s = "]"`). This is immediately invalid, so we return `false`.
* **Matching Check:** We peek at the top of the stack (`st.top()`). If the current closing bracket matches the type of the top opening bracket (e.g., `)` matches `(`), we successfully paired them up, so we remove the open bracket from the stack using `st.pop()`. If they don't match (e.g., `}` trying to close `(`), it's a mismatch, and we return `false`.


3. **Final Verification:** After checking the entire string, there is one last catch—unclosed brackets (e.g., `s = "(()"`). If the stack still has characters remaining inside it, the string is invalid. Returning `st.empty()` ensures we only return `true` if every single opening bracket found its correct match.

---

## Complexities

### Time Complexity: $O(n)$

* **Why:** The algorithm scans the string `s` exactly once, processing each character one by one, where $n$ is the length of the string. Inside the loop, the stack operations (`push`, `pop`, `top`, and `empty`) all execute in $O(1)$ constant time. Therefore, the execution time scales linearly with the number of brackets in the string.

### Space Complexity: $O(n)$

* **Why:** In the worst-case scenario, the string consists entirely of opening brackets (e.g., `s = "((((((("`). In this case, no brackets are popped, and the stack will grow to store all $n$ characters. Thus, the auxiliary space used by the stack scales linearly with the input size, resulting in $O(n)$ space complexity.
