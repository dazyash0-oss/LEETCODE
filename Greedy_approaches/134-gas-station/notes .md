This solution uses a **Greedy Algorithm** to solve the Gas Station problem in **$\mathcal{O}(N)$ time complexity** and **$\mathcal{O}(1)$ space complexity**.

---

## Explanation: Core Intuition & Logic

The solution relies on two fundamental principles:

1. **Global Fuel Balance Constraint:**
If $\sum \text{gas}[i] < \sum \text{cost}[i]$, you cannot complete a circuit regardless of where you start. Conversely, if $\sum \text{gas}[i] \ge \sum \text{cost}[i]$, a unique starting station is **guaranteed to exist**.
2. **The Greedy Skip Property:**
Suppose you start at station $A$ with $0$ gas and run out of fuel at station $B$. Then **no station $K$ between $A$ and $B$ ($A \le K \le B$) can be a valid starting station**.
* **Why?** Since you managed to reach station $K$ starting from $A$, you arrived at $K$ with extra gas ($\ge 0$). If starting from $A$ with extra bonus gas wasn't enough to pass station $B$, starting at $K$ with $0$ initial gas will fail even sooner.
* **Greedy Decision:** When your fuel balance becomes negative (`currentGas < 0`) at station $i$, reset the start candidate directly to **$i + 1$** and set `currentGas = 0`.



---

## Greedy Textual Diagram

### Example Input

* `gas  = [1, 2, 3, 4, 5]`
* `cost = [3, 4, 5, 1, 2]`
* `diff = [-2, -2, -2, +3, +3]` *(where diff[i] = gas[i] - cost[i])*

### Step-by-Step Traversal

```text
Station Index (i):       [ 0 ]   --->   [ 1 ]   --->   [ 2 ]   --->   [ 3 ]   --->   [ 4 ]
Gas available:            (1)            (2)            (3)            (4)            (5)
Cost to next:             [3]            [4]            [5]            [1]            [2]
Net Fuel Delta:           -2             -2             -2             +3             +3

=============================================================================================

Candidate Start = 0
-------------------
At i = 0: currentGas = 0 + (-2) = -2
          [FAILED: Tank dropped below 0!]
          --> Reset candidate start to index (0 + 1) = 1
          --> Reset currentGas = 0

Candidate Start = 1
-------------------
At i = 1: currentGas = 0 + (-2) = -2
          [FAILED: Tank dropped below 0!]
          --> Reset candidate start to index (1 + 1) = 2
          --> Reset currentGas = 0

Candidate Start = 2
-------------------
At i = 2: currentGas = 0 + (-2) = -2
          [FAILED: Tank dropped below 0!]
          --> Reset candidate start to index (2 + 1) = 3
          --> Reset currentGas = 0

Candidate Start = 3
-------------------
At i = 3: currentGas = 0 + (+3) = 3   [Passes]
At i = 4: currentGas = 3 + (+3) = 6   [Passes]

=============================================================================================
FINAL CHECK:
Total Gas (15) >= Total Cost (15)  --> TRUE
Return start = 3

```

---

## Cumulative Gas Balance Curve

You can also visualize the greedy selection by plotting the cumulative gas balance starting from station `0`:

```text
Tank Balance
   ^
 0 |---+ (Start candidate 0)
   |    \
-2 |     * (i=0)
   |      \
-4 |       * (i=1)
   |        \
-6 |         * (i=2) <--- GLOBAL MINIMUM (Lowest point in journey)
   |          \
-3 |           * (i=3) <--- Starting at the station immediately AFTER 
   |            \           the global minimum guarantees we never 
 0 |-------------* (i=4)    drop below zero!

```

---

## Complexity Breakdown

* **Time Complexity:** $\mathcal{O}(N)$ — The algorithm passes through the array twice (or once in an optimized single-pass loop) where $N$ is the number of gas stations.
* **Space Complexity:** $\mathcal{O}(1)$ — Uses constant extra space to track balance counters and indices.
