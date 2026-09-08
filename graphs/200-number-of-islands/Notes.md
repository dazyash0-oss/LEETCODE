Here are clean mentor-style notes, an ASCII diagram walk-through, and key takeaways for optimizing your solution.

---

### Mentor Notes

#### 1. Core Logic & Strategy

* **Goal:** Count connected components of `'1'`s (land) surrounded by `'0'`s (water).
* **Strategy (BFS):** Iterate through the grid cell by cell. When you encounter an unvisited `'1'`, increment your island counter and fire off a Breadth-First Search (BFS) using a Queue to visit and mark all reachable land cells.

---

#### 2. Optimization Opportunities

Your current implementation is functional, but there are two main areas to improve for efficiency:

##### Bottleneck A: String Conversions for Visited Tracking

```cpp
// ❌ Slower: Dynamic memory allocation & hashing strings
visited.find(to_string(r) + "," + to_string(c))

```

* **Why it hurts:** `to_string()` creates a heap allocation for every single coordinate lookup and insertion. Hashing strings in an `unordered_set` is significantly slower than hashing integer types.
* **Fix Options:**
1. **In-place Mutation (Zero extra memory):** Overwrite visited land directly by changing `'1'` to `'0'` (often called "sinking" the island).
2. **2D Boolean Matrix:** Use `vector<vector<bool>> visited(rows, vector<bool>(cols, false))` for $O(1)$ primitive lookups.



##### Bottleneck B: Late Queue Marking

Always mark a node as **visited immediately when pushing it into the queue**, rather than when popping it. Delaying this can lead to the same cell being added to the queue multiple times across neighboring iterations, inflating queue size.

---

### Step-by-Step Traversal Walkthrough

Consider this $3 \times 3$ grid:

```
    Col 0   Col 1   Col 2
Row 0 [ 1 ]   [ 1 ]   [ 0 ]
Row 1 [ 1 ]   [ 0 ]   [ 0 ]
Row 2 [ 0 ]   [ 0 ]   [ 1 ]

```

```
--- BFS Execution for Island 1 ---

1. Scan grid from (0,0):
   Found grid[0][0] == '1'. Increment islands = 1.
   Mark grid[0][0] = '0' and push to Queue.
   Queue: [(0,0)]

2. Pop (0,0):
   Check 4 directional neighbors:
   - Down (1,0): Land ('1') -> Mark grid[1][0] = '0', push (1,0).
   - Right (0,1): Land ('1') -> Mark grid[0][1] = '0', push (0,1).
   Queue: [(1,0), (0,1)]

3. Pop (1,0):
   Check neighbors:
   - Up (0,0): Already '0'.
   - Down (2,0): Water ('0').
   - Right (1,1): Water ('0').
   - Left: Out of bounds.
   Queue: [(0,1)]

4. Pop (0,1):
   Check neighbors:
   - All surrounding neighbors are '0' or out of bounds.
   Queue: [] (BFS terminates)

--- Grid State after Island 1 ---
Row 0 [ 0 ]   [ 0 ]   [ 0 ]
Row 1 [ 0 ]   [ 0 ]   [ 0 ]
Row 2 [ 0 ]   [ 0 ]   [ 1 ]

5. Continue Grid Loop:
   Skip visited (now '0') cells until scanning reaches (2,2).
   Found grid[2][2] == '1'. Increment islands = 2.
   BFS clears (2,2).

Final Count: 2 Islands

```

---

### Complexity Analysis

| Metric | Original Code | Refactored Code |
| --- | --- | --- |
| **Time Complexity** | $\mathcal{O}(M \times N)$ | $\mathcal{O}(M \times N)$ |
| **Space Complexity** | $\mathcal{O}(M \times N)$ (due to string set allocations) | $\mathcal{O}(\min(M, N))$ (Queue width bound) |
| **Runtime Efficiency** | Slower (Heap churn from string creation) | Optimal (Direct matrix mutation) |
