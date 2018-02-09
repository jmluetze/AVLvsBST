/* public interface for the AVL Tree class, by Jonathan Luetze
 *
 * see avlt.c for a description
 *
 */

#ifndef avlt_h
#define avlt_h

#endif

#include "queue.h"
#include "stdio.h"

typedef struct avl
{
    struct treeNode *root;
    int count;
}avl;

struct avl * newAVLT      (struct treeNode *root);
int levelOrderTraversal   (struct treeNode *root, int counter,int choice);
void printNode            (struct treeNode *n, int *minHeight, int lcount,
                           int counter, int choice);
int isLinear              (struct treeNode *n);
int isFavorite            (struct treeNode *n);
struct treeNode *favorite (struct treeNode *n);
struct treeNode *gParent  (struct treeNode *n);
struct treeNode *sibling  (struct treeNode *n);
struct avl * rotate       (struct treeNode *n, struct avl *a);
struct avl *insertFixup   (struct treeNode *n, struct avl *a);
struct avl *deleteFixup   (struct treeNode *n, struct avl *a);
struct avl * rotateLeft   (struct treeNode *n, struct avl *a);
struct avl * rotateRight  (struct treeNode *n, struct avl *a);
