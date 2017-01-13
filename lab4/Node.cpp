#include "Node.h"

Node:: Node(){
    flag = 0;
    voltage = 0;
} 

Node:: Node(int nodeId_value, Node* next_value) {
    nodeId = nodeId_value;
    next = next_value;
    flag = 0;
    voltage = 0;
}


void Node:: setVoltage(double vol) {
    voltage = vol;
}

int Node:: getNodeId() {
    return nodeId;
}

double Node:: getVoltage() {
    return voltage;
}

ResistorList& Node:: getResistorList() {
    return resistorList;
}

int Node:: addResistor(string name, double resistance, int points[]) {
        resistorList.addResistor(name, resistance, points);
}

void Node:: print() {
    int numRes = resistorList.getNumRes(); // getting the #of resistors in the list
    
    if ( numRes != 0) {// if the resistor list is empty, don't print
        cout << "Connections at node " << nodeId << ": " << numRes << " resistor(s)" << endl;
        resistorList.printAllResistor();
    }
}

void Node:: set(double vol) {
    voltage = vol;
    flag = 1;
}

void Node:: unSet() {
    flag = 0;
    voltage = 0; 
}


