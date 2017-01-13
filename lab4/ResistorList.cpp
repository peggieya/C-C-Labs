#include "ResistorList.h"


ResistorList::ResistorList() {
    numRes = 0;
    head = NULL;
}

 Resistor* ResistorList:: getHead() {
       return head;
 }
 
 int ResistorList:: getNumRes() {
     return numRes;
 }
  
void ResistorList:: addResistor(string name_, double resistance_, int endpoints_[]) {
    Resistor* prev = NULL;
    Resistor* cur = head;
    
    while (cur!= NULL) {
        prev = cur;
        cur = cur-> next;
    }
    
    Resistor* newResistor = new Resistor ( name_, resistance_,  cur, endpoints_);
    if (prev != NULL)
        prev->next = newResistor;
    else
        head = newResistor;
    
    numRes++;
}

Resistor* ResistorList:: searchResistor( string name) {
    Resistor *ptr;

    for(ptr = head; ptr !=NULL; ptr = ptr->next) {
        if (name == ptr->name)
            return ptr;
    }
    
    return (NULL);
}

int ResistorList::delResistor(string name) {
    Resistor *ptr, *prev = NULL;

    
    for (ptr = head; ptr!= NULL; ptr = ptr->next) {
        if (name == ptr->getName()) {
            if (prev != NULL)
                prev->next = ptr->next;
            else 
                head = ptr->next;
        delete ptr;
        numRes --; 
        return (1); 
        }
    prev = ptr;
    }
    
    return 0;
}
  
void ResistorList:: delAllResistor() {
    Resistor *ptr = head;

    while (head != NULL) {
        head = head->next;
        delete ptr;
        ptr = head;
    }
    numRes = 0;
}
  
 void ResistorList::printAllResistor() {
     Resistor *cur;
     
     for (cur = head; cur != NULL; cur = cur->next) {
         (*cur).print();
     }
 }
 



