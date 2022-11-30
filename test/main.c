#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "schedules.h"



int main(){
    int selector;
    int n; 
    process* jobs;
    do
    {
        MainPrompt();
        printf("enter selection: ");
        scanf("%d", &selector);
        switch (selector)
        {
        case 1:
            printf("how many processes would you like: ");
            scanf("%d", &n);
            jobs = EnterParams(n);
            PrintTable(jobs, n);
            break;
        case 2:
            FifoSchedule(jobs, n);
            break;
        case 3:
            SjfSchedule();
            break;
        case 4:
            SrtSchedule();
            PrintTable(jobs, n);
            break;
        case 5:
            printf("goodbye \n");
            exit(0);
            break;
        case 6:
            n = 3;
            // quickProcesses is in queue.*
            jobs = quickProcesses(n);
            printf(" size of schedule block: %d\n\n", n);
            PrintTable(jobs, n);
            break; 
        default:
            printf("input not understood:  \n");
        }
    } while (selector != 5);
     return 0; 
}












/*      queue *q = createQueue();
     enQueue(q, &process_schedule[0]); 
     enQueue(q, &process_schedule[1]); 
     enQueue(q, &process_schedule[2]); 
     printf("so far so fare i guess \n");
     printf("head of queue process id : %d  arrival time: %d; finish: %d\n",
      q->head->nodeProcess->pid, 
      q->head->nodeProcess->arrival,
      q->head->nodeProcess->finish);
     deQueue(q);
         printf(" after dequeue, head of queue process id : %d  arrival time: %d; finish: %d\n",
      q->head->nodeProcess->pid, 
      q->head->nodeProcess->arrival,
      q->head->nodeProcess->finish); */