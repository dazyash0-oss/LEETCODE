Here is a step-by-step textual diagram and dry run of your single-pass Peak-Valley algorithm for **LeetCode 135: Candy**.

---

## 1. Example Input & Setup

Consider the ratings array:

* `ratings = [1, 3, 5, 4, 2, 1, 2, 2, 1]`
* Array length $N = 9$
* Initial `totalCandies = 9` *(1 baseline candy per child)*

---

## 2. Ratings Profile & Slopes Visualized

```text
Ratings:      1    3    5    4    2    1    2    2    1
Indices:     [0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]  [8]

Visual Profile:
                   (5) [Peak]
                  /   \
                (3)    (4)
               /          \
             (1)           (2)
                              \
                               (1)---(2)---(2)
                                              \
                                               (1)

```

---

## 3. Step-by-Step Execution Diagram

```text
========================================================================================
START: totalCandies = 9 (Base 1 candy for all 9 kids)
========================================================================================

--- SLOPE 1: Upward slope [index 0 to 2] ---
  i=1: ratings[1]=3 > ratings[0]=1  --> currentPeak = 1, totalCandies += 1  (Total = 10)
  i=2: ratings[2]=5 > ratings[1]=3  --> currentPeak = 2, totalCandies += 2  (Total = 12)
  --> End of UP slope: currentPeak = 2

--- SLOPE 1: Downward slope [index 2 to 5] ---
  i=3: ratings[3]=4 < ratings[2]=5  --> currentValley = 1, totalCandies += 1 (Total = 13)
  i=4: ratings[4]=2 < ratings[3]=4  --> currentValley = 2, totalCandies += 2 (Total = 15)
  i=5: ratings[5]=1 < ratings[4]=2  --> currentValley = 3, totalCandies += 3 (Total = 18)
  --> End of DOWN slope: currentValley = 3

--- ADJUSTMENT AT PEAK (index 2) ---
  Peak was counted by both UP slope (2) and DOWN slope (3).
  Adjustment: totalCandies -= min(2, 3)  --> totalCandies -= 2
  Updated totalCandies = 16

========================================================================================

--- SLOPE 2: Upward slope [index 5 to 6] ---
  i=6: ratings[6]=2 > ratings[5]=1  --> currentPeak = 1, totalCandies += 1  (Total = 17)
  --> End of UP slope: currentPeak = 1

--- FLAT / EQUAL RATINGS [index 6 to 7] ---
  i=7: ratings[7]=2 == ratings[6]=2 --> Reset slope, skip (i++)
  (Child 7 just keeps their base 1 candy)

========================================================================================

--- SLOPE 3: Downward slope [index 7 to 8] ---
  i=8: ratings[8]=1 < ratings[7]=2  --> currentValley = 1, totalCandies += 1 (Total = 18)
  --> End of DOWN slope: currentValley = 1

--- ADJUSTMENT AT PEAK (index 7) ---
  Adjustment: totalCandies -= min(currentPeak=0, currentValley=1) --> totalCandies -= 0
  Updated totalCandies = 18

========================================================================================
END OF ARRAY: Return totalCandies = 18
========================================================================================

```

---

## 4. Final Candy Distribution Check

If we map the actual candies awarded to each child, we get:

```text
Indices:       [0]   [1]   [2]   [3]   [4]   [5]   [6]   [7]   [8]
Ratings:        1     3     5     4     2     1     2     2     1
Candies:        1     2     4     3     2     1     2     2     1
                             ^
                   (Max of Peak & Valley = 4)

Sum of Candies = 1 + 2 + 4 + 3 + 2 + 1 + 2 + 2 + 1 = 18

```

---

## 5. Summary of Why Peak Adjustment Works

```text
         PEAK
        /    \
       /      \
  Peak = 2   Valley = 3

  Ascending height needed  = 2  (0 -> 1 -> 2)
  Descending height needed = 3  (3 -> 2 -> 1 -> 0)

  The peak element needs max(2, 3) = 3 extra candies above baseline.
  Since adding both sequences gives (2 + 3) = 5 extra candies,
  subtracting min(2, 3) = 2 corrects the overcounting perfectly: 5 - 2 = 3.

```
