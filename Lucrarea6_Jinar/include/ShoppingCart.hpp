#pragma once

#include <map>
#include <string>

class ShoppingCart {
public:
    void add(const std::string& product);
    unsigned quantity(const std::string& product) const;

private:
    std::map<std::string, unsigned> quantities_;
};