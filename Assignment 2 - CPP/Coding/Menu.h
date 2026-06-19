/****************************************
Assignment C++: 2
Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*****************************************/

#ifndef MENU_H
#define MENU_H

#include "Supplier.h"
#include "Customer.h"

using namespace std;

// Menu class manages the interaction between the supplier and customer.
// All user I/O (besides methods defined in other classes) is handled here.
class Menu {
private:
    Supplier supplier;   // The store's supplier (composition)
    Customer* customer;  // Polymorphic pointer to the current customer

    void storeMenu();    // Supplier-side menu
    void cartMenu();     // Customer-side menu

public:
    Menu();              // Default constructor: initializes supplier and customer
    ~Menu();             // Destructor: frees customer pointer

    void mainMenu();     // Entry point — loops until user chooses to exit
};

#endif // MENU_H
