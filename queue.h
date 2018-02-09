/* public interface for the Queue class, by Jonathan Luetze
 *
 * see queue.c for a description
 *
 */

#ifndef queue_h
#define queue_h

#include <stdio.h>
#endif

#include "BinarySearchTree.h"

struct Queue
{
    struct treeNode * data;
    struct Queue* next;
    struct Queue* front;
    struct Queue* rear;
};

void makeEmpty          ();
struct Queue* newQueue  (struct treeNode * x);
void Enqueue            (struct Queue *q, struct treeNode * x); //enque an element
struct Queue * Dequeue  (struct Queue *q);      //dequeue an element
struct Queue * Front    (struct Queue *q);      //return front of queue
void Print              (struct Queue *q);      //print queue
