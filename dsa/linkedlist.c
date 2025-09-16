#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "linkedlist.h"

linkedlist_t list;

void append(int data)
{
    Node_t *new = new_node(data);
    if (new)
    {
        //case 1: list is empty
        if (list.head == NULL || list.tail == NULL) {
            list.head = new;
            list.tail = new;
        }
        //case 2: list not empty
        else {
            list.tail->next = new;
            list.tail = new;
        }
    }
}

void prepend(int data)
{
    Node_t *new = new_node(data);
    if (new) {
        //case 1: list is empty
        if (list.head == NULL || list.tail == NULL)
        {
            list.head = new;
            list.tail = new;
        }
        else {
        //case 2: list is not empty
            new->next = list.head;
            list.head = new;
        }
    }
}

void removeFirst()
{
    // check if list is empty
    if (list.head == NULL || list.tail == NULL)
        printf("List is empty\n");
    // case 1: only one node
    if (list.head == list.tail) {
        delete_node(list.head);
        list.head = NULL;
        list.tail = NULL;
    } else {
        // case 2: more than 1 node
        Node_t *temp = list.head; // point temp to head
        list.head = temp->next; // move head to next node using temp
        delete_node(temp); // delete temp
    }
}

void removeLast()
{
    // check if list is empty
    if (list.head == NULL || list.tail == NULL)
        printf("List is empty\n");
    // case 1: only 1 node in list
    if (list.head == list.tail) {
        delete_node(list.head);
        list.tail = NULL;
    } else {
        // case 2: more than 1 node
        Node_t *temp = list.head;
        while(temp->next != list.tail) { // traverse till second last node
            temp = temp->next;
        }

        list.tail = temp;   // update tail
        list.tail->next = NULL;
        delete_node(temp->next); // delete last node

    }
}

void removeAt(int pos)
{
    // check if pos is valid
    int len = getLength();
    if (pos < 1 && pos > (len+1)) {
        printf("Invalid node position to remove\n");
        return;
    }

    if (pos == 1) { // if pos ==1 
        removeFirst();
    } else if (pos == len) { // if pos == last
        removeLast();
    } else { // any other position
        Node_t *prev;
        Node_t *curr = list.head;
        int count =1;
        while( count != pos) {
            prev = curr;
            curr = curr->next;
            count++;
        }

        prev->next = curr->next;
        delete_node(curr);
    }
}

int getLength()
{
    Node_t* temp = list.head;
    int length = 0;

    while(temp != NULL) {
        temp = temp->next;
        length++;
    }
    return length;
}

void printList()
{
    if (list.head== NULL || list.tail==NULL)
        printf("List is empty");
    else {
        Node_t *temp = list.head;
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}
