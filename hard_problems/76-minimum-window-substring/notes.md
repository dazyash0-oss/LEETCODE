This code solves **LeetCode 76: Minimum Window Substring** using the **Dynamic Sliding Window** pattern with a frequency hashtable.

---

## 1. Core Structural Patterns

### Pattern A: Two-Pointer Sliding Window (Expand & Shrink)

* **Expand (`endIndex`):** Move the right boundary forward to include characters until all target requirements are met (`targetCharsRemaining == 0`).
* **Shrink (`startIndex`):** Contract the left boundary from the left to remove unnecessary characters and find the minimum valid window size.

```
       [   Sliding Window   ]
  s = " A D O B E C O D E B A N C "
        ^               ^
   startIndex       endIndex

```

---

### Pattern B: Frequency Counter & Counter Variable

* **Map Tracking:** A hash map tracks required counts for target characters. Decrementing past `0` yields negative values, indicating extra/surplus characters inside the current window.
* **`targetCharsRemaining` Counter:** Tracks missing unique/total character counts needed to satisfy string `t`. Avoids re-checking the whole frequency map on every iteration ($O(1)$ validity check).

```
  Frequency Map State:

```

---

Target 'A':  0  -> Exact match in window
Target 'B': -1  -> 1 extra 'B' inside window (safe to pop)
Non-target: -2  -> Irrelevant characters (safe to pop)

```

```

---

### Pattern C: Eager Contraction Guard (`charCount == 0`)

* **What it does:** Shrinks the left side until `charCount[s[startIndex]] == 0`.
* **Why it works:** When a character's map count is negative, it means it is present in excess. The `while` loop pops excess or non-target characters until it reaches a critical target character whose loss would invalidate the window.

```
       Start Contracting
               |
  s = " A   A   B   C "  (Target: "ABC")
        ^   ^
      Excess 'A' (Count: -1) -> Pop and increment map count!

```

---

## 2. Textual Diagram & Execution Trace

Consider input: `s = "ADOBECODEBANC"`, `t = "ABC"`

### Initial Setup

* Initial Map: `{'A': 1, 'B': 1, 'C': 1}`
* `targetCharsRemaining = 3`
* `minWindow = [0, INT_MAX]`

---

### Step-by-Step State Flow

```
Expansion Phase (endIndex = 0 to 5):

endIndex = 0 ('A'): Match! charCount['A'] -> 0 | targetCharsRemaining = 2
endIndex = 1 ('D'): Non-target -> charCount['D'] = -1
endIndex = 2 ('O'): Non-target -> charCount['O'] = -1
endIndex = 3 ('B'): Match! charCount['B'] -> 0 | targetCharsRemaining = 1
endIndex = 4 ('E'): Non-target -> charCount['E'] = -1
endIndex = 5 ('C'): Match! charCount['C'] -> 0 | targetCharsRemaining = 0

```

---

Window Valid! Current Range: s[0..5] ("ADOBEC")

Shrinking Phase at endIndex = 5:
• startIndex = 0 ('A'): charCount['A'] is 0 -> Cannot shrink further!
• Record minWindow = [0, 5] (Length = 6, Substring: "ADOBEC")
• Break valid state: Pop 'A', charCount['A'] = 1, targetCharsRemaining = 1
• startIndex becomes 1

Stack / Window State:
Window: "DOBEC" (Missing 'A')
startIndex = 1, endIndex = 5

---

Resume Expansion Phase (endIndex = 6 to 10):

endIndex = 6 ('O') ... endIndex = 9 ('A')
endIndex = 10 ('N'):
• At endIndex = 9 ('A'): Match! targetCharsRemaining = 0

---

Window Valid! Current Range: s[1..10] ("DOBECODEBA")

Shrinking Phase at endIndex = 10:
• startIndex = 1 ('D'): Surplus -> Pop 'D', startIndex = 2
• startIndex = 2 ('O'): Surplus -> Pop 'O', startIndex = 3
• startIndex = 3 ('B'): Surplus -> Pop 'B', startIndex = 4
• startIndex = 4 ('E'): Surplus -> Pop 'E', startIndex = 5
• startIndex = 5 ('C'): charCount['C'] is 0 -> Cannot shrink further!

Record minWindow = [5, 10] (Length = 6, Substring: "CODEBA")
• Break valid state: Pop 'C', charCount['C'] = 1, targetCharsRemaining = 1
• startIndex becomes 6

---

Resume Expansion Phase & Final Shrink (endIndex = 12):

endIndex = 12 ('C'): Match! targetCharsRemaining = 0
Window Range: s[6..12] ("ODEBANC")

Shrinking Phase:
• Shrinks past 'O', 'D', 'E' until startIndex = 9 ('B')
• Valid Window Range: s[9..12] ("BANC")
• Length = 4 < Previous Min Length 6!

Update minWindow = [9, 12] ("BANC")

Final Result: "BANC"

```

```

---

## 3. Key Notes & Complexity

* **Time Complexity:** $O(\vert{}S\vert{} + \vert{}T\vert{})$ — Right pointer (`endIndex`) and left pointer (`startIndex`) each traverse string `s` at most once.
* **Space Complexity:** $O(\vert{}S\vert{} + \vert{}T\vert{})$ — For storing character counts in `unordered_map` (can be optimized to $O(1)$ using a fixed array of size 128 for ASCII).
* **Pattern Trigger:** Use **Dynamic Sliding Window** whenever you are asked to find the *shortest/longest contiguous substring* that satisfies a set of character count constraints.
