### Algorithm Overview

The Minimum Number of Arrows to Burst Balloons problem is solved using a **Greedy Algorithm**:

1. **Sort by End Coordinate:** Sort balloons based on their end position ($x_{\text{end}}$). Sorting by the end point ensures that when an arrow is fired at the earliest possible end boundary, it pops the current balloon while maximizing the chance of overlapping with subsequent balloons.
2. **Greedy Arrow Placement:** Place the first arrow at the end position of the first balloon (`prevEnd = points[0][1]`).
3. **Iterate and Check:** For each next balloon:
* If its start position ($x_{\text{start}}$) is **less than or equal to** `prevEnd`, it overlaps with the current arrow and bursts.
* If its start position is **strictly greater than** `prevEnd`, the arrow misses. Increment the arrow count and update `prevEnd` to the end position of this new balloon.



---

### Example Walkthrough

Consider the balloons defined by intervals: `[[10, 16], [2, 8], [1, 6], [7, 12]]`.

#### Step 1: Sort by End Coordinate ($x_{\text{end}}$)

After sorting based on $a[1] < b[1]$:

* Balloon A: `[1, 6]`
* Balloon B: `[2, 8]`
* Balloon C: `[7, 12]`
* Balloon D: `[10, 16]`

#### Step 2: Visual Diagram of Intervals

```
x-axis:   0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16
          |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

A: [1,6]      [===================]
B: [2,8]          [=======================]
C: [7,12]                             [===================]
D: [10,16]                                        [=======================]

Arrow 1:                          ^ (at x = 6)
Arrow 2:                                              ^ (at x = 12)

```

#### Step 3: Simulation Steps

1. **Initialize:** `arrows = 1`, `prevEnd = 6` (end of Balloon A).
2. **Check Balloon B `[2, 8]`:**
* Start $2 \le 6$ (`prevEnd`).
* **Result:** Burst by Arrow 1. `arrows` remains 1.


3. **Check Balloon C `[7, 12]`:**
* Start $7 > 6$ (`prevEnd`). Missed!
* **Result:** Shoot **Arrow 2** at $x = 12$. Update `arrows = 2`, `prevEnd = 12`.


4. **Check Balloon D `[10, 16]`:**
* Start $10 \le 12$ (`prevEnd`).
* **Result:** Burst by Arrow 2. `arrows` remains 2.



**Total Arrows Required:** `2` (fired at $x = 6$ and $x = 12$).

---

### Code Analysis & Edge Cases

Your implementation handles the core interval logic correctly, but keep these two points in mind:

1. **Empty Input Safety:** If `points` is empty, accessing `points[0]` causes runtime errors. Adding `if (points.empty()) return 0;` handles this gracefully.
2. **Interval Boundaries:** The problem specifies that balloons touching at a boundary (e.g., `[1, 2]` and `[2, 3]`) can be burst by a single arrow at $x = 2$. Your condition `points[i][0] > prevEnd` correctly handles this overlap boundary condition.

---

### Complexity Analysis

* **Time Complexity:** $\mathcal{O}(N \log N)$ due to sorting $N$ points. The linear scan takes $\mathcal{O}(N)$ time.
* **Space Complexity:** $\mathcal{O}(1)$ auxiliary space (excluding the space required by `std::sort`, which is $\mathcal{O}(\log N)$ in C++).
