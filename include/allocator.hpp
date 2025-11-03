/*
  allocator.hpp
  date: 02.11.2025 
  author: Sememov Lev

*/

#pragma once
#include <iostream>
#include <new>

template <typename T> 
class TrackingAllocator {
public:
  using value_type = T;
  static inline size_t total_allocated = 0;

  TrackingAllocator() noexcept {}
  template<class U> TrackingAllocator(const TrackingAllocator<U> &) noexcept {}
  
  [[nodiscard]]T * Allocate(std::size_t n) {
    size_t bytes = n * sizeof(T);
    total_allocated += bytes;
    std::cout << "[Allocator]" << bytes << "bytes (total" << total_allocated << ")\n";
    return static_cast<T*>(::operator new(bytes));
  }

  void Deallocate(T* p, std::size_t n) noexcept {
    size_t bytes = n * sizeof(T);
    total_allocated -= bytes;
    std::cout << "[Allocator]" << bytes << "bytes (total" << total_allocated << ")\n";
    ::operator delete(p);
  }

  T * allocate(std::size_t n) {
    return Allocate(n);
  }

  void deallocate(T * p, std::size_t n) {
    return Deallocate(p, n);
  }
  
  template <class U>
  struct rebind { 
    using other = TrackingAllocator<U>; 
  };

  
};

template<class T, class U>
bool operator==(const TrackingAllocator<T> &, const TrackingAllocator<U> &) noexcept {
  return true;
}

template<class T, class U>
bool operator!=(const TrackingAllocator<T> &, const TrackingAllocator<U> &) noexcept {
  return false;
}

