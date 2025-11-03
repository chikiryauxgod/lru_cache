/*
  lru_cache.cpp
  date: 03.11.2025
  author: Semenov Lev
*/

#include "lru_cache.hpp"

template<typename Key, typename Value, typename Allocator>
LRUCache<Key, Value, Allocator>::LRUCache(size_t capacity, const Allocator & allocator)
    : capacity_(capacity),
      order_(allocator),
      map_(0, std::hash<Key>(), std::equal_to<Key>(),
           typename std::allocator_traits<Allocator>::template rebind_alloc<
               std::pair<const Key, typename LRUCache<Key, Value, Allocator>::ListType::iterator>>(allocator))
{}

template<typename Key, typename Value, typename Allocator>
bool LRUCache<Key, Value, Allocator>::Contains(const Key & key) const {
    return map_.find(key) != map_.end();
}

template<typename Key, typename Value, typename Allocator>
Value * LRUCache<Key, Value, Allocator>::Get(const Key & key) {
    auto it = map_.find(key);
    if (it == map_.end())
        return nullptr;

    order_.splice(order_.begin(), order_, it->second);
    return &it->second->second;
}

template<typename Key, typename Value, typename Allocator>
void LRUCache<Key, Value, Allocator>::Put(const Key & key, const Value & value) {
    auto it = map_.find(key);

    if (it != map_.end()) {
        it->second->second = value;
        order_.splice(order_.begin(), order_, it->second);
        return;
    }

    if (order_.size() >= capacity_) {
        auto& last = order_.back();
        map_.erase(last.first);
        order_.pop_back();
    }

    order_.emplace_front(key, value);
    map_[key] = order_.begin();
}

template<typename Key, typename Value, typename Allocator>
void LRUCache<Key, Value, Allocator>::Print() const {
    std::cout << "[LRUCache] ";
    for (auto& [k, v] : order_)
        std::cout << k << ":" << v << " ";
    std::cout << "\n";
}

template class LRUCache<int, std::string, TrackingAllocator<std::pair<const int, std::string>>>;
template class LRUCache<int, std::string>;
