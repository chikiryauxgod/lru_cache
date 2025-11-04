#include "database.hpp"

Database::Database(const std::string & host,
                   const std::string & user,
                   const std::string & password,
                   const std::string & db)
    : host_(host), user_(user), password_(password), db_(db), driver_(nullptr) {}

Database::~Database() {
    if (conn_) conn_->close();
}

bool Database::Connect() {
    try {
        driver_ = get_driver_instance();
        conn_.reset(driver_->connect(host_, user_, password_));
        conn_->setSchema(db_);
        std::cout << "[DB] Connected to : " << db_ << "\n";
        return true;
    } catch (sql::SQLException & e) {
        std::cerr << "[DB] Connection failed: " << e.what() << "\n";
        return false;
    }
}

// TODO: queries
std::string Database::GetValue(int id) {
    try {
        std::unique_ptr<sql::PreparedStatement> stmt(
            conn_->prepareStatement("SELECT full_name, phone, salary FROM employees"));
        stmt->setInt(1, id);

        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
        if (res->next())
            return res->getString("value");
    } catch (sql::SQLException & e) {
        std::cerr << "[DB] Query error: " << e.what() << "\n";
    }
    return {};
}
