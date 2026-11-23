#include "ShoppingCart.hpp"

void ShoppingCart::add(const std::string& product) {
    ++quantities_[product];
}

unsigned ShoppingCart::quantity(const std::string& product) const {
    const auto item = quantities_.find(product);
    return item == quantities_.end() ? 0 : item->second;
}