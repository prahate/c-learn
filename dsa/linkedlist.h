#include <stdio.h>
#include "node.h"

#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H


typedef struct linkedlist {
    Node_t *head;
    Node_t *tail;
} linkedlist_t;

void append(int data);
void prepend(int data);
void removeFirst();
void removeLast();
void removeAt(int pos);
void deleteList();
void printList();
int getLength();

#endif
