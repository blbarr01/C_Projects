#include <stdio.h>
#include <stdlib.h>

// declare structure to store block information (id, starting address, ending address, link to next block)
struct process_block
{
    /* data */
    int id,
        start,
        end,
        size;
    struct process_block *next;
};

typedef struct process_block process_block;

// declare linked list to connect allocation block
process_block *PROCESS_CHAIN;
// declare global variables
int PHYSICAL_MEMORY,
    REMAINING_MEMORY,
    ALGO_TYPE;

/********************************************************************/
void EnterParameters()
{
    // declare local variables (if any)
    // prompt for size of physical memory and choice of hole-fitting algorithm (0=first-fit, 1=best-fit), initialize remaining memory
    printf("Enter the size of Physical Memory: ");
    scanf("%d", &PHYSICAL_MEMORY);
    REMAINING_MEMORY = PHYSICAL_MEMORY;

    // a little safety to make sure user selected 1 or 0;
    do
    {
        printf("choose hole-fitting algorithm (0=first-fit, 1=best-fit): ");
        scanf("%d", &ALGO_TYPE);
        // you got triped on the logic for this one
    } while ((ALGO_TYPE != 1) && (ALGO_TYPE != 0));

    //printf("successfuly selected algo \n");
    // initilize linked list with "dummy" block of size 0
    PROCESS_CHAIN = (process_block*)malloc(sizeof(process_block));
    PROCESS_CHAIN->size= 0; 
    PROCESS_CHAIN->start= 0; 
    PROCESS_CHAIN->end= 0; 
    PROCESS_CHAIN->next= NULL; 
    printf("\n\n");

}

/********************************************************************/
void PrintAllocationTable()
{
    // declare local variables
    if (PROCESS_CHAIN->next == NULL)
    {
        printf("no processeses allocated yet \n\n");
        return;
    }

    process_block *curr = PROCESS_CHAIN->next;

    // print table containing block id, starting address, ending address
    printf("id\tstart\tend\tsize \n");
    printf("---------------------------------\n");
    while (curr != NULL)
    {
        printf("%d\t", curr->id);
        printf("%d\t", curr->start);
        printf("%d\t", curr->end);
        printf("%d\n", curr->size);
        curr = curr->next;
    }
    printf("\n\n");
    return;
}

/********************************************************************/
void AllocateMemoryBlock()
{

    // declare local variables
    int temp_id,
        temp_size,
        hole_start,
        hole_end,
        curr_hole,
        best_hole;
    process_block *best_start, *best_end;
    // initialize best hole so far to size of physical memory
    best_hole = REMAINING_MEMORY;
    printf("remaining memory %d \n", REMAINING_MEMORY);

    // prompt for block id & block size
    printf("Enter Block Id: ");
    scanf("%d", &temp_id);
    printf("Enter Block size: ");
    scanf("%d", &temp_size);

    // check if size of block is larger than remaining unallocated space, if so, print message and return
    if (temp_size > REMAINING_MEMORY)
    {
        printf("\nnot enough memory available; allocation cancelled; returning to main \n\n");
        return;
    }

    // allocate space for new block and set id
    process_block *new_block = (process_block *)malloc(sizeof(process_block));
    new_block->id = temp_id;
    new_block->size = temp_size;
    //printf("after process creation and id assignment \n");
    // if only "dummy" block exists, insert block at end of linked list, set fields, return
    if (PROCESS_CHAIN->next == NULL)
    {
        new_block->start = PROCESS_CHAIN->end;
        new_block->end = new_block->start + new_block->size;
        new_block->next = NULL;
        PROCESS_CHAIN->next = new_block;
        REMAINING_MEMORY -= temp_size;
        return;
    }
    // else traverse list until either appropriate hole is found or the end of the list is reached
    else
    {
        process_block *curr = PROCESS_CHAIN->next;
        // printf("address of curr: %p \n", curr);
        // printf("address of process_Chain: %p \n", PROCESS_CHAIN);
        while (curr != NULL)
        {
            // if id already exists, reject request and return
            if (curr->id == new_block->id)
            {
                printf("current id: %d \n", curr->id);
                printf("attempted new block id: %d \n", new_block->id);
                printf("id already exists; allocation canceled; returning to main \n");
                return;
            }

            hole_start = curr->end; 
            if(curr->next != NULL){
                hole_end = curr->next->start;
            }else{
                hole_end = PHYSICAL_MEMORY;
            }

            curr_hole = hole_end - hole_start;
            printf( "hole start %d \n", hole_start);
            printf( "hole end %d \n", hole_end);

            // if hole is large enough for block
            if ( temp_size <= (hole_end - hole_start))
            {
                // if first-fit algorithm
                if (ALGO_TYPE == 0)
                {
                    new_block->start = hole_start; // set start & end fields of new block & add block into linked list
                    new_block->end = hole_start + temp_size; // reduce remaining available memory and return
                    new_block->next = curr->next;
                    curr->next = new_block; 
                    REMAINING_MEMORY -= temp_size;
                    return; 
                }
                // else--best-fit algorithm
                else
                {
                    // if hole is smaller than best so far
                    if (curr_hole <= best_hole)
                    {
                    // set values of best start & best end & best hole size so far
                    best_hole = curr_hole;
                    best_start = curr;
                    if (curr->next != NULL); 
                    {
                        best_end = curr->next;
                    }
                    
                    // update best block & advance next block
                    }
                    
                }
            }

            curr = curr->next;
        } // end while loop
    }

    // set start & end fields of new block & add block into linked list
    new_block->start = best_start->end;
    new_block->end = new_block->start + temp_size;
    new_block->next = best_end;
    best_start->next = new_block;
    // reduce remaining available memory and return
    REMAINING_MEMORY -= temp_size;
}

/********************************************************************/
void DeallocateMemoryBlock()
{

    // declare local variables
    int search_id;
    process_block *prev = PROCESS_CHAIN->next;
    process_block *curr = PROCESS_CHAIN->next;
    // prompt for block id
    printf("which Block would you like to destroy: ");
    scanf("%d", &search_id);
    // until end of linked list is reached or block id is found
    // traverse list
    while (curr != NULL)
    {
        if (curr->id == search_id)
        {
            prev->next = curr->next;
            REMAINING_MEMORY += (curr->end - curr->start);
            free(curr);
            printf("node %d successfully removed \n", search_id);
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    // if end of linked list reached, print block id not found
    printf("the process was not found; returning to main \n\n ");
    // else remove block and deallocate memory
    return;
}

/********************************************************************/
void Defragment()
{
    printf("Defrag called \n");

    // declare local variables
    process_block *curr = PROCESS_CHAIN->next;
    int curr_hole;


    // until end of list is reached
    while (curr->next != NULL)
    {   
        curr_hole = curr->next->start - curr->end; 
        if(curr_hole > 0 ){
            curr->next->start -= curr_hole;
            curr->next->end -= curr_hole;
        }
        
        curr = curr->next;
    }

    return;
}

/********************************************************************/
// what is option 5 used for ? why are we passing it a node ?
void Option5(process_block *node)
{
    // if node is NULL, return
        if(node == NULL){
            return;
        }
    // else
    // recursively call procedure on node->link
     Option5(node->next);   
    // deallocate memory from node
    free(node); 
    return;
}

void PrintMainPrompt()
{
    printf("Memory Allocation\n");
    printf("-----------------------\n");
    printf("1. Enter Parameters \n");
    printf("2. Allocate Memory for Block \n");
    printf("3. Deallocate memory for Block\n");
    printf("4. Defrag memory\n");
    printf("5. Quit Program\n\n");
}

/***************************************************************/
int main()
{
    /* declare local vars */
    int selector;
    /* while user has not chosen to quit */
    while (1)
    {
        /* print menu of options */
        PrintMainPrompt();
        /* prompt for menu selection */
        printf("Enter selection: ");
        scanf("%d", &selector);
        /* call appropriate procedure based on choice--use switch statement or series of if, else if, else statements */
        switch (selector)
        {
        case 1:
            /* code */
            EnterParameters();
            break;
        case 2:
            AllocateMemoryBlock();
            PrintAllocationTable();
            break;
        case 3:
            DeallocateMemoryBlock();
            PrintAllocationTable();
            break;
        case 4:
            Defragment();
            PrintAllocationTable();
            break;
        case 5:
            printf("Quiting . . .\n");
            Option5(PROCESS_CHAIN);
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("input not understood \n\n");
            break;
        }
    }

    return 1; /* indicates success */
} /* end of procedure */