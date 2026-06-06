/* Assignment C++: 1
   Author: Israel Israeli, ID: 01234567
*/ 
#include "Stack.h"
#include <climits>

// --- 1. Constructors & Destructor ---

// Constructor: Initializes the stack to be empty.
// We set the top pointer to null because there are no nodes yet.
Stack::Stack() : top(nullptr) {
}

// Destructor: Must clean up all dynamic nodes to prevent memory leaks.
// We use a loop to delete nodes one by one until the stack is empty.
Stack::~Stack() {
   while (!isEmpty()) {
      pop(); // pop will handle deleting the top node and moving to the next
   }
}

// --- 2. Standard Stack Operations ---

// Returns true if the stack has no elements, false otherwise.
// Const because it only checks the state without modifying anything.
bool Stack::isEmpty() const {
   return top == nullptr;
}

// Inserts a new element at the top of the stack.
void Stack::push(int val) {
   // Create a new node and point its 'next' to the current top node.
   StackNode* newNode = new StackNode(val, top);
   // Make the new node the new top of the stack.
   top = newNode;
}

// Removes the top element. If empty, prints "Stack is empty".
void Stack::pop() {
   // Check the edge case required by the instructions
   if (isEmpty()) {
      std::cout << "Stack is empty" << std::endl;
      return;
   }
   // Save the current top node to a temporary pointer
   StackNode* temp = top;
   // Advance top to point to the next node down the stack
   top = top->getNext();
   // Free the memory of the old top node
   delete temp;
}

// Returns the top element without modifying the stack.
// Returns INT_MIN if the stack is empty.
int Stack::peek() const {
   // Check the edge case required by the instructions
   if (isEmpty()) {
      return INT_MIN;
   }
   // Otherwise, return the data of the top node using its getter
   return top->getData();
}

// --- 3. Operator Overloading ---

// Concatenate two stacks: S1 + S2
Stack Stack::operator+(const Stack& other) const {
   Stack result;
   Stack temp;
   // 1. Push all elements of the first stack (S1 / this) to temp
   StackNode* current = this->top;
   while (current != nullptr) {
      temp.push(current->getData());
      current = current->getNext();
   }
   // 2. Push all elements of the second stack (S2 / other) to temp
   current = other.top;
   while (current != nullptr) {
      temp.push(current->getData());
      current = current->getNext();
   }
   // 3. Move everything from temp to result
   while (!temp.isEmpty()) {
      result.push(temp.peek());
      temp.pop();
   }
   return result;
}

// Concatenate stack with an integer (integer on the right): S1 + int
// The integer becomes the bottom element of the returned stack {S1, int}.
Stack Stack::operator+(int val) const {
   Stack result;
   Stack temp;
   // 1. Push the integer first, so it sits at the absolute bottom of result
   result.push(val);
   // 2. Push all elements of the current stack (this) to temp to reverse them
   StackNode* current = this->top;
   while (current != nullptr) {
      temp.push(current->getData());
      current = current->getNext();
   }
   // 3. Move from temp to result (restores order, placing them On Top of the integer)
   while (!temp.isEmpty()) {
      result.push(temp.peek());
      temp.pop();
   }
   return result;
}

// Concatenate stack with an integer (integer on the left): int + S1
// The integer becomes the new top element of the returned stack {int, S1}.
Stack operator+(int val, const Stack& stack) {
   Stack result;
   // 1. Push the integer first into our empty result stack
   result.push(val);
   // 2. use the operator+(const Stack&) we already wrote.
   // This will  append all elements of 'stack' underneath 'val'
   return result + stack;
}

// Push an integer to the stack using += operator: S += int
// This modifies the original stack directly by pushing the value onto the top.
Stack& Stack::operator+=(int val) {
   // 1. Insert the value directly to the top of the current stack
   this->push(val);
   // 2. Return a reference to the current object
   return *this;
}

// Compare two stacks for equality: S1 == S2
// Returns true if both stacks have the same elements in the same order.
bool Stack::operator==(const Stack& other) const {
   // Create temporary pointers to traverse both stacks from the top
   StackNode* curr1 = this->top;
   StackNode* curr2 = other.top;
   // Loop until at least one of the tracks reaches the end of the stack
   while (curr1 != nullptr && curr2 != nullptr) {
      // If any paired elements do not match, the stacks are not equal
      if (curr1->getData() != curr2->getData()) {
         return false;
      }
      // Advance both pointers to the next node down the line
      curr1 = curr1->getNext();
      curr2 = curr2->getNext();
   }
   // If both reached null at the exact same time, they are equal.
   // If one stack is longer than the other, this will correctly return false.
   return (curr1 == nullptr && curr2 == nullptr);
}

// Print the stack elements from top to bottom: os << S1
std::ostream& operator<<(std::ostream& os, const Stack& stack) {
   // Create a safe deep copy of the stack using our member operator+
   Stack emptyStack;
   Stack tempStack = emptyStack + stack;
   // Initialize a counter for the numbered list format
   int count = 1;
   // Safely dismantle the temporary copy to print elements with their index
   while (!tempStack.isEmpty()) {
      os << count << ". " << tempStack.peek() << std::endl;
      tempStack.pop();
      count++;
   }
   // Return the output stream to allow chaining
   return os;
}