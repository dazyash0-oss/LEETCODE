### Code Explanation

 implementation for **LeetCode 417: Pacific Atlantic Water Flow** is **correct** and optimal with a time complexity of $O(m \times n)$.

Instead of starting a search from every single cell to see if water can reach both oceans, the algorithm works **in reverse**:

1. Start from the **Pacific Ocean** borders (top and left edges) and move **uphill** (to adjacent cells with a height greater than or equal to the current cell) using DFS to mark all reachable cells.
2. Start from the **Atlantic Ocean** borders (bottom and right edges) and do the same uphill search to mark all reachable cells.
3. The cells that are marked `true` in both `pacific` and `atlantic` matrices can flow to both oceans.

---

### Key Components

* **`visited[x][y] = true`**: Serves dual purposes—it keeps track of which cells can reach the ocean and prevents infinite loops during DFS.
* **`heights[x][y] < heights[i][j]`**: Because the search works backwards from the ocean inland, water can only flow uphill or to equal heights (`heights[neighbor] >= heights[current]`).

---

### Step-by-Step Example Walkthrough

Consider a $3 \times 3$ grid of heights:

```text
       Pacific Ocean (Top)
      +---+---+---+
      | 1 | 2 | 2 |  Pacific Ocean
      +---+---+---+  (Left)
      | 3 | 2 | 3 |
      +---+---+---+
      | 2 | 4 | 5 |
      +---+---+---+
        Atlantic Ocean (Bottom & Right)

```

#### 1. Pacific DFS Search

Starting from top row `(0,0), (0,1), (0,2)` and left column `(0,0), (1,0), (2,0)`:

* `(0,0) [1]` $\rightarrow$ Can reach `(0,1) [2]` and `(1,0) [3]`.
* `(1,0) [3]` $\rightarrow$ Can reach `(2,0) [2]`? No ($2 < 3$).
* `(0,1) [2]` $\rightarrow$ Can reach `(0,2) [2]`.
* `(2,0) [2]` $\rightarrow$ Can reach `(2,1) [4]`.
* `(2,1) [4]` $\rightarrow$ Can reach `(2,2) [5]` and `(1,1) [2]`? Only `(2,2)` because $5 \ge 4$.

**Pacific Reachable Grid:**

```text
  [T] [T] [T]
  [T] [F] [F]
  [T] [T] [T]

```

#### 2. Atlantic DFS Search

Starting from bottom row `(2,0), (2,1), (2,2)` and right column `(0,2), (1,2), (2,2)`:

* `(2,2) [5]` $\rightarrow$ Already high, cannot go uphill anywhere.
* `(2,1) [4]` $\rightarrow$ Can reach `(2,2) [5]` (already visited).
* `(1,2) [3]` $\rightarrow$ Can reach `(0,2) [2]`? No ($2 < 3$).
* `(2,0) [2]` $\rightarrow$ Can reach `(1,0) [3]` and `(2,1) [4]`.
* `(1,0) [3]` $\rightarrow$ Cannot go further uphill to unvisited cells.

**Atlantic Reachable Grid:**

```text
  [F] [F] [T]
  [T] [F] [T]
  [T] [T] [T]

```

#### 3. Overlap (Intersection)

Cells marked `True` in both grids:

* `(1,0)`, `(2,0)`, `(2,1)`, `(2,2)`, `(0,2)`

**Result:** `[[0,2], [1,0], [2,0], [2,1], [2,2]]`

---

### Complexity Analysis

* **Time Complexity:** $O(m \times n)$ — Each cell is visited at most a constant number of times per ocean search.
* **Space Complexity:** $O(m \times n)$ — For the `pacific` and `atlantic` boolean matrices and the recursion stack.
