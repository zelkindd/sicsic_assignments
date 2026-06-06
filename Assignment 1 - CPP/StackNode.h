/* Assignment C++: 1
Author: Israel Israeli, ID: 01234567
*/


#ifndef STACKNODE_H
#define STACKNODE_H

class StackNode {
private:
   int data;            // The value stored in this node
   StackNode* next;     // Pointer to the next node in the stack

public:
   // Constructor: Initializes the node with a value and an optional next pointer
   // If nextNode is not provided, it defaults to null.
   StackNode(int val, StackNode* nextNode = nullptr);

   // Destructor
   ~StackNode();

   // Getters: const because they only return data without modifying the node
   int getData() const;
   StackNode* getNext() const;

   // Setters: Used to modify the node's internal state
   void setData(int val);
   void setNext(StackNode* nextNode);
};
#endif // STACKNODE_H