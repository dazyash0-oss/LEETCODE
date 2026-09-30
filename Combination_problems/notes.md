

### Multi-Pattern Breakdown

#### Pattern 1: Breadth-First Search (BFS) for Shortest Path

* **Why it fits:** The grid is an unweighted graph where every valid step has a cost of $1$. Standard BFS processes nodes layer by layer, guaranteeing that the first time we reach the target $(m-1, n-1)$, the path taken is optimal.
* **Mechanism:** A queue (`std::queue`) maintains state processing order, while an integer `steps` tracks the distance level.

#### Pattern 2: Multi-Dimensional State Space

* **Why it fits:** A simple 2D visited array `visited[r][c]` is insufficient because reaching a cell $(r, c)$ with **more remaining obstacle eliminations** is strictly better than reaching it with fewer.
* **State Representation:** The state is represented as a 3D coordinate $(r, c, k_{\text{rem}})$, where $k_{\text{rem}}$ is the remaining obstacle elimination capacity.

#### Pattern 3: State Pruning / Dominance Optimization

* **Why it fits:** Exploring every possible state can lead to TLE (Time Limit Exceeded) or memory overhead.
* **Pruning Logic (`best[r][c]`):** We keep track of the maximum remaining eliminations seen so far at cell $(r, c)$.
* If a new path reaches $(r, c)$ with $k_{\text{new}} \le \text{best}[r][c]$, this path is strictly dominated and can be discarded (`if (best[nr][nc] >= nrem) continue;`).
* If $k_{\text{new}} > \text{best}[r][c]$, we update `best[nr][nc] = k_new` and push to queue.



#### Pattern 4: Manhattan Distance Shortcut Optimization

* **Why it fits:** The minimum steps required to travel from $(0, 0)$ to $(m-1, n-1)$ without obstacles is the Manhattan distance: $(m - 1) + (n - 1) = m + n - 2$.
* **Shortcut:** If $k \ge m + n - 2$, you have enough obstacle eliminations to take the direct path regardless of grid content. You can immediately return $m + n - 2$ in $O(1)$ time.

---

### Complexity Analysis

* **Time Complexity:** $\mathcal{O}(m \cdot n \cdot k)$ — In the worst-case scenario, each cell $(r, c)$ is visited at most $k + 1$ times (once for each remaining elimination value from $0$ to $k$).
* **Space Complexity:** $\mathcal{O}(m \cdot n \cdot k)$ — Needed for the BFS queue state storage and the `best` matrix of size $m \times n$.

---

### Textual Diagram Notes with Example

#### Example Setup

```text
Grid (m = 3, n = 3):
[0, 1, 0]
[1, 1, 0]
[0, 0, 0]

k = 1
Start: (0, 0) | Target: (2, 2)

```

#### Manhattan Shortcut Check

$$\text{Manhattan Distance} = 3 + 3 - 2 = 4$$

Since $k = 1 < 4$, we proceed to standard BFS execution.

---

#### Step-by-Step Execution Diagram

```text
INITIALIZATION:
q = [ {r:0, c:0, rem:1} ]
best matrix:
[ 1, -1, -1 ]
[-1, -1, -1 ]
[-1, -1, -1 ]
steps = 0

==================================================
STEP 1: Expand (0, 0, rem=1)

```

---

Neighbors of (0,0):
-> Down  (1,0): Grid=1 -> nrem = 1 - 1 = 0 (Valid! best[1][0] becomes 0)
-> Right (0,1): Grid=1 -> nrem = 1 - 1 = 0 (Valid! best[0][1] becomes 0)

Queue after Step 1: [ (1,0, rem=0), (0,1, rem=0) ]
steps = 1

Visual Queue State:
[ (1,0, rem=0) ]
[ (0,1, rem=0) ]

==================================================
STEP 2: Expand level (steps = 1 -> 2)

---

1. Pop (1,0, rem=0):
-> Try (2,0): Grid=0 -> nrem = 0 - 0 = 0 (Valid! best[2][0] becomes 0)
-> Try (1,1): Grid=1 -> nrem = 0 - 1 = -1 (Blocked! nrem < 0)
2. Pop (0,1, rem=0):
-> Try (0,2): Grid=0 -> nrem = 0 - 0 = 0 (Valid! best[0][2] becomes 0)
-> Try (1,1): Grid=1 -> nrem = 0 - 1 = -1 (Blocked! nrem < 0)

Queue after Step 2: [ (2,0, rem=0), (0,2, rem=0) ]
steps = 2

==================================================
STEP 3: Expand level (steps = 2 -> 3)

---

1. Pop (2,0, rem=0):
-> Try (2,1): Grid=0 -> nrem = 0 - 0 = 0 (Valid! best[2][1] becomes 0)
2. Pop (0,2, rem=0):
-> Try (1,2): Grid=0 -> nrem = 0 - 0 = 0 (Valid! best[1][2] becomes 0)

Queue after Step 3: [ (2,1, rem=0), (1,2, rem=0) ]
steps = 3

==================================================
STEP 4: Expand level (steps = 3 -> 4)

---

1. Pop (2,1, rem=0):
-> Try (2,2): Target reached!
-> Return steps = 4

Result: 4

```

```

---

### Final Code Walkthrough Summary

1. **Edge Check (`m==1 && n==1`):** Handles single-cell grid immediately ($0$ steps).
2. **Shortcut Check (`k >= m + n - 2`):** Direct $O(1)$ fast path.
3. **Queue Processing:** Standard layer-by-layer BFS guarantees the earliest exit is the shortest path.
4. **Dominance Matrix (`best[r][c]`):** Filters out paths that arrive at a cell with fewer or equal remaining eliminations than a previously recorded state.
