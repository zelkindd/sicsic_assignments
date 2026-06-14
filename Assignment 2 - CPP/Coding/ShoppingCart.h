/****************************************
Assignment C++: 1 Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*****************************************/

#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H

#include <vector>
#include <ostream>
#include "Product.h"

using namespace std;

class ShoppingCart {
protected:
	vector<Product> items; // List of products in the shopping cart.
	double total_price; // Total price of products in the cart.

public:
	// Constructors & Destructor:
	ShoppingCart(); // Default constructor initializing an empty cart.
	virtual ~ShoppingCart(); // Destructor to clean up resources.

	// Methods:
	bool add_Product(const Product &p); // Adds a product to the cart. And update the total price by (p.price * p.quantity)
	bool add_Product(const Product &p, int quantity); // Adds a product with a specific quantity. And update the total price by (p.price * quantity)
	bool remove_Product(const Product &p); // Removes a product from the cart.
	bool remove_Product(const Product &p, int quantity); // Removes a specific quantity of a product. update the total price
	const vector<Product> &Get_List() const; // Returns the list of products in the cart.
	void printcart() const; // Prints the shopping cart and total price.
	virtual double Get_total() const; // Returns the total price.

	// Operator Overloads:
	friend ostream &operator<<(ostream &os, const ShoppingCart &cart); // Prints cart details and total price.
	Product* operator[](int id); // Accesses a pointer to product by its ID. If there is none
};

#endif // SHOPPING_CART_H
