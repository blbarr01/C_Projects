#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

// goal is to get the value from roll_dice into main
// trick is within the 2nd arg't of join_thread()


//cannot just return a simple value 
// vanishes when poped off stack
void* roll_dice(){
    int value = (rand() % 6) + 1; 
// must allocate memory on the heap 
    int *result =  malloc(sizeof(int)); 
    *result = value; 

    // to show we are accessing the same region of memory
    printf("address of function result: %p \n", result);
    //cast to void pointer 
    return(void *) result;
}

int main(int argc, char* argv[])
{
pthread_t th; 
int **result;

    if(pthread_create(&th,NULL,&roll_dice,NULL) != 0){
        return 1;
    }
    // key is the pthread_join 2nd arg't
    // takes a pointer to pointer 
    if(pthread_join(th, (void **)result) != 0){
        return 2;
    }

    printf("result: %d\n", **result);
    // to show we are accessing the same region of memory
    printf(" adress of main result: %p\n", *result);
return 0;
}


// if we are accessing the same location in memory then we are working with consistent data !! 