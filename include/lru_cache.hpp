/*
  allocator.hpp
  date: 03.11.2025 
  author: Sememov Lev

*/

#pragma once
#include <list>
#include <unordered_map>
#include <iostream>
#include "allocator.hpp"

template<typename Key, typename Value, typename Allocator = std::allocator<std::pair<const Key, Value>>>
class LRUCache {
public:
    explicit LRUCache(size_t capacity, const Allocator & allocator = Allocator());

    bool Contains(const Key & key) const;
    Value * Get(const Key & key);
    void Put(const Key & key, const Value & value);
    void Print() const;

private:
    using ListAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<std::pair<Key, Value>>;
    using ListType = std::list<std::pair<Key, Value>, ListAllocator>;

    using MapValueType = std::pair<const Key, typename ListType::iterator>;
    using MapAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<MapValueType>;

    size_t capacity_;
    ListType order_;
    std::unordered_map<Key, typename ListType::iterator, std::hash<Key>, std::equal_to<Key>, MapAllocator> map_;
};


