#ifndef RESISTORLIST_H
#define	RESISTORLIST_H

#include "Resistor.h"
#include <cstring>

class ResistorList {
public:
    // constructor; default destructor is fine
    ResistorList();     
    
 
    Resistor* getHead();
    int getNumRes();

    void addResistor( string name_, double resistance_, int endpoints_[]);
    int delResistor(string name);
    void delAllResistor();
    Resistor* searchResistor(string name);
    
    
    void printAllResistor();
    

private:
    Resistor* head;
    int numRes; 
};

#endif
