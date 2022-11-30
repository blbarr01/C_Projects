#ifndef QUEUE
#define QUEUE
#include<stdbool.h>
#include "process.h"



// create nodes for the queue
typedef struct
{
    process *nodeProcess;
    struct node *next;
} node;

typedef struct
{
    node *head, *tail;
} queue;


node *newNode(process *nprocess);
queue *createQueue();
void enQueue(queue *q, process *p);
void deQueue(queue *q);
void peek(queue *q);
bool isEmpty(queue *q)
void printQueue(queue *q);
process* quickProcesses(int n);

#endif 