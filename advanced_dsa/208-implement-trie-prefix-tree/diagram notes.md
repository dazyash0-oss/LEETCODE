### Analysis & Key Takeaways

Your **Trie (Prefix Tree)** implementation is clean, idiomatic, and optimal:

* **Time Complexity:**
* `insert(s)`: **$O(L)$**, where $L$ is the length of string $s$.
* `search(key)` & `startsWith(prefix)`: **$O(L)$**, where $L$ is the length of the query string.


* **Space Complexity:**
* **$O(N \times \Sigma)$**, where $N$ is the total number of nodes created across all words, and $\Sigma = 26$ is the alphabet size (lowercase English letters `'a'` through `'z'`).


* **Design Highlight:** Combining exact word lookup and prefix matching into a single unified `search()` helper function using an optional `prefix` parameter keeps the codebase concise and DRY (Don't Repeat Yourself).

---

### Class Design & Data Flow

#### High-Level Structural Layout

Below is a visual representation of the Trie structure after inserting `"cat"`, `"car"`, and `"do"`:

```
                            [ root ]
                           /        \
                    'c'  /            \  'd'
                       /                \
                 [ TrieNode ]        [ TrieNode ]
                    /                    |
             'a'  /                      | 'o'
                /                        |
          [ TrieNode ]              [ TrieNode ]
           /        \              (isWord = true)  --> "do"
    't'  /            \  'r'
       /                \
  [ TrieNode ]        [ TrieNode ]
(isWord = true)     (isWord = true)
   --> "cat"           --> "car"

```

#### TrieNode Internal Layout

```
                  +----------------------------------------+
                  |               TrieNode                 |
                  +----------------------------------------+
                  | bool isWord = false / true             |
                  | TrieNode* child[26]                    |
                  |  [0]: 'a' -> ptr / nullptr             |
                  |  [1]: 'b' -> ptr / nullptr             |
                  |  ...                                   |
                  |  [25]: 'z' -> ptr / nullptr            |
                  +----------------------------------------+

```

---

### Operations Breakdown

#### 1. `insert(string s)` Flow

```
Start at root node (p = root)
  │
  ├── Loop through each character 'a' in string 's':
  │    ├── Calculate child index: i = a - 'a'
  │    ├── If p->child[i] is nullptr:
  │    │    └── Allocate new TrieNode: p->child[i] = new TrieNode()
  │    └── Advance pointer: p = p->child[i]
  │
  └── Set word termination flag: p->isWord = true

```

#### 2. `search(string key, bool prefix = false)` Flow

```
Start at root node (p = root)
  │
  ├── Loop through each character 'a' in 'key':
  │    ├── Calculate child index: i = a - 'a'
  │    ├── If p->child[i] is nullptr ──> Return false (Character path does not exist)
  │    └── Advance pointer: p = p->child[i]
  │
  └── End of string reached:
       ├── If prefix == true  ──> Return true (Path exists; valid prefix)
       └── If prefix == false ──> Return p->isWord (Valid complete word?)

```

#### 3. `startsWith(string prefix)` Flow

```
Delegates directly to search:
  └── Return search(prefix, true)

```

---

### Technical Highlights & Modern C++ Improvements

1. **Memory Management (Destructor):**
* **Observation:** The class uses raw `new` pointers (`new TrieNode()`) without a class destructor (`~Trie()`). This leads to memory leaks when a `Trie` object goes out of scope or is deleted.
* **Fix:** Add a recursive destructor or use `std::unique_ptr<TrieNode>` to handle memory deallocation automatically:
```cpp
~TrieNode() {
    for (auto childPtr : child) {
        delete childPtr;
    }
}

```




2. **Character Set Constraint:**
* Index calculation `i = a - 'a'` assumes inputs strictly consist of lower-case English characters (`'a'` to `'z'`). If uppercase, digits, or special characters are passed, this causes out-of-bounds array access.
