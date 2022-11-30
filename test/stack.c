#include "process.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    /* data */
    int top, capacity;
    process *activeProcess;

} stack;

stack *createStack(int capacity)
{
   stack *s  =(stack*)malloc(sizeof(stack));
    s->top = -1;
    s->activeProcess = (process*)malloc(sizeof(process) * capacity);
    return s;  
}
bool isEmpty(stack *s)
{
   if(s->top == -1 ){
       return true;
   }
   return false;
}

bool isFull(stack *s){
    if( s->top == (s->capacity)-1){
        return true;
    }
    return false;
}
void push(stack *s, process *p)
{
    s->top+=1;
    s->activeProcess = p; 
}
void pop(stack *s)
{
}
