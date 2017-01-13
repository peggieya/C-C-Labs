
#ifndef DBENTRY_H
#define	DBENTRY_H

#include <string>
#include <iostream>
using namespace std;

class DBentry {
public:
    DBentry(string  _name, unsigned int _IPaddress, bool _active);
    DBentry(const DBentry& dRight);
    virtual ~DBentry();
    
    void setName(string  _name);
    void  setIPaddress(unsigned int _IPaddress);
    void setActive (bool _active);
    
    string getName() const;
    unsigned int getIPaddress() const;
    bool getActive() const;
    
    friend ostream& operator << (ostream& os, const DBentry& right);
    
private:
    string name;
    unsigned int IPaddress;
    bool active;
};

ostream& operator << (ostream& os, const DBentry& right);
#endif	
