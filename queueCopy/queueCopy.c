#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<time.h>
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


// utility to make a new process
node *newNode(process *nprocess)
{
    node *temp = (node *)(malloc(sizeof(node)));
    temp->nodeProcess = nprocess;
    return temp;
}

queue *createQueue()
{
    queue *q = (queue *)malloc(sizeof(queue));
    q->head = q->tail = NULL;
    return q;
}

void enQueue(queue *q, process *p)
{
    node *temp = newNode(p);
    if (q->tail == NULL)
    {
        q->head = q->tail = temp;
        return;
    }
    // add new node to the end of the queue
    q->tail->next = temp;
    q->tail = temp;
}

void deQueue(queue *q)
{
    if (q->head == NULL)
    {
        return;
    }

    node *temp = q->head;
    q->head = q->head->next;
    if (q->head == NULL)
    {
        q->tail = NULL;
    }
    free(temp);
}

process* quickProcesses(int n){
    printf("you reached the qprocess thread %d \n", n);
    process *jobs = (process*)malloc(sizeof(process) * n);
    time_t t;
    srand((unsigned) time(&t));
    for(int i = 0; i < n; i++){
        jobs[i].pid = i; 
        jobs[i].arrival = (rand() % 8);
        jobs[i].totalCpu = (rand() % 16) +1; 
    }   
    return jobs;

}