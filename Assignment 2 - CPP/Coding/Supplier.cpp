/****************************************
Assignment C++: 2
Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*****************************************/

#include "Supplier.h"
#include "Customer.h"
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

                return true;
            }
        }
    }
    return false; // Product not found in inventory
}

// Updates stock and profit for a single customer's entire cart.
// Returns true if the purchase was successful, false if any item was out of stock.
bool Supplier::customer_purchases(Customer &c) {
    const vector<Product>& cart_items = c.get_cart().Get_List();

    // Step 1: Pre-validation (Check if supplier has enough stock for ALL items)
    for (int i = 0; i < cart_items.size(); ++i) {
        const Product& cart_prod = cart_items[i];
        bool found = false;

        for (int j = 0; j < inventory.size(); ++j) {
            if (inventory[j] == cart_prod.get_id()) {
                found = true;
                if (inventory[j].get_quantity() < cart_prod.get_quantity()) {
                    return false; // Not enough stock for this product
                }
                break;
            }
        }
        if (!found) {
            return false; // Product in cart does not exist in supplier's inventory
        }
    }



    // Step 2: Execution (Deduct from supplier inventory)
    for (int i = 0; i < cart_items.size(); ++i) {
        const Product& cart_prod = cart_items[i];
        for (int j = 0; j < inventory.size(); ++j) {
            if (inventory[j] == cart_prod.get_id()) {
                inventory[j] -= cart_prod.get_quantity(); // Deduct the quantity
                break;
            }
        }
    }

    // Step 3: Financial update (Call checkout to empty cart and get final payment amount)
    double payment = c.checkout();
    counter += payment;

    return true;
}

// Updates stock and profit based directly on a generic ShoppingCart object.
// Returns true if the purchase was successful, false if any item was out of stock.
bool Supplier::customer_purchases(const ShoppingCart &cart) {
    const vector<Product>& cart_items = cart.Get_List();

    // Step 1: Pre-validation (Check if supplier has enough stock for ALL items)
    for (int i = 0; i < cart_items.size(); ++i) {
        const Product& cart_prod = cart_items[i];
        bool found = false;

        for (int j = 0; j < inventory.size(); ++j) {
            if (inventory[j] == cart_prod.get_id()) {
                found = true;
                if (inventory[j].get_quantity() < cart_prod.get_quantity()) {
                    return false; // Not enough stock for this product
                }
                break;
            }
        }
        if (!found) {
            return false; // Product in cart does not exist in supplier's inventory
        }
    }

    // Step 2: Execution (Deduct from supplier inventory)
    for (int i = 0; i < cart_items.size(); ++i) {
        const Product& cart_prod = cart_items[i];
        for (int j = 0; j < inventory.size(); ++j) {
            if (inventory[j] == cart_prod.get_id()) {
                inventory[j] -= cart_prod.get_quantity(); // Deduct the quantity directly
                break;
            }
        }
    }

    // Step 3: Financial update (Add the cart's full total price to the supplier's profit counter)
    counter += cart.Get_total();

    return true;
}


// Changes the price of a product by ID.
bool Supplier::change_price(int id, double new_price) {
    // Validation to ensure the new price is not negative
    if (new_price < 0) {
        return false;
    }

    // Search for the product in the supplier's inventory
    for (int i = 0; i < inventory.size(); ++i) {
        if (inventory[i] == id) {
            // Update the price using the Product's setter function
            inventory[i].set_price(new_price);
            return true; // Successfully found and updated
        }
    }
    return false; // Product with the given ID was not found
}

// Returns the total profit accumulated from customer purchases.
double Supplier::get_total_profit() const {
    return counter;
}

// Friend operator to print supplier details and total profit.
ostream &operator<<(ostream &os, const Supplier &supplier) {
    os << "Supplier Details:" << endl;
    for (int i = 0; i < supplier.inventory.size(); ++i) {
        os << supplier.inventory[i] << endl;
    }
    os << "Total Profit: " << supplier.counter << endl;
    return os;
}

// Adds a brand new product to the inventory and debits its cost from the counter.
void Supplier::add_new_product(string name, double price, int quantity) {
    Product p(name, price, quantity);
    inventory.push_back(p);
    counter -= price * quantity;
}

// Adds quantity to an existing product and debits its cost from the counter.
// Returns true if the product was found, false otherwise.
bool Supplier::add_quantity(int id, int quantity) {
    for (int i = 0; i < inventory.size(); ++i) {
        if (inventory[i] == id) {
            double price = inventory[i].get_price();
            inventory[i] += quantity;
            counter -= price * quantity;
            return true;
        }
    }
    return false;
}

// Returns a const pointer to a product by ID, or nullptr if not found.
const Product* Supplier::find_product(int id) const {
    for (int i = 0; i < inventory.size(); ++i) {
        if (inventory[i] == id) {
            return &inventory[i];
        }
    }
    return nullptr;
}

