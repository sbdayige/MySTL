#pragma once

#include <vector>
#include <mutex>
#include <list>
#include <unordered_map>

template <typename K, typename V>
class LRUCache
{
private:
    mutable std::mutex mtx_;
    using Item = std::pair<K, V>;
    std::list<Item> item_;
    std::unordered_map<K, typename std::list<Item>::iterator> map_;
    size_t cap_;

public:
    explicit LRUCache(size_t cap) : cap_(cap) {}

    size_t capacity() const
    {
        return cap_;
    }

    size_t size() const
    {
        std::lock_guard<std::mutex> lock_(mtx_);
        return item_.size();
    }

    void clear()
    {
        std::lock_guard<std::mutex> lock_(mtx_);
        map_.clear();
        item_.clear();
    }

    bool erase(const K &key)
    {
        std::lock_guard<std::mutex> lock_(mtx_);
        auto it = map_.find(key);
        if (it == map_.end())
            return false;
        item_.erase(it.second);
        map_.erase(it);
        return true;
    }

    void put(const K &key, const V &val)
    {
        std::lock_guard<std::mutex> lock_(mtx_);
        auto it = map_.find(key);
        if (it != map_.end())
        {
            it->second->second = val;
            item_.splice(item_.begin(), item_, it->second);
            return;
        }
        if (item_.size() == capacity())
        {
            auto tail = item_.end();
            tail--;
            map_.erase(tail->first);
            item_.pop_back();
        }
        item_.emplace_front(key, val);
        map_[key] = item_.begin();
    }

    bool get(const K &key, V &val)
    {
        std::lock_guard<std::mutex> lock_(mtx_);
        auto it = map_.find(key);
        if (it == map_.end())
            return false;
        item_.splice(item_.begin(), item_, it->second);
        val = it->second->second;
        return true;
    }
};