/****************************************
Assignment C++: 2
Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*****************************************/

#include "Supplier.h"
#include <iostream>

// Default constructor initializing empty values
Supplier::Supplier() : name(""), counter(0.0) {}

// Parameterized constructor initializing the supplier's name
Supplier::Supplier(string name) : name(name), counter(0.0) {}

// Destructor (Vector automatically handles memory clean-up for inventory)
Supplier::~Supplier() {}

// Removes a product completely from the inventory and subtracts its full value from the counter.
// Returns true if the product was successfully found and removed, otherwise returns false.
bool Supplier::remove_Product(const Product &p) {
    // Loop through the inventory vector
    for (int i = 0; i < inventory.size(); ++i) {
        // Compare the current product's ID with the given product's ID
        if (inventory[i] == p.get_id()) {
            // Subtract the total cost of this product stock from the counter
            counter -= inventory[i].get_price() * inventory[i].get_quantity();

            // Erase the product from the inventory vector
            inventory.erase(inventory.begin() + i);
            return true;
        }
    }
    return false; // Product not found
}

// Removes a specific quantity of a product from the inventory and updates the counter.
// If the quantity to remove matches or exceeds the current stock, the product is completely removed.
bool Supplier::remove_Product(const Product &p, int quantity) {
    // Validate that the quantity to remove is positive
    if (quantity <= 0) {
        return false;
    }

    // Search for the product in the inventory
    for (int i = 0; i < inventory.size(); ++i) {
        if (inventory[i] == p.get_id()) {
            // Check if the requested removal quantity meets or exceeds available stock
            if (quantity >= inventory[i].get_quantity()) {
                // Reuse the complete removal function to maintain consistency
                return remove_Product(p);
            } else {
                // Deduct the specified quantity from the product instance in inventory
                inventory[i] -= quantity;

                // Subtract the value of the removed items from the supplier counter
                counter -= inventory[i].get_price() * quantity;
                return true;
            }
        }
    }
    return false; // Product not found in inventory
}

