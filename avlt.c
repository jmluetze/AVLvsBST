/*
 * AVL Tree structure implementation by Jonathan Luetze
 *
 *    methods: newAVLT, creates a new tree root
 *           : isLinear, determines if node, parent and granparent are linear
 *           : *gParent, returns grandparent
 *           : *sibling, returns sibling
 *
 *           : *rotate, determins direction of rotation
 *           : *rotateLeft, rotates node with subtrees left
 *           : *rotateRight, rotates node with subtrees right
 *
 *           : setBalance, calculates height of AVL tree
 *           : balance, calculates balance of node
 *
 *           : isFavorite, checks if child is the favorite
 *           : *favorite, returns the favorite
 *
 *           : insertFixUp, fixes AVL tree after BST insert operation
 *           : deleteFixUp, fixes AVL tree after delete operation
 *
 *           : levelOrderTraversal, prints tree in BFS (or Level-Order)
 *           : printNode, prints a node
 */

#include "avlt.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

struct avl * newAVLT(struct treeNode *root)
{
    avl *a = malloc(sizeof(avl));
    a->root = root;
    a->count = 1;
    return a;
}

int isLinear (struct treeNode *n)
{
    if(gParent(n) != n->parent) // checks for root
    {
        if(whatChild(n) == whatChild(n->parent)) {return 1;}
        else                                     {return 0;}
    }
    return 0;
}

struct treeNode *gParent (struct treeNode *n) // returns Grandparent
{
    return n->parent->parent;
}

struct treeNode *sibling (struct treeNode *n) //returns sibling
{
    if(whatChild(n) == 'L')    {return n->parent->right;}
    else                       {return n->parent->left;}
}

struct avl * rotate (struct treeNode *n, struct avl *a) //specifies rotation
{
    if (whatChild(n) == 'L')    {a = rotateRight(n,a);}
    else                        {a = rotateLeft(n,a);}
    return a;
}

struct avl * rotateLeft(struct treeNode *n, struct avl *a)
{
    int rootFlag = 0; char parentTypeLR = whatChild(n->parent);
    struct treeNode *GP  = gParent(n);
    
    if (n->left == NULL) {n->parent->right = NULL;}
    if (n->left != NULL)
    {
        n->parent->right = n->left;
        n->left->parent = n->parent;
    }
    
    n->left = n->parent;
    if (GP == n->left) {n->parent = n; a->root = n;rootFlag = 1;} // parent was root
    else {n->parent = GP;}
    n->left->parent = n;
    
         if(rootFlag == 0 && parentTypeLR == 'R') {GP->right = n;}
         if(rootFlag == 0 && parentTypeLR == 'L') {GP->left = n;}
    else if(rootFlag == 1) {GP = a->root;}
    
    return a;
}

struct avl * rotateRight(struct treeNode *n, struct avl *a)
{
    int rootFlag = 0;  char parentTypeLR = whatChild(n->parent);
    struct treeNode *GP  = gParent(n);
    
    if (n->right == NULL) {n->parent->left = NULL;}
    if (n->right != NULL)
    {
        n->parent->left = n->right;
        n->right->parent = n->parent;
    }
    
    n->right = n->parent;
    if (GP == n->right) {n->parent = n; a->root = n;rootFlag = 1;} // parent was root
    else {n->parent = GP;}
    n->right->parent = n;
    
         if(rootFlag == 0 && parentTypeLR == 'R') {GP->right = n;}
         if(rootFlag == 0 && parentTypeLR == 'L') {GP->left = n;}
    else if(rootFlag == 1) {GP = a->root;}
    
    return a;
}

void setBalance(struct treeNode *n)
{
    if (n->left != NULL)  {n->leftHeight = getHeight(n->left);}
    else                  {n->leftHeight = 0;}
    
    if (n->right != NULL) {n->rightHeight = getHeight(n->right);}
    else                  {n->rightHeight = 0;}
    
    if (n->rightHeight > n->leftHeight) {n->avlHeight = n->rightHeight + 1;}
    else                                {n->avlHeight = n->leftHeight + 1;}
}

int balance(struct treeNode *n)
{
    int balanceOfNode = n->leftHeight - n->rightHeight;
    
         if (balanceOfNode < 0) {balanceOfNode = -1;}
    else if (balanceOfNode > 0) {balanceOfNode = 1;}
    
    return balanceOfNode;
}

int isFavorite(struct treeNode *n)
{
         if (whatChild(n) == 'L' && balance(n->parent) == 1) {return 1;}
    else if (whatChild(n) == 'R' && balance(n->parent) == -1){return 1;}
    else                                                     {return 0;}
}

struct treeNode *favorite(struct treeNode *n)
{
    if (n->left != NULL && isFavorite(n->left) == 1) {return n->left;}
    else                                             {return n->right;}
}

struct avl *insertFixup(struct treeNode *n, struct avl *a)
{
    struct treeNode *y = NULL;
    
    while (n != a->root)
    {
        struct treeNode *s = sibling(n);
        
        if (s != NULL && isFavorite(s) == 1)
        {
            setBalance(n->parent);
            break;
        }
        else if (balance(n->parent) == 0)
        {
            setBalance(n->parent);
            n = n->parent;
        }
        else
        {
            struct treeNode *p = n->parent;
            y = favorite(n);
            if (isLinear(y) == 0)
            {
                rotate (y,a);
                rotate (y,a);
                setBalance(n);
                setBalance(p);
                setBalance(y);
                break;
            }
            else
            {
                rotate (n,a);
                setBalance(p);
                setBalance(n);
                break;
            }
        }
    } a->count++;
    return a;
}


struct avl *deleteFixup(struct treeNode *n, struct avl *a)
{
    n->avlHeight = 0;
    while (n != a->root)
    {
        if (isFavorite(n))
        {
            setBalance(n->parent);
            n = n->parent;
        }
        else if (balance(n->parent) == 0)
        {
            setBalance(n->parent);
            break;
        }
        else
        {
            struct treeNode *p = n->parent;
            struct treeNode *s = sibling(n);
            struct treeNode *y = favorite(s);
            if (y != NULL && isLinear(y) == 0)
            {
                rotate (y,a);
                rotate (y,a);
                setBalance(p);
                setBalance(s);
                setBalance(y);
                n = y;
            }
            else
            {
                rotate(s,a);
                setBalance(p);
                setBalance(s);
                if (y == NULL) {break;}
                n = s;
            }
        }
    }a->count--;
    return a;
}


int levelOrderTraversal(struct treeNode *root, int counter, int choice)
{
    if(treeSize == 0) {return 0;}
    struct Queue *tQueue = newQueue(root), *ptemp, *temp;
    struct treeNode *n; int lcount = 0, minHeight = -1, nInQueue = 0, nLeft = 0;
    int rootFlag = 1;
    
    Enqueue(tQueue, root); nInQueue = 1;
    
    while(!NULL)
    {
        nLeft = nInQueue; lcount++;
        
        if(nLeft == 0) {break;}
        else if(counter == 0 && rootFlag != 1) {printf("\n%d: ",lcount-1);}
        else if (counter==0 && rootFlag == 1)
                {printf("%d: ",lcount-1);rootFlag = 0;}
       
        while (nLeft > 0)
        {
            temp = Dequeue(tQueue); nInQueue--; n = temp->data;
            
            if(ptemp != temp) printNode(n,&minHeight,lcount,counter,choice);

            if(counter == 1 && minHeight != -1) {return minHeight;}
            
            if (n->left != NULL)  {Enqueue(tQueue,n->left); nInQueue+= 1;}
            if (n->right != NULL) {Enqueue(tQueue, n->right);nInQueue+= 1;}
            ptemp = temp; nLeft--;
        }
    } 
    return minHeight;
}

void printNode(struct treeNode *n, int *minHeight, int lcount, int counter,
               int choice)
{
    char pfav = '*',nfav = '*';
    
    if(choice == 1)
    {
        setBalance(n); setBalance(n->parent);
        
        if(balance(n) == -1) {nfav = '+';}
        if(balance(n) == 1)  {nfav = '-';}
        
        if(balance(n->parent) == -1) {pfav = '+';}
        if(balance(n->parent) == 1)  {pfav = '-';}
    }
    if(isLeaf(n) == 1)
    {
        if (counter == 0)    {printf("=");}
    }
    if(counter == 1 && (n->left == NULL || n->right == NULL))
    {
        if (*minHeight == -1) {*minHeight = lcount;}
    }
    if(counter == 0)
    {
        printf("%s",n->value);
        if(choice == 1 && nfav != '*') {printf("%c",nfav);}
        printf("(%s",n->parent->value);
        if(choice == 1 && pfav != '*') {printf("%c",pfav);}
        printf(")%d%c ",n->frequency,whatChild(n));
    }
}
