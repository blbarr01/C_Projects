#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

int n; // total processes for the program

int MAX(int a, int b)
{
  if (a > b)
    {
      return a;
    }
  else
    {
      return b;
    }
}

struct process
{
    int pid,
        arrival,
        total_cpu,
        total_remaining,
        start,
        finish,
        turn_around;

    bool is_finished,
        in_progress;
};

typedef struct process process;

process *quickProcesses(int n)
{
    // printf("you reached the qprocess thread %d \n", n);
    process *jobs = (process *)malloc(sizeof(process) * n);
    time_t t;
    srand((unsigned)time(&t));
    for (int i = 0; i < n; i++)
    {
        jobs[i].pid = i;
        jobs[i].arrival = (rand() % 8);
        jobs[i].total_cpu = (rand() % 16) + 1;
    }
    return jobs;
}

int allDone(process *jobs)
{
    for (int i = 0; i < n; i++)
    {
        if (jobs[i].is_finished != true)
        {
            return 0;
        }
    }

    return 1;
}

void printProcess(process *p)
{
    printf("process id: %d total cpu %d \n", p->pid, p->total_cpu);
}

void PrintTable(process *process_schedule)
{
    int length = sizeof(process_schedule) / n;

    printf("Id    Arrival  Total \t Start \t End \t turn Around \n");
    printf("------------------------------------------------------------- \n");
    for (int i = 0; i < n; i++)
    {
        if (process_schedule[i].is_finished == 1)
        {
            printf("%d \t %d \t %d \t %d \t %d \t %d \n",
                   process_schedule[i].pid,
                   process_schedule[i].arrival,
                   process_schedule[i].total_cpu,
                   process_schedule[i].start,
                   process_schedule[i].finish,
                   process_schedule[i].turn_around);
        }
        else
        {
            printf("%d \t %d \t %d \n",
                   process_schedule[i].pid,
                   process_schedule[i].arrival,
                   process_schedule[i].total_cpu);
        }
    }
}

process *EnterParams()
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
        jobs[i].total_cpu = bucket;

        jobs[i].total_remaining = jobs[i].total_cpu;
        jobs[i].is_finished = 0;
        jobs[i].in_progress = 0;
    }

    return jobs;
}

void FifoSchedule(process *jobs)
{
    // local declerations
    int eat = INT_MAX; // earliest arrival time
    int runtimeClock = 0;
    int eati = INT_MAX; //  earliest arrival time index

    for (int i = 0; i < n; i++)
    {
        // reset the finished state and total remaining time
        jobs[i].is_finished = false;
        jobs[i].total_remaining = jobs[i].total_cpu;
    }
    while (!allDone(jobs))
    {
        eat = INT_MAX;
        // figure out who arrives the earliest
        for (int j = 0; j < n; j++)
        {
            if (jobs[j].is_finished == false && jobs[j].arrival < eat)
            {
                /* code */
                eat = jobs[j].arrival;
                eati = j;
            }
        }
        /* load the earliest arriving job onto the cpu
        and operate on it  */
        jobs[eati].start = runtimeClock;
        while (!jobs[eati].is_finished)
        {
            // operate on the process
            jobs[eati].total_remaining--;
            runtimeClock++;

            // once we finish a process
            if (jobs[eati].total_remaining == 0)
            {
                jobs[eati].is_finished = true;
                jobs[eati].finish = runtimeClock;
                jobs[eati].turn_around = jobs[eati].finish - jobs[eati].arrival;
            }
        }

    } // end all done

    PrintTable(jobs);
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
}

void SjfSchedule(process *jobs)
{

    /* declare (and initilize when appropriate) local variables */
    int eat = INT_MAX; // earliest arrival time
    int runtime_clock = 0;
    int lowest_cycle_time, // lowest total cycle time
        active_process_index;  
	
    /* for each process, reset "done" field to 0 */
    for (int i = 0; i < n; i++)
    {
        // reset the finished state and total remaining time
        jobs[i].is_finished = false;
        jobs[i].total_remaining = jobs[i].total_cpu;
    }
	
    /* while there are still processes to schedule */	
    while (!allDone(jobs))
    {
		/* initilize the lowest total cycle time to INT_MAX (largest integer value) */
        lowest_cycle_time = INT_MAX; 
		/* for each process not yet scheduled */
        for (int i = 0; i < n; i++)
        {
			/* check if process has lower total cycle time than current lowest and has arrival time less than current cycle time and update */	
            if ((jobs[i].is_finished != true) && (jobs[i].total_cpu < lowest_cycle_time) && (jobs[i].arrival < runtime_clock))
            {
                /* code */
                lowest_cycle_time = jobs[i].total_cpu;
                active_process_index = i; 
            }
            
        }
        
		/* set start time, end time, turnaround time, done fields for unscheduled process with lowest (and available) total cycle time */       	
		jobs[active_process_index].start = runtime_clock;
        jobs[active_process_index].finish = runtime_clock + jobs[active_process_index].total_cpu;
        runtime_clock = jobs[active_process_index].finish;
        jobs[active_process_index].is_finished = true; 
        jobs[active_process_index].turn_around = runtime_clock - jobs[active_process_index].arrival;

    }
    
	/* print contents of table */
    PrintTable(jobs);
return;
}

void SrtSchedule(process *jobs)
{
 /* declare (and initilize when appropriate) local variables */
    int scheduled_process = 0;
    int scheduled = 0;
    int lowest_total_remaining_time;
    int cycles = 0;
    /* for each process, reset "done", "total_remaining" and "already_started" fields to 0 */
    for(int i = 0; i < n; i++){
        jobs[i].is_finished = 0;
        jobs[i].total_remaining = jobs[i].total_cpu;
        jobs[i].in_progress = 0;
    }
    /* while there are still processes to schedule */
    while(scheduled < n){
        /* initilize the lowest total remaining time to INT_MAX (largest integer value) */
        lowest_total_remaining_time = INT_MAX;
        /* for each process not yet scheduled */
        for(int i = 0; i < n; i++){
            if(!jobs[i].is_finished){
                /* check if process has lower total remaining time than current lowest and has arrival time less than current cycle time and update */
                if((jobs[i].total_remaining < lowest_total_remaining_time) && (jobs[i].arrival <= cycles)){
                    lowest_total_remaining_time = jobs[i].total_remaining;
                    scheduled_process = i;
                }
            }
        }
        /* check if process already partially-scheduled */
        if(!jobs[scheduled_process].in_progress){
            /* if so, set "start time", "already_started" fields of process with lowest (and available) total remaining cycle time */
            jobs[scheduled_process].start = MAX(cycles, jobs[scheduled_process].arrival);
            jobs[scheduled_process].in_progress = 1;
        }
        
        /* decrement total remaining time of process with lowest (and available) total remaining cycle time */
        jobs[scheduled_process].total_remaining--;
        
        /* set end time, turnaround time of process with lowest (and available) total remaining cycle time */
        jobs[scheduled_process].finish = jobs[scheduled_process].start + jobs[scheduled_process].total_remaining;
        jobs[scheduled_process].turn_around = jobs[scheduled_process].finish = jobs[scheduled_process].start;
        
        /* if remaining time is 0, set done field to 1, increment cycle time and number of scheduled processes*/
        if(jobs[scheduled_process].total_remaining == 0){
            jobs[scheduled_process].finish = cycles + 1;
            jobs[scheduled_process].turn_around = jobs[scheduled_process].finish - jobs[scheduled_process].arrival;
            jobs[scheduled_process].is_finished = 1;
            scheduled++;
        }
        cycles++;
    }
    /* print contents of table */
    PrintTable(jobs);
    return;  
    
}

int main()
{
    int selector;
    process *jobs;
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
            jobs = EnterParams();
            PrintTable(jobs);
            break;
        case 2:
            FifoSchedule(jobs);
            break;
        case 3:
            SjfSchedule(jobs);
            break;
        case 4:
            SrtSchedule(jobs);
            break;
        case 5:
            free(jobs);
            printf("goodbye \n"); // 5/4 12:54 pm
            exit(0);              // Brian Barr
            break;
        default:
            printf("input not understood:  \n");
        }
    } while (selector != 5);
    return 0;
}
