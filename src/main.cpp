#include "allocator.hpp"
#include "lru_cache.hpp"
#include "database.hpp"
#include <iostream>

int main() {
    Database db("localhost", "boss", "boss_password", "DB_EMPLOYEES");

    if (!db.Connect())
        return 1;

    using Alloc = TrackingAllocator<std::pair<const int, std::string>>;
    LRUCache<int, std::string, Alloc> cache(2);

    auto fetch = [&](int id) -> std::string {
        if (auto val = cache.Get(id)) {
            std::cout << "[CACHE HIT] " << id << " -> " << *val << "\n";
            return *val;
        }
        std::cout << "[CACHE MISS] Fetching from DB...\n";
        auto value = db.GetValue(id);
        cache.Put(id, value);
        return value;
    };

    fetch(1);
    fetch(2);
    fetch(1);
    fetch(3);
    fetch(2);
    fetch(3);

    return 0;
}
