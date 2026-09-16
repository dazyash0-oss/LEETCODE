This is the optimal **$\mathcal{O}(1)$ time and space** solution for checking if a integer is a power of two using bit manipulation.

### How It Works

A power of two in binary has **exactly one bit set to `1**`, with all other bits being `0`.

When you subtract `1` from a power of two, that single `1`-bit flips to `0`, and all the trailing `0`-bits flip to `1`. Performing a bitwise `AND` (`&`) between `n` and `n - 1` will result in `0` if and only if `n` is a power of two.

The condition `n > 0` handles non-positive numbers, as negative numbers and zero cannot be powers of two.

---

### Textual Diagram

#### Case 1: `n = 8` (Power of Two)

```text
n       =  8  ->  0 1 0 0  (Binary)
n - 1   =  7  ->  0 0 1 1  (Binary)
-----------------------------------
n & (n-1)     ->  0 0 0 0  (Result is 0 -> TRUE)

```

#### Case 2: `n = 6` (Not a Power of Two)

```text
n       =  6  ->  0 1 1 0  (Binary)
n - 1   =  5  ->  0 1 0 1  (Binary)
-----------------------------------
n & (n-1)     ->  0 1 0 0  (Result is non-zero -> FALSE)

```

---

### Key Properties

* **Time Complexity:** $\mathcal{O}(1)$ — Executes a single bitwise operation and comparison.
* **Space Complexity:** $\mathcal{O}(1)$ — Uses no extra space.
* **Edge Case:** `n = 0` evaluates to `false` without causing underflow issues because of short-circuit evaluation in `n > 0`.
