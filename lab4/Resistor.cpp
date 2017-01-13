#include "Resistor.h"

Resistor::Resistor() {
}

Resistor:: Resistor( string name_, double resistance_, Resistor* next_, int endpoints_[]) {
    name = name_;
    resistance = resistance_;
    next = next_;
    points[0] = endpoints_[0];
    points[1] = endpoints_[1];
}


string Resistor::getName() const {
    return name;
}
 
double Resistor::getResistance() const {
    return resistance;
}

int Resistor:: getEndpoints(int arg) {
  
    if (arg == 0) 
        return points[0];
    
    else if (arg == 1)
        return points[1];
}

Resistor* Resistor:: getNext() {
    return next;
}

void Resistor::setResistance(double resistance_) {
    resistance = resistance_;
}

void Resistor::print(){
    cout << setw(20) << left <<name << setw(8) << right << resistance << " Ohms " << points[0] << " -> " << points[1] << endl; 
}


ostream& operator<< (ostream& os, const Resistor& res) {
  os << res.name << setw(20) <<res.resistance << " Ohms " << res.points[0] << " -> " << res.points[1] << endl;
}

