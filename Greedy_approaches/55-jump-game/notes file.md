### Conceptual Flow Diagram

The **backward greedy strategy** shifts the target destination leftward whenever a valid jump path is confirmed.

```
[Start at last index]
        │
        ▼
   Set goal = N - 1
        │
        ▼
┌─────────────────────────┐
│ Loop i from N - 2 down  │
│ to index 0              │
└───────────┬─────────────┘
            │
            ▼
   Is i + nums[i] >= goal ?
      ├─── YES ───► Shift Goal Left: goal = i
      │
      └─── NO  ───► Keep current goal unchanged
            │
            ▼
┌─────────────────────────┐
│ End Loop                │
└───────────┬─────────────┘
            │
            ▼
   Is goal == 0 ?
      ├─── TRUE  ───► Return true  (Path exists from index 0)
      └─── FALSE ───► Return false (Trapped behind a gap/zero)

```

---

### Textual Diagram: Successful Execution (`[2, 3, 1, 1, 4]`)

```
Initial State:
Indices:   [ 0 ]   [ 1 ]   [ 2 ]   [ 3 ]   [ 4 ]
Values:    [ 2 ]   [ 3 ]   [ 1 ]   [ 1 ]   [ 4 ]
Goal:                                      ▲ (goal = 4)

---------------------------------------------------------------
Step 1: Inspect i = 3 (val = 1)
Reach: 3 + 1 = 4 >= 4 (Goal) ──► SUCCESS
Indices:   [ 0 ]   [ 1 ]   [ 2 ]   [ 3 ]   [ 4 ]
Values:    [ 2 ]   [ 3 ]   [ 1 ]   [ 1 ]   [ 4 ]
Goal Shift:                        ▲ (goal = 3)

---------------------------------------------------------------
Step 2: Inspect i = 2 (val = 1)
Reach: 2 + 1 = 3 >= 3 (Goal) ──► SUCCESS
Indices:   [ 0 ]   [ 1 ]   [ 2 ]   [ 3 ]   [ 4 ]
Values:    [ 2 ]   [ 3 ]   [ 1 ]   [ 1 ]   [ 4 ]
Goal Shift:                ▲ (goal = 2)

---------------------------------------------------------------
Step 3: Inspect i = 1 (val = 3)
Reach: 1 + 3 = 4 >= 2 (Goal) ──► SUCCESS
Indices:   [ 0 ]   [ 1 ]   [ 2 ]   [ 3 ]   [ 4 ]
Values:    [ 2 ]   [ 3 ]   [ 1 ]   [ 1 ]   [ 4 ]
Goal Shift:        ▲ (goal = 1)

---------------------------------------------------------------
Step 4: Inspect i = 0 (val = 2)
Reach: 0 + 2 = 2 >= 1 (Goal) ──► SUCCESS
Indices:   [ 0 ]   [ 1 ]   [ 2 ]   [ 3 ]   [ 4 ]
Values:    [ 2 ]   [ 3 ]   [ 1 ]   [ 1 ]   [ 4 ]
Goal Shift:▲ (goal = 0)

---------------------------------------------------------------
Result: goal == 0 (true) ──► Valid Path: 0 ──► 1 ──► 4 (or 0 ──► 1 ──► 2 ──► 3 ──► 4)

```

---

### Textual Diagram: Failed Execution (`[3, 2, 1, 0, 4]`)

```
Initial State:
Indices:   [ 0 ]   [ 1 ]   [ 2 ]   [ 3 ]   [ 4 ]
Values:    [ 3 ]   [ 2 ]   [ 1 ]   [ 0 ]   [ 4 ]
Goal:                                      ▲ (goal = 4)

---------------------------------------------------------------
Step 1: Inspect i = 3 (val = 0)
Reach: 3 + 0 = 3 < 4 (Goal) ──► FAIL
Goal Unchanged:                            ▲ (goal = 4)

---------------------------------------------------------------
Step 2: Inspect i = 2 (val = 1)
Reach: 2 + 1 = 3 < 4 (Goal) ──► FAIL
Goal Unchanged:                            ▲ (goal = 4)

---------------------------------------------------------------
Step 3: Inspect i = 1 (val = 2)
Reach: 1 + 2 = 3 < 4 (Goal) ──► FAIL
Goal Unchanged:                            ▲ (goal = 4)

---------------------------------------------------------------
Step 4: Inspect i = 0 (val = 3)
Reach: 0 + 3 = 3 < 4 (Goal) ──► FAIL
Goal Unchanged:                            ▲ (goal = 4)

---------------------------------------------------------------
Result: goal != 0 (false) ──► Goal blocked at index 4 (0 trapped behind index 3)

```
