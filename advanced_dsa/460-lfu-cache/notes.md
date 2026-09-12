### Analysis & Key Takeaways

 **Least Frequently Used (LFU) Cache** implementation handles both frequency tracking and tie-breaking using a Least Recently Used (LRU) policy when frequencies match.

* **Time Complexity:**
* **$O(\log K)$** for `get` and `put` operations, where $K$ is the number of distinct frequencies present. This logarithmic factor is due to `std::map<int, list<vector<int>>> freq`, which performs $O(\log K)$ red-black tree operations on inserts and lookups (such as `freq[f]`, `freq.erase(f)`, and `freq.begin()`).
* *Optimal $O(1)$ alternative:* Tracking a `minFreq` variable alongside `std::unordered_map<int, list<...>> freq` achieves true $O(1)$ time complexity.


* **Space Complexity:** **$O(\text{capacity})$** to store the map entries, lists, and node data.

---

### Class Design & Data Flow

#### High-Level Data Structure Layout

```
                 UNORDERED MAP (Key Lookup)
               +---------+--------------------+
               |   Key   | List Node Iterator |
               +---------+--------------------+
               |  key_A  | ------> [Node A]   |
               |  key_B  | ------> [Node B]   |
               +---------+--------------------+
                                    |
                                    v
                 ORDERED MAP (Frequency Bucket Map)
      Freq Key          Doubly Linked List (std::list)
      +------+         +---------------------------------------+
      |  1   | ------> | [Node C] <---> [Node D]               |
      +------+         +---------------------------------------+
      |  2   | ------> | [Node A (MRU)] <---> [Node B (LRU)]   |
      +------+         +---------------------------------------+
      (freq.begin() = Min Freq)

```

* **`std::unordered_map<int, list<vector<int>>::iterator> mpp`**: Maps a key to its corresponding node location in the frequency bucket list for $O(1)$ access.
* **`std::map<int, list<vector<int>>> freq`**: Keyed by frequency counter (`f`). Each bucket holds a `std::list` of nodes `{key, value, f}`:
* **Front (Head):** Most Recently Used node for that frequency.
* **Back (Tail):** Least Recently Used (LRU) node for that frequency.
* **`freq.begin()`:** Always points to the smallest frequency bucket currently in existence (used for eviction).



---

### Operations Breakdown

#### 1. `makeMostFrequentlyUsed(key)` Helper Flow

```
1. Fetch vector from mpp[key]. Read current frequency 'f'.
2. Erase node iterator from freq[f] list.
3. If freq[f] becomes empty ──> erase frequency bucket 'f' from freq map.
4. Increment frequency: f = f + 1.
5. Push updated node {key, value, f} to front of freq[f] list.
6. Update iterator in lookup map: mpp[key] = freq[f].begin().

```

#### 2. `get(key)` Flow

```
1. Lookup 'key' in 'mpp' hash table.
   ├── Not Found ──> Return -1
   └── Found
       ├── Retrieve value from vector node
       ├── Call makeMostFrequentlyUsed(key)   [Promotes node to frequency f + 1]
       └── Return value

```

#### 3. `put(key, value)` Flow

```
1. If capacity == 0 ──> Return immediately.
   │
2. Lookup 'key' in 'mpp':
   ├── Key Exists (Update)
   │   ├── Update value in vector node: vec[1] = value
   │   └── Call makeMostFrequentlyUsed(key)
   │
   └── Key Does NOT Exist (Insert)
       ├── Check Capacity: Is size < cap?
       │   ├── YES (Space available):
       │   │   └── Increment size counter
       │   │
       │   └── NO (Capacity full -> Evict LFU + LRU tie-breaker):
       │       ├── Target lowest frequency list: freq.begin()->second
       │       ├── Extract tail key: key_to_delete = kaun_sa_list.back()[0]
       │       ├── Remove node from back: kaun_sa_list.pop_back()
       │       ├── If kaun_sa_list is empty ──> Erase freq.begin()->first
       │       └── Erase key from lookup map: mpp.erase(key_to_delete)
       │
       └── Insert new element with frequency 1:
           ├── freq[1].push_front({ key, value, 1 })
           └── Update lookup map: mpp[key] = freq[1].begin()

```

---

### Technical Observations & Optimization Notes

1. **Space Efficiency (`std::vector<int>` inside List):**
Storing `{key, value, counter}` inside a dynamic `std::vector<int>` causes dynamic heap memory allocation per node. Replacing `std::vector<int>` with a lightweight custom `struct Node { int key, val, freq; };` eliminates dynamic vector allocations and improves cache locality.
2. **$O(\log K)$ vs True $O(1)$ Optimization:**
Currently, using `std::map` gives $O(\log K)$ operational complexity. To achieve strict **$O(1)$**:
* Change `freq` from `std::map` to `std::unordered_map<int, list<Node>>`.
* Maintain an integer variable `minFreq`.
* When inserting a new key, set `minFreq = 1`.
* When promoting a node in `makeMostFrequentlyUsed`, if `freq[minFreq]` becomes empty after node removal, increment `minFreq++`.
