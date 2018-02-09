#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "scanner.h"
#include "avlt.h"
#include <ctype.h>
#include <math.h>

/* INSERT METHODS */

struct treeNode * readAll (const char *name, int *c);  // reads in and sends strings from file
struct avl * readAllAvl   (const char *name, int *c);
struct treeNode * readCom (const char *commands, struct treeNode *root,
                           int choice,avl* avlRoot,int *c);

/* OTHER METHODS */

struct treeNode * toBST (char * x, struct treeNode * root); // BST insert function
char * grammar          (char * x, int * empty);            // strips string to specifications
int Options             (int argc, char **argv);            // input options

int main(int argc, char **argv)
{
    int optionNumber = 0; struct treeNode * BSTroot; int c = 1;
    struct avl *avlRoot;
    
    char *name = argv[2]; char *commands = argv[3];

    optionNumber = Options(argc,argv);
    
    if (optionNumber == 0)
    {
        BSTroot = readAll(name,&c);
        readCom(commands,BSTroot,0,0,&c);
    }
    if (optionNumber == 1)
    {
        avlRoot = readAllAvl(name,&c);
        
        if(treeSize != 0) {BSTroot = avlRoot->root;}
        readCom(commands,BSTroot,1,avlRoot,&c);
    }
    return 0;
}

int Options(int argc, char **argv)
{
    int c;
    for (c = 0; c < argc; ++c)
    {
         if (argv[c][0] == '-' && argv[c][1] == 'b' && !argv[c][2]) {return 0;}
    else if (argv[c][0] == '-' && argv[c][1] == 'a' && !argv[c][2]) {return 1;}
    }
    return 0;
}

struct treeNode * readAll(const char *name, int *c)
{
    struct treeNode* root; char *x; int empty = 1;
    
    FILE *fp = fopen(name, "r");
    
    if (stringPending(fp)) {x = readString(fp);} else {x = readToken(fp);}
    while (x != NULL)
    {
       empty = 1; x = grammar(x,&empty);
       if(empty != 1)
       {
            if (*c == 1) {root = Root(x); *c = 0;}
            else         {toBST(x,root);}
       }
        if (stringPending(fp)) {x = readString(fp);} else {x = readToken(fp);}
    }fclose(fp);

    return root;
}

struct avl * readAllAvl(const char *name, int *c)
{
    avl* avlRoot;
    struct treeNode *root,*insertedNode,*piNode; char *x;int flag = 1,empty = 1;
    
    FILE *fp = fopen(name, "r");
    
    if (stringPending(fp)) {x = readString(fp);} else {x = readToken(fp);}
    while (x != NULL)
    {
        empty = 1; x = grammar(x,&empty);
        if(empty != 1)
        {
            if (*c == 1) {root = Root(x); *c = 0;}
            else  {toBST(x,root);}
            insertedNode = findTree(x,root);
            if(insertedNode->frequency == 1)
            {
                 if (flag == 1) {avlRoot = newAVLT(root); flag = 0;}
            else if (insertedNode != piNode && insertedNode != root)
                    {insertFixup(insertedNode,avlRoot); root = avlRoot->root;}
                
            }piNode = insertedNode;
        }
        if (stringPending(fp)) {x = readString(fp);} else {x = readToken(fp);}
    }fclose(fp);
    
    return avlRoot;
}

struct treeNode * readCom(const char *commands, struct treeNode *root,
                          int choice,avl* avlRoot,int *c)
{
    FILE *com = fopen(commands, "r"); char *x; char* whatCommand;
    int inTree = 0,empty = 1,flag = 0,minheight = 0, height = 0,cmdFlag = 0;
    
    if (stringPending(com)) {x = readString(com);} else {x = readToken(com);}
    while (x != NULL)
    {
      x = grammar(x,&empty); inTree = 0;
      if(empty != 1)
      {
        if (cmdFlag == 0 &&(strcmp(x,"i") == 0 || strcmp(x,"s") == 0 ||
                            strcmp(x,"r") == 0 || strcmp(x,"d") == 0 ||
                            strcmp(x,"f") == 0)) {whatCommand = x; cmdFlag = 1;}
        
        else if (strcmp(whatCommand,"i") == 0 && cmdFlag == 1)
        {
            empty = 1; grammar(x,&empty);
          if(empty != 1)
          {
            if(choice == 0){if(*c == 1|| treeSize == 0){root = Root(x); *c = 0;}
                            else {toBST(x,root);}}
            if(choice == 1)
            {
                if(*c == 1 || treeSize == 0) {root = Root(x); *c = 0;flag = 1;}
                else {toBST(x,root);}
                struct treeNode *iNode = findTree(x,root);
                if(iNode->frequency == 1)
                {
                    if (flag == 1) {avlRoot = newAVLT(root);flag = 0;}
                    else if (iNode != root)
                    {insertFixup(iNode,avlRoot); root = avlRoot->root;}
                }
            }
          }cmdFlag = 0;
        }
        else if (strcmp(whatCommand,"d") == 0 && cmdFlag == 1)
        {
            if(treeSize == 0) {fprintf(stderr,"ERROR: %s is not in tree\n",x);}
            else if(choice == 0) {updateTree(x,root,&inTree,0);} // BST delete
            else if(choice == 1)                                 // AVL delete
            {
                updateTree(x,root,&inTree,3); // decreases frequency
                if(inTree == 1)
                {
                    struct treeNode *dNode = findTree(x,root);
                    if(dNode->frequency == 0) // delete it
                    {
                        dNode = swapToLeaf(dNode,0);
                        deleteFixup(dNode,avlRoot); root = avlRoot->root;
                        leafDelete(dNode);
                    }
                }
            }
            if (treeSize > 0 && inTree == 0) {fprintf(stderr,"ERROR: %s is not in tree\n",x);}
            cmdFlag = 0;
        }
        else if (strcmp(whatCommand,"f") == 0 && cmdFlag == 1)
        {
            if (treeSize == 0) {fprintf(stderr,"ERROR: %s is not in tree\n",x);}
            else {updateTree(x,root,&inTree,2);}
            if (inTree == 0 && treeSize > 0)
               {fprintf(stderr,"ERROR: %s is not in tree\n",x);}
            cmdFlag = 0;
        }
        if (strcmp(whatCommand,"s") == 0 && cmdFlag == 1)
        {levelOrderTraversal(root,0,choice); printf("\n"); cmdFlag = 0;}
        else if (strcmp(whatCommand,"r") == 0 && cmdFlag == 1)
        {
            if(treeSize == 0) {printf("Tree is empty\n");}
            else
            {
                height = getHeight(root)-1;
                minheight = levelOrderTraversal(root,1,choice)-1;
            printf("Nodes: %d\nmaxheight: %d\nminheight: %d\n",treeSize,height,minheight);
            }
            cmdFlag = 0;
        }
      }
        if (stringPending(com)) {x = readString(com);}
        else                    {x = readToken(com);}
    }fclose(com);
    return root;
}

char * grammar (char * x, int * empty)
{
    int i = 0; char *final = malloc(sizeof(char)*strlen(x)+1); int flag = 0;
	
    for(i = 0; i < (int) strlen(x); i++)
    {
        if (isalpha(x[i]))
        {
            flag = 0; *empty = 0;
            x[i] = tolower(x[i]);
            sprintf(final,"%s%c",final,x[i]);
        }
        else if (isspace(x[i]) && flag == 0)
        {
            sprintf(final,"%s ",final);
            flag = 1; *empty = 0;
        }
    }
    return final;
}

struct treeNode * toBST(char * x, struct treeNode * root) // BST insert function
{
    int inTree = 0;
    
    updateTree(x,root,&inTree,1);
    
    if (inTree == 0) {build(x,root);}
    return root;
}
