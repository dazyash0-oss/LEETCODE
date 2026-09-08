### Code Analysis

Your code solves **LeetCode 1584: Min Cost to Connect All Points** using **Prim's Algorithm** with a priority queue (Min-Heap).

Overall, your logic is **correct** and will pass. However, there are a few key details about efficiency:

1. **`unordered_map<int, int> cache` optimization**: Using a hash map to track the minimum distance to each unvisited node helps avoid pushing redundant worse-cost edges into the priority queue. However, an `std::vector<int> min_dist(n, INT_MAX)` is faster and avoids dynamic heap allocations caused by `std::unordered_map`.
2. **Complexity**:
* **Time Complexity**: $O(N^2 \log N)$ with the Priority Queue (or $O(N^2)$ if implemented with a simple array search for Prim's, which is theoretically optimal since the graph is dense with $E = O(N^2)$).
* **Space Complexity**: $O(N)$ for `visited`, `cache`/`min_dist`, and `pq`.



---

### Step-by-Step Example Walkthrough

Consider $N = 4$ points on a 2D plane:

```text
       y
       ^
    3  |      P2 (2,3)
    2  |
    1  |  P0 (0,0)      P1 (3,1)
    0  +-------------------------> x
   -1  |      P3 (2,-1)

```

**Coordinates:**

* $P_0 = (0, 0)$
* $P_1 = (3, 1)$
* $P_2 = (2, 3)$
* $P_3 = (2, -1)$

**Manhattan Distance Formula:**


$$\text{dist}(A, B) = \vert{}x_A - x_B\vert{} + \vert{}y_A - y_B\vert{}$$

#### Step-by-Step Execution:

1. **Initialize**:
* `visited = [false, false, false, false]`
* `pq.push({0, 0})` (Start at $P_0$)


2. **Pop $P_0$ (Cost: 0)**:
* Mark `visited[0] = true`. Total `min_cost = 0`.
* Calculate distances from $P_0$ to all unvisited points:
* $P_0 \rightarrow P_1$: $\vert{}0-3\vert{} + \vert{}0-1\vert{} = 4 \implies$ Push `{4, 1}`
* $P_0 \rightarrow P_2$: $\vert{}0-2\vert{} + \vert{}0-3\vert{} = 5 \implies$ Push `{5, 2}`
* $P_0 \rightarrow P_3$: $\vert{}0-2\vert{} + \vert{}0-(-1)\vert{} = 3 \implies$ Push `{3, 3}`




```text
PQ State: [{3, P3}, {4, P1}, {5, P2}]
MST Edges Chosen so far: {P0}

```


3. **Pop $P_3$ (Cost: 3)**:
* Mark `visited[3] = true`. Total `min_cost = 0 + 3 = 3`.
* Calculate distances from $P_3$ to remaining unvisited points ($P_1, P_2$):
* $P_3 \rightarrow P_1$: $\vert{}2-3\vert{} + \vert{}-1-1\vert{} = 3 \implies$ Better than $4$! Update `cache[1] = 3`, Push `{3, 1}`.
* $P_3 \rightarrow P_2$: $\vert{}2-2\vert{} + \vert{}-1-3\vert{} = 4 \implies$ Better than $5$! Update `cache[2] = 4`, Push `{4, 2}`.




```text
PQ State: [{3, P1}, {4, P2}, {4, P1} (stale), {5, P2} (stale)]
MST Edges Chosen so far: P0 --(3)-- P3

```


4. **Pop $P_1$ (Cost: 3)**:
* Mark `visited[1] = true`. Total `min_cost = 3 + 3 = 6`.
* Calculate distances from $P_1$ to $P_2$:
* $P_1 \rightarrow P_2$: $\vert{}3-2\vert{} + \vert{}1-3\vert{} = 3 \implies$ Better than $4$! Update `cache[2] = 3`, Push `{3, 2}`.




```text
PQ State: [{3, P2}, {4, P2}, {4, P1} (stale), {5, P2} (stale)]
MST Edges Chosen so far: P0 --(3)-- P3 --(3)-- P1

```


5. **Pop $P_2$ (Cost: 3)**:
* Mark `visited[2] = true`. Total `min_cost = 6 + 3 = 9`.
* All nodes are now visited (`visited = [true, true, true, true]`).


6. **Remaining PQ elements**:
* Subsequent pops (`{4, P2}`, `{4, P1}`, `{5, P2}`) will trigger `if (visited[u]) continue;` and be skipped.



---

### Minimum Spanning Tree Visual

```text
        P2 (2,3)
           |
          (3)
           |
P0 (0,0) --(3)-- P3 (2,-1) --(3)-- P1 (3,1)

```

**Total Minimum Cost** = $3 + 3 + 3 = 9$.

---

### Optimized Code Version ($O(N^2)$ Prim's without Min-Heap)

Since the graph is **dense** (every point connects to every other point, $E = N^2$), standard array-based Prim's runs faster and uses less memory:

```cpp
class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        int min_cost = 0;
        vector<int> min_dist(n, INT_MAX);
        vector<bool> visited(n, false);
        
        min_dist[0] = 0;

        for (int i = 0; i < n; ++i) {
            int u = -1;

            // Pick the unvisited node with the smallest distance
            for (int j = 0; j < n; ++j) {
                if (!visited[j] && (u == -1 || min_dist[j] < min_dist[u])) {
                    u = j;
                }
            }

            visited[u] = true;
            min_cost += min_dist[u];

            // Update distances to all remaining unvisited nodes
            for (int v = 0; v < n; ++v) {
                if (!visited[v]) {
                    int dist = abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1]);
                    min_dist[v] = min(min_dist[v], dist);
                }
            }
        }

        return min_cost;
    }
};

```
