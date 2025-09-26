#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct sNode {
    int value;
    struct sNode *next;
    struct sNode *prev;
} node_t;

typedef struct sdoubly {
    node_t *head;
    node_t *tail;
    int size;
} dlist_t;

dlist_t* dlist_init()
{
    dlist_t *dl = (dlist_t *)malloc(sizeof(dlist_t));
    if (dl) {
        dl->head = NULL;
        dl->tail = NULL;
        dl->size = 0;
    }
    return dl;
}

void dlist_free(dlist_t *dl)
{
    if (dl) {
        if (dl->head)
            free(dl->head);
        if (dl->tail)
            free(dl->tail);
        free(dl);
    }
}

node_t * create_node(int data)
{
    node_t *new =NULL;
    new = (node_t *)malloc(sizeof(node_t));
    if (new) {
        new->value =data;
        new->next = NULL;
        new->prev = NULL;
    }
    return new;
}

void delete_node(node_t *n)
{
    if (n)
        free(n);
}

int getSize(dlist_t *dl)
{
    return dl->size;
}

void append(dlist_t *dl, int data)
{
    node_t *n = create_node(data);
    // case 1: list is empty
    if (dl->head == NULL && dl->size == 0) {
        dl->head = n;
        dl->tail = n;
    }
    // case 2: list is not empty
    else {
        dl->tail->next = n;
        n->prev = dl->tail;
        dl->tail = n;
    }
    dl->size++;
}

void prepend(dlist_t *dl, int data)
{
    node_t *n = create_node(data);
    // case 1: list is empty
    if (dl->head == NULL && dl->size == 0) {
        dl->head = n;
        dl->tail = n;
    }
    // case 2: list is not empty
    else {
        dl->head->prev = n;
        n->next = dl->head;
        dl->head = n;
    }
    dl->size++;
}

void insertAt(dlist_t *dl, int data, int pos)
{
    if (pos > dl->size+ 1 || pos < 1)
        return;

    if (pos ==  1)
        prepend(dl, data);
    else if (pos == dl->size + 1)
        append(dl, data);
    else {
        int count =1;
        node_t *temp = dl->head;
        node_t *n = create_node(data);
        while (count != pos -1) {
            temp = temp->next;
            count++;
        }
        n->prev = temp;
        n->next = temp->next;
        temp->next = n;
    }
    dl->size++;
}

void printreverse(dlist_t *dl)
{
    node_t *temp = dl->tail;
    while(temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->prev;
    }
    printf("\n");
}

void printlist(dlist_t *dl)
{
    node_t *temp;
    temp = dl->head;
    while( temp != NULL)
    {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}


int main()
{
    dlist_t *dlist = dlist_init();

    append(dlist, 23);
    append(dlist, 19);
    append(dlist, 11);
    append(dlist, 44);
    printf("After Append: ");
    printlist(dlist);
    prepend(dlist, 12);
    prepend(dlist, 38);
    printf("After prepend: ");
    printlist(dlist);
    insertAt(dlist, 98, 7);
    printf("After insertAt: ");
    printlist(dlist);
    insertAt(dlist, 67, 1);
    printf("After insertAt: ");
    printlist(dlist);
    printf("printing reverse: ");
    printreverse(dlist);
    //dlist_free(dlist);

    return 0;
}
