/****************************************
Assignment C++: 1 Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*****************************************/

#include "Product.h"
#include <iostream>
#include <iomanip>

using namespace std;

int Product::next_id = 1;

// Default constructor initializing with reasonable default values
Product::Product() : id(0), name(""), price(0.0), quantity(0) {}

// Destructor
Product::~Product() {}

// copy constructor with the same ID
Product::Product(const Product &p) : id(p.id), name(p.name), price(p.price), quantity(p.quantity) {}

// copy constructor with a limited quantity
Product::Product(const Product &p, int q) : id(p.id), name(p.name), price(p.price), quantity(q) {}

// constructor with a new ID
Product::Product(string name, double price, int q) : id(next_id++), name(name), price(price), quantity(q) {}

double Product::get_price() const {
    return price;
}

unsigned int Product::get_quantity() const {
    return quantity;
}

int Product::get_id() const {
    return id;
}

ostream &operator<<(ostream &os, const Product &p) {
    os << "Product ID: " << p.id
       << ", Name: " << p.name
       << ", Price: " << p.price
       << ", Quantity: " << p.quantity;
    return os;
}

// checks equality of product IDs with another product
bool Product::operator==(const Product &other) const {
    return id == other.id;
}

// checks equality of product IDs with an integer ID
bool Product::operator==(int other_id) const {
    return id == other_id;
}

// checks inequality of product IDs with another product
bool Product::operator!=(const Product &other) const {
    return id != other.id;
}

// checks inequality of product IDs with an integer ID
bool Product::operator!=(int other_id) const {
    return id != other_id;
}

// increment the quantity of the product by 1 and return the updated product object
Product &Product::operator++() {
    ++quantity;
    return *this;
}

// add a specific quantity to the product and return the updated product object
Product &Product::operator+=(unsigned int q) {
    quantity += q;
    return *this;
}

// subtract a specific quantity from the product and return the updated product object
Product &Product::operator-=(unsigned int q) {  
    if (q > quantity) {
        quantity = 0; // Ensure quantity does not go negative
    } else {
        quantity -= q;
    }
    return *this;
}

void Product::set_price(double new_price) {
    if (new_price >= 0) {
        price = new_price;
    }
}

