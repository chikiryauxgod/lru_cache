#include "postgres_db.hpp"

PostgresDB::PostgresDB(const std::string & host,
                       const std::string & user,
                       const std::string & password,
                       const std::string & db)
    : host_(host), user_(user), password_(password), db_(db), connected_(false) {}

bool PostgresDB::Connect() {
    std::cout << "[Postgres] Simulating connection to " << db_
              << " at " << host_ << " as user " << user_ << "\n";
    connected_ = true;
    return connected_;
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
