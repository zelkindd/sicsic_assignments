/****************************************
Assignment C++: 1 Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*****************************************/

#include "ShoppingCart.h"
#include <iostream>

ShoppingCart::ShoppingCart() : total_price(0.0) {}

ShoppingCart::~ShoppingCart() {
    // delete the items ??
}

bool ShoppingCart::add_Product(const Product &p) {
    items.push_back(p);
    total_price += p.get_price() * p.get_quantity();
    return true;
}

bool ShoppingCart::add_Product(const Product &p, int quantity) {
    if (quantity <= 0) {
        return false; // Invalid quantity
    }
    Product new_product(p, quantity); // Create a new product with the specified quantity
    items.push_back(new_product);
    total_price += new_product.get_price() * quantity;
    return true;
}
