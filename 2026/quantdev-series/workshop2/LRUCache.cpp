#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;


class LRUCache {
    using key = int;
    using value = int;

public:
    LRUCache(int capacity) {
        capacity_ = capacity;
    }

    int get(int k) {
        auto it = map.find(k);
        if (it == map.end()) {
            return -1;
        }

        value v = it->second->second;

        // move this entry to the front (most recently used)
        order.erase(it->second);
        order.push_front({k, v});
        map[k] = order.begin();

        return v;
    }

    void put(int k, int v) {
        auto it = map.find(k);

        if (it != map.end()) {
            // key already exists: remove old node, we'll re-insert at front
            order.erase(it->second);
            map.erase(it);
        } else if ((int)map.size() == capacity_) {
            // at capacity and inserting a new key: evict least recently used
            auto leastRecentlyUsed = order.back();
            order.pop_back();
            map.erase(leastRecentlyUsed.first);
        }

        // insert (or re-insert) at the front as most recently used
        order.push_front({k, v});
        map[k] = order.begin();
    }

private:
    int capacity_;

    list<pair<key, value>> order;
    unordered_map<key, list<pair<key, value>>::iterator> map;
};




int main() {
    LRUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);

    cout << cache.get(1) << endl;   // 1

    cache.put(3, 3);                // evicts key 2

    cout << cache.get(2) << endl;   // -1

    cache.put(4, 4);                // evicts key 1

    cout << cache.get(1) << endl;   // -1
    cout << cache.get(3) << endl;   // 3
    cout << cache.get(4) << endl;   // 4

    return 0;
}
