#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "node.h"

Node_t* new_node(int data)
{
    Node_t *n = (Node_t *)malloc(sizeof(Node_t));
    if (n) {
        n->data = data;
        n->next = NULL;
        return n;
    }
    return NULL;
}

void delete_node(Node_t *n)
{
    if(!n)
        free(n);
    n = NULL;
}
