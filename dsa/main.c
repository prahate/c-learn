#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "node.h"
#include "linkedlist.h"
#include "stack.h"

int main()
{
// for testing linked list
#if 0
    append(5);
    append(4);
    append(8);
    append(7);
    //printList();
    prepend(3);
    prepend(9);
    //printList();
    //removeFirst();
    append(34);
    append(77);
    printList();
    //removeLast();
    //printList();
    removeAt(3);
    removeAt(1);
    printList();
#endif

// for testing stack
    push(3);
    push(2);
    push(8);
    push(9);
    pop();
    pop();
    pop();
    push(7);
    push(1);
    pop();
    pop();
    return 0;
}
