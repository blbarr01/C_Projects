/* 
* Brian Barr
* Professor 
*
* this program is intended to simulate the Process Control Block and process creation
* code has comments throughout
* any commented-out print statements were used for testing purposes  
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// define structs and globals
// for brevity parent and child refer to respective addresses

/* isParent field of the struct is supposed to be a utility to
help with the print child function */

struct Process
{
    /* data */
    int pid;
    int parentsId;
    struct Process *parent;
    struct Process *children;
    bool isParent;
};

// process control board array pointer
struct Process *PCB;
int MAX_PROCESS_COUNT;

/*-----------------------*/
// function prototypes

// option 1
void CreateProcessBlock();

// option 2
void CreateChildren();

// option 3
void DestroyChildren();

// recursive destruction call
void RecursiveDestroy(struct Process *destroyer);

void PrintHeirarchy();

void PrintMainPrompt();

/*-----------------------*/
// main driver
int main()
{
    int selector = 0;
    do
    {
        PrintMainPrompt();
        scanf("%d", &selector);
        switch (selector)
        {
        case 1:
            CreateProcessBlock();
            break;
        case 2:
            CreateChildren();
            break;
        case 3:
            DestroyChildren();
            break;
        case 4:
            free(PCB);
            break;
        default:
            printf("entry not understood");
            break;
        }
    } while (selector != 4);
    printf("goodbye! \n");
    return 1;
}

/*-----------------------*/
// function definitions

void CreateChildren()
{
    // create locals
    int processIndex;
    int nextFreeIndex;
    struct Process *current;

    // ask for parent process
    printf(" enter parent process index: ");
    scanf("%d", &processIndex);

    // set the toggle the parent so it is now a process
    (PCB + processIndex)->isParent = true;

    // find next free spot on PCB
    for (int i = 0; i < MAX_PROCESS_COUNT; i++)
    {
        // if the process block in question has no parent
        // and is not the parent itself
        if ((PCB + i)->parentsId == -1 && (PCB + i)->pid != processIndex)
        {
            nextFreeIndex = i;
            break;
        }
    }

    // set the parent id of the new process
    (PCB + nextFreeIndex)->parentsId = (PCB + processIndex)->pid;


    // link the new child to the parent; go down the list
    current = (PCB + processIndex);
    while (current->children != NULL)
    {
        current = current->children;
    }
    current->children = (PCB + nextFreeIndex);

    PrintHeirarchy();
    //printf("create children function exit \n");
}
void CreateProcessBlock()
{
    // prompt for process count
    printf("enter maximum number of processes: ");
    scanf("%d", &MAX_PROCESS_COUNT);
    // printf("the number of processes inside function call is %d \n", MAX_PROCESS_COUNT);

    // allocate memory
    PCB = (struct Process *)malloc(sizeof(struct Process) * MAX_PROCESS_COUNT);

    // define pcb[0]
    PCB->pid = 0;
    PCB->parent = NULL;

    PCB->parentsId = 0;
    PCB->isParent = true;

    // instatiate all other pcb parents to null (-1)
    for (size_t i = 1; i < MAX_PROCESS_COUNT; i++)
    {
        (PCB + i)->pid = i;
        (PCB + i)->parentsId = -1;
        (PCB + i)->parent = NULL;
        (PCB + i)->children = NULL;
        (PCB + i)->isParent = false;
    }
}

void PrintHeirarchy()
{
    struct Process *ptr;
    for (int i = 0; i < MAX_PROCESS_COUNT; i++)
    {
        ptr = (PCB+i);
        if (ptr ->isParent == true)
        {
            printf("PCB[%d] is the parent of ", ptr->pid);
            // loop through all  the children of the 
            while (ptr->children != NULL)
            {
                ptr = ptr->children;

                if (ptr->parentsId == i)
                {
                printf("PCB[%d] ", ptr->pid);
                }
                
            }
            printf("\n");
        }
    }
}
void PrintMainPrompt()
{
    printf("\n");
    printf("process creation and destruction \n");
    printf("---------------------------------- \n");
    printf("1.) create new process \n");
    printf("2.) create a new child process \n");
    printf("3.) destroy all descendants of a process \n");
    printf("4.) quit program and free memory \n\n");
    printf("enter selection: ");
}

void DestroyChildren()
{
    int pIndex;
    // prompt for parent PCB index
    printf("Enter the index of the process whose descendants are to be destroyed:");
    scanf("%d", &pIndex);
    RecursiveDestroy((PCB + pIndex));
    PrintHeirarchy();
};

void RecursiveDestroy(struct Process *destroyer)
{
    // check if end of linked list
    if (destroyer->children == NULL)
    {
        return;
    }
    // call self
    RecursiveDestroy(destroyer->children);

    // reset the values
    destroyer->parentsId = -1;
    destroyer->children = NULL;
    destroyer->parent = NULL;
};