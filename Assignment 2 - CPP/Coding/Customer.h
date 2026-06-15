/****************************************
Assignment C++: 2
Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*****************************************/

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <ostream>
#include "ShoppingCart.h"

using namespace std;

class Customer {
protected:
    string name; // Customer's name
    ShoppingCart cart; // Customer's shopping cart (Composition)

public:
    // Constructors and Destructor:
    Customer(); // Added: Default constructor for framework requirements
    Customer(string name);
    virtual ~Customer();

    // Getters for Supplier and Menu functionality
    string get_name() const;
    const ShoppingCart& get_cart() const;
    ShoppingCart& get_cart_modifiable();

    // Methods:
    virtual bool add_to_cart(const Product &p, int quantity); // Adds a product to the cart
    virtual bool remove_from_cart(int id, int quantity); // Removes a product from the cart by ID
    virtual double checkout(); // Calculates the total to pay, empties the cart, and returns the total amount
    void print_cart() const; // Prints the customer's cart contents

    // Operator Overloads:
    friend ostream &operator<<(ostream &os, const Customer &c); // Prints the customer's details and cart contents
};


class BusinessCustomer : public Customer {
private:
    string company_name; // Company name
    double discount_rate; // Discount rate

public:
    // Constructors and Destructor:
    BusinessCustomer(); // Added: Default constructor for framework requirements
    BusinessCustomer(string name, string company_name, double discount_rate);
    virtual ~BusinessCustomer();

    // Methods:
    virtual double checkout() override; // Override: Calculates the total to pay including the business discount, empties the cart, and returns the amount

    // Operator Overloads:
    friend ostream &operator<<(ostream &os, const BusinessCustomer &bc); // Prints the customer's details including company name and discount rate
};

#endif // CUSTOMER_H