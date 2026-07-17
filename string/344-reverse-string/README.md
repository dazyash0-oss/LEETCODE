<h2><a href="https://leetcode.com/problems/reverse-string">Reverse String</a></h2> <img src='https://img.shields.io/badge/Difficulty-Easy-brightgreen' alt='Difficulty: Easy' /><hr><p>Write a function that reverses a string. The input string is given as an array of characters <code>s</code>.</p>

<p>You must do this by modifying the input array <a href="https://en.wikipedia.org/wiki/In-place_algorithm" target="_blank">in-place</a> with <code>O(1)</code> extra memory.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<pre><strong>Input:</strong> s = ["h","e","l","l","o"]
<strong>Output:</strong> ["o","l","l","e","h"]
</pre><p><strong class="example">Example 2:</strong></p>
<pre><strong>Input:</strong> s = ["H","a","n","n","a","h"]
<strong>Output:</strong> ["h","a","n","n","a","H"]
</pre>
<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= s.length &lt;= 10<sup>5</sup></code></li>
	<li><code>s[i]</code> is a <a href="https://en.wikipedia.org/wiki/ASCII#Printable_characters" target="_blank">printable ascii character</a>.</li>
</ul>

---
---

# Approach: Symmetric Swapping (In-Place Two-Pointer Concept)

The problem asks to reverse an array of characters in-place, meaning we must modify the input vector directly using $O(1)$ extra space.

1. **Midpoint Termination:** The `for` loop is designed to run from `0` up to exactly half the size of the vector (`s.size() / 2`). This is a crucial detail: if the loop went all the way to the end, it would swap the characters a second time, restoring the string to its original order.
2. **Symmetric Indexing:** For any index `i` on the left half of the vector, its perfectly symmetrical counterpart on the right half is calculated using the formula:

$$s.\text{size}() - 1 - i$$


3. **In-Place Swapping:** The built-in `swap()` function exchanges the values of `s[i]` and its reflection on the right side.
* **Even lengths:** If the vector has 4 elements (indices 0, 1, 2, 3), the loop runs for $i = 0$ (swaps 0 and 3) and $i = 1$ (swaps 1 and 2), perfectly reversing it.
* **Odd lengths:** If the vector has 5 elements (indices 0, 1, 2, 3, 4), the loop runs for $i = 0$ and $i = 1$. The absolute middle element at index 2 is automatically left untouched, which is exactly what we want since the middle element of an odd-length string stays in the same spot when reversed.



---

## Complexities

### Time Complexity: $O(n)$

* **Why:** The loop performs exactly $n / 2$ iterations, where $n$ is the total number of characters in the vector `s`. Inside the loop, the `swap()` operation executes in $O(1)$ constant time. Since constants are dropped in Big-O notation, $\frac{1}{2}n$ translates directly to a linear time complexity of $O(n)$.

### Space Complexity: $O(1)$ (Constant Space)

* **Why:** The algorithm modifies the input vector `s` entirely in-place. It only uses a single primitive loop counter variable `i`, requiring no additional data structures or dynamic memory allocations. Thus, the space used remains constant regardless of how large the input vector grows.
