#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>



int main(int argc, char *argv[])
{
    // fork forks the execution; 
    //a child process spawns and executes simultaneously  
    // id 0 is assigned to child process
    // we can use the id to perform things conditionally 
    // split the work between parent and child processes
    // each process has it's own data 
    int id = fork();


    //each fork call generates 2^n process where n is number of times fork is called

    // a way to split a child from a main process without 
    // building an additional child process
 /*    if (id != 0){
        fork();
        printf("hello world from id[%d] \n", id);
    } */



    int n; 
    if(id == 0 ){
        n=1;
    }else
    {
        n = 6;
    }
// if we are in the main process wait for the child to terminate
    if(id != 0){
        wait(NULL);
    }
    for (int i = n; i < n+5; i++)
    {
        printf("%d ", i);
        fflush(stdout);
    }
    
    if(id != 0){
        printf("\n");
    }

    
    
    return 0;
}