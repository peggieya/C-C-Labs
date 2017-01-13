
#ifndef TREEDB_H
#define	TREEDB_H
#include "TreeNode.h"

class TreeDB {
public:
    TreeDB();
    TreeDB(const TreeDB& tRight);
    virtual ~TreeDB();
   
    DBentry* find (string name); 
    void remove (string name); 
    bool insert(DBentry* newEntry); 
    void clear();
    void printProbes();
    DBentry* findLeft(TreeNode* node) const;
    DBentry* findMax(TreeNode* node) const;
    void print() const;
    void countActive () const;
    void removeAll();
    void clearTree();
    
private:
    TreeNode *root;
    int probesCount;
    int activeCount;
    DBentry* findNode (string name, TreeNode *node); 
    bool insertNode(DBentry *entry, TreeNode *node); 
    void printNode(TreeNode* node) const; 
    TreeNode* removeNode (string name, TreeNode *node); 
    void removeAllNode(TreeNode* node);
    int countActiveNode (TreeNode* node) const;
};

#endif	
