
#include "DBentry.h"
using namespace std; 

DBentry::DBentry(string  _name, unsigned int _IPaddress, bool _active){
    name =  _name;
    IPaddress = _IPaddress;
    active = _active;
}

DBentry::DBentry(const DBentry& dRight) {}

DBentry::~DBentry() {}

void DBentry::setActive(bool _active){
    active = _active;
}
void DBentry:: setIPaddress(unsigned int _IPaddress){
    IPaddress = _IPaddress;
}
void DBentry::setName(string  _name){
    name =  _name;
}

bool DBentry::getActive() const{
    return active;
}

unsigned int DBentry::getIPaddress() const{
    return IPaddress;
}
string DBentry::getName() const{
    return name;
}
ostream& operator << (ostream& os, const DBentry& right){
    string active;
	if(right.active)  
		active = "active";
	else 
		active ="inactive";
    
    os << right.name << " : " << right.IPaddress<< " : " << active << endl;
    return os;
}
