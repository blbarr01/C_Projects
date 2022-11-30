#ifndef SCHEDULES_H
#define SCHEDULES_H


/*  prototype declarations */

// option 1
process *EnterParams(int n);
// option 2
void FifoSchedule(process *jobs, int n);
// option 3
void SjfSchedule();
// option 4
void SrtSchedule();

void PrintTable(process *process_schedule, int n);

void MainPrompt();
 

#endif