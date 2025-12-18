/*
  Idatabase.hpp
  date: 04.11.2025 
  author: Sememov Lev

*/


#pragma once
#include "database_base.hpp"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>

class MySQLDB : public DatabaseBase {
public:
  explicit MySQLDB(const DatabaseConfig& cfg);

  bool Connect() override;
  std::string GetValue(int id) override;

private:
  std::string table_  = "data";
  std::string column_ = "value";
};

