/****************************************
Assignment C++: 1 Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*****************************************/

#include "ShoppingCart.h"
#include <iostream>

ShoppingCart::ShoppingCart() : total_price(0.0) {}

ShoppingCart::~ShoppingCart() {
    // delete the items ??
}

// Adds a product to the cart. If it exists, increments its quantity.
bool ShoppingCart::add_Product(const Product &p) {
    // Search for the product in the cart using the operator[]
    Product* existing = operator[](p.get_id());

    if (existing != nullptr) {
        // Product exists, update its quantity using Product's operator+=
        *existing += p.get_quantity();
    } else {
        // Product does not exist, add it as a new item to the vector
        items.push_back(p);
    }

    // Update the total price of the cart by (price * quantity)
    total_price += p.get_price() * p.get_quantity();
    return true;
}


// Adds a product with a specific quantity to the cart.
bool ShoppingCart::add_Product(const Product &p, int quantity) {
    // Validation to ensure the quantity provided is positive
    if (quantity <= 0) {
        return false;
    }

    // Search for the product in the cart using the operator[]
    Product* existing = operator[](p.get_id());

    if (existing != nullptr) {
        // Product exists, add the specified quantity to it
        *existing += quantity;
    } else {
        // Product does not exist, create a limited quantity copy and add it
        Product new_product(p, quantity);
        items.push_back(new_product);
    }

    // Update the total price by multiplying the product's price by the new quantity
    total_price += p.get_price() * quantity;
    return true;
}

// Removes a product completely from the shopping cart.
// Updates the total price by deducting the full value of this product.
bool ShoppingCart::remove_Product(const Product &p) {
    // Loop through the items vector
    for (int i = 0; i < items.size(); ++i) {
        // Check if the current product matches the given product ID
        if (items[i] == p.get_id()) {
            // Deduct the product's total cost from the cart's total price
            total_price -= items[i].get_price() * items[i].get_quantity();

            // Remove the item from the vector
            items.erase(items.begin() + i);
            return true; // Return true indicating successful removal
        }
    }
    return false; // Return false if the product was not found
}

// Removes a specific quantity of a product from the shopping cart.
// Updates the total price of the cart accordingly.
bool ShoppingCart::remove_Product(const Product &p, int quantity) {
    // Validate that the quantity to remove is positive
    if (quantity <= 0) {
        return false;
    }

    // Find the product in the cart
    Product* existing = operator[](p.get_id());
    if (existing == nullptr) {
        return false; // Product not found in the cart
    }

    // If requested quantity covers or exceeds existing stock, remove the product entirely
    if (quantity >= existing->get_quantity()) {
        return remove_Product(p); // Reuse previous remove function
    } else {
        // Deduct the specific quantity from the product instance
        *existing -= quantity;

        // Update the shopping cart total price
        total_price -= existing->get_price() * quantity;
        return true;
    }
}

// Returns a constant reference to the list of products in the cart.
const vector<Product>& ShoppingCart::Get_List() const {
    return items; // Return the internal vector of products
}

// Prints the shopping cart contents and the total price.
// Reuses the stream insertion operator<<
void ShoppingCart::printcart() const {
    cout << *this;
}

// Returns the total price of all products currently in the shopping cart.
double ShoppingCart::Get_total() const {
    return total_price; // Return the accumulated total price
}

// Friend operator to format and print the entire shopping cart contents
ostream &operator<<(ostream &os, const ShoppingCart &cart) {
    // Exact header from the output file
    os << "--- Shopping Cart Contents ---" << endl;

    // Loop through the cart items
    for (int i = 0; i < cart.items.size(); ++i) {
        // Print each individual product using operator<<
        os << cart.items[i] << endl;
    }

    // Print the final accumulated total price of the cart
    os << "Total Price: " << cart.total_price << endl;

    return os; // Return the output stream to allow operator chaining
}

// Accesses a pointer to a product in the cart by its ID.
// Returns a pointer to the product if found, otherwise returns nullptr.
Product* ShoppingCart::operator[](int id) {
    // Loop through the items vector
    for (int i = 0; i < items.size(); ++i) {
        // Compare the current product's ID with the given ID
        if (items[i] == id) {
            return &items[i]; // Return the memory address of the found product
        }
    }
    return nullptr; // Return nullptr if the product with the given ID does not exist
}