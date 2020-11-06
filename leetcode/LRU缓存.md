    class LRUCache {
    public:
    LRUCache(int capacity) : cap(capacity) {} 
    
    int get(int key) {
        auto it = mp.find(key);
        if(it == mp.end())  return -1;
        
        auto it_ = it->second;
        pair<int, int> temp {it_->first, it_->second};

        //如果存在，先删除再添加到链表头部
        cache.erase(it_);
        cache.push_front(temp);
        mp[key] = cache.begin();

        return temp.second;
    }
    
    void put(int key, int value) {
        //查找是否已经存在
        auto it = mp.find(key);
        if(it != mp.end())
        {
            cache.erase(it->second);
            mp.erase(key);
        }
        
        //put
        pair<int, int> temp {key, value};
        cache.push_front(temp);
        mp.emplace(key, cache.begin());
        
        //缓存容量达到上线
        if(cache.size() > cap)
        {
            mp.erase(cache.back().first);
            cache.pop_back();
        }
    }

    private:
    int cap;
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>>::iterator> mp;  //value是list的迭代器
    };

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
