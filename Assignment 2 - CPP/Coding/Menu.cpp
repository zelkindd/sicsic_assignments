/****************************************
Assignment C++: 2
Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*****************************************/

#include "Menu.h"
#include <iostream>
#include <string>

using namespace std;

// Default constructor: creates a default customer
Menu::Menu() : customer(new Customer("")) {}

// Destructor: frees the dynamically allocated customer
Menu::~Menu() {
    delete customer;
}

// Prints and handles the main menu loop
void Menu::mainMenu() {
    int choice;
    while (true) {
        cout << "\nMain Menu:" << endl;
        cout << "1. Store Menu" << endl;
        cout << "2. Shopping Cart Menu" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                storeMenu();
                break;
            case 2:
                cartMenu();
                break;
            case 3:
                cout << "Goodbye!" << endl;
                return;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }
}

// Prints and handles the supplier (store) menu loop
void Menu::storeMenu() {
    int choice;
    while (true) {
        cout << "\nStore Menu:" << endl;
        cout << "1. Print store" << endl;
        cout << "2. Add quantity to existing product or add new product" << endl;
        cout << "3. Change existing product price" << endl;
        cout << "4. Remove product from the store" << endl;
        cout << "5. View total profit" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        int id;
        string name;
        double price;
        int qty;

        switch (choice) {
            case 1:
                // Print all products in the supplier inventory
                cout << supplier;
                break;

            case 2:
                // Add quantity to existing product, or add a brand new product
                cout << supplier;
                cout << "Enter product ID: ";
                cin >> id;
                if (supplier.find_product(id) != nullptr) {
                    // Product exists — add quantity to it
                    cout << "Product found: " << *supplier.find_product(id) << endl;
                    cout << "Enter quantity to add: ";
                    cin >> qty;
                    supplier.add_quantity(id, qty);
                    cout << "Quantity updated." << endl;
                } else {
                    // Product not found — add a new one
                    cout << "Product not found." << endl;
                    cout << "Adding new product." << endl;
                    cout << "Enter product name: ";
                    cin >> name;
                    cout << "Enter product price: ";
                    cin >> price;
                    cout << "Enter quantity: ";
                    cin >> qty;
                    supplier.add_new_product(name, price, qty);
                    cout << "Product added." << endl;
                }
                break;

            case 3:
                // Change the price of an existing product
                cout << supplier;
                cout << "Enter product ID: ";
                cin >> id;
                if (supplier.find_product(id) != nullptr) {
                    cout << "Product found: " << *supplier.find_product(id) << endl;
                    cout << "Enter new price: ";
                    cin >> price;
                    supplier.change_price(id, price);
                    cout << "Price updated successfully." << endl;
                } else {
                    cout << "Product not found." << endl;
                }
                break;

            case 4:
                // Remove a product from the inventory
                cout << supplier;
                cout << "Enter product ID: ";
                cin >> id;
                if (supplier.find_product(id) != nullptr) {
                    supplier.remove_Product(*supplier.find_product(id));
                    cout << "Product removed." << endl;
                } else {
                    cout << "Product not found." << endl;
                }
                break;

            case 5:
                // Display total profit
                cout << "Total profit: " << supplier.get_total_profit() << endl;
                break;

            case 6:
                cout << "Exiting supplier menu." << endl;
                return;

            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }
}

// Prints and handles the customer (shopping cart) menu loop
void Menu::cartMenu() {
    int choice;
    while (true) {
        cout << "\nShopping Cart Menu:" << endl;
        cout << "1. Print items in store" << endl;
        cout << "2. Add product to cart from store" << endl;
        cout << "3. Remove product" << endl;
        cout << "4. View cart" << endl;
        cout << "5. Check out" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        int id, qty;
        char confirm;

        switch (choice) {
            case 1:
                // Print all available products in the store
                cout << "Items in the store:" << endl;
                cout << supplier;
                break;

            case 2: {
                // Add a product from the store to the customer's cart
                cout << "Items in the store:" << endl;
                cout << supplier;
                cout << "Enter product ID to add: ";
                cin >> id;

                const Product* p = supplier.find_product(id);
                if (p == nullptr) {
                    cout << "Product not found." << endl;
                    break;
                }

                cout << "Enter quantity: ";
                cin >> qty;

                int supplier_stock = p->get_quantity();
                // Check if there is enough stock in the supplier
                if (qty > supplier_stock) {
                    cout << "Not enough stock." << endl;
                }

                // Calculate how much can actually be added (cap at available stock)
                int cart_qty = 0;
                Product* in_cart = customer->get_cart_modifiable()[id];
                if (in_cart != nullptr) {
                    cart_qty = in_cart->get_quantity();
                }
                int qty_to_add = min(qty, supplier_stock - cart_qty);
                if (qty_to_add < 0) qty_to_add = 0;

                if (qty_to_add > 0) {
                    customer->add_to_cart(*p, qty_to_add);
                }
                cout << "Product added to cart." << endl;
                break;
            }

            case 3: {
                // Remove a product from the customer's cart
                cout << "Items in the cart:" << endl;
                cout << customer->get_cart();
                cout << "Enter product ID to remove: ";
                cin >> id;
                cout << "Enter quantity to remove: ";
                cin >> qty;
                if (!customer->remove_from_cart(id, qty)) {
                    cout << "Product not found in cart." << endl;
                } else {
                    cout << "Product removed." << endl;
                }
                break;
            }

            case 4:
                // View all items currently in the cart
                cout << "Items in the cart:" << endl;
                cout << customer->get_cart();
                break;

            case 5: {
                // Checkout: ask user to confirm payment
                double total = customer->get_cart().Get_total();
                cout << "Total price: " << total << endl;
                cout << "Would you like to check out? (y/n): ";
                cin >> confirm;
                if (confirm == 'y') {
                    // Print receipt before cart is cleared
                    cout << "Total price: " << total << endl;
                    customer->get_cart().print_receipt();
                    // Deduct stock from supplier and clear cart
                    supplier.customer_purchases(*customer);
                }
                break;
            }

            case 6:
                cout << "Exiting shopping cart menu." << endl;
                return;

            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }
}
