
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>

#include "Rparser.h"

using namespace std;

int main() {
    
    cout.setf(ios::fixed);
    cout.precision(2);
    
    Rparser mRparser;
    return mRparser.excute(); 
}
