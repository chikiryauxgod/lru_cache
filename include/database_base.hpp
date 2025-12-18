/*
  database_base.hpp
  date: 18.12.2025 
  author: Sememov Lev

*/

#pragma once
#include "Idatabase.hpp"
#include "config.hpp"

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <memory>

class DatabaseBase : public IDatabase {
public:
  explicit DatabaseBase(const DatabaseConfig& cfg)
      : cfg_(cfg), driver_(nullptr) {}

  virtual ~DatabaseBase() = default;

protected:
  DatabaseConfig cfg_;
  sql::Driver* driver_;
  std::unique_ptr<sql::Connection> conn_;
};


