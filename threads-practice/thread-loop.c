#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>


void* routine(){

    
}


//do not call pthread_create and pthread_join within the same for loop
// it defeats the purpose of creating threads 
int main(int argc, char* argv[])
{
    int n = 4;
    pthread_t th[n];
    for (int  i = 0; i < n; i++)
    {
        if(pthread_create( th+i, NULL, &routine, NULL ) != 0){
            perror("failed to create thread \n");
            return 1;
        }
        printf("thread %d starting \n", i);
    }

    for (int i = 0; i < n; i++)
    {
        printf("thread %d terminating \n", i);
        /* code */
        if (pthread_join(th[i],NULL) != 0)
        {
            return 5;
        }
    }
    
     

return 0;
}