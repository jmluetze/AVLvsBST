/*
 * Binary Search Tree structure implementation by Jonathan Luetze
 *
 *    methods: *Root, creates a new tree root
 *           : *Current, creates a new node
 *
 *           : build, inserts value passed in as a new treeNode into the BST
 *           : whatChild, returns the side of the parent that the node is on
 *           : getHeight, calculates the height of the tree
 *
 *           : *getPredecessor, returns predecessor of current node
 *           : *getSuccessor, returns successor of current node
 *
 *           : leafDelete, deletes the node after AVL deleteFixup method
 *           : *swapToLeaf, swaps the passed in node to the leaf before AVL delete
 *           : isLeaf, determines if the current node is a leaf or not
 *
 *           : *findTree, finds a node in the tree and returns it
 *           : udateTree, updates frequency of node or adds or deletes it
 */

#include "BinarySearchTree.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

struct treeNode* Root(char * x)
{
    struct treeNode* root = (struct treeNode*)malloc(sizeof(struct treeNode));

    root->value = x;
    root->left = root->right = NULL;
    root->parent = root;
    root->leftHeight = root->rightHeight = root->avlHeight = 0;
    root->frequency = 1; treeSize = 1;
    return root;
}

struct treeNode* Current(char * x)
{
    struct treeNode* Curr = (struct treeNode*)malloc(sizeof(struct treeNode));
    
    Curr->value = x;
    Curr->left = Curr->right = Curr->parent = NULL;
    Curr->frequency = 1; treeSize++;
    return Curr;
}

void build(char * x,struct treeNode *root)
{
    if ((strcmp(x,root->value) < 0) && (root->left != NULL))
        {build(x, root->left);}
    
    else if ((strcmp(x,root->value) < 0) && !root->left)
    {
        struct treeNode* curr = Current(x);
        
        root->left = curr;
        curr->parent = root;
    }
    else if ((strcmp(x,root->value) > 0) && root->right)
            {build(x, root->right);}
    
    else if ((strcmp(x,root->value) > 0) && !root->right)
    {
        struct treeNode* curr = Current(x);
        
        root->right = curr;
        curr->parent = root;
    }
}

char whatChild(struct treeNode *child)
{
    char isChild;
         if (child->parent == child)        {isChild = 'X';}
    else if (child->parent->left == child)  {isChild = 'L';}
    else                                    {isChild = 'R';}
    return isChild;
}

int getHeight(struct treeNode *root)
{
    if (root == NULL) {return 0;}
    else
    {
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);
        
        if (leftHeight > rightHeight)   {return(leftHeight+1);}
        else                            {return(rightHeight+1);}
    }
}

struct treeNode * getPredecessor(struct treeNode *root)
{
    root = root->left;
    while (root->right != NULL) {root = root->right;}
    return root;
}

struct treeNode * getSuccessor(struct treeNode *root)
{
    root = root->right;
    while (root->left != NULL) {root = root->left;}
    return root;
}

void leafDelete(struct treeNode *ntbd)
{
    char leftOrRight = whatChild(ntbd); treeSize--;
    
         if (leftOrRight == 'L') {ntbd->parent->left = NULL;}
    else if (leftOrRight == 'R') {ntbd->parent->right = NULL;}
    else if (leftOrRight == 'X') {ntbd->parent = NULL;}
}

struct treeNode * swapToLeaf(struct treeNode *ntbd, int choice)
{
    struct treeNode *predOrSucc = findTree(ntbd->value,ntbd);
    
    if (ntbd->left == NULL &&  ntbd->right == NULL && choice == 1) // no kids
    {
        leafDelete(ntbd); return predOrSucc;
    }
    if(ntbd->left != NULL || ntbd->right != NULL)  // has one or both children
    {
        if (ntbd->left == NULL) {predOrSucc = getSuccessor(ntbd);}
        else                    {predOrSucc = getPredecessor(ntbd);}

        char * tempValue = ntbd->value;
        ntbd->value = predOrSucc->value;
        ntbd->frequency = predOrSucc->frequency;
        predOrSucc->value = tempValue;
        
        return swapToLeaf(predOrSucc,choice);
    }
    else
    {predOrSucc = ntbd; return ntbd;} // return to fixup
}

int isLeaf (struct treeNode *root)
{
    if (root->left == NULL && root->right == NULL) {return 1;}
    else                                           {return 0;}
}

struct treeNode * findTree(char * x, struct treeNode *root)
{
    if ((strcmp(x,root->value) == 0))
    {
        return root;
    }
    else if ((strcmp(x,root->value) > 0) && root->right)
            {return findTree(x,root->right);}
    else if ((strcmp(x,root->value) < 0) && root->left)
            {return findTree(x,root->left);}
    else    {return 0;}
}

void updateTree(char * x, struct treeNode *root, int *inTree,int iOrD)
{
     if ((strcmp(x,root->value) == 0))
     {
        *inTree = 1;
              if (iOrD == 2) {printf("%s %d\n",root->value,root->frequency);} // return found word's frequency
         else if (iOrD == 1) {root->frequency += 1;} // inserting value -> increasing frequency
         else if (iOrD == 0 || iOrD == 3)            // deleting  value -> decreasing frequency
         {
             root->frequency -= 1;
             if (root->frequency == 0 && iOrD == 0) {swapToLeaf(root,1);}
         }
     }
    else if ((strcmp(x,root->value) > 0) && root->right)
            {updateTree(x,root->right,inTree,iOrD);}
    else if ((strcmp(x,root->value) < 0) && root->left)
            {updateTree(x,root->left,inTree,iOrD);}
}
