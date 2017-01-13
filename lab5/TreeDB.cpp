
#include "TreeDB.h"
#include <cstdlib>

using namespace std; 

TreeDB::TreeDB() {
    root = NULL;
    probesCount = 0;
}

TreeDB::TreeDB(const TreeDB& tRight) {}

TreeDB::~TreeDB() {}

DBentry* TreeDB::findNode(string name, TreeNode* node){
    probesCount++;
    if (node == NULL){
        probesCount = 0; 
        return NULL;
    }

    if (node->getEntry()->getName() == name)
        return node->getEntry();
    if (node->getEntry()->getName() > name){
        return findNode (name, node->getLeft());
    }
    if (node->getEntry()->getName() < name){
       
        return findNode (name, node->getRight());
    }
    return NULL;
}

bool TreeDB::insert(DBentry* newEntry){
    
    if (root == NULL)//the tree is empty
    {
        root = new TreeNode (newEntry);
        root->setLeft(NULL);
        root->setRight(NULL);
        return true;
    }
    //Helper function to facilitate the recursion
    return insertNode(newEntry, root);
}

bool TreeDB::insertNode(DBentry* entry, TreeNode *node){
    
    if (entry->getName() == node->getEntry()->getName()){
        delete entry;
        return false;
    }
    if (entry->getName() < node->getEntry()->getName()){
       
        if (node->getLeft() == NULL)
		{
            node->setLeft(new TreeNode(entry));
            return true;
        }
        else{
            return insertNode(entry, node->getLeft());
        }
    }
    else{
        if (node->getRight() == NULL){
            node->setRight(new TreeNode(entry));
            return true;
        }
        else{
            return insertNode(entry, node->getRight());
        }
    }
}

void TreeDB::remove(string name){
    TreeNode *node = removeNode(name, root);
}

DBentry* TreeDB::find(string name){
	probesCount=0;
    return findNode(name, root);
}

int TreeDB::countActiveNode(TreeNode* node) const{
    if(node == NULL) 
        return 0;
    else if (node->getLeft() == NULL && node->getRight() == NULL)
       
        if(node->getEntry()->getActive())
            return 1;
        else 
            return 0;
    else{
        if (node->getEntry()->getActive())
            return countActiveNode(node->getLeft()) + countActiveNode(node->getRight()) + 1;
        return countActiveNode(node->getLeft()) + countActiveNode(node->getRight());
    }
}

DBentry* TreeDB::findLeft(TreeNode* node) const{
    if (node->getLeft() == NULL)
        return node->getEntry();
    return findLeft(node->getLeft());
}

void TreeDB::print() const{
    printNode (root);
}

void TreeDB::printProbes(){
    if (probesCount == 0)
        return;
    cout << probesCount << endl;
    probesCount = 0;
}

//clear the entire tree
void TreeDB::clearTree(){
        if (root != NULL)
        removeAllNode(root);
    root = NULL;
    
}

void TreeDB::removeAll(){
    if (root != NULL)
        //Helper function to facilitate the recursion
        removeAllNode(root);
    cout << "Success" << endl;
    root = NULL;
}

//helper function
void TreeDB::removeAllNode(TreeNode* node){

    if (node == NULL){
        return;
    }
    removeAllNode(node->getLeft());
    removeAllNode(node->getRight()); 
    delete node;
}

//remove a certain node with input name
TreeNode* TreeDB::removeNode(string name, TreeNode* node){
 
    if (node == NULL){ 
        cout << "Error: entry does not exist" << endl;
        return NULL;
    }
    if (name < node->getEntry()->getName()){
       
        node->setLeft(removeNode(name, node->getLeft()));
        return node;
    }
    if (name > node->getEntry()->getName()){
      
        node->setRight(removeNode(name, node->getRight()));
        return node;
    }
  
    if (node->getLeft() != NULL){
        node->setEntry(findMax(node->getLeft()));
        node->setLeft(removeNode(node->getEntry()->getName(), node->getLeft()));
        return node;
    }
  
    if (node->getRight() != NULL){
        node->setEntry(findLeft(node->getRight()));
        
        node->setRight(removeNode(node->getEntry()->getName(), node->getRight()));
        return node;
    }
    delete node;
    
    cout << "Success" << endl;
    return NULL;
}

void TreeDB::printNode(TreeNode* node) const{
    if (node == NULL) 
        return;
    printNode(node->getLeft());
    cout << *(node->getEntry());
    printNode(node->getRight());
}
void TreeDB::countActive() const{
    int count;
    count = countActiveNode(root);
    cout << count << endl;    
}

//find the maximum node(right most)
DBentry* TreeDB::findMax(TreeNode* node) const{
    if (node->getRight() == NULL)
        return node->getEntry();
    return findMax(node->getRight());
}




