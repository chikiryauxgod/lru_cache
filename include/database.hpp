/*
  database.hpp
  date: 03.11.2025 
  author: Sememov Lev

*/

#pragma once
#include <string>
#include <memory>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <iostream>

class Database {
public:
    Database(const std::string & host,
             const std::string & user,
             const std::string & password,
             const std::string & db);
    ~Database();

    bool Connect();
    std::string GetValue(int id);

private:
    std::string host_, user_, password_, db_;
    sql::Driver * driver_;
    std::unique_ptr<sql::Connection> conn_;
};
