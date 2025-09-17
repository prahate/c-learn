#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "node.h"

typedef struct queue {
    Node_t *head;
    Node_t *tail;
} queue_t;

queue_t q;

void enqueue(int data)
{
    Node_t *new = new_node(data);
    printf("Enqueued %d\n", data);
    // case 1: queue is empty
    if (q.head == NULL) {
        q.head = new;
        q.tail = new;
    } else {
    // case 2: queue is not empty
        q.tail->next = new;
        q.tail = new;
    }
}

int dequeue()
{
    int ret=0;
    // case 1: queue is empty
    if (q.head == NULL) {
        printf("Queue is empty\n");
        return 0;
    }
    // case 2: queue has one element
    else if (q.head == q.tail) {
        ret = q.head->data;
        delete_node(q.head);
        q.head = NULL;
        q.tail = NULL;
    } else {
    // case 3: queue has 2 or more
        Node_t *temp = q.head;
        ret = q.head->data;

        temp = q.head->next;
        delete_node(q.head);
        q.head = temp;
    }
    printf("Dequeued %d\n", ret);
    return ret;
}



int main()
{
    enqueue(3);
    enqueue(4);
    enqueue(7);
    enqueue(2);
    enqueue(8);
    enqueue(1);
    enqueue(9);
    dequeue();
    dequeue();
    dequeue();
    dequeue();
    dequeue();
    dequeue();
    dequeue();
    dequeue();
    return 0;
}
