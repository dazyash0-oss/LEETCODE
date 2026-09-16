This code calculates the sum of two integers without using the `+` or `-` operators by simulating hardware-level binary addition using bitwise operations.

### How It Works

* **XOR (`a ^ b`):** Performs addition without taking carry into account (also known as half-addition).
* **AND (`a & b`) shifted left by 1 (`<< 1`):** Finds the carry bits and shifts them to the next higher bit position where they need to be added.
* **The Loop:** Keeps adding the running carry (`b`) to the running sum (`a`) until there are no remaining carry bits (`b == 0`).

---

### Textual Diagram

#### Adding `a = 5` and `b = 3` (Target: 8)

**Initial State:** `a = 5` (`0101`), `b = 3` (`0011`)

```text
Iteration 1:
   a       = 0 1 0 1  (5)
   b       = 0 0 1 1  (3)
   ---------------------
   sum     = 0 1 1 0  (a ^ b  = 6 -> addition without carry)
   carry   = 0 0 1 0  (a & b  = 1)
   b_next  = 0 1 0 0  (carry << 1 = 4)

   a = 6 (0110), b = 4 (0100)

Iteration 2:
   a       = 0 1 1 0  (6)
   b       = 0 1 0 0  (4)
   ---------------------
   sum     = 0 0 1 0  (a ^ b  = 2)
   carry   = 0 1 0 0  (a & b  = 4)
   b_next  = 1 0 0 0  (carry << 1 = 8)

   a = 2 (0010), b = 8 (1000)

Iteration 3:
   a       = 0 0 1 0  (2)
   b       = 1 0 0 0  (8)
   ---------------------
   sum     = 1 0 1 0  (a ^ b  = 10)
   carry   = 0 0 0 0  (a & b  = 0)
   b_next  = 0 0 0 0  (carry << 1 = 0)

   a = 10 (1010), b = 0 (0000)

Loop terminates because b == 0.
Return a = 8 (Note: bit representation signed result gives 8).

```

---

### Key Properties

* **Time Complexity:** $\mathcal{O}(1)$ — At most 32 iterations for 32-bit integers.
* **Space Complexity:** $\mathcal{O}(1)$ — Uses a constant amount of memory.
* **C++ Specific Note:** In standard C++, shifting negative integers using `<<` can lead to undefined behavior. If signed overflow causes issues in competitive programming platforms, `carry = (unsigned int)(a & b) << 1;` is used to prevent compiler warnings.
