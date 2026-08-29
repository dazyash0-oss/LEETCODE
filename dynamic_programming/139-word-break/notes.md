This code solves the **Word Break** problem using **Dynamic Programming** in **$O(n \cdot m \cdot k)$ time**, where $n$ is the length of string `s`, $m$ is the number of words in `wordDict`, and $k$ is the average word length.

---

## Code Analysis & How It Works

1. **`dp` Array**: `dp[i]` represents whether the prefix of `s` of length `i` (`s[0...i-1]`) can be segmented into dictionary words.
2. **Base Case (`dp[0] = true`)**: An empty string is always valid (base case for building valid words).
3. **Outer Loop (`i` from 1 to `s.size()`)**: Checks if the substring ending at index `i - 1` can be formed using dictionary words.
4. **Inner Loop (`for (const string& w : wordDict)`)**: Checks if word `w` can end at index `i - 1`:
* **`start >= 0`**: Ensures `w` isn't longer than the prefix `s[0...i-1]`.
* **`dp[start]`**: Checks if the remainder of the string preceding `w` is valid.
* **`s.substr(start, w.length()) == w`**: Confirms the substring actually matches `w`.


5. **Early Exit (`break`)**: Once `dp[i]` is set to `true`, it stops checking other words for position `i` and moves to `i + 1`.

---

## Hash Set Optimization (Alternative Pattern)

Instead of iterating over every word in `wordDict`, you can store words in an `unordered_set` and iterate over all possible partition split points $j < i$. This is often faster when `wordDict` is large or dictionary words are long.

```cpp
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;

        for (int i = 1; i <= s.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break; // Move to next i
                }
            }
        }
        return dp[s.size()];
    }
};

```

---

## Word Break Cheat Sheet

### 1. Key Concepts

* **DP Definition**: `dp[i] == true` $\iff$ `s[0...i-1]` is a valid combination of dictionary words.
* **Recurrence Relation**:

$$dp[i] = \bigvee_{w \in wordDict} (dp[i - \vert{}w\vert{}] \land s[i - \vert{}w\vert{} \dots i - 1] == w)$$


* **Trie / BFS Alternative**: Word Break can also be solved using a **Trie + Memoization/BFS**, which excels when there are high word-prefix overlaps.

### 2. Implementation Pattern Cheat Sheet

| Approach | Outer Loop | Inner Loop | Time Complexity | Best Used When... |
| --- | --- | --- | --- | --- |
| **Dictionary-Driven** (Your Code) | String length `i` | Dictionary words `w` | $O(n \cdot m \cdot k)$ | Small dictionary, long string |
| **Substring-Driven** (Hash Set) | End index `i` | Start index `j` | $O(n^2 \cdot k)$ | Large dictionary, short string |
| **Trie Optimization** | String index `i` | Trie traversal | $O(n^2 + \text{Trie Build})$ | Reusing dictionary across many queries |

### 3. Complexity Summary

* **Time Complexity**: $O(n \cdot m \cdot k)$ — Iterating through string length $n$, checking $m$ words, where `substr` comparison takes $O(k)$ time.
* **Space Complexity**: $O(n)$ — Dynamic programming array `dp` of size $n + 1$.
