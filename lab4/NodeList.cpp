#include "NodeList.h"

NodeList:: NodeList() {
    head = NULL;
}
Node* NodeList:: searchOrInsert(int id) {
    
    Node* cur = head;
    Node* prev = NULL;

    while ( cur && id > cur->nodeId) {
        prev = cur;
        cur = cur->next;
    }
 
    if (head == NULL) {
        head = new Node(id, cur);
        return head;
    }
	
    if (cur != NULL && cur->nodeId == id)
        return cur;

    if (prev !=NULL) {
        prev->next = new Node(id, cur);
        return prev->next;
    }
    
    head = new Node(id, cur);
    return head;
}

void NodeList:: printNodes() {
	
    Node* cur = head;

    while (cur != NULL) {
        if (cur->resistorList.getNumRes() != 0)
        	cur->print();
        cur = cur->next;
    }
}

void NodeList:: delAllNodes() {
     Node *ptr = head;
       
       while (head != NULL) {
           head = head->next;
           delete ptr;
           ptr = head;
       }  
}
           
Resistor* NodeList:: searchResistor(string name) {
    Node* cur = head;
    Resistor* tmp1 = NULL;

    while (cur!= NULL && tmp1 == NULL) {
        tmp1 = cur->getResistorList().searchResistor(name); 
        cur = cur->next;
    }
    return tmp1;
}
    
int NodeList:: modifyResistor(string name, double &oldRes, double newRes) {
    Node* cur = head;
    Resistor* tmp1 = NULL;
    Resistor* tmp2 = NULL;

    while (cur!= NULL && tmp1 == NULL) {
        tmp1 = cur->getResistorList().searchResistor(name); 
        cur = cur->next;
    }
    while (cur!= NULL && tmp2 == NULL ) {
        tmp2 = cur->getResistorList().searchResistor(name); 
        cur = cur->next;
    }
    if (tmp1 == NULL || tmp2 == NULL)
        return 0;
    else {
        oldRes = tmp1->getResistance();
        tmp1->setResistance(newRes);
        tmp2->setResistance(newRes);
        return 1;
    }
}   
int NodeList:: is_exist_Resistor(string name){
	Node* cur = head;
    Resistor* tmp1 = NULL;
   

    while (cur!= NULL && tmp1 == NULL) {
        tmp1 = cur->getResistorList().searchResistor(name); 
        if(tmp1 != NULL)
        	return 1;
        cur = cur->next;
    }
   	return 0;
}     
int NodeList::delResistor(string name) {
    Node* cur = head;
    Node* tempv=NULL;
    int tmpDeleted, status;

    while (cur!= NULL ) {
        tmpDeleted =  cur->getResistorList().delResistor(name);
        
        
        if (tmpDeleted) {
            status = 1; 
            if(cur->getResistorList().getHead()==NULL ){
	        	tempv = cur->next;
				delete cur;
				cur = tempv;	
	            continue;
        	} 
        }
        cur = cur->next;
    }
    return status;
}
    
void NodeList:: delAllResistor(){
	
    Node* cur = head;
    while (cur!= NULL) {
        cur->getResistorList().delAllResistor();
        cur = cur->next;
    }
    
    cur = head; 
    while (head != NULL) {
        head = head->next;
        delete cur;
        cur = head;
    }
    
    head=NULL;
}
int NodeList:: checkOneSetV() {
    
    Node * cur = head;
    int flag = 0;
    while (cur != NULL) {
    	
        if (cur->flag)
            flag = 1;
        cur = cur->next;
    }
    return flag;
}

void NodeList:: solve() {
    int flag = 0;

    while (!flag) {
        flag = 1;
        Node* cur = head;
        while(cur != NULL ) {

            if ( !(cur->flag) ) {

                double newVoltage = solveHelp(cur);
                double change = abs (newVoltage - cur->getVoltage());
                cur->setVoltage(newVoltage);
            
                // unless any change in voltage > 0.0001, flag is kept '1'
                if (change > CHANGE)
                    flag = 0;
            }
            cur = cur->next;
        }
    }

    Node *cur = head;
    while (cur != NULL) {
        //print if the node's resistorList has more than one resistor
        if (cur->getResistorList().getNumRes() != 0)
                cout << " Node "<< cur->nodeId << ": "<<cur->voltage<< " V"<<endl;

        cur = cur->next;
    }
}

double NodeList:: solveHelp(Node * tmp) {
    
       Resistor *ptr = tmp->getResistorList().getHead();
       int nodeid = tmp->nodeId;
       
       double val1 = 0; 
       double val2 = 0; 
       
       while (ptr != NULL) {
            
          
            if (ptr->getEndpoints(0) == nodeid)
                val2 = val2 + (this->searchOrInsert(ptr->getEndpoints(1))->voltage)/ptr->getResistance();

            else if (ptr->getEndpoints(1) == nodeid)
                val2 = val2 + (this->searchOrInsert(ptr->getEndpoints(0))->voltage)/ptr->getResistance();
            
            
            val1 = val1 + (1/(ptr->getResistance()));
            ptr = ptr->getNext();
       }
      
       return ((1/val1)*val2);
}

