#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include "Rparser.h" 
#include "Resistor.h"
#include "Node.h"

#define MAX_RESISTORS_PER_NODE 5

using namespace std;

double theResistance;

bool checkArgAll(string argument);

void insertSuccess(string name, double theResistance, string nodeid1, string nodeid2);
void modifySucess(string name, double theResistance);
void sameNode(string nodeid);

bool checkPrintAll(string all);
bool checkDeletAll(string all);

void printAllResistor();
void printResistor(string name);

void printAllNode();
void printNode(string nodeid);

void deletResistor(string name);
void deletAllResistor();

void tooManyArg();
void tooFewArg();
void invalidMaxVal();
void sameResistorNameError(string name);
void newNetwork(int MAX_NODE_NUMBER, int MAX_RESISTORS);

bool checkValidNodeid(string nodeid, int MAX_NODE_NUMBER);
int returnInt(string nodeid);
double returnDouble(string resistance);
bool checkValidResistance(string resistance);
bool checkValidMaxVal(int MaxVal);
void putinorderforprintnode(int *x);

void Rparser() {

    bool toContinue = true;
    string line, command;
    string name;
    string nodeid;
    string nodeid1, nodeid2;
    int nodeID_1, nodeID_2;
    string temp;
    string resistance;
    string next;

    int MAX_NODE_NUMBER = 0, MAX_RESISTORS = 0;
    Resistor* pAllR = NULL;
    Node* pAllNode = NULL;

    int countR = 0;
    int nodeArray[1];


    cout << ">";

    getline(cin, line); // Get a line from standard input

    while (!cin.eof()) {

        // Put the line in a stringstream for parsing
        // Making a new stringstream for each line so flags etc. are in a known state

        stringstream lineStream(line);
        lineStream >> command;

        if (!lineStream.fail()) {

            if (command == "maxVal") {

                lineStream >> MAX_NODE_NUMBER;
                if (lineStream.fail()) {
                    tooFewArg();
                    toContinue = false;
                } else if (!checkValidMaxVal(MAX_NODE_NUMBER)) {
                    invalidMaxVal();
                    lineStream.ignore(1000, '\n');
                    toContinue = false;
                }

                if (toContinue) {
                    lineStream >> MAX_RESISTORS;
                    if (lineStream.fail()) {
                        //there is nothing after the command
                        //too few argument
                        tooFewArg();
                        toContinue = false;
                    } else if (!checkValidMaxVal(MAX_RESISTORS)) {
                        invalidMaxVal();
                        lineStream.ignore(1000, '\n');
                        toContinue = false;
                    }
                }

                if (toContinue)
                    lineStream >> next;

                if (toContinue && lineStream.fail()) {
                    toContinue = true;

                } else if (toContinue && !lineStream.fail()) {
                    //there are too many arguments after the valid inputs
                    toContinue = false;
                    tooManyArg();
                    lineStream.ignore(1000, '\n');
                    lineStream.clear();
                }


                if (toContinue) {
                    newNetwork(MAX_NODE_NUMBER, MAX_RESISTORS);
                    int countAllResistors = 0;

                    //delete the previous resistor and node array when set up a new network
                    delete pAllR;
                    delete pAllNode;
                    countR = 0;
                    pAllR = new Resistor[MAX_RESISTORS - 1];
                    pAllNode = new Node[MAX_NODE_NUMBER - 1];
                }



            } else if (command == "insertR") {
                // parse an insertR command

                if (countR == MAX_RESISTORS) {
                    cout << "Error: resistor array is full" << endl;
                    toContinue = false;
                }

                if (toContinue) {
                    lineStream >> name;
                    if (lineStream.fail()) {
                        //there is nothing after the command
                        //too few argument
                        tooFewArg();
                        toContinue = false;
                    }
                }

                if (toContinue) {
                    bool sameResistorName = false;
                    for (int i = 0; i < MAX_RESISTORS; i++) {
                        if (name == pAllR[i].getName())
                            sameResistorName = true;
                    }

                    if (sameResistorName) {
                        sameResistorNameError(name);
                        toContinue = false;
                    }
                }

                if (toContinue) {
                    if (checkArgAll(name)) {
                        toContinue = false;
                    }
                }

                if (toContinue) {
                    lineStream >> temp;
                    if (lineStream.fail()) {
                        //there is nothing after the resistance
                        //too few argument
                        tooFewArg();
                        toContinue = false;
                    } else if (!checkValidResistance(temp)) {
                        toContinue = false;
                    } else {
                        resistance = temp;
                        theResistance = returnDouble(resistance);
                        pAllR[countR].setResistance(theResistance);
                    }
                }

                if (toContinue) {
                    lineStream >> temp;
                    if (lineStream.fail()) {
                        tooFewArg();
                        toContinue = false;
                    }
                }

                if (toContinue) {
                    if (checkValidNodeid(temp, MAX_NODE_NUMBER)) {
                        nodeid1 = temp;
                        nodeID_1 = returnInt(nodeid1);
                        pAllNode[nodeID_1].addResistor(countR + 1);

                        //check is one node is full by comparing the current resistor# with the MAX_NODE_PER_NODE
                        if ((pAllNode[nodeID_1].getNumRes()) == MAX_RESISTORS_PER_NODE) {
                            cout << "Error: node is full" << endl;
                            toContinue = false;
                        } else
                            toContinue = true;
                    } else toContinue = false;
                }

                if (toContinue) {
                    lineStream >> temp;
                    if (lineStream.fail()) {
                        tooFewArg();
                        toContinue = false;
                    }
                }
                if (toContinue) {
                    //checks if the input argument nodeid is valid
                    if (checkValidNodeid(temp, MAX_NODE_NUMBER)) {
                        nodeid2 = temp;
                        nodeID_2 = returnInt(nodeid2);
                        pAllNode[nodeID_2].addResistor(countR + 1);

                        //check is one node is full by comparing the current resistor# with the MAX_NODE_PER_NODE
                        if ((pAllNode[nodeID_1].getNumRes()) == MAX_RESISTORS_PER_NODE) {
                            cout << "Error: node is full" << endl;
                            toContinue = false;
                        } else
                            toContinue = true;
                    } else toContinue = false;
                }

                if (toContinue) {
                    if (nodeid1 == nodeid2) {
                        sameNode(nodeid1);
                        toContinue = false;
                    }
                }

                if (toContinue)
                    lineStream >> next;


                if (toContinue && lineStream.fail()) {
                    toContinue = true;

                } else if (toContinue && !lineStream.fail()) {
                    //there are too many arguments after the valid inputs
                    toContinue = false;
                    tooManyArg();
                    lineStream.clear();
                    lineStream.ignore(1000, '\n');
                }


                if (toContinue) {
                    insertSuccess(name, theResistance, nodeid1, nodeid2);
                    countR = countR + 1;

                    //set values to the resistor class
                    pAllR[(countR - 1)].setResistance(theResistance);
                    pAllR[(countR - 1)].setnamenode(name, nodeID_1, nodeID_2);

                    pAllNode[nodeID_1].addResistor(countR - 1);
                    pAllNode[nodeID_2].addResistor(countR - 1);

                }

            } else if (command == "modifyR") {
                // parse an modifyR command

                lineStream >> name;
                if (lineStream.fail()) {
                    tooFewArg();
                    toContinue = false;
                }
                if (toContinue) {
                    if (checkArgAll(name)) {
                        toContinue = false;
                    }
                }

                if (toContinue) {

                    lineStream >> temp;
                    if (lineStream.fail()) {
                        tooFewArg();
                        toContinue = false;
                    } else if (!checkValidResistance(temp)) {
                        toContinue = false;
                    }

                    lineStream >> next;
                    if (toContinue && lineStream.fail()) {
                        toContinue = true;

                    } else if (toContinue && !lineStream.fail()) {
                        //there are too many arguments after the valid inputs
                        toContinue = false;
                        tooManyArg();
                        lineStream.clear();
                        lineStream.ignore(1000, '\n');

                    }
                }

                if (toContinue) {
                    int I;
                    resistance = temp;
                    theResistance = returnDouble(resistance);
                    modifySucess(name, theResistance);

                    bool found = false;
                    //compare the input argument with the resistor array
                    for (int i = 0; i < MAX_RESISTORS && !found; i++) {
                        if (pAllR[i].getName() == name)
                            I = i;
                        found = true;
                    }


                    if (found)
                        //set the resistance
                        pAllR[I].setResistance(theResistance);
                }


            } else if (command == "printR") {
                // parse an printR command

                lineStream >> name;
                if (lineStream.fail()) {
                    tooFewArg();
                    toContinue = false;
                }

                if (toContinue) {

                    lineStream >> next;
                    if (toContinue && lineStream.fail()) {
                        toContinue = true;

                    } else if (toContinue && !lineStream.fail()) {
                        //there are too many arguments after the valid inputs
                        toContinue = false;
                        tooManyArg();
                        lineStream.clear();
                        lineStream.ignore(1000, '\n');
                    }
                }

                if (toContinue) {
                    if (name == "all") {
                        //print all resistors
                        cout << "Print:" << endl;
                        for (int i = 0; i < MAX_RESISTORS; i++) {
                            if (pAllR[i].getResistance() >= 0) {
                                pAllR[i].print();
                            }
                        }
                    } else {
                        bool found = false;
                        for (int i = 0; i < MAX_RESISTORS && !found; i++) {
                            if (pAllR[i].getName() == name) {
                                found = true;
                                cout << "Print:" << endl;
                                pAllR[i].print();
                            } else
                                //can not find the resistor in the resistor array
                                cout << "Error: resistor " << name << " not found" << endl;
                        }
                    }
                }

            } else if (command == "printNode") {
                // parse an printNode command
                lineStream >> temp;

                if (lineStream.fail()) {
                    tooFewArg();
                    toContinue = false;
                }

                if (toContinue) {

                    lineStream >> next;
                    if (toContinue && lineStream.fail()) {
                        toContinue = true;
                    } else if (toContinue && !lineStream.fail()) {
                        //there are too many arguments after the valid inputs
                        toContinue = false;
                        tooManyArg();
                        lineStream.clear();
                        lineStream.ignore(1000, '\n');
                    }
                }

                if (toContinue) {
                    if (temp == "all") {
                        cout << "Print:" << endl;

                        //print nodes and resistor in order
                        for (int i = 0; i < MAX_NODE_NUMBER; i++) {
                            pAllNode[i].print(i);
                            int tempindex[5];
                            for (int j = 0; j < 5; j++) {
                                tempindex[j] = pAllNode[i].getResistorArray(j);
                            };
                            putinorderforprintnode(tempindex);
                            for (int k = 0; k < 5; k++) {
                                if (tempindex[k] != -1) {
                                    cout << "  ";
                                    pAllR[tempindex[k]].print();

                                }
                            }
                        }
                    }
                }


                if (toContinue) {
                    if (checkValidNodeid(temp, MAX_NODE_NUMBER)) {
                        nodeid = temp;
                        toContinue = true;
                    } else toContinue = false;
                }

                if (toContinue) {
                    {
                        //print nodes in order
                        cout << "Print:" << endl;
                        cout << "  ";
                        int nodeID_ = returnInt(nodeid);
                        pAllNode[nodeID_].print(nodeID_);
                        int tempindex[5];
                        for (int j = 0; j < 5; j++) {
                            tempindex[j] = pAllNode[nodeID_].getResistorArray(j);
                        };
                        putinorderforprintnode(tempindex);
                        for (int k = 0; k < 5; k++) {
                            if (tempindex[k] != -1)
                                pAllR[tempindex[k]].print();
                        }
                    }
                }


            } else if (command == "deleteR") {
                // parse an deleteR command

                lineStream >> temp;

                if (lineStream.fail()) {
                    tooFewArg();
                    toContinue = false;
                }

                if (toContinue && checkDeletAll(temp)) {

                    lineStream >> next;
                    if (lineStream.fail()) {
                        toContinue = true;
                    } else if (toContinue && !lineStream.fail()) {
                        //there are too many arguments after the valid inputs
                        toContinue = false;
                        tooManyArg();
                        lineStream.clear();
                        lineStream.ignore(1000, '\n');
                    }
                    if (toContinue) {
                        deletAllResistor();
                        toContinue = false;
                    }
                }

                lineStream >> next;
                if (toContinue && lineStream.fail()) {
                    toContinue = true;

                } else if (toContinue && !lineStream.fail()) {
                    //there are too many arguments after the valid inputs
                    toContinue = false;
                    tooManyArg();
                    lineStream.clear();
                    lineStream.ignore(1000, '\n');
                }

                if (toContinue) {
                    name = temp;
                    deletResistor(name);
                }
            } else
                //user input an invalid command
                cout << "Error: invalid command" << endl;

            //user input nothing

        } else
            cout << "Error: invalid command" << endl;


        toContinue = true;
        cout << ">";
        getline(cin, line);
    }
    // End input loop until EOF.

}

bool checkArgAll(string argument) {

    if (argument == "all") {
        cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
        return true;
    } else {
        return false;
    }
}
//display error of too few input arguments
void tooFewArg() {
    cout << "Error: too few arguments" << endl;
}

void sameNode(string nodeid) {
    cout << "Error: both terminals of resistor connect to node " << nodeid << endl;
}

void insertSuccess(string name, double theResistance, string nodeid1, string nodeid2) {

    cout << fixed << setprecision(2) << "Inserted: resistor " << name << " "
            << theResistance << " Ohms " << nodeid1 << " -> "
            << nodeid2 << endl;
}

void modifySucess(string name, double theResistance) {
    cout << fixed << setprecision(2) << "Modified: resistor " << name << " to " << theResistance << " Ohms" << endl;
}

//this function checks if the input argument is 'all'
bool checkPrintAll(string all) {

    if (all == "all")
        return true;
    else
        return false;
}

//this function checks if the input argument is 'all'
bool checkDeletAll(string all) {
    if (all == "all") {
        return true;
    } else
        return false;
}

void printAllResistor() {
    cout << "Print: all resistors" << endl;
}

void printAllNode() {
    cout << "Print: all nodes" << endl;
}

void printResistor(string name) {
    cout << "Print: resistor " << name << endl;
}

void printNode(string nodeid) {
    cout << "Print: node " << nodeid << endl;
}
//display error of too many input arguments
void tooManyArg() {
    cout << "Error: too many arguments" << endl;
}

void deletResistor(string name) {
    cout << "Deleted: resistor " << name << endl;
}

void deletAllResistor() {
    cout << "Deleted: all resistors" << endl;
}

//This function checks if a input nodeid valid

bool checkValidNodeid(string nodeid, int MAX_NODE_NUMBER) {

    int checkValid;
    string next;
    stringstream temp(nodeid);
    temp >> checkValid;

    if (!temp.fail()) {
        temp >> next;
        if (temp.fail()) {
            if (checkValid > MAX_NODE_NUMBER || checkValid < 0) {
                cout << "Error: node " << nodeid << " is out of permitted range 0-" << MAX_NODE_NUMBER << endl;
                return false;
            } else
                return true;
        }
    } else {
        //The input nodeid is not an integer
        cout << "Error: invalid argument" << endl;
        return false;
    }

}

//This function checks if a input resistance valid

bool checkValidResistance(string resistance) {

    double checkValid;
    string next;
    stringstream temp(resistance);
    temp >> checkValid;
    if (!temp.fail()) {
        temp >> next;
        if (temp.fail()) {
            if (checkValid < 0) {
                cout << "Error: negative resistance" << endl;
                return false;
            } else {
                theResistance = checkValid;
                return true;
            }
        }
    } else {
        cout << "Error: invalid argument" << endl;
        return false;
    }
}

//this function transfers the type of a string to a integer
int returnInt(string nodeid) {
    int returnInt;
    stringstream intString(nodeid);
    intString >> returnInt;
    return returnInt;
}

//this function transfers the type of a string to a double
double returnDouble(string resistance) {
    double returnDouble;
    stringstream intString(resistance);
    intString >> returnDouble;
    return returnDouble;
}

//checks the inputted MaxVal is positive
bool checkValidMaxVal(int MaxVal) {
    if (MaxVal <= 0) {
        return false;
    } else
        return true;

}

//display error of input maxVal
void invalidMaxVal() {
    cout << "Error: maxVal arguments must be greater than 0" << endl;
}

//set up a new network
void newNetwork(int MAX_NODE_NUMBER, int MAX_RESISTORS) {
    cout << "New network: max node number is " << MAX_NODE_NUMBER << "; " << "max resistors is " << MAX_RESISTORS << endl;
}

//display error of trying to insert a resistor has the same name
void sameResistorNameError(string name) {

    cout << "Error: resistor " << name << " already exists" << endl;
}

//this function print nodes in order
void putinorderforprintnode(int *x) {
    for (int i = 0; i < 4; i++) {
        if (*(x + i) > *(x + i + 1)) {
            int temp = *(x + i);
            *(x + i) = *(x + i + 1);
            *(x + i + 1) = temp;
        }
    }
}
