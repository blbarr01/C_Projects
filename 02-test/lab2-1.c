#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Process{
    int id;
    int arrival;
    int total;
    int start;
    int end;
    int turnaround;
    int done;
};

struct Process *Batch;
int MAX_PROCESS_COUNT;

/* declare global variables including a table structure to hold scheduling information */
void PrintTable();
void GenPara();
void FIFO();
void SJF();
void SRT();
void Quit(); //destroy 

/* optional: define a function that finds the maximum of two integers */

/***************************************************************/
void PrintTable() {
	/* declare local variables */
	int i, n;
	struct Process *ptr = Batch;
	/* print table header */
	printf("\nID\tArrival\tTotal\tStart\tEnd\tTurnaround");
	printf("\n--------------------------------------------------");
	/* for each process */
	for(i = 0; i < MAX_PROCESS_COUNT; i++){
		/* print the contents (id, arrival time, total_cycles) of each field of the table's index */
		printf("\n%d", (ptr+i)->id);
		printf("\t%d", (ptr+i)->arrival);
		printf("\t%d", (ptr+i)->total);
		printf("\t%d", (ptr+i)->start);
		printf("\t%d", (ptr+i)->end);
		printf("\t%d", (ptr+i)->turnaround);
		/* if process has been scheduled ("done" field is 1, print other contents (start time, end time, turnaround time) */
	}
	return;
}


/***************************************************************/
void GenPara() {	
	/* declare local variables */
	int n, id, arrival, total;
	struct Process *ptr = Batch;
	/* prompt for total number of processes */	
	printf("\nEnter total number of processes: ");
	scanf("%d", &MAX_PROCESS_COUNT);
	/* allocate memory for table to hold process parameters */
	Batch = (struct Process *)malloc(sizeof(struct Process) * MAX_PROCESS_COUNT);
	
	//Batch->id = 0;
	//Batch->arrival = 0;
	//Batch->total = 0;
	//Batch->start = 0;
	//Batch->end = 0;
	//Batch->turnaround = 0;
	
	/* for each process */
	for(size_t n = 0; n < MAX_PROCESS_COUNT; n++){
		/* prompt for process id, arrival time, and total cycle time */	
		
		printf("\nEnter process id: ");
		scanf("%i", &id);
		(Batch + n)->id = id;
		printf("Enter arrival cycle for process P[%d]: ", id);
		scanf("%d", &arrival);
		(Batch + n)->arrival = arrival;
		printf("Enter total cycles for process P[%d]: ", id);
		scanf("%d", &total);
		(Batch + n)->total = total;
	}
	/* print contents of table */
	PrintTable();
	return;		
}	
		

/***************************************************************/
void FIFO() {
	/* declare (and initilize when appropriate) local variables */
	int n, id, arrival, total, start, end = 0, turnaround = 0, done = 0;
	int started, already_started, counter = 0;
	int check = INT_MAX;
	struct Process *ptr = Batch;
	/* for each process, reset "done" field to 0 */
	for(n = 0; n < MAX_PROCESS_COUNT; n++){
	    (ptr + n)->done = 0;
	    counter++;
	}
	/* while there are still processes to schedule */	
	do{
		/* initilize the earliest arrival time to INT_MAX (largest integer value) */
		for(n =0; n < MAX_PROCESS_COUNT; n++){
		    //find undone arrival time
		    if((ptr + n)->done != 1){
		        //declare current arrival time to compare 
		        printf("\ndone %d", (ptr+n)->done);
                //find earliest arrival time
                if((ptr + n)->arrival < check){
                    ptr = (ptr + n);
                }
		    }
		}
		printf("\ncurrent id %d", ptr->id);
		ptr->start = end;
		ptr->end += ptr->total;
		total = ptr->total;
		printf("\ttotal %d", total);
		
		
		/* for each process not yet scheduled */
        for(n = 0; n < total; n++){
			/* check if process has earlier arrival time than current earliest and update */	
            turnaround++;    
        }
        printf("\nturn %d", turnaround);
		/* set start time, end time, turnaround time, done fields for unscheduled process with earliest arrival time */       	
		
		/* update current cycle time and increment number of processes scheduled */
		ptr->end = end;
		ptr->turnaround = turnaround;
		ptr->done = 1;
		counter--;
	} while (counter > 0);
	/* print contents of table */
	PrintTable();
	return;		
}	


/***************************************************************/
void SJF() {
	/* declare (and initilize when appropriate) local variables */
	/* for each process, reset "done" field to 0 */
	/* while there are still processes to schedule */	
		/* initilize the lowest total cycle time to INT_MAX (largest integer value) */
		/* for each process not yet scheduled */
			/* check if process has lower total cycle time than current lowest and has arrival time less than current cycle time and update */	
		/* set start time, end time, turnaround time, done fields for unscheduled process with lowest (and available) total cycle time */       	
		/* update current cycle time and increment number of processes scheduled */
	/* print contents of table */
	return;		
}	
        	

/***************************************************************/
void SRT() {
	/* declare (and initilize when appropriate) local variables */
	/* for each process, reset "done", "total_remaining" and "already_started" fields to 0 */
	/* while there are still processes to schedule */	
		/* initilize the lowest total remaining time to INT_MAX (largest integer value) */
		/* for each process not yet scheduled */
			/* check if process has lower total remaining time than current lowest and has arrival time less than current cycle time and update */	
		/* check if process already partially-scheduled */
			/* if so, set "start time", "already_started" fields of process with lowest (and available) total remaining cycle time */       	
		/* set end time, turnaround time of process with lowest (and available) total remaining cycle time */
		/* decrement total remaining time of process with lowest (and available) total remaining cycle time */
		/* if remaining time is 0, set done field to 1, increment cycle time and number of scheduled processes*/
	/* print contents of table */
	return;		
}	
        	

/***************************************************************/
void Quit() {
	/* free the schedule table if not NULL */
	return;
}


/***************************************************************/
int main() {
    
	int ans = 0;
	
    do{
        printf("\n\nBatch Scheduling");
        printf("\n----------------");
        printf("\n1) Enter parameters");
        printf("\n2) Schedule processes with FIFO algorithm");
        printf("\n3) Schedule processes with SJF algorithm");
        printf("\n4) Schedule processes with SRT algorithm");
        printf("\n5) Quit and free memory\n");
        
        printf("Enter selection: ");
        scanf("%d", &ans);
        switch(ans){
            case 1:
                GenPara();
                break;
            case 2: 
                FIFO();
                break;
            case 3:
                SJF();
                break;
            case 4:
                SRT();
                break;
            default:
                printf("\nUnknown selection.");
                break;
	    }
    } while (ans != 5);
	 return 1;
}