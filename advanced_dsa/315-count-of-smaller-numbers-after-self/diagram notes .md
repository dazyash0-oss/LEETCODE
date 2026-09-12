### Analysis & Key Takeaways

This solution addresses the classic problem **"Count of Smaller Numbers After Self"** (LeetCode 315) using a modified **Merge Sort** algorithm on indexed pairs.

* **Time Complexity:** **$O(N \log N)$** for all cases (Best, Average, Worst).
* **Space Complexity:** **$O(N)$** auxiliary space for the temporary vector `tmp` and the array of pairs `v`.
* **Key Technique (Inversion Counting during Descending Merge Sort):**
* By keeping track of each number's original index via `pair<value, original_index>` and sorting subarrays in **descending order**, any element remaining in the right subarray `[j...right]` that is strictly smaller than `v[i]` will automatically appear *after* `v[i]` in the original array.
* When `v[i].first > v[j].first`, since `[j...right]` is sorted in descending order, all elements from index `j` to `right` are smaller than `v[i]`. Thus, we add `right - j + 1` directly to `count[v[i].second]`.



---

### Class Design & Data Flow

#### High-Level Data Structure Layout

```text
ORIGINAL INPUT: nums = [5, 2, 6, 1]

PAIR VECTOR (Value, Original Index):
v = [ (5, 0), (2, 1), (6, 2), (1, 3) ]

COUNT ARRAY:
count = [0, 0, 0, 0]   (Stores total smaller elements after self)

```

---

### Step-by-Step Example Walkthrough

Let's trace how the algorithm processes `nums = [5, 2, 6, 1]`.

#### 1. Initial State

* `v = [(5, 0), (2, 1), (6, 2), (1, 3)]`
* `count = [0, 0, 0, 0]`

#### 2. Divide Phase

Split into two halves:

* Left subproblem: `[(5, 0), (2, 1)]`
* Right subproblem: `[(6, 2), (1, 3)]`

---

#### 3. Merge Left Half: `[(5, 0)]` and `[(2, 1)]`

* `left = 0`, `mid = 0`, `right = 1`
* Compare `v[i = 0]` (5) and `v[j = 1]` (2):
* `5 > 2`: `v[i].first > v[j].first`.
* Elements in right half that are smaller than `5`: from `j = 1` to `right = 1` $\rightarrow$ Count = `1 - 1 + 1 = 1`.
* `count[v[0].second] += 1` $\rightarrow$ `count[0]` becomes `1`.
* Copy `(5, 0)` to `tmp`, `i` advances.


* Copy remaining `(2, 1)`.
* **Sorted Left Half:** `[(5, 0), (2, 1)]`, `count = [1, 0, 0, 0]`

---

#### 4. Merge Right Half: `[(6, 2)]` and `[(1, 3)]`

* `left = 2`, `mid = 2`, `right = 3`
* Compare `v[i = 2]` (6) and `v[j = 3]` (1):
* `6 > 1`: `v[i].first > v[j].first`.
* Elements in right half smaller than `6`: `3 - 3 + 1 = 1`.
* `count[v[2].second] += 1` $\rightarrow$ `count[2]` becomes `1`.
* Copy `(6, 2)` to `tmp`, `i` advances.


* Copy remaining `(1, 3)`.
* **Sorted Right Half:** `[(6, 2), (1, 3)]`, `count = [1, 0, 1, 0]`

---

#### 5. Final Merge: Left `[(5, 0), (2, 1)]` and Right `[(6, 2), (1, 3)]`

* `left = 0`, `mid = 1`, `right = 3`, `i = 0`, `j = 2`

```text
Step 1: Compare v[i=0] (5) and v[j=2] (6)
        5 <= 6  --> Right element is larger or equal!
        No count update.
        Copy (6, 2) to tmp. j becomes 3.

Step 2: Compare v[i=0] (5) and v[j=3] (1)
        5 > 1   --> Left element is larger!
        Elements in right subarray from j=3 to right=3 are smaller than 5.
        Addition: right - j + 1 = 3 - 3 + 1 = 1.
        count[v[0].second] += 1  --> count[0] becomes 1 + 1 = 2.
        Copy (5, 0) to tmp. i becomes 1.

Step 3: Compare v[i=1] (2) and v[j=3] (1)
        2 > 1   --> Left element is larger!
        Addition: right - j + 1 = 3 - 3 + 1 = 1.
        count[v[1].second] += 1  --> count[1] becomes 0 + 1 = 1.
        Copy (2, 1) to tmp. i becomes 2 (exceeds mid).

Step 4: Copy remaining elements from right half: (1, 3).

```

* **Final Merged `v`:** `[(6, 2), (5, 0), (2, 1), (1, 3)]`
* **Final `count` Array:** `[2, 1, 1, 0]`

---

### Textual Merge Execution Diagram

```text
MERGE STEP (Descending Order):

Left Subarray (Sorted Desc):          Right Subarray (Sorted Desc):
[ (5, idx=0), (2, idx=1) ]           [ (6, idx=2), (1, idx=3) ]
       ^                                    ^
       i                                    j

1. v[i].val (5) <= v[j].val (6)
   - Copy (6, idx=2) to output.
   - Advance j -> points to (1, idx=3).

Left:  [ (5, idx=0), (2, idx=1) ]     Right: [ (6, idx=2), (1, idx=3) ]
                ^                                                ^
                i                                                j

2. v[i].val (5) > v[j].val (1)
   - Remaining elements in Right from j to end = [ (1, idx=3) ] (Size = 1)
   - count[idx=0] += 1
   - Copy (5, idx=0) to output.
   - Advance i -> points to (2, idx=1).

3. v[i].val (2) > v[j].val (1)
   - Remaining elements in Right from j to end = [ (1, idx=3) ] (Size = 1)
   - count[idx=1] += 1
   - Copy (2, idx=1) to output.

```

---

### Operational Flowchart

```text
                           countSmaller(nums)
                                   |
                     Create v = [(nums[i], i)]
                   Initialize count array with 0s
                                   |
                        mergeSort(v, 0, N-1)
                                   |
                  +----------------+----------------+
                  |                                 |
        left >= right? (Yes)              left < right (No)
             Return                                 |
                                             Calculate mid
                                       mergeSort(left, mid)
                                      mergeSort(mid+1, right)
                                                 |
                                    merge(left, mid, right)
                                                 |
                                       +---------+---------+
                                       | While i<=mid &    |
                                       |       j<=right    |
                                       +---------+---------+
                                                 |
                                   v[i].first <= v[j].first?
                                      /                 \
                                   (YES)                (NO)
                                    /                     \
                             Copy v[j] to tmp       count[v[i].second] += (right - j + 1)
                                 j++                Copy v[i] to tmp
                                                        i++

```
