#ifndef QUEUE
#define QUEUE
#include<stdbool.h>

typedef struct
{
    int pid,
        arrival,
        totalCpu,
        totalRemaining,
        start,  
        finish,
        turnAround;

    bool is_finished,
        in_progress;

} process;

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
process* quickProcesses(int n);

#endif 