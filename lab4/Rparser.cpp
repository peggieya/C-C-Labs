
#include "Rparser.h"

NodeList* drawList;

Rparser::Rparser() {
   
}
int Rparser::judge_same_name( string name){
	if( nodeList.is_exist_Resistor(name) ){
		cout<<"Error: resistor " <<name<<" already exists "<<endl;
		return 1;
	}
	return 0;
}

int Rparser:: excute() {
    
    string line, command;
    
    cout << ">";
    getline(cin, line); 
    
    while (!cin.eof()) {
    stringstream lineStream(line);
    if ( line != "") {   
            lineStream >> command;
            
            if (command == "insertR") {
                insertR(lineStream);
            }
            else if (command =="modifyR") {
                modifyR(lineStream);
            }
               else if (command == "setV") {
                setV(lineStream);
            }
           
            else if (command == "unsetV") {
                unsetV(lineStream);
            }
            
            else if (command == "solve") {
                solve(lineStream);
            }
            else if (command== "printR" ) {
                printR(lineStream);
            }
            else if (command=="printNode" ) {
                printNode(lineStream);
            }
            
            else if (command=="deleteR") {
                deleteR(lineStream);
            }
            else {
                cout << "Error: invalid command" << endl;
            }
        }
       
        arrange(lineStream); 
        cout << ">";   
        getline (cin, line);   
    } 
    
    
  
   stringstream stream(" end");
   deleteR (stream);
   nodeList.delAllNodes();
    
    return 0;
}

// Removing  the spaces before the next input
void Rparser:: arrange (stringstream & commandStream) {
    while (commandStream.peek() == 13 || commandStream.peek() == '\t' || commandStream.peek() == ' ') {
        commandStream.get();
    }
}

// Test inputs are valid or not  
int Rparser:: checkCommand(stringstream &commandStream ) {
    
    
   
    if (commandStream.fail()  ) {
        
        commandStream.clear();
        commandStream.ignore(200000000, '\n');
        cout << "Error: invalid argument"<< endl;
    
        return 1;
    }
    
    else if (commandStream.peek() != ' ' && commandStream.peek() != '\n' && commandStream.peek() != '\t' && commandStream.peek() != -1) {
        
        commandStream.clear();
        commandStream.ignore(200000000, '\n');
        cout << "Error: invalid argument"<< endl;
        return 1;
    }
    return 0;
}

//whether the resistance  is negative or not
int Rparser:: checkNegative (double resistance) {
    if (resistance < 0) {
        cout << "Error: negative resistance" << endl;
        return 1;
    }
    return 0;
    
}

//Testing whether the user input the name of resistance as "all"
int Rparser:: checkNameAll (string resistor) {
    if (resistor == "all") {
        cout << "Error: resistor name cannot be the keyword \"all\""<< endl;
        return 1;
    }
    return 0;
}

// Testing if the two nodes have the same value
int Rparser:: judgeNode (int left, int right) {
    if (left == right) {
       cout<< "Error: both terminals of resistor connect to node "<< right << endl;
       return 1;
    }
    
    return 0;
}


int Rparser:: judgeArgsHigh(stringstream & commandStream) {
    char c = commandStream.get();
    
    if (commandStream.peek() != -1 && commandStream.peek() != '\n' && commandStream.peek() != '\t' && commandStream.peek() != ' ') {
        cout << "Error: too many arguments" << endl;
        return 1;
    }
    return 0;
}

int Rparser:: judgeArgsLow (stringstream & commandStream) {
    char c = commandStream.get();
    
    if (commandStream.peek() == -1){
        
        cout << "Error: too few arguments" << endl;
        commandStream.clear(); 
        return 1;
    }
    return 0;
}

void Rparser:: insertR (stringstream &commandStream) 
{
    string name;
    int nodeId1, nodeId2;
    double resistance;

    if (judgeArgsLow (commandStream)) 
        return;
    
    commandStream >> name;
        
    if (checkNameAll(name)) 
        return;
   	if(judge_same_name(name) )
   		return ;
    if (judgeArgsLow (commandStream)) 
        return;
    
    commandStream >> resistance;
    
    if (checkCommand(commandStream))
        return;
    
    if (checkNegative (resistance))
        return;
    
    if (judgeArgsLow (commandStream)) 
        return;
               
    commandStream >> nodeId1;
    
    if (checkCommand(commandStream))
        return;
    
    if (judgeArgsLow (commandStream)) 
        return;
    
    commandStream >> nodeId2;
    
    if (checkCommand(commandStream))
        return;
                   
    if (judgeNode (nodeId1, nodeId2))
        return;
    
    if (judgeArgsHigh (commandStream))
        return;
    
    cout << "Inserted: resistor " << name << " " << resistance << " Ohms "<< nodeId1 << " -> " << nodeId2 <<endl;
  
    int points[] = {nodeId1, nodeId2};
    
    Node* tmp1 = nodeList.searchOrInsert(nodeId1);
    
	Node* tmp2 = nodeList.searchOrInsert(nodeId2);
    
    tmp1->addResistor(name, resistance, points);
    
    tmp2->addResistor(name, resistance, points);
}

void Rparser:: modifyR(stringstream &commandStream) 
{
    string name;
    double resistance, oldRes;
    int index;

    if (judgeArgsLow (commandStream)) 
        return;
    
    commandStream >> name;
        
    if (checkNameAll(name)) 
        return;
    
    if (judgeArgsLow (commandStream)) 
        return;
    
    commandStream >> resistance;
               
    if (checkCommand(commandStream))
        return;

    if (checkNegative (resistance))
        return;
                    
    if (judgeArgsHigh (commandStream))
        return;
    
    if (nodeList.modifyResistor(name, oldRes, resistance)) {
         cout << "Modified: resistor " << name << " from " << oldRes <<" Ohms to "<< resistance << " Ohms" << endl;
        return;
    }
    cout << "Error: resistor " << name << " not found"<< endl;
}

void Rparser::printR(stringstream &commandStream) 
{
    string arg;
    int index;
    
    if(judgeArgsLow(commandStream)) 
        return;
    
    commandStream >> arg; 
    if (checkCommand(commandStream)) 
        return;
            
    if (judgeArgsHigh(commandStream)) 
        return;

    Resistor* tmp = nodeList.searchResistor(arg);
    if (tmp != NULL) {
        cout << "Print:" << endl;
        tmp->print();
        return;
    }    
    cout << "Error: resistor " << arg << " not found"<< endl;
}

void Rparser::printNode(stringstream &commandStream)
{
    int arg1 = 0;   
    string arg2; 
    int printNode = 1; 
                    
    if (judgeArgsLow(commandStream)) 
        return;
    
    commandStream >> arg1;
      
    if (commandStream.fail()) { 
        commandStream.clear();
        commandStream >> arg2;
        printNode = 0;
    }
    if(checkCommand(commandStream)) 
        return;
    if (judgeArgsHigh(commandStream))
        return;   
    if (printNode) {
        cout << "Print:" << endl;
        (nodeList.searchOrInsert(arg1))->print();
    }
    else if (arg2 == "all") {
        cout << "Print:" << endl;
        nodeList.printNodes();
    }
    else
        cout << "Error: invalid argument" << endl;
}
void Rparser::deleteR (stringstream &commandStream) 
{
    string arg; 
    int index;
    int status = 0;
  
    if (judgeArgsLow (commandStream))
        return;
    
    commandStream >> arg;
    
    if (judgeArgsHigh(commandStream)) 
        return;
    
    if (arg == "all")  {
        nodeList.delAllResistor();
        cout << "Deleted: all resistors" << endl;    
        return;
    }
    
    if (arg == "end") {
        nodeList.delAllResistor();
        return;
    }
    status = nodeList.delResistor(arg);

    if (status) {
        cout << "Deleted: resistor "<< arg << endl;
        return;
    }       
    cout << "Error: resistor " << arg << " not found"<< endl; 
}

void Rparser::setV(stringstream& commandStream)
{
    int nodeId;
    double voltage;
    
    if (judgeArgsLow(commandStream))
        return;
    
    commandStream >> nodeId;
    
    if (checkCommand(commandStream))
        return;
    
    if (judgeArgsLow(commandStream))
        return;
    
    commandStream >> voltage;
    
    if (checkCommand(commandStream))
        return;
    
    if (judgeArgsHigh(commandStream))
        return;

    nodeList.searchOrInsert(nodeId)->set(voltage);
    cout << "Set: node " << nodeId << " to "<< voltage << " Volts" << endl;
}

void Rparser:: unsetV (stringstream& commandStream)
{
    int id;
    
    if (judgeArgsLow(commandStream))
        return;
    
    commandStream >> id;
    
    if (checkCommand(commandStream))
        return;
    
    if (judgeArgsHigh(commandStream))
        return;
    
    nodeList.searchOrInsert(id)->unSet();
    cout << "Unset: the solver will determine the voltage of node " << id << endl;
}

void Rparser:: solve(stringstream& commandStream) {
	
    if (judgeArgsHigh(commandStream))
        return;
    
    if (!(nodeList.checkOneSetV())) {
        cout << "Error: no nodes have their voltage set" << endl;
         return;
    }
    cout << "Solve: "<< endl;
    nodeList.solve(); 
}
