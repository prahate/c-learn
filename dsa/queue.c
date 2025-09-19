#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "queue.h"
#include "node.h"

queue_t* init_queue()
{
    queue_t *que = (queue_t *)malloc(sizeof(queue_t));
    return que;
}

void enqueue(queue_t *q, int data)
{
    Node_t *new = new_node(data);
    printf("Enqueued %d\n", data);
    // case 1: queue is empty
    if (q->head == NULL) {
        q->head = new;
        q->tail = new;
    } else {
    // case 2: queue is not empty
        q->tail->next = new;
        q->tail = new;
    }
}

int dequeue(queue_t *q)
{
    int ret=0;
    // case 1: queue is empty
    if (q->head == NULL) {
        printf("Queue is empty\n");
        return 0;
    }
    // case 2: queue has one element
    else if (q->head == q->tail) {
        ret = q->head->data;
        delete_node(q->head);
        q->head = NULL;
        q->tail = NULL;
    } else {
    // case 3: queue has 2 or more
        Node_t *temp = q->head;
        ret = q->head->data;

        temp = q->head->next;
        delete_node(q->head);
        q->head = temp;
    }
    printf("Dequeued %d\n", ret);
    return ret;
}



int main()
{
    queue_t *q = init_queue();
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 7);
    enqueue(q, 2);
    enqueue(q, 8);
    enqueue(q, 1);
    enqueue(q, 9);
    dequeue(q);
    dequeue(q);
    dequeue(q);
    dequeue(q);
    dequeue(q);
    dequeue(q);
    dequeue(q);
    dequeue(q);
    return 0;
}
