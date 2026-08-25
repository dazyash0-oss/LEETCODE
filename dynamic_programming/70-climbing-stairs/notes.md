
---

**Code Breakdown & Notes**

* **Base Cases ($n \le 3$):** Direct return since $n=1 \to 1$, $n=2 \to 2$, and $n=3 \to 3$ match their respective inputs.
* **State Shift:**
* `a` represents $f(i-2)$
* `b` represents $f(i-1)$
* `c` represents $f(i)$


* **Recurrence Relation:** To reach step $i$, you can either come from step $i-1$ (take 1 step) or step $i-2$ (take 2 steps):

$$f(i) = f(i-1) + f(i-2)$$



---

**Pattern Cheatsheet: Dynamic Programming (1D Fibonacci Pattern)**

Use this pattern whenever a choice at the current state depends on a fixed combination of previous states.

| Problem Type | Recurrence / Core Logic | Example Problems | Space Optimization Trick |
| --- | --- | --- | --- |
| **Standard Fibonacci** | $f(n) = f(n-1) + f(n-2)$ | Climbing Stairs, House Robber | Use 2–3 variables instead of an array ($O(1)$ space). |
| **Variable Steps** | $f(n) = \sum_{k=1}^{k} f(n-k)$ | Min Cost Climbing Stairs, Staircase with $K$ steps | Keep a rolling window or a running sum array. |
| **Grid Path Counting** | $dp[i][j] = dp[i-1][j] + dp[i][j-1]$ | Unique Paths | Keep only 1D array representing the previous row. |

---

**Common Variations & Tweaks**

* **If you could take up to $k$ steps:** Use an inner loop over $k$ steps instead of hardcoding $1$ and $2$.
* **If step costs apply:** State transitions become $dp[i] = \min(dp[i-1], dp[i-2]) + cost[i]$.
