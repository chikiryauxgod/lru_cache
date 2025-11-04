/*
  Idatabase.hpp
  date: 03.11.2025 
  author: Sememov Lev

*/

#pragma once
#include <string>

class IDatabase {
public:
    virtual ~IDatabase() = default;

    virtual bool Connect() = 0;
    virtual std::string GetValue(int id) = 0;
};
