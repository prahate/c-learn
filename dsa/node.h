#include <stdio.h>

#ifndef _NODE_H
#define _NODE_H

typedef struct node {
    int data;
    struct node *next;
} Node_t;

Node_t* new_node(int data);
void delete_node(Node_t *n);

#endif
