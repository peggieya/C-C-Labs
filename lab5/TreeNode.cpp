
#include "TreeNode.h"

TreeNode::TreeNode(DBentry* newEntry){
    left = NULL;
    right = NULL;
    entryPtr = newEntry;
}
void TreeNode::setLeft(TreeNode* newLeft){
    left = newLeft;
}

void TreeNode::setRight(TreeNode* newRight){
    right = newRight;
}

TreeNode::TreeNode(const TreeNode& orig) {
}

TreeNode::~TreeNode() {

    delete entryPtr;
    left = NULL;
    right = NULL;

}

//member functions to access the private members
TreeNode* TreeNode::getLeft() const{
    return left;
}

TreeNode* TreeNode::getRight() const{
    return right;
}

DBentry* TreeNode::getEntry() const{
    return entryPtr;
}

void TreeNode::setEntry(DBentry* newEntry){
    entryPtr->setName(newEntry->getName());
    entryPtr-> setIPaddress(newEntry->getIPaddress());
    entryPtr->setActive(newEntry->getActive());
}



