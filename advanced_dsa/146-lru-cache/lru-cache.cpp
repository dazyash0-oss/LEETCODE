
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
 class LRUCache {
private:
    int cap;
    list<pair<int, int>> lst;
    unordered_map<int, list<pair<int, int>>::iterator> cache;

public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        auto it = cache.find(key);
        if (it == cache.end()) return -1;

        lst.splice(lst.begin(), lst, it->second);

        return it->second->second;
    }

    void put(int key, int value) {
        auto it = cache.find(key);

        if (it != cache.end()) {
            it->second->second = value;
            lst.splice(lst.begin(), lst, it->second);
            return;
        }

        if ((int)lst.size() >= cap) {
            auto lru = lst.back();
            cache.erase(lru.first);
            lst.pop_back();
        }

        lst.emplace_front(key, value);
        cache[key] = lst.begin();
    }
};