
#ifndef TREENODE_H
#define	TREENODE_H
#include "DBentry.h"

class TreeNode {
public:
    TreeNode(DBentry* newEntry);
    TreeNode(const TreeNode& orig);
    virtual ~TreeNode();
    
    void setLeft (TreeNode *newLeft);
    void setRight (TreeNode *newRight);
    void setEntry (DBentry* newEntry);
   
    TreeNode* getLeft() const;
    TreeNode* getRight() const;
    DBentry* getEntry() const;
    
private:
    DBentry *entryPtr;
    TreeNode *left, *right;
};

#endif	
