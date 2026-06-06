/* Assignment C++: 1
   Authors: Razel Elmoznino ID: 206004095
            Dan Zelkind     ID: 211571948
*/

#include "MyQueue.h"

// --- 1. Constructor & Destructor ---

// Constructor: Initializes the maximum capacity of the queue.
// The vector 'elements' is initialized automatically as empty.
MyQueue::MyQueue(int maxQ) : maxQ(maxQ) {
}

// Destructor: Empty because std::vector handles its own memory management.
// When MyQueue is destroyed, 'elements' automatically frees its internal array.
MyQueue::~MyQueue() {
}

// --- 2. Standard Queue Operations ---

// Inserts a new element at the end of the queue.
// Returns true if successful, or false if the queue has reached its max capacity.
bool MyQueue::enQueue(int val) {
    // Check if the current size has already reached the maximum allowed capacity
    int currentSize = elements.size();
    if (currentSize >= maxQ) {
        return false; // Queue is full, insertion failed
    }
    // Insert the element at the back of the vector
    elements.push_back(val);
    return true; // Insertion succeeded
}

// Removes the oldest element from the front of the queue.
// Returns true if successful, or false if the queue was empty.
bool MyQueue::deQueue() {
    // Check the edge case to see if there are any elements to remove
    if (isEmpty()) {
        return false; // Queue is empty, nothing to remove
    }
    // Erase the first element using the vector's iterator
    elements.erase(elements.begin());
    return true; // Removal succeeded
}

// Returns the first element in the queue without removing it.
// Returns -1 if the queue is empty.
int MyQueue::peek() const {
    // Check if the queue is empty before trying to access elements
    if (isEmpty()) {
        return -1;
    }
    // Return the element at the front of the queue by value
    return elements.front();
}

// Checks if the queue is empty.
// Returns true if the vector has 0 elements, false otherwise.
bool MyQueue::isEmpty() const {
    return elements.empty(); // Returns true if size is 0
}