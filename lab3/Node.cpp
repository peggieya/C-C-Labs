#include <string>
#include <cstring>
#include <iostream>
#include<iomanip>

#include "Resistor.h"
#include "Node.h"
#include "Rparser.h"

using namespace std;

//default construtor
Node::Node() {
    numRes = -1;
    for (int i = 0; i < MAX_RESISTORS_PER_NODE; i++)
        resIDArray[i] = -1;
};

//This constructor initialize the variables

Node::Node(int numRes_, int resIDArray_) {
    numRes = numRes_;
    for (int i = 0; i < MAX_RESISTORS_PER_NODE; i++)
        resIDArray[i] = -1;
};

//destructor
Node::~Node() {

};

//this function checks if there is position avaliable for a new resistor
bool Node::canAddResistor(int rIndex_) {

    bool blank = false;
    bool differentIndex = true;
    bool result;

    for (int i = 0; i < MAX_RESISTORS_PER_NODE && !blank && differentIndex; i++) {
        if (resIDArray[i] == -1) {
            blank = true;
        } else {
            if (resIDArray[rIndex_] == rIndex_)
                differentIndex = false;
        }
    }
    result = (blank && differentIndex);
    return result;

};


//add an resistor to the reaIDarray
void Node::addResistor(int rIndex_) {
	bool blank = false;
	for (int i = 0; i < MAX_RESISTORS_PER_NODE && !blank; i++) {
		if (resIDArray[i] == -1)
		{
			blank = true;
			resIDArray[i] = rIndex_;
			numRes = numRes++;
		}
	}
};

//print two node terminal
void Node::print(int nodeIndex_) {
	if (nodeIndex == nodeIndex_)
		cout << "Connections at node " << nodeIndex << ": " << numRes << " resistor(s)" << endl;
};

//set the value of node index
void Node::setNodeIndex(int nodeIndex_) {
    nodeIndex = nodeIndex_;
};

//get the resistor array
int Node::getResistorArray(int index_) const {
    return resIDArray[index_];
};

//get how many resistor are in the node currently
int Node::getNumRes() const{
  return numRes;  
};

