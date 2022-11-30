#include<stdbool.h>
#ifndef PROCESS_H
#define PROCESS_H


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
        in_progress,
        is_ready;

} process;


#endif