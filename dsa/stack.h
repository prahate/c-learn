#include <stdio.h>
#include "node.h"

typedef struct stack {
    Node_t* tos;
} stack_t;

void push(int data);
int pop();
