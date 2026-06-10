/* Assignment C++: 1
   Authors: Razel Elmoznino ID: 206004095
            Dan Zelkind     ID: 211571948
*/

#include "Menu.h"
#include <iostream>

using namespace std;

// --- 1. Main Menu ---

// Shows the top-level menu in a loop.
// Dispatches to stackMenu() or queueMenu() based on user input.
// Prints "Goodbye!" when the user exits.
void Menu::mainMenu() {
    int choice;
    do {
        // Print the three top-level options
        cout << "(1) Integer Stack" << endl;
        cout << "(2) Integer Queue Menu" << endl;
        cout << "(3) Exit" << endl;

        cin >> choice;
        switch(choice) {
            case 1: stackMenu(); break;
            case 2: queueMenu(); break;
            case 3: break;
            default: cout << "Invalid selection." << endl; break;
        }
    } while (choice != 3);
    cout << "Goodbye!" << endl;
}

// --- 2. Stack Sub-menu ---

// Creates a local Stack and lets the user operate on it until they choose exit.
// The stack is destroyed automatically when this function returns.
void Menu::stackMenu() {
    int choice;
    Stack stack;
    do {
        // Print all available stack operations
        cout << "*** Manage your integer stack ***" << endl;
        cout << "1 Push new element" << endl;
        cout << "2 Pop element" << endl;
        cout << "3 Check if empty" << endl;
        cout << "4 Print stack elements" << endl;
        cout << "5 to exit" << endl;
        cin >> choice;
        switch(choice) {

            // Push: read a value from the user and push it onto the stack
            case 1: {
                int num;
                cout << "Please insert the new element: ";
                cin >> num;
                stack.push(num);
                break;
            }

            // Pop: guard against an empty stack, then peek the value before
            // removing it so we can report what was removed
            case 2: {
                if (stack.isEmpty()) {
                    cout << "Stack empty" << endl;
                } else {
                    int val = stack.peek();
                    stack.pop();
                    cout << "Removing " << val << endl;
                }
                break;
            }

            // isEmpty: report whether the stack currently holds any elements
            case 3: {
                int empty;
                empty = stack.isEmpty();
                if (empty) cout << "The stack is empty" << endl;
                else cout << "The stack is not empty" << endl;
            }
            break;

            // Print: deep-copy the stack so we can destructively iterate it
            // without modifying the original; guard against printing an empty stack
            case 4: {
                if (stack.isEmpty()) {
                    cout << "The stack is empty" << endl;
                } else {
                    int num, i = 1;
                    Stack temp(stack); // copy constructor — deep copy
                    cout << "Stack elements:" << endl;
                    while (!temp.isEmpty()) {
                        num = temp.peek();
                        temp.pop();
                        cout << i << ". " << num << endl;
                        i++;
                    }
                }
                break;
            }

            // Exit: say goodbye and let the loop condition end the sub-menu
            case 5: {
                cout << "Thank you!" << endl;
                break;
            }

            default: {
                cout << "Invalid selection." << endl;
                break;
            }
        }
    } while (choice != 5);
}

// --- 3. Queue Sub-menu ---

// Prompts the user for the maximum queue capacity, creates a local MyQueue,
// then lets the user operate on it until they choose exit.
void Menu::queueMenu() {
    int size, choice;

    // Ask for capacity before entering the menu loop
    cout << "Enter the size of the queue: " << endl;
    cin >> size;
    MyQueue queue(size);

    do {
        // Print all available queue operations
        cout << "*** Welcome to Queue Menu ***" << endl;
        cout << "To select an item, enter " << endl;
        cout << "1 Show Queue" << endl;
        cout << "2 Insert new element" << endl;
        cout << "3 Remove element" << endl;
        cout << "4 Check the first element" << endl;
        cout << "5 to exit" << endl;
        cin >> choice;
        switch (choice) {

            // Show: print all elements in FIFO order (first <- ... <- last)
            case 1: {
                queue.print();
                cout << endl;
                break;
            }

            // Insert: enQueue the value; print the updated queue on success,
            // or report that the queue is at capacity
            case 2: {
                int num;
                bool method_worked;
                cout << "insert new element: ";
                cin >> num;
                method_worked = queue.enQueue(num);
                if (method_worked) {
                    cout << "The new queue:" << endl;
                    queue.print();
                }
                else cout << "Queue is full" << endl;
                cout << endl;
                break;
            }

            // Remove: deQueue the front element; if the queue was already empty
            // report that, and if it becomes empty after removal also report that
            // instead of printing an empty "new queue"
            case 3: {
                if (queue.isEmpty()) {
                    cout << "Queue is empty" << endl;
                } else {
                    queue.deQueue();
                    if (queue.isEmpty()) {
                        cout << "Queue is empty" << endl;
                    } else {
                        cout << "The new queue:" << endl;
                        queue.print();
                    }
                }
                cout << endl;
                break;
            }

            // Peek: show the front element without removing it
            case 4: {
                if (queue.isEmpty()) cout << "Queue is empty" << endl;
                else cout << queue.peek() << endl;
                cout << endl;
                break;
            }

            // Exit: let the loop condition end the sub-menu
            case 5: {
                break;
            }

            default: {
                cout << "Invalid selection." << endl;
                cout << endl;
                break;
            }
        }
    } while (choice != 5);
}
