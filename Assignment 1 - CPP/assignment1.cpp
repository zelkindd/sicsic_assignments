/* Assignment C++: 1
   Authors: Razel Elmoznino ID: 206004095
            Dan Zelkind     ID: 211571948
*/

#include "Menu.h"
#include "Stack.h"
#include "MyQueue.h"
#include <iostream>

using namespace std;

int main() {

    // =================================================================================================================
    // <<< TEMP STACK CHECK >>>
    // =================================================================================================================
    std::cout << "--- Starting Stack Sanity Check ---" << std::endl;

    // 1. Create two empty stacks
    Stack s1;
    Stack s2;

    // 2. Test push and individual operations
    s1.push(5);
    s1.push(1); // s1 is now {1, 5} -> 1 is at the top

    s2.push(9);
    s2.push(8); // s2 is now {8, 9} -> 8 is at the top

    std::cout << "\nInitial Stack 1 (Should be 1 then 5):" << std::endl;
    std::cout << s1;

    std::cout << "\nInitial Stack 2 (Should be 8 then 9):" << std::endl;
    std::cout << s2;

    // 3. Test Operator+ (Stack + Stack) using your optimized approach
    Stack s3 = s1 + s2;
    std::cout << "\nResult of s1 + s2 (s1 elements must stay on top: 1, 5, 8, 9):" << std::endl;
    std::cout << s3;

    // 4. Test Operator+ with integers (Respectively check)
    Stack s4 = s1 + 3; // 3 should go to the bottom -> {1, 5, 3}
    std::cout << "\nResult of s1 + 3 (3 at the bottom):" << std::endl;
    std::cout << s4;

    Stack s5 = 3 + s1; // 3 should go to the top -> {3, 1, 5}
    std::cout << "\nResult of 3 + s1 (3 at the top):" << std::endl;
    std::cout << s5;

    // 5. Test Operator+=
    s1 += 100; // Modifies s1 directly -> {100, 1, 5}
    std::cout << "\nResult of s1 += 100 (Direct modification, 100 at top):" << std::endl;
    std::cout << s1;

    // 6. Test Operator==
    Stack testEqual1;
    Stack testEqual2;
    testEqual1.push(10);
    testEqual2.push(10);

    std::cout << "\nEquality Check (Should be 1 - True): " << (testEqual1 == testEqual2) << std::endl;
    testEqual2.push(20);
    std::cout << "Equality Check after change (Should be 0 - False): " << (testEqual1 == testEqual2) << std::endl;

    std::cout << "\n--- Sanity Check Completed Successfully ---" << std::endl;

    // =================================================================================================================
    // <<< TEMP STACK CHECK END >>>
    // =================================================================================================================

    // =================================================================================================================
    // <<< TEMP MYQUEUE CHECK >>>
    // =================================================================================================================

    std::cout << "--- Starting MyQueue Sanity Check ---" << std::endl;

    // 1. Create a queue with a maximum capacity of 3 elements
    MyQueue q(3);

    // 2. Test isEmpty on a fresh queue (Should be 1 - True)
    std::cout << "Is queue empty initially? (Should be 1): " << q.isEmpty() << std::endl;

    // 3. Test peek on an empty queue (Should be -1 as required)
    std::cout << "Peek on empty queue (Should be -1): " << q.peek() << std::endl;

    // 4. Test enQueue (Inserting elements)
    std::cout << "\nInserting elements 10, 20, 30..." << std::endl;
    std::cout << "EnQueue 10: " << q.enQueue(10) << std::endl; // Should be 1 (True)
    std::cout << "EnQueue 20: " << q.enQueue(20) << std::endl; // Should be 1 (True)
    std::cout << "EnQueue 30: " << q.enQueue(30) << std::endl; // Should be 1 (True)

    // 5. Test peek after insertions (Should show the first element: 10)
    std::cout << "Peek after insertions (Should be 10): " << q.peek() << std::endl;

    // 6. Test capacity limit (The queue maxQ is 3, so the 4th element should fail)
    std::cout << "EnQueue 40 on a full queue (Should be 0 - False): " << q.enQueue(40) << std::endl;

    // 7. Test deQueue (Removing elements in FIFO order)
    std::cout << "\nRemoving elements (FIFO order)..." << std::endl;

    std::cout << "Current Front (Peek): " << q.peek() << std::endl; // 10
    std::cout << "DeQueue: " << q.deQueue() << std::endl;          // Removes 10

    std::cout << "Current Front (Peek): " << q.peek() << std::endl; // 20
    std::cout << "DeQueue: " << q.deQueue() << std::endl;          // Removes 20

    std::cout << "Current Front (Peek): " << q.peek() << std::endl; // 30
    std::cout << "DeQueue: " << q.deQueue() << std::endl;          // Removes 30

    // 8. Test deQueue on an empty queue (Should fail)
    std::cout << "\nDeQueue on an empty queue (Should be 0 - False): " << q.deQueue() << std::endl;
    std::cout << "Is queue empty now? (Should be 1 - True): " << q.isEmpty() << std::endl;

    std::cout << "\n--- MyQueue Sanity Check Completed Successfully ---" << std::endl;

    // =================================================================================================================
    // <<< TEMP MYQUEUE CHECK END >>>
    // =================================================================================================================


    //simply creating a menu instance, then calling mainMenu(). the rest is inside mainMenu().
    Menu a;
    a.mainMenu();
    return 0;
}