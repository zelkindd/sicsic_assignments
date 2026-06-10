/* Assignment C++: 1
   Authors: Razel Elmoznino ID: 206004095
            Dan Zelkind     ID: 211571948
*/

#ifndef MENU_H
#define MENU_H

#include "Stack.h"
#include "MyQueue.h"

class Menu {
public:
   // --- 1. Public Interface ---

   // Entry point: shows the main menu in a loop until the user chooses Exit
   void mainMenu();

private:
   // --- 2. Sub-menus ---

   // Manages a single Stack instance: push, pop, isEmpty, print, exit
   void stackMenu();

   // Prompts for queue size, then manages a single MyQueue instance:
   // show, insert, remove, peek, exit
   void queueMenu();
};

#endif // MENU_H
