This implementation solves **LeetCode 84: Largest Rectangle in Histogram** using the **Monotonic Increasing Stack** pattern.

---

## 1. Core Structural Patterns

### Pattern A: Monotonic Increasing Stack

* **What it is:** A stack where elements are kept in strictly increasing order of their heights (`heights[stack[i]] < heights[stack[i+1]]`).
* **Why it's used:** To track the left boundary of potential rectangles. As long as heights increase, any bar could potentially extend further to the right.

```
       Visual Monotonic Stack (Heights)
       
       [5]  <- Pop! Trapped by incoming height 2
       [2]  <- Stack maintains increasing heights
  -1   [1]  <- Base sentinel

```

---

Stack Contents (Stores indices, not values)

```

```

---

### Pattern B: Sentinel Value (`-1`)

* **What it is:** Pushing `-1` onto the stack before processing elements.
* **Why it's used:** Acts as a left boundary marker representing index `-1`. It prevents underflow errors and simplifies width calculation for rectangles that stretch all the way to index `0`.

```
  Index:   -1   0   1   2   3
  Height:  |    2   1   5   6
           ^
       Sentinel Base

```

---

### Pattern C: Width Calculation Strategy

When popping index $k$ from the stack:

* **Height:** $H = \text{heights}[k]$
* **Right Boundary:** Current index $i$ (for main loop) or $\text{heights.size()}$ (for cleanup loop).
* **Left Boundary:** New `stack.top()` *after* popping index $k$.
* **Width Formula:** $\text{Width} = \text{Right Boundary} - \text{Left Boundary} - 1$

```
          Left Boundary                   Right Boundary
          (stack.top())    Popped Index       (i)
                |               |              |
  Heights:    [ 1 ]           [ 5 ]          [ 2 ]
  Indices:      0               1              2
  
  Width = 2 - 0 - 1 = 1

```

---

## 2. Textual Diagram & Execution Trace

Consider input: `heights = [2, 1, 5, 6, 2, 3]`

### Step-by-Step State Flow

```
Initialization:
Stack: [-1] | Max Area: 0

--- Processing Loop (i = 0 to 5) ---

i = 0 (Height = 2):
• heights[0] (2) > heights[stack.top()] (N/A) -> Push index 0
Stack: [-1, 0] | Max Area: 0

i = 1 (Height = 1):
• 1 < heights[0] (2) -> Pop 0!
  - Popped Height = 2
  - Right = 1, Left = stack.top() (-1)
  - Width = 1 - (-1) - 1 = 1
  - Area = 2 * 1 = 2 | Max Area = 2
• Push index 1
Stack: [-1, 1] | Max Area: 2

i = 2 (Height = 5):
• 5 > heights[1] (1) -> Push index 2
Stack: [-1, 1, 2] | Max Area: 2

i = 3 (Height = 6):
• 6 > heights[2] (5) -> Push index 3
Stack: [-1, 1, 3] | Max Area: 2

i = 4 (Height = 2):
• 2 < heights[3] (6) -> Pop 3!
  - Popped Height = 6, Right = 4, Left = 2
  - Width = 4 - 2 - 1 = 1
  - Area = 6 * 1 = 6 | Max Area = 6
• 2 < heights[2] (5) -> Pop 2!
  - Popped Height = 5, Right = 4, Left = 1
  - Width = 4 - 1 - 1 = 2
  - Area = 5 * 2 = 10 | Max Area = 10
• Push index 4
Stack: [-1, 1, 4] | Max Area: 10

i = 5 (Height = 3):
• 3 > heights[4] (2) -> Push index 5
Stack: [-1, 1, 4, 5] | Max Area: 10

--- Cleanup Loop (Flush Stack to Right Boundary = 6) ---

Pop 5 (Height = 3):
• Right = 6, Left = 4 -> Width = 6 - 4 - 1 = 1 -> Area = 3 * 1 = 3

Pop 4 (Height = 2):
• Right = 6, Left = 1 -> Width = 6 - 1 - 1 = 4 -> Area = 2 * 4 = 8

Pop 1 (Height = 1):
• Right = 6, Left = -1 -> Width = 6 - (-1) - 1 = 6 -> Area = 1 * 6 = 6

Final Answer: 10

```

---

## 3. Key Notes & Summary

* **Time Complexity:** $O(N)$ — Every index is pushed and popped at most once.
* **Space Complexity:** $O(N)$ — Monotonic stack uses space proportional to input array length.
* **Pattern Trigger:** Use a monotonic stack whenever you need to find the **Next Smaller Element** or **Previous Smaller Element** for every item in an array.
