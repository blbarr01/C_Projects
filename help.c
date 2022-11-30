#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//global function to find the max of two numbers
//works
int MAX_OF_TW0 (int a, int b)
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

int n = -1; //max number of process

//defines what is held within the table
//also hold a dynamic array
typedef struct Table
{
  int id; //the unique identifier of the process
  int arrival; //the point in time when the process enters the ready list to be executed by the CPU 
  int total_cpu; //the amount of CPU time the process will consume between arrival and 
                //departure
  int total_remaining;
  int done; //a flag that indicates whether the process has been successfully completed (1) or 
            //not (0)
  int start_time; //the time when the process hhas begun being executed by the CPU
  int already_started;		//?
  int end_time; //the time when the process has been completed by the CPU
  int turnaround_time;
} TABLE;

TABLE* table;

/******************************************************************************/
void printTable() {
	/* declare local variables */
	/* print table header */
	printf("\nID      Arrival Total   Start   End     Turnaround\n");
	printf("--------------------------------------------------");
	/* for each process print the contents (id, arrival time, total_cycles) 
	of each field of the table's index */
	for(int i = 0; i < n; i++){
	    printf("\n %d      %d", table[i].id,table[i].arrival);
	    printf("       %d",table[i].total_cpu);
	    /* if process has been scheduled ("done" field is 1, print other 
	    contents(start time, end time, turnaround time) */
	    if(table[i].done == 1){
	        printf("       %d       %d", table[i].start_time,table[i].end_time);
	        printf("         %d", table[i].turnaround_time);
	    }
	}
	return;
}

/******************************************************************************/
void getParameters() { //option 1	
	/* declare local variables */
	/* prompt for total number of processes */
	printf("Enter the total number of process: ");
	scanf("%d", &n);
	
	//printf("\n User entered: %d", n);
	/* allocate memory for table to hold process parameters */
	table = malloc( n * sizeof(table));

	/* for each process */
	/* prompt for process id, arrival time, and total cycle time */
	for(int i = 0; i < n; i++){
	    printf("Enter process id: ");
	    scanf("%d", &table[i].id);
	    printf("Enter arrival cycle for process P[%d]: ", table[i].id);
	    scanf("%d", &table[i].arrival);
	    printf("Enter total cycles for process P[%d]:", table[i].id);
	    scanf("%d", &table[i].total_cpu);
	}
	
	/* print contents of table */
	printTable();
	return;		
}	
/******************************************************************************/
void FIFO_algo() { //option2
	/* declare (and initilize when appropriate) local variables */
	int process_left = n; //counter to keep track of # of process left
	int earliest_arrival; //keeps track of the earliest arrival time
	int current_turnarround = 0; //increases the overall turnaround time
	int current_end = 0; //keeps track of current endtime
	int current_start_time = table[0].total_cpu; //keeps track of where the process begins
	int scheduled_process = 0;   //keeps track of scheduled process
	/* for each process, reset "done" field to 0 */
	for(int i = 0; i< n; i++){
	    table[i].done = 0;
	}
	
	while (process_left != 0){
	    /* initilize the earliest arrival time to INT_MAX (largest integer value)
	       for each process not yet scheduled*/
	    for(int i = 0; i < n; i++){
	        if(table[i].done != 1){
	            earliest_arrival = INT_MAX;
	            if (table[i].arrival < earliest_arrival){
	            earliest_arrival = table[i].arrival;
	            scheduled_process = i;
	            } 
	        }
        /* set start time, end time, turnaround time, done fields for
           unscheduled process with earliest arrival time */
        table[scheduled_process].start_time = current_end;
        table[scheduled_process].end_time = current_end + table[scheduled_process].total_cpu;
        current_end = table[scheduled_process].end_time;
        table[scheduled_process].done = 1;
        table[scheduled_process].turnaround_time = current_end - table[scheduled_process].arrival;
	    process_left--;
	    }
	}
	printTable();
	return;		
}

/******************************************************************************/
void SJF_alg() { // "PROCEDURE FOR OPTION #3"
    /* declare (and initilize when appropriate) local variables */
    int processes_scheduled = 0; //keeps track of scheduled process
    int lowest_cycle_time = 0;  // keeps track of the smallest cycle time
    int current_cycle_time = 0;
    int scheduled_process = 0;   //keeps track of scheduled process
    /* for each process, reset "done" field to 0 */
    for(int i = 0; i < n; i++){
        table[i].done = 0;
    }
    /* while there are still processes to schedule */
    while(processes_scheduled < n){
        /* initilize the lowest total cycle time to INT_MAX (largest integer value) */
        lowest_cycle_time = INT_MAX;
        /* for each process not yet scheduled */
        for(int i = 0; i < n; i++){
            if(!table[i].done){
                /* check if process has lower total cycle time than current lowest and has arrival time less than current cycle time and update */
                if((table[i].total_cpu < lowest_cycle_time) && (table[i].arrival < current_cycle_time)){
                    lowest_cycle_time = table[i].total_cpu;
                    scheduled_process = i;
                }
            }
        }
        /* set start time, end time, turnaround time, done fields for unscheduled process with lowest (and available) total cycle time */
        table[scheduled_process].start_time = current_cycle_time;
        table[scheduled_process].end_time = table[scheduled_process].start_time + table[scheduled_process].total_cpu;
        table[scheduled_process].turnaround_time = table[scheduled_process].end_time - table[scheduled_process].arrival;
        table[scheduled_process].done = 1;
        /* update current cycle time and increment number of processes scheduled */
        current_cycle_time += table[scheduled_process].total_cpu;
        processes_scheduled++;
    }
    /* print contents of table */
    printTable();
    return;        
}

/******************************************************************************/
void SRT_alg() {
 /* declare (and initilize when appropriate) local variables */
    int scheduled_process = 0;
    int scheduled = 0;
    int lowest_total_remaining_time;
    int cycles = 0;
    /* for each process, reset "done", "total_remaining" and "already_started" fields to 0 */
    for(int i = 0; i < n; i++){
        table[i].done = 0;
        table[i].total_remaining = table[i].total_cpu;
        table[i].already_started = 0;
    }
    /* while there are still processes to schedule */
    while(scheduled < n){
        /* initilize the lowest total remaining time to INT_MAX (largest integer value) */
        lowest_total_remaining_time = INT_MAX;
        /* for each process not yet scheduled */
        for(int i = 0; i < n; i++){
            if(!table[i].done){
                /* check if process has lower total remaining time than current lowest and has arrival time less than current cycle time and update */
                if((table[i].total_remaining < lowest_total_remaining_time) && (table[i].arrival <= cycles)){
                    lowest_total_remaining_time = table[i].total_remaining;
                    scheduled_process = i;
                }
            }
        }
        /* check if process already partially-scheduled */
        if(!table[scheduled_process].already_started){
            /* if so, set "start time", "already_started" fields of process with lowest (and available) total remaining cycle time */
            table[scheduled_process].start_time = MAX_OF_TW0(cycles, table[scheduled_process].arrival);
            table[scheduled_process].already_started = 1;
        }
        
        /* decrement total remaining time of process with lowest (and available) total remaining cycle time */
        table[scheduled_process].total_remaining--;
        
        /* set end time, turnaround time of process with lowest (and available) total remaining cycle time */
        table[scheduled_process].end_time = table[scheduled_process].start_time + table[scheduled_process].total_remaining;
        table[scheduled_process].turnaround_time = table[scheduled_process].end_time = table[scheduled_process].start_time;
        
        /* if remaining time is 0, set done field to 1, increment cycle time and number of scheduled processes*/
        if(table[scheduled_process].total_remaining == 0){
            table[scheduled_process].end_time = cycles + 1;
            table[scheduled_process].turnaround_time = table[scheduled_process].end_time - table[scheduled_process].arrival;
            table[scheduled_process].done = 1;
            scheduled++;
        }
        cycles++;
    }
    /* print contents of table */
    printTable();
    return;    
}

/******************************************************************************/
void freeMemory(){
    if (table != NULL){
        free(table);
    }
}

int main ()
{
  /* declare local vars */
  int userChoice = -1;

  /* while user has not chosen to quit */
  while (userChoice != 5)
    {
      /* print menu of options */
      printf ("\n\n");
      printf ("Process Creation and Destruction\n");
      printf ("--------------------------------\n");
      printf ("1) Enter parameters\n");
      printf ("2) Schedule processes with FIFO algorithm\n");
      printf ("3) Schedule processes with SJF algorithm\n");
      printf ("4) Schedule processes with SRF algorithm\n");
      printf ("5) Quit and free memory\n");

      /* prompt for menu selection */
      printf ("Enter selection: ");
      scanf ("%d", &userChoice);

      /* call appropriate procedure based on choice--use switch statement 
      or series of if, else if, else statements */
    switch(userChoice){
            case 1:
                getParameters();
                break;
            case 2:
                FIFO_algo();
                break;
            case 3:
                SJF_alg();
                break;
            case 4:
                SRT_alg();
                break;
            case 5:
                freeMemory();
                printf("Quitting program...");
                break;
        }
    } /* while loop */

  return 1;	/* indicates success */
}/* end of procedure */











