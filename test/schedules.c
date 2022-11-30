#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include<limits.h>
process *EnterParams(int n)
{
    int bucket;
    process *jobs = (process *)malloc(sizeof(process) * n);
    for (int i = 0; i < n; i++)
    {
        printf("enter process id: ");
        scanf("%d", &bucket);
        jobs[i].pid = bucket;
        printf("enter arrival cycle for process p[%d]: ", jobs[i].pid);
        scanf("%d", &bucket);
        jobs[i].arrival = bucket;
        printf("enter the total cycle for process p[%d]: ", jobs[i].pid);
        scanf("%d", &bucket);
        jobs[i].totalCpu = bucket;

        jobs[i].totalRemaining = jobs[i].totalCpu;
        jobs[i].is_finished = 0;
        jobs[i].in_progress = 0;
    }

    return jobs;
}

void FifoSchedule(process *jobs, int n)
{
    // local declerations
    int eat = INT_MAX;  // earliest arrival time
    int cpuClock = 0; 
        //create a queue 
    queue *readyQueue = createQueue();
    queue *activeCpu = createQueue();
    // set finished falgs to false
    // set total remaining to total CPU  
    printf("checking the isEmpty utility: %", isEmpty(readyQueue)); 
    for(int i = 0; i<n; i++){
        for (int j = 0; j < n; j++)
        {
            if(jobs[j].is_ready == false && jobs[j].arrival < eat)
            {
                jobs[j].is_ready = true;
                enQueue(readyQueue, (jobs+j));
            }
            
        }
    }


    printQueue(readyQueue);
    while (!isEmpty(readyQueue))
    {
        /* code */
    }
    
    

}

void MainPrompt()
{
    printf("Batch Scheduling \n");
    printf("----------------- \n");
    printf("1) Enter parameters \n");
    printf("2) Schedule processes with FIFO \n");
    printf("3) Schedule processes with SJF \n");
    printf("4) Schedule processes with SRT \n");
    printf("5) Quit and free memory \n");
    printf("6) create processes quickly \n");
}

void PrintTable(process *process_schedule, int n)
{
    int length = sizeof(process_schedule) / n;
    printf(" length variable: %d \n", length);

    printf("Id    Arrival  Total \t Start \t End \t Turnaround \n");
    printf("------------------------------------------------------------- \n");
    for (int i = 0; i <= length; i++)
    {
        if (process_schedule[i].is_finished == 1)
        {
            printf("%d \t %d \t %d \t %d \t %d \t %d \n",
                   process_schedule[i].pid,
                   process_schedule[i].arrival,
                   process_schedule[i].totalCpu,
                   process_schedule[i].start,
                   process_schedule[i].finish,
                   process_schedule[i].turnAround);
        }
        else
        {
            printf("%d \t %d \t %d \n",
                   process_schedule[i].pid,
                   process_schedule[i].arrival,
                   process_schedule[i].totalCpu);
        }
    }
}

void SjfSchedule()
{
}

void SrtSchedule()
{
}
