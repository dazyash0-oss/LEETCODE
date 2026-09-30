Here is the detailed breakdown of your C++ solution for **LeetCode 85: Maximal Rectangle** (which builds directly on **LeetCode 84: Largest Rectangle in Histogram**).

---

### Multi-Pattern Breakdown

#### Pattern 1: Dynamic Histogram Reduction (Problem Transformation)

* **Why it fits:** Finding the largest subgrid of `'1'`s in a 2D matrix directly can be complex. By processing the matrix row by row, each row can be treated as the base of a 1D histogram where consecutive `'1'`s above each cell define the column heights.
* **Mechanism:**
* If `matrix[i][j] == '1'`, increment `height[j]` by $1$.
* If `matrix[i][j] == '0'`, reset `height[j]` to $0$ (since a rectangle cannot cross a `'0'`).



#### Pattern 2: Monotonic Stack for Largest Rectangle in Histogram

* **Why it fits:** For each column index $i$, we want to find the largest rectangle with height $h[i]$. To maximize its width, we need the **first smaller element to the left** and the **first smaller element to the right**. A monotonic increasing stack tracks candidate heights in $O(1)$ amortized time.
* **Mechanism:**
* Maintain indices in a stack such that heights corresponding to indices are strictly increasing.
* When encountering a lower height `curr`, pop elements from the stack. For each popped height $H$:
* Right boundary is $i$ (current index).
* Left boundary is `st.top()` (after popping).
* $\text{Width} = i - \text{st.top()} - 1$ (or simply $i$ if stack becomes empty).





#### Pattern 3: Virtual Sentinel Element

* **Why it fits:** Processing elements remaining in the stack at the end of the histogram array normally requires clean-up code after the loop.
* **Mechanism:** The loop runs up to index $n$ (`i <= n`), injecting a virtual bar of height `0` at $i = n$. This forces all remaining elements in the stack to be popped and evaluated before returning.

---

### Complexity Analysis

* **Time Complexity:** $\mathcal{O}(N \times M)$
* Each element of the $N \times M$ matrix is visited once to update the height array.
* For each of the $N$ rows, `hist()` processes an $M$-length array. Since every index is pushed onto and popped from the stack at most once, `hist()` runs in $\mathcal{O}(M)$ time per row.
* Total time: $N \times \mathcal{O}(M) = \mathcal{O}(N \times M)$.


* **Space Complexity:** $\mathcal{O}(M)$
* We maintain a 1D `height` vector of size $M$ and a monotonic stack holding at most $M + 1$ indices.



---

### Textual Diagram Notes with Example

#### Matrix Setup ($3 \times 4$)

$$\begin{bmatrix}  \text{'1'} & \text{'0'} & \text{'1'} & \text{'0'} \\ \text{'1'} & \text{'0'} & \text{'1'} & \text{'1'} \\ \text{'1'} & \text{'1'} & \text{'1'} & \text{'1'} \end{bmatrix}$$

---

#### Row-by-Row Execution & Histogram Heights

```text
ROW 0: ['1', '0', '1', '0']
Heights: [1, 0, 1, 0]
Calling hist([1, 0, 1, 0]) -> Max Area = 1

```

---

ROW 1: ['1', '0', '1', '1']
Heights: [2, 0, 2, 1]  (height[0] incremented, height[1] reset to 0)
Calling hist([2, 0, 2, 1]) -> Max Area = 2

---

ROW 2: ['1', '1', '1', '1']
Heights: [3, 1, 3, 2]  (height[1] incremented to 1)
Calling hist([3, 1, 3, 2]) -> Max Area = 6

```

```

---

#### Detailed Stack Execution Trace for Row 2 (`hist([3, 1, 3, 2])`)

```text
Input Histogram: h = [3, 1, 3, 2], n = 4 (Virtual element h[4] = 0 appended)

i = 0: curr = 3
  Stack empty -> push index 0. Stack: [0]

i = 1: curr = 1
  h[st.top()] = 3 > 1 -> POP 0
    height = 3
    st empty -> width = i = 1
    area = 3 * 1 = 3
  Push index 1. Stack: [1]

i = 2: curr = 3
  h[st.top()] = 1 <= 3 -> push index 2. Stack: [1, 2]

i = 3: curr = 2
  h[st.top()] = 3 > 2 -> POP 2
    height = 3
    st top is 1 -> width = 3 - 1 - 1 = 1
    area = 3 * 1 = 3
  Push index 3. Stack: [1, 3]

i = 4 (Virtual Bar): curr = 0
  h[st.top()] = 2 > 0 -> POP 3
    height = 2
    st top is 1 -> width = 4 - 1 - 1 = 2
    area = 2 * 2 = 4

  h[st.top()] = 1 > 0 -> POP 1
    height = 1
    st empty -> width = 4
    area = 1 * 4 = 4

MAX AREA OVERALL = 6 (Achieved by width=3, height=2 or height=3, width=2)

```

---

### Key Takeaways Summary

1. **Problem Reduction:** Converts 2D matrix dynamic subgrids into $N$ standard 1D histogram problems.
2. **Monotonic Stack Mechanics:** Maintains indices with monotonically increasing heights to locate boundaries in $O(1)$ time per pop operation.
3. **Width Formula:** $\text{width} = i - \text{st.top()} - 1$ works because `st.top()` holds the closest index to the left with a strictly smaller height.
