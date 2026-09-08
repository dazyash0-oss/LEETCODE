### Mentor Notes

#### 1. Core Concept & Strategy

* **Goal:** Create a deep copy (clone) of a connected, undirected graph.
* **Key Challenge:** The graph contains **cycles**. If Node A connects to Node B, and Node B connects to Node A, naive recursive traversals will loop infinitely.
* **Strategy:** Use an `unordered_map<Node*, Node*> mp` to map each **original node $\rightarrow$ cloned node**. This map doubles as your **visited tracker** to break recursive loops.

---

#### 2. Evaluating Your Original Code

Your original logic works for simple graphs, but structured recursion can be significantly cleaner.

##### What You Did Right

* Created the `copy` node before traversing neighbors (`mp[node] = copy;`), which is critical for handling cyclic references!

##### Opportunities for Refactoring

1. **Redundant Logic in Loop:** Checking `if (mp.find(ng) != mp.end())` inside the loop causes unnecessary branches. If you move the visited check to the very top of the function as a base case, your recursive logic becomes much simpler.
2. **Function Return Value:** Instead of a `void` function, making `dfs` return `Node*` lets you directly push the cloned neighbor result into `copy->neighbors`.

---

### Text Diagram & Walkthrough

Let's trace a cyclic graph with 3 nodes connected in a triangle:

`1 --- 2`

`\   /`

`  3  `

```
                        RECURSION TRACE (DFS)
                        --------------------

cloneGraph(Node 1)
  │
  ├── dfs(1)
  │     ├── Create Copy(1) & save mp[1] = Copy(1)
  │     ├── Neighbor Node 2: Not in map -> Call dfs(2)
  │     │     │
  │     │     ├── dfs(2)
  │     │     │     ├── Create Copy(2) & save mp[2] = Copy(2)
  │     │     │     ├── Neighbor Node 1: IN MAP! -> Returns Copy(1)
  │     │     │     ├── Neighbor Node 3: Not in map -> Call dfs(3)
  │     │     │     │     │
  │     │     │     │     ├── dfs(3)
  │     │     │     │     │     ├── Create Copy(3) & save mp[3] = Copy(3)
  │     │     │     │     │     ├── Neighbor Node 1: IN MAP! -> Returns Copy(1)
  │     │     │     │     │     ├── Neighbor Node 2: IN MAP! -> Returns Copy(2)
  │     │     │     │     │     └── Returns Copy(3)
  │     │     │     │
  │     │     │     ├── Attach Copy(3) to Copy(2)'s neighbors
  │     │     │     └── Returns Copy(2)
  │     │
  │     ├── Attach Copy(2) to Copy(1)'s neighbors
  │     ├── Neighbor Node 3: IN MAP! -> Returns Copy(3)
  │     ├── Attach Copy(3) to Copy(1)'s neighbors
  │     └── Returns Copy(1)
  │
  └── Final Output: Deep copy starting at Copy(1)

```

---

### Complexity Analysis

* **Time Complexity:** $\mathcal{O}(V + E)$ where $V$ is the number of nodes (vertices) and $E$ is the number of edges. Every node and edge is processed once.
* **Space Complexity:** $\mathcal{O}(V)$ to store the recursion stack depth and the hash map entries for all $V$ nodes.
