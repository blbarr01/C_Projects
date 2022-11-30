#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *routine(){
    printf("Test from threads \n");
    sleep(3);
    printf("end threads \n");

}

int main(int argc, char* argv[]){
    pthread_t t1, t2; 
    // pass the pointer to the thread, 
    // attributes : customization options
    // pointer to function 
    // arguments to pass to the routine
    pthread_create(&t1, NULL, &routine, NULL);

    // example of how to error check function calls 
    //pthread returns an int: 0 or error no
    if(pthread_create(&t2, NULL, &routine, NULL) != 0){
        return 1;
    }   

    if (pthread_join(t1,NULL) != 0){
        return 2;
    }
    if (pthread_join(t2,NULL) != 0){
        return 3; 
    }

    
    return 0; 
}