### Mentor Notes

#### 1. Core Concept & Strategy

* **Problem:** **Course Schedule** (Detecting cycles in a Directed Graph).
* **Strategy (Kahn’s Algorithm / Topological Sort BFS):**
* If a directed graph has **no cycles** (a Directed Acyclic Graph, or DAG), you can order the vertices linearly such that for every directed edge $U \rightarrow V$, vertex $U$ comes before $V$.
* If the graph **has a cycle**, it's impossible to complete all courses because there's a circular dependency (e.g., Course A requires B, and Course B requires A).



---

#### 2. Evaluating Your Original Code

Your code uses **Kahn's Algorithm (BFS)**, which is an excellent choice for this problem! However, there is a **subtle direction bug** in how you build the adjacency list.

##### The Critical Bug: Directed Edge Direction

```cpp
// ❌ INCORRECT DIRECTION IN YOUR CODE:
adj[x[0]].push_back(x[1]); 
indegree[x[1]]++;

```

* In LeetCode's problem statement, `[a, b]` means: **To take course `a`, you must first complete course `b**`.
* This means the edge points **from `b` to `a**` ($b \rightarrow a$), because taking $b$ unlocks $a$.
* In your code, you treated `[a, b]` as $a \rightarrow b$.

While Kahn's Algorithm happens to detect cycles correctly regardless of edge direction (since reversing all edges in a graph doesn't destroy or create cycles), your adjacency list models the dependencies **backwards**, which will break if you ever need to return the actual course ordering (e.g., *Course Schedule II*).

##### Minor Optimization

You don't actually need the `vector<int> ans` array to store elements. You can simply maintain a `count` variable that increments every time you pop a node from the queue!

---

### Text Diagram & Walkthrough

Consider 3 courses with prerequisites: `[1, 0]` (take 0 before 1) and `[2, 1]` (take 1 before 2).

**Graph Representation:**

`0  ──>  1  ──>  2`

```
                      KAHN'S ALGORITHM TRACE
                      ----------------------

Initial In-degrees:
  Node 0: 0
  Node 1: 1
  Node 2: 1

Queue Initial State: [ 0 ] (Nodes with in-degree 0)
Processed Count = 0

Step 1:
  - Pop 0 from Queue. Processed Count = 1.
  - Decrease in-degree of 0's neighbor (Node 1): indegree[1] becomes 0.
  - Node 1 in-degree is 0 -> Push 1 to Queue.
  - Queue State: [ 1 ]

Step 2:
  - Pop 1 from Queue. Processed Count = 2.
  - Decrease in-degree of 1's neighbor (Node 2): indegree[2] becomes 0.
  - Node 2 in-degree is 0 -> Push 2 to Queue.
  - Queue State: [ 2 ]

Step 3:
  - Pop 2 from Queue. Processed Count = 3.
  - Node 2 has no outgoing edges.
  - Queue State: [ ] (Empty)

Check: Processed Count (3) == Total Courses (3) -> Return true (No cycle!)

```

---

### Key Takeaways

1. **Direction Matters:** Always verify which element represents the prerequisite vs. the dependent node (`[a, b]` means $b \rightarrow a$).
2. **Space Efficiency:** Using `int processedCourses = 0` saves memory compared to allocating a full `vector<int> ans` when you only need to return a `bool`.
3. **Prefer Modern C++ Types:** Use `vector<vector<int>> adj(n)` instead of raw C-style arrays `vector<int> adj[n]`. It avoids standard vector array pitfalls and plays nicely with memory managers.

---

### Complexity Analysis

* **Time Complexity:** $\mathcal{O}(V + E)$ where $V = \text{numCourses}$ and $E = \text{prerequisites.size()}$. We visit each vertex and iterate through each edge once.
* **Space Complexity:** $\mathcal{O}(V + E)$ to build the adjacency list, along with $\mathcal{O}(V)$ memory for the queue and in-degree array.
