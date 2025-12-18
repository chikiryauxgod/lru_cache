#include <iostream>
#include <memory>
#include "mysql_db.hpp"
#include "postgres_db.hpp"
#include "lru_cache.hpp"
#include "allocator.hpp"


int main() {
  std::unique_ptr<IDatabase> db;

#ifdef USE_POSTGRES
  std::cout << "[CONFIG] Using PostgreSQL backend\n";
  db = std::make_unique<PostgresDB>(PostgresConfig);
#else
  std::cout << "[CONFIG] Using MySQL backend\n";
  db = std::make_unique<MySQLDB> (MySQLConfig);
#endif

  if (!db->Connect()) {
      std::cerr << "Failed to connect to DB\n";
      return 1;
  }

  TrackingAllocator<std::pair<const int, std::string>> alloc;
  LRUCache<int, std::string, TrackingAllocator<std::pair<const int, std::string>>> cache(3, alloc);

  for (int id = 1; id <= 3; ++id) {
      auto val = db->GetValue(id);
      cache.Put(id, val);
  }

  cache.Print();
}
