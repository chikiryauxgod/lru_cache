#include "mysql_db.hpp"


MySQLDB::MySQLDB(const std::string & host,
                             const std::string & user,
                             const std::string & password,
                             const std::string & db,
                             const std::string & table,
                             const std::string & column)
    : host_(host), user_(user), password_(password), db_(db),
      table_(table), column_(column), driver_(nullptr) {}

bool MySQLDB::Connect() {
    try {
        driver_ = get_driver_instance();
        conn_.reset(driver_->connect(host_, user_, password_));
        conn_->setSchema(db_);
        std::cout << "[MySQL] Connected to " << db_ << "\n";
        std::unique_ptr<sql::Statement> stmt(conn_->createStatement());
        stmt->execute(
            "CREATE TABLE IF NOT EXISTS " + table_ + " ("
            "id INT PRIMARY KEY, " + column_ + " VARCHAR(255) NOT NULL)");

        return true;
    } catch (sql::SQLException & e) {
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
