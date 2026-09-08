### Mentor Notes

#### 1. Core Concept & Strategy

* **Problem:** **Word Ladder** (Find the shortest transformation sequence length from `beginWord` to `endWord`).
* **Strategy:** **Bidirectional Breadth-First Search (BFS)**.
* Standard BFS expands outwards in one direction from `beginWord`.
* **Bidirectional BFS** runs two simultaneous searches: one forward from `beginWord` and one backward from `endWord`. They meet in the middle!
* **Why Bidirectional BFS is faster:** Standard BFS expands exponentially $O(b^d)$ where $b$ is the branching factor and $d$ is depth. Bidirectional BFS reduces this search tree footprint to $O(b^{d/2} + b^{d/2})$, which is exponentially faster in practice.



---

#### 2. Evaluating Your Code

Your implementation uses **Bidirectional BFS** and is already **exceptionally well-designed**!

##### What You Did Right

* **Set Swapping Optimization:** `if (beginSet.size() > endSet.size()) swap(beginSet, endSet);` ensures that you always expand the smaller frontier set, keeping the branching factor as small as possible.
* **Level Tracking:** Correctly tracks `steps` starting from `1`.

##### Minor Bug & Optimization

1. **Redundant `visited` tracking:** You are maintaining both `wordSet` and `visited`. Instead of managing two sets, simply **remove words from `wordSet**` as soon as they are inserted into `nextSet`. This eliminates the need for `visited` altogether!
2. **Missing `wordSet.erase(beginWord)`:** It's good practice to erase `beginWord` from `wordSet` upfront so you don't accidentally loop back to it.

---

### Text Diagram & Walkthrough

Let's trace `beginWord = "hit"`, `endWord = "cog"`, `wordList = ["hot","dot","dog","lot","log","cog"]`.

```
                    BIDIRECTIONAL BFS VISUALIZATION
                    --------------------------------

   beginSet = {"hit"}                           endSet = {"cog"}
   steps = 1                                    wordSet = {"hot","dot","dog","lot","log","cog"}
   
   =============================================================================
   
   ROUND 1:
   - Expand smaller set -> beginSet {"hit"}
   - Mutate "hit" -> finds "hot" in wordSet.
   - nextSet = {"hot"}. Remove "hot" from wordSet.
   - beginSet becomes {"hot"}.
   - steps = 2.
   
   -----------------------------------------------------------------------------
   
   ROUND 2:
   - Sizes: beginSet=1 ("hot"), endSet=1 ("cog"). No swap needed.
   - Expand beginSet {"hot"}
   - Mutate "hot" -> finds "dot" and "lot" in wordSet.
   - nextSet = {"dot", "lot"}. Remove them from wordSet.
   - beginSet becomes {"dot", "lot"}.
   - steps = 3.
   
   -----------------------------------------------------------------------------
   
   ROUND 3:
   - Sizes: beginSet=2 ("dot", "lot"), endSet=1 ("cog"). 
   - SWAP! Now beginSet = {"cog"}, endSet = {"dot", "lot"}.
   - Expand beginSet {"cog"}
   - Mutate "cog" -> finds "dog" and "log" in wordSet.
   - Is "dog" or "log" in endSet? No.
   - nextSet = {"dog", "log"}. Remove them from wordSet.
   - beginSet becomes {"dog", "log"}.
   - steps = 4.
   
   -----------------------------------------------------------------------------
   
   ROUND 4:
   - Sizes: beginSet=2 ("dog", "log"), endSet=2 ("dot", "lot").
   - Expand beginSet {"dog", "log"}:
   - Mutating "dog" -> generates "dot".
   - Check: Is "dot" in endSet {"dot", "lot"}? YES! 🎯 MEET IN THE MIDDLE!
   
   RETURN steps + 1 -> 4 + 1 = 5

```
---

### Complexity Analysis

* **Time Complexity:** $\mathcal{O}(N \times 26 \times L) = \mathcal{O}(N \times L)$, where $N$ is the length of `wordList` and $L$ is the length of each word. For each word, we check $L \times 26$ mutations.
* **Space Complexity:** $\mathcal{O}(N \times L)$ to store `wordSet`, `beginSet`, and `endSet`.
