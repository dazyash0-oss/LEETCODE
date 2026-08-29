This implementation solves the **Longest Increasing Subsequence (LIS)** problem using the **Patience Sorting algorithm** in **$O(n \log n)$ time** and **$O(n)$ space**.

---

## Code Analysis & How It Works

1. **`res` vector**: Stores the smallest tail of all increasing subsequences of various lengths found so far.
2. **Appending (`res.back() < n`)**: If `n` is strictly greater than all elements in `res`, extend the longest subsequence by appending `n`.
3. **Replacing (`res[idx] = n`)**: Otherwise, find the smallest element in `res` that is greater than or equal to `n` (using `binarySearch`) and overwrite it with `n`. This lowers the tail value, making it easier for future numbers to extend the sequence.
4. **Binary Search Logic**: The `binarySearch` helper function implements standard lower bound logic (`std::lower_bound`), returning the index of the first element $\ge \text{target}$.

---

## C++ Standard Library Alternative

In C++, you can replace the custom `binarySearch` member function entirely using `std::lower_bound`:

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> res;
        for (int n : nums) {
            auto it = lower_bound(res.begin(), res.end(), n);
            if (it == res.end()) {
                res.push_back(n);
            } else {
                *it = n;
            }
        }
        return res.size();
    }
};

```

---

## LIS & Binary Search Cheat Sheet

### 1. Key Concepts

* **`res` is NOT the actual sequence**: The elements inside `res` at the end do not necessarily represent a valid LIS array, but `res.size()` **is guaranteed to be the exact length** of the LIS.
* **Strictly Increasing vs. Non-Decreasing**:
* **Strictly Increasing (`<`)**: Use `std::lower_bound` (finds first element $\ge \text{target}$).
* **Non-Decreasing / Duplicates Allowed ($\le$)**: Use `std::upper_bound` (finds first element $> \text{target}$).



### 2. Binary Search Patterns Cheat Sheet

| Function / Goal | Condition | C++ STL Equivalent | Result Pointer |
| --- | --- | --- | --- |
| **First element $\ge \text{target}$** | Standard LIS (Strictly Increasing) | `std::lower_bound` | Returns `left` index |
| **First element $> \text{target}$** | Longest Non-Decreasing Subsequence | `std::upper_bound` | Returns `left` index |
| **Mid calculation to avoid overflow** | Large range indices | — | `int mid = left + (right - left) / 2;` |

### 3. Complexity Summary

* **Time Complexity**: $O(n \log n)$ — Iterating through $n$ elements takes $O(n)$, and binary searching in `res` takes $O(\log n)$.
* **Space Complexity**: $O(n)$ — Auxiliary array `res` stores at most $n$ elements.
