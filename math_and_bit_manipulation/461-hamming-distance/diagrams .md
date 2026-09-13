This solution computes the Hamming distance between two integers `x` and `y` by combining two classic bit-manipulation techniques:

1. **`x ^ y` (Bitwise XOR):** Isolate the differing bits.
2. **`n &= n - 1` (Brian Kernighan's Algorithm):** Count set bits in $O(k)$ time, where $k$ is the number of set bits.

---

### Step 1: `int n = x ^ y;`

The XOR operator ($\oplus$) sets a bit to `1` **only if** the corresponding bits of `x` and `y` are different.

For example, taking $x = 9$ (`1001`) and $y = 14$ (`1110`):

```text
  x = 9 :  1  0  0  1
  y = 14:  1  1  1  0
  -------------------
  n     :  0  1  1  1   (3 differing bit positions)
              ^  ^  ^

```

Now, the problem reduces to **counting the total number of 1s in `n**`.

---

### Step 2: `n &= n - 1;` (Brian Kernighan's Bit-Trick)

Instead of checking all 32 bits one by one using a shift loop (`n >> 1`), **`n &= n - 1` clears the lowest (rightmost) set bit of `n` to `0` in a single operation.**

#### Why `n - 1` flips the lowest set bit

Subtracting `1` from a binary number flips all bits from the rightmost `1` down to the end:

```text
  n     :  ... 1 0 0 0   (Rightmost 1 is at index 3)
  n - 1 :  ... 0 1 1 1   (Rightmost 1 becomes 0, trailing 0s become 1s)

```

Performing a bitwise AND (`&`) between `n` and `n - 1` cancels out those lower bits:

```text
      n :  ... 1 0 0 0
& (n-1) :  ... 0 1 1 1
----------------------
  Result:  ... 0 0 0 0   <-- Rightmost 1 is gone!

```

---

### Trace Walkthrough: $x = 9$, $y = 14$

Initial state: `n = 9 ^ 14 = 7` (binary `0111`), `dist = 0`

#### **Iteration 1**

* `dist = 1`
* Operation: `n = 7 & 6`

```text
  n     = 7 :  0  1  1  1
  n - 1 = 6 :  0  1  1  0
  -----------------------
  n &= n-1  :  0  1  1  0   (Rightmost 1 cleared)

```

#### **Iteration 2**

* `dist = 2`
* Operation: `n = 6 & 5`

```text
  n     = 6 :  0  1  1  0
  n - 1 = 5 :  0  1  0  1
  -----------------------
  n &= n-1  :  0  1  0  0   (Next 1 cleared)

```

#### **Iteration 3**

* `dist = 3`
* Operation: `n = 4 & 3`

```text
  n     = 4 :  0  1  0  0
  n - 1 = 3 :  0  0  1  1
  -----------------------
  n &= n-1  :  0  0  0  0   (Final 1 cleared)

```

#### **Loop Exit**

* `n == 0` $\rightarrow$ Loop terminates.
* `return dist;` $\rightarrow$ **Output: 3**

---

### Complexity Analysis

| Metric | Time | Space | Notes |
| --- | --- | --- | --- |
| **Standard Bit-Shift Loop** | $O(W)$ | $O(1)$ | Always runs $W$ times (32 iterations for 32-bit int) |
| **Kernighan's Algorithm** | $O(k)$ | $O(1)$ | Runs only $k$ times ($k$ = number of differing bits, $k \le 32$) |
