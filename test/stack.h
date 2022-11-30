#include "process.h"
#include <stdbool.h>

#ifndef STACK_H
#define STACK_H
typedef struct 
{
    int top, capacity;
    process *activeProcess; 
} stack;

stack *createStack(int capacity);
bool isEmpty(stack* s);
bool isFull(stack *s);
void push(stack *s, process *p);
void pop(stack *s);

#endif