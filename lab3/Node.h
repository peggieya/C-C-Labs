#ifndef NODE_H
#define NODE_H

#include "Resistor.h"
#include "Rparser.h"

#define MAX_RESISTORS_PER_NODE 5


class Node
{
private:
   int nodeIndex; 
   int numRes; // number of resistors currently connected
   int resIDArray[MAX_RESISTORS_PER_NODE]; // stores the index of each resistor connected

public:
   Node(); 
   ~Node();

   //constructor used to initialize the variables
   Node(int numRes_, int resIDArray_);
   
   // Checks to see if the resistor can be added to poistion rIndex
   // in the resistor array. Returns true if yes, otherwise false.
   bool canAddResistor(int rIndex_);

   // Updates resIDArray to make the resistor in position rIndex in
   // the resistor array connected to this node.
   void addResistor (int rIndex_); 

   // prints the whole node
   // nodeIndex is the position of this node in the node array.
   void print (int nodeIndex_); 
   
   void setNodeIndex(int nodeIndex_);
   int getNumRes()const;

   int getResistorArray(int index_) const;

};

#endif	/* NODE_H */


