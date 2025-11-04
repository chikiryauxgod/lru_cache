/*
  Idatabase.hpp
  date: 04.11.2025 
  author: Sememov Lev

*/


#pragma once
#include "Idatabase.hpp"
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <memory>

class MySQLDB : public IDatabase {
public:
    MySQLDB(const std::string & host,
                  const std::string & user,
                  const std::string & password,
                  const std::string & db,
                  const std::string & table = "data",
                  const std::string & column = "value");

    bool Connect() override;
    std::string GetValue(int id) override;

private:
    std::string host_, user_, password_, db_, table_, column_;
    sql::Driver* driver_;
    std::unique_ptr<sql::Connection> conn_;
};
