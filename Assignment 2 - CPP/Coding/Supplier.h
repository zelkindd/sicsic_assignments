/****************************************
Assignment C++: 2
Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*****************************************/

#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <string>
#include <vector>
#include "Product.h"
#include "ShoppingCart.h"
// Forward declaration of Customer since it's used in the methods
class Customer;

using namespace std;

// Supplier.h
class Supplier {
private:
    string name;      // Supplier's name.
    double counter=0;   // Total money made by customer purchases.
    vector<Product> inventory;

public:
    // Constructors:
    Supplier();       // ctor supplier.
    Supplier(string name); // Parameterized constructor.
    ~Supplier();      // dtor supplier.

    // Methods:
    bool remove_Product(const Product &p); // Removes a product from the inventory and will subtract its price from the counter.
    bool remove_Product(const Product &p, int quantity); // Removes a specific quantity of a product and will subtract its price from the counter.
    bool customer_purchases(Customer &c); // Updates stock and profit for a single product and adds its price to the counter.
    bool customer_purchases(const ShoppingCart &cart); // Updates stock and profit for multiple products and adds its total_price to the counter.
    bool change_price(int id, double new_price); // Changes the price of a product by ID.
    double get_total_profit() const; // Returns the total profit accumulated from customer purchases.

    // Operator Overloads:
    friend ostream &operator<<(ostream &os, const Supplier &supplier); // Prints supplier details and total profit.
};

#endif // SUPPLIER_H