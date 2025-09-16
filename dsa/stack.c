#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "node.h"
#include "linkedlist.h"
#include "stack.h"

stack_t st;

bool isEmpty() {
    if (st.tos == NULL)
        return true;
    return false;
}

void push(int data)
{
    Node_t* new = new_node(data);
    printf("Pushing onto stack %d\n", data);
    // check is stack is empty
    if (st.tos == NULL) {
        st.tos = new;
        new->next = NULL;
    } else {
    // push data & update tos
        new->next = st.tos;
        st.tos = new;
    }
}

int pop()
{
    int ret=0;
    if (isEmpty()) {
        printf("Stack is empty\n");
        return 0;
    }
    // check if stack is empty
    if (st.tos->next == NULL) {
        ret = st.tos->data;
        printf("Popped %d\n", ret);
        delete_node(st.tos);
        st.tos = NULL;
    } else {
        Node_t *temp = st.tos;
        st.tos = temp->next;
        ret = temp->data;
        printf("Popped %d\n", ret);
        delete_node(temp);
    // pop data print it and update tos
    }
    return ret;
}
