
#ifndef RESISTOR_H
#define	RESISTOR_H

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class Resistor {
    
private:
    double resistance;
    string name;
    int points[2];
    Resistor* next;
 
public:
    // constructors
    Resistor();
    Resistor( string name, double resistance, Resistor* next, int points[]);
    
    string getName() const; 
    double getResistance() const;
    void setResistance(double resistance_);
    Resistor * getNext();
    int getEndpoints(int arg);
    
  
    void print();
    friend ostream& operator<< (ostream& os, const Resistor& res);
 
    friend class ResistorList;
};

ostream& operator<< (ostream& os, const Resistor& res);

#endif	
