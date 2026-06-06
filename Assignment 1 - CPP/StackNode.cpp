/* Assignment C++: 1
   Author: Israel Israeli, ID: 01234567
*/ 

#include "StackNode.h"

// --- 1. Constructors & Destructor ---

// Constructor: Initializes the node's data and next pointer using an initializer list.
StackNode::StackNode(int val, StackNode* nextNode) : data(val), next(nextNode) {
}

// Destructor: Empty because the node does not manage its own dynamic allocations.
// The Stack class handles freeing the nodes dynamically.
StackNode::~StackNode() {
}

// --- 2. Getters ---

// Returns the integer data stored in the node.
int StackNode::getData() const {
   return data;
}

// Returns the pointer to the next node in the stack.
StackNode* StackNode::getNext() const {
   return next;
}

// --- 3. Setters ---

// Updates the node's internal data value.
void StackNode::setData(int val) {
   data = val;
}

// Updates the node's internal next pointer.
void StackNode::setNext(StackNode* nextNode) {
   next = nextNode;
}