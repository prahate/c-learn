#ifndef __QUEUE_H
#define __QUEUE_H

#include "node.h"

struct queue {
    Node_t *head;
    Node_t *tail;
};

typedef struct queue queue_t;

queue_t* init_queue();
void enqueue(queue_t *q, int data);
int dequeue(queue_t *q);

#endif
