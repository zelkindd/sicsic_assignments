/****************************************
Assignment C++: 2
Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*****************************************/

#include "Customer.h"
#include "ShoppingCart.h"
#include <iostream>

using namespace std;

// ==========================================
// Customer Class
// ==========================================

// Default constructor initializing empty name
Customer::Customer() : name("") {}
// Parameterized constructor initializing the customer's name
Customer::Customer(string name) : name(name) {}
// Virtual destructor
Customer::~Customer() {}


// Returns the customer's name
string Customer::get_name() const {
    return name;
}
// Returns a constant read-only reference to the shopping cart
const ShoppingCart& Customer::get_cart() const {
    return cart;
}
// Returns a modifiable reference to the shopping cart
ShoppingCart& Customer::get_cart_modifiable() {
    return cart;
}

// Adds a specific quantity of a product to the customer's shopping cart.
// Returns true if the product was successfully added, false if the quantity is invalid.
bool Customer::add_to_cart(const Product &p, int quantity) {
    // Validate that the quantity to add is a positive number
    if (quantity <= 0) {
        return false;
    }
    // Use the existing ShoppingCart method to add the product with its specific quantity
    // This automatically updates the total price inside the cart object.
    return cart.add_Product(p, quantity);
}

// Removes a specific quantity of a product from the shopping cart by its ID.
// Returns true if the operation succeeded, false if the quantity is invalid or product not found.
bool Customer::remove_from_cart(int id, int quantity) {
    // Validate that the quantity to remove is a positive number
    if (quantity <= 0) {
        return false;
    }
    // Use ShoppingCart's operator[] to find the pointer to the actual product in the cart
    Product* existing_product = cart[id];

    // If the product is not found in the cart, we cannot remove it
    if (existing_product == nullptr) {
        return false;
    }
    // Call the existing removal function from the ShoppingCart class using the real product instance
    // This updates the internal items vector and modifies the cart's total price.
    return cart.remove_Product(*existing_product, quantity);
}

// Calculates the total to pay, empties the cart, and returns the total amount.
double Customer::checkout() {
    // Get the current total price of the items in the shopping cart
    double total_amount = cart.Get_total();

    // Reset the shopping cart by assigning a newly constructed empty ShoppingCart
    cart = ShoppingCart();

    // Return the calculated total amount before the cart was emptied
    return total_amount;
}

// Prints the contents of the customer's shopping cart.
void Customer::print_cart() const {
    // Call the existing print function from the ShoppingCart
    cart.printcart();
}

// Friend operator to format and print the customer's details and cart contents
ostream &operator<<(ostream &os, const Customer &c) {
    os << "Customer Name: " << c.name << endl;
    os << c.cart; // Reuse the ShoppingCart insertion operator<<
    return os;
}

// ==========================================
// BusinessCustomer Class Implementation
// ==========================================

// Default constructor initializing base class and business specific fields
BusinessCustomer::BusinessCustomer() : Customer(), company_name(""), discount_rate(0.0) {}

// Parameterized constructor updating the base class and specific fields
BusinessCustomer::BusinessCustomer(string name, string company_name, double discount_rate)
    : Customer(name), company_name(company_name), discount_rate(discount_rate) {}

// Virtual destructor
BusinessCustomer::~BusinessCustomer() {}

// Calculates the total to pay including the business discount, empties the cart, and returns the amount
double BusinessCustomer::checkout() {
    // Get the base total price from the shopping cart
    double original_total = cart.Get_total();

    // Apply the discount rate (e.g., 0.1 means a 10% discount, so they pay 90%)
    double discounted_total = original_total * (1.0 - discount_rate);

    // Empty the cart by assigning a new empty ShoppingCart object
    cart = ShoppingCart();

    // Return the final discounted total
    return discounted_total;
}

// Friend operator to print the business customer's details including company name and discount rate
ostream &operator<<(ostream &os, const BusinessCustomer &bc) {
    os << "Customer Name: " << bc.name
       << ", Company Name: " << bc.company_name
       << ", Discount Rate: " << bc.discount_rate << endl;
    os << bc.cart; // Reuse the ShoppingCart insertion operator<<
    return os;
}