#pragma once
#include <string>

struct DatabaseConfig {
  std::string host;
  int         port;  
  std::string user;
  std::string password;
  std::string database;
};

inline DatabaseConfig MySQLConfig {
  "localhost",
  3306,
  "boss",
  "boss_password",
  "DB_EMPLOYEES"
};

inline DatabaseConfig PostgresConfig {
    "localhost",
    5432,
    "root",
    "root",
    "DB_EMPLOYEES"
};