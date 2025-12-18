/*
  postgres_db.hpp
  date: 04.11.2025
  author: Sememov Lev
*/

#pragma once
#include "database_base.hpp"
#include <iostream>
#include <string>

class PostgresDB : public DatabaseBase {
public:
  explicit PostgresDB(const DatabaseConfig& cfg);

  bool Connect() override;
  std::string GetValue(int id) override;

private:
    std::string host_, user_, password_, db_;
    bool connected_;
};
