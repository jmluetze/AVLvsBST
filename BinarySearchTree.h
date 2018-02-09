/* public interface for the Binary Search Tree class, by Jonathan Luetze
 *
 * see BinarySearchTree.c for a description
 *
 */

#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#endif

int treeSize;

struct treeNode
{
    char * value;
    struct treeNode *left, *right, *parent;
    int leftHeight,rightHeight,avlHeight;
    int frequency;
};

void build                      (char * x,struct treeNode *curr);
struct treeNode * findTree      (char * x,struct treeNode *root);
struct treeNode* Root           (char * x);
struct treeNode* getPredecessor (struct treeNode *root);
struct treeNode* getSuccessor   (struct treeNode *root);
void inOrderTraversal           (struct treeNode *curr2);
struct treeNode* swapToLeaf     (struct treeNode *ntbd,int choice);
void updateTree       (char * x, struct treeNode *root, int *inTree, int iOrD);
char whatChild        (struct treeNode *child);
void leafDelete       (struct treeNode *ntbd);
int getHeight         (struct treeNode *root);
int isLeaf            (struct treeNode *root);

