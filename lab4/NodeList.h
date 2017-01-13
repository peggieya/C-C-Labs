#ifndef NODELIST_H
#define	NODELIST_H

#include "Node.h"
#include <cmath>

#define CHANGE 0.0001

class NodeList {
    
public:
    NodeList();
    ~NodeList();
    Node* searchOrInsert(int nodeId);
    int modifyResistor(string name, double &oldres, double newRes);
    void printNodes();
    Resistor* searchResistor(string name);
    int is_exist_Resistor(string name); 
    void delAllResistor();
    void delAllNodes(); 
    int delResistor(string name);
    int checkOneSetV();
    void solve();
    
private:
    Node * head;
    double solveHelp(Node * tmp); 
};

#endif
