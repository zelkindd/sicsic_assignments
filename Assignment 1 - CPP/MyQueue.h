/* Assignment C++: 1
   Authors: Razel Elmoznino ID: 206004095
            Dan Zelkind     ID: 211571948
*/

#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <vector> // Required for using std::vector

class MyQueue {
private:
   std::vector<int> elements; // Vector to store the integer elements inside the queue
   int maxQ;                  // The maximum capacity of the queue

public:
   // --- 1. Constructor & Destructor ---

   // Constructor: Initializes the queue with a given maximum capacity
   MyQueue(int maxQ);

   // Copy constructor: Deep copies elements and maxQ from other
   MyQueue(const MyQueue& other);

   // Destructor: Defined explicitly as required.
   // Vector automatically cleans up its memory, so the body will be empty.
   ~MyQueue();

   // --- 2. Standard Queue Operations ---

   // Inserts a new element at the end of the queue.
   // Returns true if successful, false if the queue is full.
   bool enQueue(int val);

   // Removes the next element from the front of the queue.
   // Returns true if successful, false if the queue is empty.
   bool deQueue();

   // Returns the value of the first element in the queue without removing it.
   // Returns -1 if the queue is empty.
   int peek() const;

   // Returns true if the queue contains no elements, false otherwise.
   bool isEmpty() const;

   // Prints all elements as: first <- second <- ... <- last
   void print() const;
};

#endif // MYQUEUE_H