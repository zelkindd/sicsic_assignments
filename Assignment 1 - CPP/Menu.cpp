/* Assignment C++: 1
   Authors: Razel Elmoznino ID: 206004095
            Dan Zelkind     ID: 211571948
*/

#include "Menu.h"
#include <iostream>

using namespace std;

void Menu::mainMenu() {
    int choice;
    do {
        // print menu options
        cout << "(1) Integer Stack" << endl;
        cout << "(2) Integer Queue Menu" << endl;
        cout << "(3) Exit" << endl;        
        
        // get user choice
        cin >> choice;
        switch(choice) {
            case 1: stackMenu(); break;
            case 2: queueMenu(); break;
            case 3: break;
            default: cout << "Invalid selection." << endl; break;
        }
    } while (choice != 3);
}

void Menu::stackMenu() {
   int choice;
   Stack stack; 
   do {
       // print stack menu options
       cout << "*** Manage your integer stack ***";
       cin >> choice;
       switch(choice) {
                
        case 1: {
            int num;
            cout << "Please insert the new element: " << endl;
            cin >> num;
            stack.push(num);
            break;
        }

        case 2: {
            int pop;
            pop = stack.peek();
            stack.pop();
            cout << "Removing " << pop << endl;
            break;
        }

        case 3: {
            int empty;
            empty = stack.isEmpty();
            if (empty) cout << "The stack is empty" << endl;
            else cout << "The stack is not empty" << endl;
        }
        break;

        case 4: {
            int num, i;
            Stack temp(stack);
            while (!temp.isEmpty()){
                num = temp.peek();
                temp.pop();
                cout << i << ". " << num << endl;
            }
            break;
        }

        case 5: {
            cout << "Thank You!" << endl;
            break;
        }


        default: {
            break;
        }

       }
   } while (choice != 5);

}

void Menu::queueMenu() {
    int size, choice;

    cout << "Enter the size of the queue: ";
    cin >> size;
    MyQueue queue(maxQ=size);

    cout << ""

    switch (choice) {

        case 1:{
            //print the whole queue
            MyQueue temp(queue);
            int num;
            while (!temp.isEmpty()) {
                cout << temp.peek() << "<-" << endl; // last element doesn't need <- i trust claude to do it
                temp.deQueue();
            }
            break;
        }

        case 2: {
            //add element
            int num;
            bool method_worked;	
            cout << "insert new element: "
            cin >> num;
            method_worked = queue.enQueue(num);
            if (method_worked) {
                cout << "The new queue: " << endl;
                print_the_whole_queue; in this format: first <- ... <- last;	
            }
            else cout << "Queue is full";
            break;
        }

        case 3: {
            //remove element
            if (queue.isEmpty()) cout << "Queue is empty";
            else {
                queue.deQueue();
                cout << "The new queue: " << endl;
                print_the_whole_queue; in this format: first <- ... <- last;	
            }
            break;
        }

        case 4: {
            if (queue.isEmpty()) cout << "Queue is empty";
            else cout << queue.peek();
            break;		
        }
        
        case 5; {
            break;
        }
        
        
    }

}