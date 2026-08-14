<h2><a href="https://leetcode.com/problems/task-scheduler">Task Scheduler</a></h2> <img src='https://img.shields.io/badge/Difficulty-Medium-orange' alt='Difficulty: Medium' /><hr><p>You are given an array of CPU <code>tasks</code>, each labeled with a letter from A to Z, and a number <code>n</code>. Each CPU interval can be idle or allow the completion of one task. Tasks can be completed in any order, but there&#39;s a constraint: there has to be a gap of <strong>at least</strong> <code>n</code> intervals between two tasks with the same label.</p>

<p>Return the <strong>minimum</strong> number of CPU intervals required to complete all tasks.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<div class="example-block" style="
    border-color: var(--border-tertiary);
    border-left-width: 2px;
    color: var(--text-secondary);
    font-size: .875rem;
    margin-bottom: 1rem;
    margin-top: 1rem;
    overflow: visible;
    padding-left: 1rem;
">
<p><strong>Input:</strong> <span class="example-io" style="
    font-family: Menlo,sans-serif;
    font-size: 0.85rem;
">tasks = [&quot;A&quot;,&quot;A&quot;,&quot;A&quot;,&quot;B&quot;,&quot;B&quot;,&quot;B&quot;], n = 2</span></p>

<p><strong>Output:</strong> <span class="example-io" style="
font-family: Menlo,sans-serif;
font-size: 0.85rem;
">8</span></p>

<p><strong>Explanation:</strong> A possible sequence is: A -&gt; B -&gt; idle -&gt; A -&gt; B -&gt; idle -&gt; A -&gt; B.</p>

<p>After completing task A, you must wait two intervals before doing A again. The same applies to task B. In the 3<sup>rd</sup> interval, neither A nor B can be done, so you idle. By the 4<sup>th</sup> interval, you can do A again as 2 intervals have passed.</p>
</div>

<p><strong class="example">Example 2:</strong></p>

<div class="example-block" style="
    border-color: var(--border-tertiary);
    border-left-width: 2px;
    color: var(--text-secondary);
    font-size: .875rem;
    margin-bottom: 1rem;
    margin-top: 1rem;
    overflow: visible;
    padding-left: 1rem;
">
<p><strong>Input:</strong> <span class="example-io" style="
    font-family: Menlo,sans-serif;
    font-size: 0.85rem;
">tasks = [&quot;A&quot;,&quot;C&quot;,&quot;A&quot;,&quot;B&quot;,&quot;D&quot;,&quot;B&quot;], n = 1</span></p>

<p><strong>Output:</strong> <span class="example-io" style="
    font-family: Menlo,sans-serif;
    font-size: 0.85rem;
">6</span></p>

<p><strong>Explanation:</strong> A possible sequence is: A -&gt; B -&gt; C -&gt; D -&gt; A -&gt; B.</p>

<p>With a cooling interval of 1, you can repeat a task after just one other task.</p>
</div>

<p><strong class="example">Example 3:</strong></p>

<div class="example-block" style="
    border-color: var(--border-tertiary);
    border-left-width: 2px;
    color: var(--text-secondary);
    font-size: .875rem;
    margin-bottom: 1rem;
    margin-top: 1rem;
    overflow: visible;
    padding-left: 1rem;
">
<p><strong>Input:</strong> <span class="example-io" style="
    font-family: Menlo,sans-serif;
    font-size: 0.85rem;
">tasks = [&quot;A&quot;,&quot;A&quot;,&quot;A&quot;, &quot;B&quot;,&quot;B&quot;,&quot;B&quot;], n = 3</span></p>

<p><strong>Output:</strong> <span class="example-io" style="
    font-family: Menlo,sans-serif;
    font-size: 0.85rem;
">10</span></p>

<p><strong>Explanation:</strong> A possible sequence is: A -&gt; B -&gt; idle -&gt; idle -&gt; A -&gt; B -&gt; idle -&gt; idle -&gt; A -&gt; B.</p>

<p>There are only two types of tasks, A and B, which need to be separated by 3 intervals. This leads to idling twice between repetitions of these tasks.</p>
</div>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= tasks.length &lt;= 10<sup>4</sup></code></li>
	<li><code>tasks[i]</code> is an uppercase English letter.</li>
	<li><code>0 &lt;= n &lt;= 100</code></li>
</ul>

---
---

## **Key Concept: Framing the Core Bottleneck**

The entire logic relies on the **Greedy Choice Principle**:

> The overall time to execute all tasks is dictated by the task that appears the **most frequently**.

Instead of manually simulating the CPU execution using a Queue or Max-Heap, this solution calculates the minimum possible intervals using a visual **bucket/grid arrangement**.

---

## **How the Math Works**

1. **Find the Maximum Frequency (`maxfreq`)**:
Let’s say the most frequent task appears `maxfreq` times.
2. **Create Idle Frame Blocks**:
To prevent same tasks from violating the cooling distance `n`, we arrange the most frequent task into `maxfreq - 1` groups. Each group needs a slot of size `n + 1` (1 spot for the task itself + `n` cooling/idle spots).
3. **Handle Ties (`cm`)**:
`cm` (count of maximum frequency tasks) represents how many tasks tie for the highest frequency. These tie tasks will fill the final row after the main groups.

### **Formula**

$$\text{Min Slots Required} = (\text{maxfreq} - 1) \times (n + 1) + \text{cm}$$

---

## **Visual Example**

Suppose `tasks = ["A","A","A","B","B","B"]`, and `n = 2`.

* `maxfreq = 3` (Task A and B both appear 3 times)
* `cm = 2` (Both A and B have frequency 3)

### **Grid Layout**

* **Frame Size:** `maxfreq - 1 = 2` full blocks.
* **Block Width:** `n + 1 = 3` slots per row.

| Block Row | Slot 1 | Slot 2 | Slot 3 |
| --- | --- | --- | --- |
| **Row 1** | **A** | **B** | `idle` |
| **Row 2** | **A** | **B** | `idle` |
| **Row 3 (Final)** | **A** | **B** | *(Done)* |

**Calculation:**

$$\text{Formula Result} = (3 - 1) \times (2 + 1) + 2 = 8 \text{ units of time}$$

---

## **Why `max(tasks.size(), ...)`?**

What if there are so many unique tasks that they completely fill up all the idle slots and spill over?

* **Case 1 (Idle Slots Remain):** The formula calculation is greater than `tasks.size()`. The answer is the formula result.
* **Case 2 (No Idle Slots Needed):** There are enough low-frequency tasks to fill all gaps naturally without inserting any idle units. The CPU never sits idle, so total time is simply `tasks.size()`.

Taking `max((int)tasks.size(), formula_result)` safely handles both scenarios without needing extra condition checks.

---

## **Complexity Analysis**

* **Time Complexity:** $\mathcal{O}(N)$ where $N$ is the number of tasks (to count frequencies). Scanning the fixed `freq` array of size 26 takes $\mathcal{O}(1)$ time.
* **Space Complexity:** $\mathcal{O}(1)$ because the frequency map size is fixed at 26 (constant memory).
