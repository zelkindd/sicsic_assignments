/* Assignment C++: 1
   Authors: Razel Elmoznino ID: 206004095
            Dan Zelkind     ID: 211571948
*/

#ifndef STACK_H
#define STACK_H

#include "StackNode.h"
#include <iostream>


class Stack {
private:
   StackNode* top; // Pointer to the top node of the stack

public:
   // --- 1. Constructors & Destructor ---
   // Constructor: Initializes the stack to be empty (top = nullptr)
   Stack();

   // Copy constructor: Deep copies every node from other into this stack
   Stack(const Stack& other);

   // Destructor: Must free all dynamically allocated nodes to prevent memory leaks
   ~Stack();

   // --- 2. Standard Stack Operations ---
   // Inserts a new element at the top of the stack
   void push(int val);

   // Removes the top element. If empty, prints "Stack is empty"
   void pop();

   // Returns the top element without modifying the stack. Returns INT_MIN if empty
   int peek() const;

   // Returns true if the stack is empty, false otherwise
   bool isEmpty() const;

   // --- 3. Operator Overloading (As Member Functions) ---
   // Concatenate two stacks: S1 + S2
   Stack operator+(const Stack& other) const;

   // Concatenate stack with an integer (integer on the right): S1 + int
   Stack operator+(int val) const;

   // Push an integer to the stack using += operator: S += int
   Stack& operator+=(int val);

   // Compare two stacks for equality: S1 == S2
   bool operator==(const Stack& other) const;
};

// --- 4. Global Operator Overloading (Outside the Class) ---
// Concatenate stack with an integer (integer on the left): int + S1
Stack operator+(int val, const Stack& stack);

// Insertion operator for easy printing: cout << S1
std::ostream& operator<<(std::ostream& os, const Stack& stack);

#endif // STACK_H