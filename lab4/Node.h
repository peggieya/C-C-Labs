
#ifndef NODE_H
#define	NODE_H
#include <iostream>

#include "ResistorList.h"
using namespace std;

class Node {

private:
    ResistorList resistorList; 
    int nodeId, drawID;
    double voltage;
    Node* next; 
    int flag; 
    
public:
    
    Node();
    Node(int nodeId, Node* next);
    
    
    void setVoltage(double voltage);
    int getNodeId();
    double getVoltage();
    ResistorList& getResistorList();
    
    int addResistor(string name, double resistance, int points[]);
    void print();
   
    void set (double voltage_);
    void unSet ();
    
    friend class NodeList;

};

#endif	

