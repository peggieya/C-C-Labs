#include <string>
#include <cstring>
#include <iostream>
#include<iomanip>
#include "Resistor.h"
#include "Node.h"
#include "Rparser.h"

using namespace std;

//Default constructor
Resistor::Resistor(){
        rIndex = -1;
	name = " ";
	resistance = -1;
	endpointNodeIDs[0] = -1;
	endpointNodeIDs[1] = -1;
};

//This constructor initialize the variables
Resistor::Resistor(int rIndex_, string name_, double resistance_, int endpoints_[2]) {
    rIndex = rIndex_;
    resistance = resistance_;
    name = name_;
    endpointNodeIDs[0] = endpoints_[0];
    endpointNodeIDs[1] = endpoints_[1];
};

Resistor::~Resistor(){
    
};

// this function returns the name

string Resistor::getName() const {
    return name;
};

// this function returns the resistance

double Resistor::getResistance() const {
    return resistance;
};

// this function initialize the resistance

void Resistor::setResistance(double resistance_) {
    resistance = resistance_;
};

//this function initialize the nodes id

void Resistor::setNodeId(int endpoints_[2]) {
    endpointNodeIDs[0] = endpoints_[0];
    endpointNodeIDs[1] = endpoints_[1];
}

void Resistor::setnamenode(string nameIn, int node0, int node1) {
	name = nameIn;
	endpointNodeIDs[0] = node0;
	endpointNodeIDs[1] = node1;
};

//this function print the info of one resistor

void Resistor::print() {
    cout << setiosflags(ios::right);
    cout << setw(20) << name;
    cout << setw(8) << fixed << setprecision(2) << resistance << " Ohms " << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] <<endl;
};

ostream& operator<<(ostream&o, const Resistor& temp) {
	o << "Print:" << endl;
	o << setiosflags(ios::right);
	o << setw(20) << temp.name;
	o << setw(8) << fixed << setprecision(2) << temp.resistance << " Ohms " << temp.endpointNodeIDs[0] << " -> " << temp.endpointNodeIDs[1];
        
        return o;
};
