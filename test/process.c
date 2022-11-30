#include <stdbool.h>

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