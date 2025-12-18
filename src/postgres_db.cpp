#include "postgres_db.hpp"

PostgresDB::PostgresDB(const DatabaseConfig& cfg)
    : DatabaseBase(cfg) {}

bool PostgresDB::Connect() {
  std::cout << "[Postgres] Simulating connection to "
            << cfg_.database << " at "
            << cfg_.host << ":" << cfg_.port
            << " as user " << cfg_.user << "\n";
  connected_ = true;
  return true;
}


// Imitation vaule

std::string PostgresDB::GetValue(int id) {
  if (!connected_) {
    std::cerr << "[Postgres] Not connected!\n";
    return {};
  }

  std::cout << "[Postgres] Simulating SELECT for id=" << id << "\n";

  return "fake_pg_value_" + std::to_string(id);
}
