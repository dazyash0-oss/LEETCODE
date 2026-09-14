This C++ code solves LeetCode 338 ("Counting Bits"). It uses **Dynamic Programming** to find the number of set bits (`1`s in binary representation) for all numbers from `0` to `n` in $O(n)$ time.

Here is a line-by-line breakdown of how it works:

---

### Code Breakdown

`class Solution {`

* **Line 1:** Defines the `Solution` class required by the LeetCode platform.

`public:`

* **Line 2:** Makes the `countBits` function accessible from outside the class.

`vector<int> countBits(int n) {`

* **Line 3:** Defines a function named `countBits` that takes an integer `n` as input and returns a vector of integers (`vector<int>`).

`std::vector<int> dp(n + 1, 0);`

* **Line 4:** Initializes a dynamic programming vector named `dp` of size `n + 1`, with all elements initialized to `0`. `dp[i]` will store the count of `1`s in the binary representation of `i`.

`int sub = 1;`

* **Line 5:** Tracks the largest power of 2 seen so far ($1, 2, 4, 8, \dots$). This serves as an offset to map current numbers back to previously solved smaller numbers.

`for (int i = 1; i <= n; i++) {`

* **Line 6:** Starts a loop iterating through every integer `i` from `1` up to `n`. `dp[0]` remains `0` because `0` has zero `1`s in binary.

`if (sub * 2 == i) {`

* **Line 7:** Checks if `i` has reached the next power of 2 (e.g., when `i` becomes `2`, `4`, `8`, `16`).

`sub = i;`

* **Line 8:** Updates `sub` to `i` whenever a new power of 2 is hit.

`}`

* **Line 9:** Closes the `if` block.

`dp[i] = dp[i - sub] + 1;`

* **Line 10:** **The Core DP Recurrence Relation.** Calculates set bits using previously computed results:
* Subtracting `sub` strips the most significant `1` bit from `i`.
* `dp[i - sub]` retrieves the count of remaining `1`s.
* Adding `+ 1` accounts for the most significant `1` bit that was removed.



`}`

* **Line 11:** Closes the `for` loop.

`return dp;`

* **Line 12:** Returns the populated `dp` vector containing the bit counts for numbers `0` to `n`.

`}`

* **Line 13:** Closes the `countBits` function.

`};`

* **Line 14:** Closes the `Solution` class definition.

---

### How the DP Relation Works visually

Powers of 2 reset the pattern because they add a new binary digit:

| Number (`i`) | Binary | Power of 2 offset (`sub`) | Lookup (`i - sub`) | Calculation (`dp[i - sub] + 1`) | `dp[i]` |
| --- | --- | --- | --- | --- | --- |
| **0** | `0000` | - | - | Base case | **0** |
| **1** | `0001` | 1 | 0 | `dp[0] + 1` = 0 + 1 | **1** |
| **2** | `0010` | 2 | 0 | `dp[0] + 1` = 0 + 1 | **1** |
| **3** | `0011` | 2 | 1 | `dp[1] + 1` = 1 + 1 | **2** |
| **4** | `0100` | 4 | 0 | `dp[0] + 1` = 0 + 1 | **1** |
| **5** | `0101` | 4 | 1 | `dp[1] + 1` = 1 + 1 | **2** |
| **6** | `0110` | 4 | 2 | `dp[2] + 1` = 1 + 1 | **2** |
| **7** | `0111` | 4 | 3 | `dp[3] + 1` = 2 + 1 | **3** |

---

### Complexity Analysis

* **Time Complexity:** $O(n)$ — Calculates each element from $0$ to $n$ in constant $O(1)$ time.
* **Space Complexity:** $O(n)$ — Uses a vector of size $n + 1$ to store the results.
