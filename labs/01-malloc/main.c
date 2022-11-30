#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,n;
    float *element;
printf("\n\n Pointer : Find the largest element using Dynamic Memory Allocation :\n"); 
printf("-------------------------------------------------------------------------\n"); 
    printf(" Input total number of elements(1 to 100): ");
    scanf("%d",&n);
    element= malloc(n * sizeof(float));// Memory is allocated for 'n' elements 
    if(element==NULL)
    {
        printf(" No memory is allocated.");
        exit(0);
    }
    printf("\n"); // line feed
      // for i=0 to n-1, increment i
      for(i = 0; i <= n-1; i++){
       //print "Number i:"
       printf("number %d: ", i);
       scanf("%f",element+i);
    }
      // for i=0 to n-1, increment i
      for(i = 0; i <= n-1; i++){
          printf("number is: %f ", *element+i);
      }
    {
      // find max using pointer *element 
    }
    printf(" The Largest element is :  %.2f \n\n",*element);
    return 0;
}