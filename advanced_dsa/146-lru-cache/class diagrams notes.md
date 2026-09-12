### Analysis & Key Takeaways

Your C++ implementation of the **Least Recently Used (LRU) Cache** is clean, idiomatically written, and optimal:

* **Time Complexity:** Both `get` and `put` run in **$O(1)$** average time.
* **Space Complexity:** **$O(\text{capacity})$** to store the map and doubly linked list entries.
* **Key Technique (`std::list::splice`):** You effectively use `lst.splice(lst.begin(), lst, it->second)` to move nodes to the front of the list in **$O(1)$** time without re-allocating memory or invalidating list iterators.

---

### Class Design & Data Flow

#### High-Level Data Structure Layout

```
                  UNORDERED MAP (Hash Table)
                +---------+------------------+
                |  Key    | Iterator Pointer |
                +---------+------------------+
                |  key_A  | -----> [Node A]  |
                |  key_B  | -----> [Node B]  |
                +---------+------------------+
                                  |
                                  v
                   DOUBLY LINKED LIST (std::list)
   [ HEAD ] <---> [ Node A ] <---> [ Node B ] <---> [ Node C ] <---> [ TAIL ]
  (Most Recently Used)                                       (Least Recently Used)

```

* **`std::list<pair<int, int>> lst`**: Maintains access order.
* **Front (Head):** Most Recently Used (MRU)
* **Back (Tail):** Least Recently Used (LRU)


* **`std::unordered_map<int, list<pair<int, int>>::iterator> cache`**: Map providing $O(1)$ lookup for key-to-node iterator mappings.

---

### Operations Breakdown

#### 1. `get(key)` Flow

```
1. Lookup 'key' in 'cache' hash map.
   ├── Not Found  ──> Return -1
   └── Found
       ├── Splice node 'it->second' from current location to lst.begin()   [O(1)]
       └── Return value 'it->second->second'

```

#### 2. `put(key, value)` Flow

```
1. Lookup 'key' in 'cache' hash map.
   ├── Found (Cache Hit)
   │   ├── Update value: it->second->second = value
   │   └── Move node to front via splice(lst.begin(), ...)                 [O(1)]
   │
   └── Not Found (Cache Miss)
       ├── Check Capacity: Is lst.size() >= cap?
       │   └── YES (Eviction needed):
       │       ├── Extract key from tail element: lst.back().first
       │       ├── Erase entry from map: cache.erase(lru.first)             [O(1)]
       │       └── Pop tail element: lst.pop_back()                        [O(1)]
       │
       ├── Insert new key-value pair at front: lst.emplace_front(key, value)
       └── Store new list iterator in map: cache[key] = lst.begin()

```

---

### Technical Highlights & Minor Edge Cases

* **`std::list::splice` Magic:** Standard list iterators remain valid when moved via `splice`. This guarantees the iterator stored inside `cache[key]` remains completely valid throughout relocations.
* **Capacity Cast:** `(int)lst.size() >= cap` safely avoids signed/unsigned comparison warnings between `std::size_t` and `int`.
* **Zero Capacity Edge Case:** If instantiated with `capacity = 0`, `lst.size() >= cap` triggers eviction on every `put`, but because `lst` is empty during the first eviction attempt, calling `lst.back()` would lead to undefined behavior. In practice, `capacity` is assumed to be $\ge 1$.
