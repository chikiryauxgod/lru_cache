/*
  postgres_db.hpp
  date: 04.11.2025
  author: Sememov Lev
*/

#pragma once
#include "Idatabase.hpp"
#include <iostream>
#include <string>

class PostgresDB : public IDatabase {
public:
    PostgresDB(const std::string & host,
               const std::string & user,
               const std::string & password,
               const std::string & db);

    bool Connect() override;
    std::string GetValue(int id) override;

private:
    std::string host_, user_, password_, db_;
    bool connected_;
};
