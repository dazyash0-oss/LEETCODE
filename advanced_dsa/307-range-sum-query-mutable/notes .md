### Analysis & Key Takeaways

Your **Binary Indexed Tree (Fenwick Tree)** implementation for the Range Sum Query Problem is standard and optimal:

* **Time Complexity:**
* `update(index, val)`: **$O(\log N)$**
* `sumRange(left, right)`: **$O(\log N)$**
* Constructor initialization: **$O(N \log N)$** (or $O(N)$ with linear BIT construction)


* **Space Complexity:** **$O(N)$** auxiliary space to store the BIT array and mirror `nums` vector.
* **Key Technique (`idx & (-idx)`):** Isolates the **Lowest Set Bit (LSB)** of `idx`. Traversing via `idx -= LSB` moves down the tree parent links during queries, while `idx += LSB` propagates updates upward across responsible ranges.

---

### Class Design & Data Flow

#### High-Level Data Structure Layout

Below is a visual representation of responsibility ranges covered by tree nodes in a 1-based Fenwick Tree of size 8:

```
Index:    1      2      3      4      5      6      7      8
Bit:    [0001] [0010] [0011] [0100] [0101] [0110] [0111] [1000]

       +----+
       | 8  |-----------------------------------------------> Covers [1..8]
       +----+
       /    \
   +----+  +----+
   | 4  |  | 6  |--------------------> Covers [5..6]         Covers [1..4]
   +----+  +----+
   /  \    /    \
 +--+ +--++--+ +--+
 |1 | |3 ||5 | |7 |                                           Covers length 1 elements
 +--+ +--++--+ +--+

```

---

### Operations Breakdown

#### 1. `getSum(idx)` Flow (Prefix Sum $[1 \dots idx]$)

```
Start sum = 0
Loop while idx > 0:
  ├── sum += bit[idx]
  └── Strip LSB: idx = idx - (idx & -idx)
Return sum

```

#### 2. `addValue(idx, val)` Flow (Point Update Propagation)

```
Loop while idx < bit.size():
  ├── bit[idx] += val
  └── Add LSB: idx = idx + (idx & -idx)

```

#### 3. `NumArray::update(index, val)` Flow

```
1. Calculate delta: diff = val - nums[index]
2. Propagate delta to BIT (converting 0-based index to 1-based):
   └── bit.addValue(index + 1, diff)
3. Update underlying array cache: nums[index] = val

```

#### 4. `NumArray::sumRange(left, right)` Flow

```
1. Get prefix sum up to right (1-based index = right + 1):
   └── rightSum = bit.getSum(right + 1)
2. Get prefix sum up to left - 1 (1-based index = left):
   └── leftSum = bit.getSum(left)
3. Return range sum: rightSum - leftSum

```

---

### Technical Highlights & Optimizations

1. **Linear Construction ($O(N)$ Initialization):**
* **Current Approach:** Building the tree by calling `addValue` $N$ times takes $O(N \log N)$ time.
* **$O(N)$ Optimization:** Populate `bit` directly with `nums`, then propagate values in a single pass:
```cpp
BIT(const vector<int>& nums) {
    int n = nums.size();
    bit.assign(n + 1, 0);
    for (int i = 0; i < n; ++i) bit[i + 1] = nums[i];
    for (int i = 1; i <= n; ++i) {
        int parent = i + (i & -i);
        if (parent <= n) bit[parent] += bit[i];
    }
}

```




2. **Bitwise Bit-Trick Explanation:**
* `idx & (-idx)` uses two's complement representation (`-idx = ~idx + 1`).
* Example (`idx = 6` $\rightarrow$ `0110` in binary):
* `~idx` = `1001`
* `-idx` = `1010`
* `6 & (-6)` = `0110 & 1010` = `0010` (2)
* Subtracting LSB: `6 - 2 = 4` (`0100`) $\rightarrow$ moves parent node.
