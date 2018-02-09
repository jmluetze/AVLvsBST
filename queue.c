/*
 * Queue structure implementation by Jonathan Luetze
 *
 *    methods: newQueue, creates a new queue
 *           : makeEmpty, empties a queue
 *           : Enqueue, adds a node to the queue
 *           : Dequeue, removes a node from the queue
 *
 *           : *Front, returns the first node in the queue
 *           : Print, prints a node in the queue
 */

#include "queue.h"
#include "string.h"
#include<stdio.h>
#include<stdlib.h>


struct Queue* newQueue(struct treeNode * x)
{
    struct Queue* temp = (struct Queue*)malloc(sizeof(struct Queue));
    
    temp->data = x;
    temp->next = NULL;
    temp->front = temp->rear = temp;
    return temp;
}

void makeEmpty(struct Queue * q)
{
    q->front = q->rear = NULL;
}

void Enqueue(struct Queue * q, struct treeNode * x)
{
    struct Queue* temp = (struct Queue*)malloc(sizeof(struct Queue));
    
    temp->data = x;
    temp->next = NULL;
    if (q->rear == NULL && q->front == NULL) {q->rear = q->front = temp;}
    else
    {
        q->rear->next = temp;
        q->rear = temp;
    }
}

struct Queue * Dequeue(struct Queue *q)
{
    struct Queue * temp;
    if (q->front == q->rear)
    {
        temp = q->front;
        q->front = q->rear = NULL;
        return temp;
    }
    else
    {
        q->front = q->front->next;
        return q->front;
    }
    return q->front;
}

struct Queue * Front(struct Queue *q)
{
    if(q->front != NULL)
    {
        return q->front;
    }
    else {exit(0);}
}

void Print(struct Queue *q)
{
    struct Queue* temp = q->front;
    
    while(temp != NULL)
    {
        printf("%s ",temp->data->value);
        temp = temp->next;
    }
    printf("\n");
}
