This algorithm approaches the **Coin Change** problem by framing it as a search problem over the exact number of coins used ($i$), trying candidate totals from the minimum theoretical bound (`minn`) up to the maximum theoretical bound (`maxx`).

It modifies the coin values in-place by subtracting the smallest coin (`minVal`) to search for combinations using recursion with depth limits and bounds pruning.

---

### Step-by-Step Logic Breakdown

#### 1. Basic Edge Cases & Preprocessing

* **Amount is 0:** Returns `0`.
* **Single Coin Type:** Returns `amount / coin[0]` if divisible, otherwise `-1`.
* **Sorting:** Sorts `coins` in ascending order to easily identify `minVal` (`coins[0]`).

#### 2. GCD Pruning & In-Place Coin Transformation

* Checks if `amount` equals any single coin (returns `1`).
* Computes the **GCD** of all coins smaller than or equal to `amount`. If `amount % gcdVal != 0`, it is mathematically impossible to form `amount`, so it returns `-1`.
* **Transformation:** Subtracts `minVal` from each subsequent coin:

$$\text{coins}[\text{idx}] = \text{original\_coin}[\text{idx}] - \text{minVal}$$


This converts the equation $\sum (c_k \cdot x_k) = A$ with $\sum x_k = i$ into matching remaining offsets.

#### 3. Theoretical Coin Count Bounds

* **`maxx`**: $\lfloor \text{amount} / \text{minVal} \rfloor$ (maximum possible coins if using only the smallest coin).
* **`minn`**: $\lceil \text{amount} / \text{largest\_usable\_coin} \rceil$ (minimum possible coins needed).

#### 4. Iterative Search & Recursive Backtracking (`findcomb`)

Iterates $i$ from `minn` to `maxx`. For a target count $i$, it checks whether a valid combination exists using `findcomb`. The first valid $i$ found is guaranteed to be the minimum coins required.

---

### Walkthrough Example

Consider the input: **`coins = [2, 5]`, `amount = 11**`

#### Step 1: Preprocessing & Transformation

* **`coins` array:** `[2, 5]`
* **`minVal`:** `2`
* **GCD Check:** $\text{gcd}(2, 5) = 1$. Since $11 \pmod 1 == 0$, search proceeds.
* **Coin Transformation:**
* `coins[0]` stays `2` (used as `minVal`).
* `coins[1]` becomes $5 - 2 = 3$.


* **`idx`:** `2` (both coins are $\le 11$).

#### Step 2: Bounds Calculation

* **`minn`:** $\lfloor (11 - 1) / 5 \rfloor + 1 = 2 + 1 = 3$
* **`maxx`:** $\lfloor 11 / 2 \rfloor = 5$
* Search range for coin count $i$: **$3 \le i \le 5$**

#### Step 3: Branching & Backtracking (`findcomb`)

```
                      i = 3 (Target Coins)
                Remaining Amount: 11 - (2 * 3) = 5
                 Available Transformed Coin: [3]
                                |
               +----------------+----------------+
               | p = 1                           | p = 0
       Rem: 5 - 1*3 = 2                  Rem: 5 - 0*3 = 5
       Req: 3 - 1 = 2                    Req: 3 - 0 = 3
       l == r (1==1)                     l == r (1==1)
       Returns FALSE                     Returns FALSE
                                |
                         i = 3 FAILS

                                |

                      i = 4 (Target Coins)
                Remaining Amount: 11 - (2 * 4) = 3
                 Available Transformed Coin: [3]
                                |
               +----------------+
               | p = 1
       Rem: 3 - 1*3 = 0
       Req: 4 - 1 = 3
       Amount == 0 -> Returns TRUE!
                                |
                         i = 4 SUCCEEDS

```

#### Detailed Calculations per Iteration:

1. **Testing $i = 3$ coins:**
* Target offset `amount - minVal * i` $= 11 - (2 \times 3) = 5$.
* Call `findcomb(coins, l=1, r=1, amount=5, rq=3)`:
* Try $p = 1$ coin of value `3`: remaining offset $= 5 - 3 = 2$, remaining coin quota $= 2$. Since $l == r$ and $2 \neq 0$, branch fails.
* Try $p = 0$ coins of value `3`: remaining offset $= 5$, remaining coin quota $= 3$. Fails.


* Result: **False** (11 cannot be formed with 3 coins).


2. **Testing $i = 4$ coins:**
* Target offset `amount - minVal * i` $= 11 - (2 \times 4) = 3$.
* Call `findcomb(coins, l=1, r=1, amount=3, rq=4)`:
* Try $p = 1$ coin of value `3`: remaining offset $= 3 - 1 \times 3 = 0$.
* Base case hit (`amount == 0`): returns **True**.


* Result: **True** (Combination found: one `5` coin and three `2` coins $= 5 + 2 + 2 + 2 = 11$, total **4** coins).



* **Final Return Value:** `4`
