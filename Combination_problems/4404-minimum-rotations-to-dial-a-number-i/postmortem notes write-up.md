This C++ code calculates the **minimum total number of rotations** needed to dial or enter a string of digits on a circular dial (like a circular lock or a rotary wheel with digits `0` through `9`), starting from `'0'`.

---

## Line-by-Line Explanation

```cpp
class Solution {
public:

```

* **Line 1–2:** Defines the class `Solution` and makes its member functions publicly accessible.

---

```cpp
    int dist(char a, char b){
        int x = abs((a-'0') - (b-'0'));
        return min(x, 10-x);
    }

```

* **`int dist(char a, char b)`**: A helper function that takes two character digits `a` and `b` and computes the shortest distance between them on a 10-digit circular dial (`0` to `9`).
* **`int x = abs((a-'0') - (b-'0'));`**:
* `(a - '0')` converts the character digit (e.g., `'3'`) to its corresponding integer value (`3`).
* `abs(...)` calculates the absolute difference, giving the **clockwise / direct distance** along the straight sequence.


* **`return min(x, 10 - x);`**:
* Since the dial is circular (containing 10 total numbers: `0, 1, 2, 3, 4, 5, 6, 7, 8, 9`), you can move either clockwise or counter-clockwise.
* `x` is the distance moving one way; `10 - x` is the distance moving the opposite way around the wheel.
* `min(...)` returns the shorter path.



---

```cpp
    int minRotations(string s) {
        int total = 0;
        char last = '0';

```

* **`int minRotations(string s)`**: Main function taking the target string `s` (e.g., `"821"`).
* **`int total = 0;`**: Tracks the cumulative total rotations needed for the entire string.
* **`char last = '0';`**: Initializes the starting position of the dial at digit `'0'`.

---

```cpp
        for(char c : s){
            total += dist(last, c);
            last = c;
        }

```

* **`for(char c : s)`**: Iterates through every character `c` in the input string `s` from left to right.
* **`total += dist(last, c);`**: Calculates the shortest rotation from the current dial position (`last`) to the next character (`c`) and adds it to `total`.
* **`last = c;`**: Updates `last` so the dial stays at `c` for the next character move.

---

```cpp
        return total;
    }
};

```

* **`return total;`**: Returns the final accumulated minimum rotations.

---

## Step-by-Step Example: `s = "821"`

### The Dial Setup

Imagine the 10 digits arranged on a circular clock/wheel:

```text
         0 (Start)
      9     1
    8         2
    7         3
      6     4
         5

```

---

### Step 1: Move from `'0'` to `'8'`

```text
Forward path (0 -> 1 -> 2 -> ... -> 8): 8 steps
Backward path (0 -> 9 -> 8):             2 steps

        [0] --1--> 9 --2--> [8]  (Shortest = 2)

```

* **Calculation:**
* $x = \vert{}0 - 8\vert{} = 8$
* $10 - x = 10 - 8 = 2$
* $\min(8, 2) = 2$


* **State Update:** `total` = $0 + 2 = 2$, `last` = `'8'`

---

### Step 2: Move from `'8'` to `'2'`

```text
Forward path (8 -> 9 -> 0 -> 1 -> 2):  4 steps
Backward path (8 -> 7 -> ... -> 2):    6 steps

        [8] --1--> 9 --2--> 0 --3--> 1 --4--> [2]  (Shortest = 4)

```

* **Calculation:**
* $x = \vert{}8 - 2\vert{} = 6$
* $10 - x = 10 - 6 = 4$
* $\min(6, 4) = 4$


* **State Update:** `total` = $2 + 4 = 6$, `last` = `'2'`

---

### Step 3: Move from `'2'` to `'1'`

```text
Forward path (2 -> 3 -> ... -> 1): 9 steps
Backward path (2 -> 1):            1 step

        [2] --1--> [1]  (Shortest = 1)

```

* **Calculation:**
* $x = \vert{}2 - 1\vert{} = 1$
* $10 - x = 10 - 1 = 9$
* $\min(1, 9) = 1$


* **State Update:** `total` = $6 + 1 = 7$, `last` = `'1'`

---

### Final Result for `"821"`

**Total Minimum Rotations:** $2 + 4 + 1 = \mathbf{7}$

---


After rotating to a digit `c`, the dial remains at `c`. The next move must start from where the dial was left.
