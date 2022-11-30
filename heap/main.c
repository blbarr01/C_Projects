#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<time.h>



void swap(int *a, int *b){
    printf( "swap between: %d and %d \n",*a,*b);
    int temp = *b; 
    *b = *a; 
    *a = *b; 
}

void heapify(int *arr, int n, int i){
    int p = i; // parent node // really should be thought of as parent 
    int l = 2*i +1; 
    int r = 2*i+2;
    printf("address of arr in heapify %p \n", arr);
    // if we haven't gone out of bounds and 
    // the left child is larger than the root
    if( l < n && arr[l] > arr[p]){
        p = l;
    } 
    // if the right child is less
    if( r < n && arr[r] > arr[p]){
        p = r;
    } 

    if(p != i){
        swap(&arr[i], &arr[p]);
    }

    heapify(arr,n,p);
}

void heapsort(int *arr, int n){


    printf("address of arr in heap sort %p \n", arr);

    //start from the mid point of the array and work backwards
    for (int  i = n /2 -1; i >= 0; i--)
    {
        heapify(arr,n,i);
    }

    //extract elements from the back of the heap
    for (int i = n-1; i > 0; i--)
    {
        //move current root to end 
        swap(arr, (arr+i));
        //call max heapify on the reduced heap 
        heapify(arr, i, 0);
    }
    
    
}

void printArray(int *arr, int n){
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int *createArray(int n){
    time_t t; 
    srand((unsigned)time(&t));
    int *arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        arr[i] = (rand() % 25) + 1;
    }
    
    return arr;
}

int main(int argc, char* argv[])
{
int n = 10;
int *arr;
arr = createArray(n);
printf("address of arr in main%p \n", arr);
printArray(arr, n);
heapsort(arr,n);
printArray(arr, n);

return 0;
}