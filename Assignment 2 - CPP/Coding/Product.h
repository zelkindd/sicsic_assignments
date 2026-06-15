/****************************************
Assignment C++: 1 Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*****************************************/
#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <ostream>
using namespace std;

class Product {
private:
	static int next_id; // Static member to generate unique IDs for products.
	int id; // Unique ID for each product.
	string name; // Name of the product.
	double price; // Price of the product.
	unsigned int quantity; // Quantity available of the product.
public:
	// Constructors & Destructor:
	Product(); // Default constructor
	Product(const Product &p); // Copy constructor with the same ID.
	Product(const Product &p, int q); // Copy constructor with a limited quantity.
	Product(string name, double price, int q = 1); // Constructor with a new ID.
	~Product(); // Destructor

	double get_price() const; // Returns the price of the product.
	unsigned int get_quantity() const; // Returns the quantity of the product.
	int get_id() const; // Returns the product ID.
	void set_price(double new_price); // Updates the product price.

	// Operator Overloads:
	friend ostream &operator<<(ostream &os, const Product &p); // Prints product details.
	bool operator==(const Product &other) const; // Compares product IDs.
	bool operator==(int other_id) const;
	bool operator!=(const Product &other) const; // Checks inequality of product IDs.
	bool operator!=(int other_id) const;
	Product &operator++(); // Increments the product quantity by 1.
	Product &operator+=(unsigned int q); // Adds a specific quantity to the product.
	Product &operator-=(unsigned int q); // Subtracts a specific quantity from the product.
};

#endif // PRODUCT_H


