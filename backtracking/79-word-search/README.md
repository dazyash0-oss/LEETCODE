<h2><a href="https://leetcode.com/problems/word-search">Word Search</a></h2> <img src='https://img.shields.io/badge/Difficulty-Medium-orange' alt='Difficulty: Medium' /><hr><p>Given an <code>m x n</code> grid of characters <code>board</code> and a string <code>word</code>, return <code>true</code> <em>if</em> <code>word</code> <em>exists in the grid</em>.</p>

<p>The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2020/11/04/word2.jpg" style="width: 322px; height: 242px;" />
<pre>
<strong>Input:</strong> board = [[&quot;A&quot;,&quot;B&quot;,&quot;C&quot;,&quot;E&quot;],[&quot;S&quot;,&quot;F&quot;,&quot;C&quot;,&quot;S&quot;],[&quot;A&quot;,&quot;D&quot;,&quot;E&quot;,&quot;E&quot;]], word = &quot;ABCCED&quot;
<strong>Output:</strong> true
</pre>

<p><strong class="example">Example 2:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2020/11/04/word-1.jpg" style="width: 322px; height: 242px;" />
<pre>
<strong>Input:</strong> board = [[&quot;A&quot;,&quot;B&quot;,&quot;C&quot;,&quot;E&quot;],[&quot;S&quot;,&quot;F&quot;,&quot;C&quot;,&quot;S&quot;],[&quot;A&quot;,&quot;D&quot;,&quot;E&quot;,&quot;E&quot;]], word = &quot;SEE&quot;
<strong>Output:</strong> true
</pre>

<p><strong class="example">Example 3:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2020/10/15/word3.jpg" style="width: 322px; height: 242px;" />
<pre>
<strong>Input:</strong> board = [[&quot;A&quot;,&quot;B&quot;,&quot;C&quot;,&quot;E&quot;],[&quot;S&quot;,&quot;F&quot;,&quot;C&quot;,&quot;S&quot;],[&quot;A&quot;,&quot;D&quot;,&quot;E&quot;,&quot;E&quot;]], word = &quot;ABCB&quot;
<strong>Output:</strong> false
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>m == board.length</code></li>
	<li><code>n = board[i].length</code></li>
	<li><code>1 &lt;= m, n &lt;= 6</code></li>
	<li><code>1 &lt;= word.length &lt;= 15</code></li>
	<li><code>board</code> and <code>word</code> consists of only lowercase and uppercase English letters.</li>
</ul>

<p>&nbsp;</p>
<p><strong>Follow up:</strong> Could you use search pruning to make your solution faster with a larger <code>board</code>?</p>


**Core Concept**
This C++ algorithm solves the **Word Search** problem (finding if a target string exists in a 2D character grid using adjacent steps). It combines **Depth-First Search (DFS) with Backtracking** alongside three high-level **pruning strategies** to pass LeetCode test cases efficiently.

---

**Key Technical Takeaways (Study Notes)**

* **Frequency Validation (Pruning 1):** Before searching, build a character frequency array. If the grid contains fewer instances of any required character than `word` needs, return `false` instantly without doing DFS.
* **Search Direction Optimization (Pruning 2):** Compare the grid occurrence counts of `word[0]` and `word.back()`. Reversing `word` to start searching from the rarer character significantly reduces the branching factor in early DFS calls.
* **In-Place Visited State (Pruning 3):** To avoid allocating a separate $M \times N$ `visited` array, temp-assign `board[i][j] = '*'` when entering a cell, and restore it to `tmp` when returning up the call stack (backtracking).
* **Direction Vectors:** Uses `dx` and `dy` arrays to cleanly step in four orthogonal directions (`Down`, `Up`, `Right`, `Left`) in a single loop instead of writing four repetitive `if` statements.

---

**Step-by-Step Example Walkthrough**

Consider the following input:

* **Grid (`board`):**

$$\begin{bmatrix}   \text{'A'} & \text{'B'} & \text{'C'} & \text{'E'} \\   \text{'S'} & \text{'F'} & \text{'C'} & \text{'S'} \\   \text{'A'} & \text{'D'} & \text{'E'} & \text{'E'}   \end{bmatrix}$$


* **Target Word (`word`):** `"ABCCED"`

```
Step 1: Frequency Check & Optimization
--------------------------------------------------
- Grid Counts: 'A':2, 'B':1, 'C':2, 'D':1, 'E':3, 'F':1, 'S':2
- Word Requires: 'A':1, 'B':1, 'C':2, 'D':1, 'E':1
- Frequency Check Passes!
- 'A' count = 2, 'D' count = 1. Since count['A'] > count['D'], reverse the word!
- New Search Target: "DECCBA"

Step 2: Locating the First Character ('D')
--------------------------------------------------
- Scans grid until board[2][1] == 'D'.
- Set board[2][1] = '*' and invoke DFS(row=2, col=1, index=1).

Step 3: Depth-First Search & Backtracking Path
--------------------------------------------------
[2,1] 'D' (*)  --> Check neighbors for word[1] = 'E':
                  - Neighbor [2,2] is 'E' (Match!)
                  
[2,2] 'E' (*)  --> Check neighbors for word[2] = 'C':
                  - Neighbor [1,2] is 'C' (Match!)
                  
[1,2] 'C' (*)  --> Check neighbors for word[3] = 'C':
                  - Neighbor [0,2] is 'C' (Match!)
                  
[0,2] 'C' (*)  --> Check neighbors for word[4] = 'B':
                  - Neighbor [0,1] is 'B' (Match!)
                  
[0,1] 'B' (*)  --> Check neighbors for word[5] = 'A':
                  - Neighbor [0,0] is 'A' (Match!)
                  
[0,0] 'A' (*)  --> Base Case Hit! (index == word_sz) -> Return true!

```

---

**Complexity Analysis**

* **Time Complexity:** $O(M \cdot N \cdot 3^L)$ in the worst case, where $M \times N$ is grid dimensions and $L$ is word length. (At each step after the first, you explore at most 3 directions because 1 direction is marked with `'*'`). Practical runtime is close to $O(M \cdot N)$ due to pruning.
* **Space Complexity:** $O(L)$ auxiliary space reserved for the recursive DFS stack. $O(1)$ extra memory used for grid tracking due to in-place mutation.
