#include "mysql_db.hpp"

MySQLDB::MySQLDB(const DatabaseConfig& cfg)
    : DatabaseBase(cfg) {}

bool MySQLDB::Connect() {
  try {
      const std::string uri =
          "tcp://" + cfg_.host + ":" + std::to_string(cfg_.port);

      driver_ = get_driver_instance();
      conn_.reset(driver_->connect(uri, cfg_.user, cfg_.password));
      conn_->setSchema(cfg_.database);

      std::cout << "[MySQL] Connected to " << cfg_.database << "\n";

      std::unique_ptr<sql::Statement> stmt(conn_->createStatement());
      stmt->execute(
          "CREATE TABLE IF NOT EXISTS " + table_ + " ("
          "id INT PRIMARY KEY, " + column_ + " VARCHAR(255) NOT NULL)");

      return true;
  } catch (const sql::SQLException& e) {
      std::cerr << "[MySQL] Connection failed: " << e.what() << "\n";
      return false;
  }
}

std::string MySQLDB::GetValue(int id) {
  try {
      auto query = "SELECT " + column_ + " FROM " + table_ + " WHERE id = ?";
      std::unique_ptr<sql::PreparedStatement> stmt(conn_->prepareStatement(query));
      stmt->setInt(1, id);

      std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
      if (res->next())
          return res->getString(column_);
  } catch (sql::SQLException & e) {
      std::cerr << "[MySQL] Query error: " << e.what() << "\n";
  }
  return {};
}
